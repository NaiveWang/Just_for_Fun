import data
import conf
d=data.data(conf, True)
d.gen()
print('neat, then i\'ll bang ur memory.')
d.get_list()
for i, o in d:
    print(type(i), i.shape, o.shape)
