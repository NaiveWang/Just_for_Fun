import paddle.fluid as fluid
import numpy as np

data_train = np.array([[1], [2], [3], [4], [5]]).astype('float32')
data_label = np.array([[2], [4], [6], [8], [10]]).astype('float32')

x = fluid.layers.data(name='x', shape=[1], dtype='float32')
y = fluid.layers.data(name='y', shape=[1], dtype='float32')

data_gen = fluid.layers.fc(input=x, size=1, act=None)

loss = fluid.layers.square_error_cost(input=data_gen, label=y)
loss_mean = fluid.layers.mean(loss)

sgd_opt = fluid.optimizer.SGD(learning_rate=0.0001)
sgd_opt.minimize(loss_mean)

learner = fluid.core.CPUPlace()
tutor = fluid.Executor(learner)

tutor.run(fluid.default_startup_program())
i=0
while True:
    outs = tutor.run(
        feed = {'x':data_train, 'y':data_label},
        fetch_list = [data_gen.name, loss_mean.name])
    if i%250==0 :
        print(outs)
    i+=1
