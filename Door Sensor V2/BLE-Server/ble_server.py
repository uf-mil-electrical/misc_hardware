import asyncio
from bleak import BleakScanner, BleakClient
from datetime import datetime
import logging

# Configure logging
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s'
)
logger = logging.getLogger(__name__)

# Constants - Replace with your device's MAC address
DEVICE_MAC_ADDRESS = "2C:CF:67:C9:C0:A3"  # Replace with your Pico's MAC address
ENVIRONMENTAL_SENSING_SERVICE_UUID = "0000181a-0000-1000-8000-00805f9b34fb"
TEMPERATURE_CHARACTERISTIC_UUID = "00002a6e-0000-1000-8000-00805f9b34fb"

# Global variables
door_state_history = []
connected_client = None

def door_state_notification_handler(sender, data):
    """Handle incoming notifications from the door sensor"""
    value = int.from_bytes(data, byteorder='little')
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    
    # Store in history
    door_state_history.append((timestamp, value))
    if len(door_state_history) > 100:  # Keep last 100 entries
        door_state_history.pop(0)
        
    # Print status
    state = "OPEN" if value == 1 else "CLOSED"
    logger.info(f"Door state changed: {state}")
    #print(f"Door is now {state}")

async def connect_to_device(address):
    """Connect to the device by MAC address and set up notifications"""
    global connected_client
    
    try:
        client = BleakClient(address)
        await client.connect()
        logger.info(f"Connected to device at {address}")
        
        # Subscribe to notifications
        await client.start_notify(TEMPERATURE_CHARACTERISTIC_UUID, door_state_notification_handler)
        logger.info("Subscribed to door state notifications")
        
        # Read current value
        value = await client.read_gatt_char(TEMPERATURE_CHARACTERISTIC_UUID)
        state = "OPEN" if int.from_bytes(value, byteorder='little') == 1 else "CLOSED"
        print(f"Initial door state: {state}")
        
        connected_client = client
        return client
    except Exception as e:
        logger.error(f"Connection failed: {str(e)}")
        return None

async def main():
    """Main function to run the BLE client"""
    print(f"Starting BLE client for device at {DEVICE_MAC_ADDRESS}")
    print("Press Ctrl+C to exit")
    
    try:
        while True:
            logger.info(f"Attempting to connect to {DEVICE_MAC_ADDRESS}...")
            client = await connect_to_device(DEVICE_MAC_ADDRESS)
            
            if client:
                # Keep connection alive until disconnected
                try:
                    while client.is_connected:
                        await asyncio.sleep(1)
                except Exception as e:
                    logger.error(f"Connection error: {str(e)}")
                finally:
                    logger.info("Disconnected from device")
                    try:
                        await client.disconnect()
                    except:
                        pass
                    connected_client = None
            
            # Wait before trying to reconnect
            await asyncio.sleep(5)
    except asyncio.CancelledError:
        pass
    finally:
        # Clean up any existing connection
        if connected_client and connected_client.is_connected:
            await connected_client.disconnect()

if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\nExiting application")