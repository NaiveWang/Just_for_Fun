import model as M
import conf
G = M.text_gen(conf, False)
G.train_epoch(1)
