from tensorflow.python.client import device_lib

print('check devices...')

device_lib.list_local_devices()

print('running a simple random gen...')

print (tf.reduce_sum(tf.random_normal([10000, 10000])))
