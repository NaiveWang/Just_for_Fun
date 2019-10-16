import serial

PORT='/dev/ttyS0'

device = serial.Serial(PORT, 115200, timeout=25)

device.flush()

# first byte is the char of GEAR
# second byte is the percentage of power(4 bit)
# followed 3 byte is speed

'''
    display mapping
    |-gear -> alplabet
    |-speed
    | |-left most : 0 -> void
    | |-others : normal
    |-power
    | |-4bit -> 2x8 pillar
    | | | <5 -> green
    | | | >=5 -> red
'''
