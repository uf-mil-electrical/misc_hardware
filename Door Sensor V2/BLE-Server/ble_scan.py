import asyncio
from bleak import BleakScanner

async def discover_devices():
    print("Scanning for BLE devices...")
    devices = await BleakScanner.discover()
    
    print(f"Found {len(devices)} devices:")
    for i, device in enumerate(devices):
        print(f"{i+1}. Name: {device.name} | Address: {device.address}")
        if device.name and "MIL" in device.name:
            print(f"   This might be your device! Details: {device.details}")
        elif "Pico" in str(device):
            print(f"   This might be your device! Details: {device.details}")
    
    return devices

if __name__ == "__main__":
    asyncio.run(discover_devices())