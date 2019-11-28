'''
 This python configuration file includes:
    0. the currnet version of the configuration file
    1. which kafka server to connect
    2. the request rules
'''
version="1.0"
print("Using kafka server configuration file, Version="+version)
server='10.18.48.14:9092'
'''
The captcha recognize header structure:
    request_id(fixed length)+captcha_type(fixed length)+image(byte)
'''
length_of_request_id=5
length_of_captcha_typ=1
