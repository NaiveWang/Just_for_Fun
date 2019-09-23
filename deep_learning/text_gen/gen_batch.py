import dispatcher
import conf
d=dispatcher.data(conf, True)
d.gen()
print('neat, then i\'ll bang ur memory.')
d.get_list()
for i, o in d:
    print(i.shape, d.shape)
