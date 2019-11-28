from kafka import KafkaConsumer,KafkaProducer,KafkaClient
import kafka_server_config as conf


comp_receiver = KafkaConsumer('captcha_request',bootstrap_servers=conf.server)
comp_sender = KafkaProducer(bootstrap_servers=conf.server)
for msg in comp_receiver:
    req_id = msg.value[:conf.length_of_request_id].decode()
    print('Processing id = '+req_id)
    captcha_no = value[conf.length_of_request_id:conf.length_of_request_id+length_of_captcha_typ].decode()
    # download the image and put it on the
    f=open(req_id+'.jpg','wb')
    f.write(msg.value[conf.length_of_request_id+length_of_captcha_typ:])
    f.close()
    # invoke the captcha recognize process
    # get the result
    result = os.popen('python Cracker+'captcha_no'+/server_recognize.py').read().split('$')[0]
    # send processer
    comp_sender.send(msg.value[:conf.length_of_request_id].decode(),result.encode())
    # delete the file
    os.popen('rm '+req_id+'.jpg')
