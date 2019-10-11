import model as M
import conf
G = M.text_gen(conf, True)
G.train_epoch(1)
