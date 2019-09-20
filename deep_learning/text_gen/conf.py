'''
    This is the configuration file.
    I contain all of the configuration information, here,
    and i was imported by almost all the instances.

    Notice : DO NOT MODIFY THIS FILE DURING TRAINING SESSION
'''

__STOP='\002'
SIZE_BATCH_TRAIN=128
SIZE_BATCH_MEMORY=102400
DIM_HIDDEN=1024
SSLICE=16
NUM_LAYER=5
DROPOUT=0.1
EPOC_BATCH=1
SAVE_M='default.h5m'
SAVE_W='default.h5w'
GAP=7

DATA_DIR='data/'
DATA_RAW='douban.txt'
DATA_PREFEX_I='batch_i'
DATA_PREFEX_O='batch_o'
DICT_I2C='i2c.dict.npy'
DICT_C2I='c2i.dict.npy'
