import numpy as np
import glob

class dict:
    def gen(fraw, fi2c, fc2i, return_dict=False):
        '''
            This function will generate a dictinary and save it to files.
        '''
        # load raw text data from a given file name, it is assumed to be a plain text file.
        raw = open(fraw).read().split('\n')[:-1]
        # create a set for character table
        cmap = set('\002')
        # generate character table
        for row in raw:
            cmap.update(list(row))
        #print("char mapping debug :", clen)
        # generate the 2-way char map
        i2c = {idx: c for idx, c in enumerate(cmap)}
        c2i = {c: idx for idx, c in enumerate(cmap)}
        if fi2c is not None:
            # save the i2c dict file
            np.save(fi2c, i2c)
        if fc2i is not None:
            # save the c2i dict file
            np.save(fc2i, c2i)
        if is_entity:
            self.i2c=i2c
            self.c2i=c2i
        if return_dict:
            return i2c, c2i
    def load(fi2c, fc2i):
        '''
            This generator will generate binary numpy dictionary,
            and save the whole them to a local dir
        '''
        return np.load(fi2c).item(), np.load(fc2i).item()
class data:
    def __init__(self, conf,  have_dict=False):
        self.index=0
        self.file_list_i=[]
        self.file_list_o=[]
        self.conf=conf
        #self.batch=None
        if have_dict:
            self.i2c, self.c2i=dict.load(conf.DATA_DIR+conf.DICT_I2C, conf.DATA_DIR+conf.DICT_C2I)
        else:
            self.i2c, self.c2i=dict.gen(conf.DATA_RAW, conf.DATA_DIR+conf.DICT_I2C, conf.DATA_DIR+conf.DICT_C2I, True)
        self.clen = len(self.i2c)
    def get_list(self):
        '''
            This funtion fetch the list of the data sets,
            then returns the initial index and the list of file name of it.
        '''
        self.file_list_i = sorted(glob.glob(self.conf.DATA_DIR+self.conf.DATA_PREFEX_I+'*'))
        self.file_list_o = sorted(glob.glob(self.conf.DATA_DIR+self.conf.DATA_PREFEX_O+'*'))
        #print(self.file_list_i)
        #print(self.file_list_o)
    def __next__(self):
        '''
            This function fetch next(loop) batch of the whole dataset, and return to the keras learner
        '''
        index = self.index
        if self.index == len(self.file_list_i):
            raise StopIteration
        self.index+=1

        return np.load(self.file_list_i[index]), np.load(self.file_list_o[index])
        #return index
    def __iter__(self):
        self.index=0
        return self
    def gen(self):
        '''
        v0
            this function will map the raw data to a word tensors
            for later use of the RNN,
            it splits each line of the raw data and the count chars as char embedding size,
            then this function creates a 3 ranking tensor with the length of the slice, the total
            number of the slices and the size of embeddings, which looks like a cube.
            "fname" is the name of the raw file
            "sslice" is the size(length) of every slice
            "gap" is the skips of every window, errors will occur when it is set smaller than 1

        v1
            This function will generate the trainig data set in small pieces to fit memory
            starving siturations. Saving training set to local files is the best solution
            now. other solution is to create a big file swap, and push all of the data set
            on memory, I've tried that but the performance is bad since the io flow is
            managed transparently by system.

            I've made a special prefex to mark the data sets, for seeking them later.
        '''
        # load raw text data from a given file name, it is assumed to be a plain text file.
        raw = open(self.conf.DATA_RAW)
        i2c, c2i = dict.load(self.conf.DATA_DIR+self.conf.DICT_I2C, self.conf.DATA_DIR+self.conf.DICT_C2I)
        clen=len(i2c)
        # generate preprocessed dataset, i as input and o as output
        x=[]
        y=[]
        # for each row
        save_tag=0
        for row in raw:
            # x starts from 0 to max len - slice size - gap -1
            # y starts from 1 to max len - slice size - gap
            # append an end indicator to each line
            row = row[:-1] + '\002'
            idx=0
            while idx < len(row)-self.conf.SSLICE:
                # create one-hot matrixies
                one_hotx = np.zeros((self.conf.SSLICE, self.clen), dtype=np.int8)
                one_hoty = np.zeros((self.conf.SSLICE, self.clen), dtype=np.int8)
                islice = [c2i[c] for c in row[idx:idx+self.conf.SSLICE+1]]
                # get index slices
                islicex = islice[:-1]
                islicey = islice[1:]
                # print('slice debug :', islicex, islicey)
                # convert index lists into onehot matrixies
                for i in range(self.conf.SSLICE):
                    # process each
                    one_hotx[i, islicex[i]]=1
                    one_hoty[i, islicey[i]]=1
                # add one hots to list
                x.append(one_hotx)
                y.append(one_hoty)
                #increase index
                idx+=self.conf.GAP
                #print(i)
                save_tag+=1
                if save_tag % self.conf.SIZE_BATCH_MEMORY == 0:
                    # save and clean array
                    np.save(self.conf.DATA_DIR+self.conf.DATA_PREFEX_I+str(save_tag), np.stack(x, axis=0))
                    x=[]
                    np.save(self.conf.DATA_DIR+self.conf.DATA_PREFEX_O+str(save_tag), np.stack(y, axis=0))
                    y=[]
        if len(x) > 0:
            # The edge case
            np.save(self.conf.DATA_DIR+self.conf.DATA_PREFEX_I+str(save_tag), np.stack(x, axis=0))
            x=[]
            np.save(self.conf.DATA_DIR+self.conf.DATA_PREFEX_O+str(save_tag), np.stack(y, axis=0))
            y=[]

        #print('one hot debug :', x, y)
        #return clen, i2c, c2i, np.stack(x, axis=0), np.stack(x, axis=0)
