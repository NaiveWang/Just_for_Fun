import conf
import dispatcher
import numpy as np

import torch
from torch import nn
from torch.optim import Adam
import torch.nn.functional as F

class m_charRNN(nn.Module):
    def __init__(self, conf, i2c, c2i):
        super().__init__()
        self.conf = conf
        self.layers_lstm = nn.LSTM(len(i2c), conf.DIM_HIDDEN, conf.NUM_LAYER, dropout=conf.DROPOUT, batch_first=True)
        self.layers_dropout = nn.Dropout(conf.DROPOUT)
        self.layers_o = nn.Linear(conf.DIM_HIDDEN, len(i2c))
        self.i2c = i2c
        self.c2i = c2i

    def forward(self, i, hidden):
        # build lstm layer
        o, hidden = self.layers_lstm(i.float(), hidden)
        o_drop = self.layers_dropout(o)
        o_drop = o_drop.contiguous().view(-1, self.conf.DIM_HIDDEN)
        o_drop = self.layers_o(o_drop)
        return o_drop, hidden
    def init_hidden(self):
        weight = next(self.parameters()).data
        return (
            weight.new(self.conf.NUM_LAYER, self.conf.SIZE_BATCH_TRAIN, self.conf.DIM_HIDDEN).zero_().cuda(),
            weight.new(self.conf.NUM_LAYER, self.conf.SIZE_BATCH_TRAIN, self.conf.DIM_HIDDEN).zero_().cuda())
class text_gen:
    def __init__(self, conf):
        self.conf = conf
        self.i2c, self.c2i = dispatcher.dict.load(conf.DATA_DIR+conf.DICT_I2C, conf.DATA_DIR+conf.DICT_C2I)
        self.clen = len(self.i2c)
        self.model = m_charRNN(conf, self.i2c, self.c2i)
        self.loss_function = nn.CrossEntropyLoss()
        self.optimizer = Adam(self.model.parameters(), lr=conf.LEARNING_RATE)
        self.hidden_state = self.model.init_hidden()
    def train(self, i, o, epochs=1):
        self.model.train()
        self.model.cuda()
        # loop memory batch for training batch
        for ep in range(epochs):
            index=0
            while index < len(i) - conf.SIZE_BATCH_TRAIN:
                # feed data
                torch_i = torch.from_numpy(i[index:index+conf.SIZE_BATCH_TRAIN]).cuda()
                torch_o = torch.from_numpy(o[index:index+conf.SIZE_BATCH_TRAIN]).cuda()
                self.hidden_state = tuple([n.data for n in self.hidden_state])
                self.model.zero_grad()
                #print(torch_i)

                pred, self.hidden_state = self.model(torch_i, self.hidden_state)
                #print(pred.size(), torch_o.size())
                loss = self.loss_function(pred, torch_o.view(-1))
                loss.backward()

                #nn.utils.clip_grad_norm_(self.model.parameters(), clip)
                self.optimizer.step()


                print(loss.item())
                index+=conf.SIZE_BATCH_TRAIN
    def gen(size=conf.SSLICE):
        
G = text_gen(conf)
data_feeder = dispatcher.data(conf, True)
data_feeder.get_list()
while True:
    for x, y in data_feeder:
        G.train(x, y)
        del(x)
        del(y)
