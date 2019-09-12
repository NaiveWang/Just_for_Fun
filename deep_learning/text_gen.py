from __future__ import print_function
import matplotlib.pyplot as plt
import numpy as np
import time
import csv

from keras.models import Sequential
from keras.layers.core import Dense, Activation, Dropout
from keras.layers.recurrent import LSTM, SimpleRNN
from keras.layers.wrappers import TimeDistributed
import argparse

def text_gen(model, sslice, length, clen, i2c, idx=[]):
    # the text head initializer, random given when not given
    if len(idx) < 1:
        idx = np.random.randint(0, clen, (sslice))

    #print(idx)
    pd = np.zeros((1, length, clen))
    # predict loop
    pdstr=''
    infer_point = len(idx)
    # initialize the header of the predict text
    for i in range(infer_point):
        pd[0, i, idx] = 1
        #print(idx)
        pdstr+=i2c[idx[i]]
    #print(pdstr)

    for i in range(0, length-infer_point):
        # assign value
        # the predict session, now it's just a random gen
        #idx = np.random.randint(0, clen, (sslice))
        # the predict session, now as it should be
        idx = np.argmax(model.predict(pd[:, :i+infer_point, :])[0], 1)
        pd[0, i+infer_point, idx] = 1
        # print(idx)
        pdstr+=i2c[idx[-1]]
    #print(pdstr)
    return pdstr

def d_loader(fname, sslice, gap=1):
    '''
        this function will map the raw data to a word tensors
        for later use of the RNN,
        it splits each line of the raw data and the count chars as char embedding size,
        then this function creates a 3 ranking tensor with the length of the slice, the total
        number of the slices and the size of embeddings, which looks like a cube.

        "fname" is the name of the raw file
        "sslice" is the size(length) of every slice
        "gap" is the skips of every window, errors will occur when it is set smaller than 1
    '''
    # load raw text data from a given file name, it is assumed to be a plain text file.
    raw = open(fname).read().split('\n')[:-1]
    # create a set for character table
    cmap = set()
    # generate character table
    for row in raw:
        cmap.update(list(row))
    # clen is the character set size
    clen=len(cmap)

    #print("char mapping debug :", cmap, clen)
    # generate the 2-way char map
    i2c = {idx: c for idx, c in enumerate(cmap)}
    c2i = {c: idx for idx, c in enumerate(cmap)}
    # generate preprocessed dataset, i as input and o as output
    x=[]
    y=[]
    # for each row
    for row in raw:
        # x starts from 0 to max len - slice size - gap -1
        # y starts from 1 to max len - slice size - gap
        idx=0
        while idx < len(row)-sslice:
            # create one-hot matrixies
            one_hotx = np.zeros((sslice, clen), dtype=np.int8)
            one_hoty = np.zeros((sslice, clen), dtype=np.int8)
            islice = [c2i[c] for c in row[idx:idx+sslice+1]]
            # get index slices
            islicex = islice[:-1]
            islicey = islice[1:]
            # print('slice debug :', islicex, islicey)
            # convert index lists into onehot matrixies
            for i in range(sslice):
                # process each
                one_hotx[i, islicex[i]]=1
                one_hoty[i, islicey[i]]=1
            # add one hots to list
            x.append(one_hotx)
            y.append(one_hoty)
            #increase index
            idx+=gap
    #print('one hot debug :', x, y)
    return clen, i2c, c2i, np.stack(x, axis=0), np.stack(x, axis=0)



SIZE_BATCH=100
SIZE_WEIGHTS=None
DIM_HIDDEN=1024
SSLICE=64
NUM_LAYER=2
WEIGHTS=''

clen, i2c, c2i, x, y = d_loader('douban.txt', SSLICE, 31)
#print(i2c)
#print(text_gen(None, SSLICE, 10, clen, i2c, [c2i[c] for c in '三天之内']))

args = argparse.ArgumentParser()

model = Sequential()
model.add(LSTM(DIM_HIDDEN, input_shape=(None, clen), return_sequences=True))
for i in range(NUM_LAYER-1):
    model.add(LSTM(DIM_HIDDEN, return_sequences=True))
model.add(TimeDistributed(Dense(clen)))
model.add(Activation('softmax'))
model.compile(loss='categorical_crossentropy', optimizer='rmsprop')

epoc = 0
while True:
    model.fit(x, y, batch_size=SIZE_BATCH, verbose=0, nb_epoch=1)
    print(text_gen(model, SSLICE, 32, clen, i2c))#, [c2i[c] for c in '我草你妈']))
