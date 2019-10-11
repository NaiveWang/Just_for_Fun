import model as M
import conf
G = M.text_gen(conf, True)
while True:
    print(G.infer(40))

