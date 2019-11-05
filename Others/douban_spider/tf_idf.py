import sentencepiece as spm
import numpy as np
import operator


class algo:
    def __init__(self, model, dict=None, f_raw=None):
        self.sp = spm.SentencePieceProcessor()
        self.sp.Load(model)
        if f_raw is not None:
            # generate dict
            raw=open(f_raw)
            #raw_len=0
            #print('processing corpus')
            #i=0
            recall = np.zeros(len(self.sp), dtype=np.float32)
            for line in raw:
                idz = self.sp.EncodeAsIds(line)
                #raw_len+=len(idz)
                for id in idz:
                    recall[id]+=1
                #i+=1
                #if i % 10000 == 0:
                #    print(i)
            for i in range(len(recall)):
                if recall[i]==0: recall[i]=.1
            np.save(f_raw, recall)
            self.dict = recall
        elif dict is not None:
            # load dict
            self.dict = np.load(dict)
        else:
            raise Exception
    def key_miner(self, text):
        post={}
        # post
        post_len=0
        for line in text:
            idz = self.sp.EncodeAsIds(line)
            post_len+=len(idz)
            for id in idz:
                if id in post:
                    post[id] += 1
                else:
                    post[id] = 1
        for i in post:
            post[i] = post[i]*1./(self.dict[i] * post_len)
        return sorted(post.items(), key=operator.itemgetter(1), reverse=True)
    def i2t_print(self, post_s):
        for freq in post_s:
            print(self.sp.IdToPiece(freq[0]), freq[1])
    def i2t(self, post_s):
        return [[self.sp.IdToPiece(freq[0]), freq[1], self.dict[freq[0]]] for freq in post_s]
'''
a=algo('douban.model', 'db.txt.npy')

print(a.i2t(a.key_miner(text)))
'''
