from tensorflow.python.client import device_lib
import tensorflow as tf
print('check devices...')

device_lib.list_local_devices()

print('running a simple random gen...')



print (tf.random.normal([10000, 10000]))
