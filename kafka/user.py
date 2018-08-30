from kafka import KafkaConsumer,KafkaProducer,KafkaClient
import random
import time
server='10.18.48.14:9092'
f = open('file.jpg','rb').read()
#kc=KafkaClient('in')
user_sender = KafkaProducer(bootstrap_servers=server)
# generate a key for this asynchronized connection
if True:

    req_key=random.randint(10000,99999).__str__()

    user_receiver = KafkaConsumer(req_key,consumer_timeout_ms=1000,bootstrap_servers=server)


    user_sender.send('Req',(req_key).encode()+f)

    for msg in user_receiver:
        print(msg.value.decode())
        break
