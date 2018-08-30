from kafka import KafkaConsumer,KafkaProducer,KafkaClient
server='10.18.48.14:9092'
#import random
#kc = KafkaClient('10.18.48.14:9092')
comp_receiver = KafkaConsumer('Req',bootstrap_servers=server)
comp_sender = KafkaProducer(bootstrap_servers=server)
for msg in comp_receiver:
    print(msg.value[:5].decode())
    comp_sender.send(msg.value[:5].decode(),msg.value[:5])
    content=msg.value[5:]
    f=open('newfile.jpg','wb')
    f.write(content)
    f.close()
