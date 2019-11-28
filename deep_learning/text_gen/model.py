#import conf

import numpy as np

import torch
from torch import nn
from torch.optim import Adam
import data
from sys import stdout
import time

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
    def __init__(self, conf, is_load=False):
        
        self.conf = conf
        self.i2c, self.c2i = data.dict.load(conf.DATA_DIR+conf.DICT_I2C, conf.DATA_DIR+conf.DICT_C2I)
        self.clen = len(self.i2c)
        self.model = m_charRNN(conf, self.i2c, self.c2i)
        self.loss_function = nn.CrossEntropyLoss()
        self.optimizer = Adam(self.model.parameters(), lr=conf.LEARNING_RATE)
  
        if is_load:
            # load weight
            self.hidden_state = self.load_weight()
            # print(self.hidden_state)
            
        else:
            # initialize the hidden state
            self.hidden_state = self.model.init_hidden()
    def to_str(self, v):
        # convert a embedding to a string
        s=''
        for e in v[0]:
            s+=self.i2c[e]
        return s
    def train(self, i, o, epochs=1):
        self.model.train()
        self.model.cuda()
        # loop memory batch for training batch
        for ep in range(epochs):
            index=0
            losses=[]
            while index < len(i) - self.conf.SIZE_BATCH_TRAIN:
                # feed data
                torch_i = torch.from_numpy(i[index:index+self.conf.SIZE_BATCH_TRAIN]).cuda()
                torch_o = torch.from_numpy(o[index:index+self.conf.SIZE_BATCH_TRAIN]).cuda()
                self.hidden_state = tuple([n.data for n in self.hidden_state])
                self.model.zero_grad()
                #print(torch_i)
                pred, self.hidden_state = self.model(torch_i, self.hidden_state)
                #print(pred.size(), torch_o.size())
                loss = self.loss_function(pred, torch_o.view(-1))
                loss.backward()

                #nn.utils.clip_grad_norm_(self.model.parameters(), clip)
                self.optimizer.step()
                #print(loss.item())
                losses.append(loss.item())
                stdout.write(str(index)+'/'+str(self.conf.SIZE_BATCH_MEMORY)+' '+'MAX : %f, MIN : %f, MEAN : %f'%(max(losses), min(losses), sum(losses)/len(losses))+'\r')
                #print(self.infer(36))
                stdout.flush()
                #self.save_weight()
                #input()
                index+=self.conf.SIZE_BATCH_TRAIN
                
            print('epoch batch finished, MAX : %f, MIN : %f, MEAN : %f'%(max(losses), min(losses), sum(losses)/len(losses)))
    def infer(self, size):
        # generate strings
        # generte a random seed
        self.model.cuda()
        seed = np.random.randint(0, self.clen, (1, self.conf.SSLICE))
        idx=0
        s=''
        for idx in range(size - self.conf.SSLICE):
            # apply the first character to string
            #print(seed.shape)
            s+=self.i2c[seed[0, 0]]
            # reproduce seed to every batch channel
            print('<', self.to_str(seed))
            i = np.repeat(data.data.one_hot(self.clen, seed), self.conf.SIZE_BATCH_TRAIN, axis=0)
            #i = np.repeat(data.data.one_hot(self.clen, seed), size, axis=0)
            #print(i.shape)
            #infer and refresh one hot 
            o, _ = self.model(torch.from_numpy(i).cuda(), self.hidden_state)#(self.hidden_state[0].cpu(), self.hidden_state[1].cpu()))
            #print(o.shape)
            # override seed
            seed = torch.argmax(torch.argmax(torch.reshape(o, (self.conf.SIZE_BATCH_TRAIN, self.conf.SSLICE, self.clen)), dim=0).data, dim=-1).data.reshape(1, -1).cpu().detach().numpy()
            #seed = torch.argmax(torch.reshape(o, (self.conf.SIZE_BATCH_TRAIN, self.conf.SSLICE, self.clen))[0], dim=-1).data.reshape(1, -1).cpu().detach().numpy()
            print('>', self.to_str(seed))
            #print(pred)
        # convert the last window to strings
        for seed_idx in seed[0]:
            # convert to str
            s+=self.i2c[seed_idx]
        return s
    
    def save_model(self):
        # save this model
        # this function is rare used and deprecated
        print('save model')
        torch.save(self.model, self.conf.SAVE_M)
    def save_weight(self):
        # save current weight and hidden state
        state = {
            'state_dict':self.model.state_dict(),
            'optimizer' :self.optimizer.state_dict(),
            'hidden_state': self.hidden_state
            }
        #print('save weights', type(self.hidden_state))
        torch.save(state, self.conf.SAVE_W)
    def load_model(self):
        # load model instead 
        # this function is rarely used and deprecated
        print('load mode via config file name')
        
    def load_weight(self):
        # load learned weight
        print('load weight via config file name')
        state = torch.load(self.conf.SAVE_W)
        self.model.load_state_dict(state['state_dict'])
        # DO NOT UNCOMMENT THE CODE BELOW, WILL CAUSE RUNTIME ISSUE
        #self.optimizer.load_state_dict(state['optimizer'])
        return state['hidden_state']
    def train_epoch(self, epochs):
        data_feeder = data.data(self.conf, True)
        data_feeder.get_list()
        for epoch in range(epochs):
            print('start epoch %d'%(epoch+1))
            for x, y in data_feeder:
                self.train(data.data.one_hot(self.clen, x), y)
            print('save epoch')
            self.save_weight()
                #print(G.infer(36))
