#!/usr/bin/env python3

"""Code meant to connect to servo tube and do test with"""

import struct
import serial


MAX_FWR_VAL = 2200  # us
MAX_REV_VAL = 800   # us
STOPVAL = 1500      #us

MAX_SPEED = 1
MIN_SPEED = -1

MAX_ANGLE = 90
MIN_ANGLE = -90

# ---------------------------------------------------------------------------- #
#                                   FUNCTIONS                                  #
# ---------------------------------------------------------------------------- #


def fletcher16(data: bytes):
    """Compute the Fletcher-16 checksum of a byte sequence."""
    sum1 = 0
    sum2 = 0
    for index, byte in enumerate(data):
        sum1 = (sum1 + byte) % 255
        sum2 = (sum2 + sum1) % 255

    return (sum2 << 8) | sum1


def make_msg(class_id: int, subclass_id: int, payload: bytes = b'') -> bytes:
    """
    Create a message packet to send via usb.

    Inputs:
    - class_id (int): the device that it is being sent to (check uf-mil.github.io page or USB-TO-CAN.H)
    - subclass_id (int): what operation is the device doing (check the github.io or .h file)
    - playload (byte): message being sent (again check the github.io or .h file)

    Returns
    - bytes: full message byte array
    """
    sync = b'\x37\x01'
    cid_byte = struct.pack('<B', class_id)
    scid_byte = struct.pack('<B', subclass_id)
    length = struct.pack('<H', len(payload))

    # get the current msg to find checksum
    data1 = cid_byte + scid_byte + length + payload

    checksum = fletcher16(data1)
    checksum_bytes = struct.pack('<H', checksum)

    data = sync + data1 + checksum_bytes

    return data


def msg_to_string(msg):
    """Convert a message to a string to print."""
    return ' '.join(f'{byte:02x}' for byte in msg)


def map(x: int, in_min:int, in_max: int, out_min: int, out_max:int ) -> int:
    return int((x-in_min)*(out_max-out_min)/ (in_max-in_min) + out_min)


def get_servo_duty_by_speed(speed: float) -> int:
    speed = max(MIN_SPEED, min(MAX_SPEED, speed))
    
    if speed == 0:
        return STOPVAL
    
    speed_int = int(speed*100)

    return map(speed_int, MIN_SPEED * 100, MAX_SPEED * 100, MAX_REV_VAL, MAX_FWR_VAL)

def get_servo_by_angle(angle: int) -> int:
    angle = max(MIN_ANGLE, min(MAX_ANGLE, angle))

    if angle == 0:
        return STOPVAL
    
    return map(angle, MIN_ANGLE, MAX_ANGLE, MAX_REV_VAL, MAX_FWR_VAL)


def parse_msg(data: bytes, payload_format: str = None):
    sync      = data[0:2]
    msg_class = data[2:3]
    subclass  = data[3:4]

    length_b  = data[4:6]
    length = struct.unpack_from('<H', length_b)[0] 

    payload_start = 6
    payload_end = payload_start + length
    payload = data[payload_start:payload_end]

    payload_decoded = None
    if payload_format:
        try:
            payload_decoded = struct.unpack_from(payload_format, payload)
        except struct.error as e:
            payload_decoded = f"Error unpacking payload: {e}"

    checksum      = data[payload_end:payload_end + 2]
    
    return {
        'sync': sync.hex(),
        'class': msg_class.hex(),
        'subclass': subclass.hex(),
        'length': length,
        'payload': payload,
        'payload_decoded': payload_decoded,
        'checksum': checksum.hex()
    }

# ---------------------------------------------------------------------------- #
#                                     MAIN                                     #
# ---------------------------------------------------------------------------- #

# Connect to device
# ON WINDOWS, CHANGE THIS TO COM# , /dev/ is chad linux
# ser = serial.Serial('COM#', 115200, timeout=1)
ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)

# pre-declared variables cause I am lazy
class_id = 0x02
subclass_id = 0x02

print("Starting Servo Board test file...\n")

# main loop
while True:
    try:

        thruster_id = 1

        angle = int(input(f"Enter an angle in degrees [{MIN_ANGLE}, {MAX_ANGLE}]: "))

        while abs(angle) > MAX_ANGLE:
            angle = int(input(f"Invalid option, enter an angle in degrees [{MIN_ANGLE}, {MAX_ANGLE}]: "))

        print(f"The angle entered: {angle} degrees, so the PWM would be: {get_servo_by_angle(angle)} us")

        # right now the code expect [-1, 1], so just normalize it
        speed = angle/MAX_ANGLE

        payload = struct.pack("<Bf", thruster_id, speed)

        msg = make_msg(class_id, subclass_id, payload)

        print(f"Message send: {msg_to_string(msg)}. ")
        ser.write(msg)

        # check if ack or nak
        response = ser.read(1000)

        if (response is not None):
            print(f"Receieved the message {msg_to_string(response)}")
            print(f"Parsed msg: \n {parse_msg(response)}")
        else:
            print("No message received")

    except KeyboardInterrupt:
        print("\nKeyboard Interrupt has occured! Ending program now...")
        break
    except EOFError:
        print("\nKeyboard Interrupt has occured! Ending program now...")
        break
    except Exception as e:
        print(e)

ser.read(1000)  # read any messages that were recieved
ser.close()
