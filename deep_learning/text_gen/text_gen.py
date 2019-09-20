import numpy as np

from keras.models import Sequential, load_model, save_model
from keras.layers.core import Dense, Activation, Dropout
from keras.layers.recurrent import LSTM
from keras.layers.wrappers import TimeDistributed
# from keras.callbacks import ModelCheckpoint

import conf
import dispatcher


'''
    We assumed that the \002 is the end of a chunk, and in each line we append an \002
    to indicacte this the end of the current line.
'''
def locate(a, v):
    try:
        return a.index(v)
    except Exception as E:
        return -1

def text_gen_old(model, sslice, length, clen, i2c, idx=[]):
    # the text head initializer, random given when not given
    if len(idx) < 1:
        idx = np.random.randint(0, clen, (length))

    #print(idx)
    pd = np.zeros((1, length, clen))
    # predict loop
    pdstr=''
    #infer_point =
    # initialize the header of the predict text
    for i in range(len(idx)):
        pd[0, i, idx[i]] = 1
        ##print(idx)
    pdstr+=i2c[idx[0]]
    #print(pdstr)

    for i in range(length-sslice):
        # assign value
        # the predict session, now it's just a random gen
        #idx = np.random.randint(0, clen, (sslice))
        # the predict session, now as it should be
        #print(p, p.shape)
        #get the predicted index array
        idx = np.argmax(model.predict(pd[:, i:i+sslice, :])[0], 1)
        #print(idx)
        # apply results on the output array
        for j in range(len(idx)):
            pd[0, i+j, idx[j]] = 1
        # print(idx)
        pdstr+=i2c[idx[0]]
    #print(pdstr)
    return pdstr

def text_gen(model, sslice, length, clen, i2c, idx=[]):
    # the text head initializer, random given when not given
    if len(idx) < 1:
        idx = np.random.randint(0, clen, (2, sslice))
    stopi=c2i[conf.__STOP]
    #print('initialized index :\n', idx)
    pd = np.zeros((1, sslice, clen))
    # predict loop
    pdstr=''
    # initialize the header of the predict text
    for i in range(len(idx)):
        pd[0, i, idx[0][i]] = 1
        ##print(idx)
    pdstr+=i2c[idx[0][0]]
    # define a double buffer to enhence performance, with a pointer,
    # in this case the pointer only have two states due to 2d buffer.
    flip=1
    for l in range(length):
        # assign value
        # get the predicted index array
        idx[flip] = np.argmax(model.predict(pd)[0], 1)
        #print('modified index :\n', idx)
        #print(idx)
        # apply results on the output array
        pd.fill(0)
        for j in range(sslice):
            pd[0, j, idx[flip][j]] = 1
        if locate(idx[flip], stopi) != -1:
            # there is a stop sign in it, append and exit.
            for i in range(locate(idx[flip], stopi)+1):
                pdstr+=i2c[idx[flip[flip][i]]]
            break
        else:
            pdstr+=i2c[idx[flip][0]]
        flip=(flip+1)&1
    #print(pdstr)
    return pdstr
def text_gen_endless(model, sslice, clen, i2c):
    '''
        This generator will generate a fixed string without a fixed length, say,
        the generator has no length flag instead of having a flag to indicates
        where to stop.
    '''
    stopi=c2i[conf.__STOP]
    # print(stopi)
    idx = np.random.randint(0, clen, (2, sslice))

    #print(idx)
    pd = np.zeros((1, sslice, clen))
    # predict loop
    pdstr=''
    # initialize the header of the predict text
    for i in range(len(idx)):
        pd[0, i, idx[0][i]] = 1
        ##print(idx)
    pdstr+=i2c[idx[0][0]]
    # define a double buffer to enhence performance, with a pointer,
    # in this case the pointer only have two states due to 2d buffer.
    flip=1
    while True:
        # assign value
        # get the predicted index array
        idx[flip] = np.argmax(model.predict(pd)[0], 1)
        #print(idx)
        # apply results on the output array
        pd.fill(0)
        for j in range(sslice):
            pd[0, j, idx[flip][j]] = 1
        #print(idx)
        #print(locate(idx[flip], stopi), -1)
        if locate(idx[flip], stopi) != -1:
            # there is a stop sign in it, append and exit.
            for i in range(locate(idx[flip], stopi)+1):
                pdstr+=i2c[idx[flip[flip][i]]]
            break
        else:
            pdstr+=i2c[idx[flip][0]]
        flip=(flip+1)&1
    #print(pdstr)
    return pdstr

def get_model(clen, msave=None, wsave=None):
    model=None
    if msave is not None:
        print('loading model')
        model=load_model(msave)
        model.load_weights(msave)
        model.summary()
    else:
        print('building model')
        # build the model top down, which is called sequencial
        model = Sequential()
        # add an input LSTM layer at the top as the first layer
        model.add(LSTM(conf.DIM_HIDDEN, input_shape=(None, clen), return_sequences=True))
        for i in range(conf.NUM_LAYER-1):
            # multiple layer
            model.add(LSTM(conf.DIM_HIDDEN, return_sequences=True))
            model.add(Dropout(conf.DROPOUT))
        model.add(TimeDistributed(Dense(clen)))
        model.add(Dropout(conf.DROPOUT))
        model.add(Activation('softmax'))
        model.compile(loss='categorical_crossentropy', optimizer='rmsprop')
        model.summary()
    if wsave is not None:
        print('loading weights')
        model.load_weights(wsave)
    return model

#print('generating dataset')
# This is the old data preparation step, stale one
#clen, i2c, c2i, x, y = dispatcher.data.d_init('douban.txt', conf.SSLICE, conf.GAP)



epoc = 0
print('loading dictionary')
i2c, c2i = dispatcher.dict.load(conf.DATA_DIR+conf.DICT_I2C, conf.DATA_DIR+conf.DICT_C2I)
clen=len(i2c)
print('character set size is', clen)

print('getting model')
model=get_model(clen)#, conf.SAVE_M, conf.SAVE_W

print('initizlizing data feeder')
data_feeder = dispatcher.data(conf, True)
data_feeder.get_list()
print('training')
while True:
    for x, y in data_feeder:
        model.fit(x, y, batch_size=conf.SIZE_BATCH_TRAIN, verbose=1, epochs=conf.EPOC_BATCH)
        del(x)
        del(y)
    epoc+=1
    print('epoc :', epoc)
    save_model(model, conf.SAVE_M)
    model.save_weights(conf.SAVE_W)
    print(text_gen_old(model, conf.SSLICE, 32, clen, i2c))#, [c2i[c] for c in '你好优秀']))
    print(text_gen(model, conf.SSLICE, 32, clen, i2c))
    print(text_gen_old(model, conf.SSLICE, 32, clen, i2c))
    print(text_gen(model, conf.SSLICE, 32, clen, i2c))
