import sentencepiece as spm

sp=spm.SentencePieceProcessor()
sp.load('m.model')

print(sp.encode_as_pieces('没有什么不良嗜好。 爱好特别广泛，什么运动游戏看书听音乐看电影看动漫看话剧旅行等等等。 思维方式比较道家，包容性较强，活的较为佛系，凡事都可以商量着来，没有令人恶心的那部分直男逻辑。 接受丁克。 目前在北京，去哪都行。 对了，不会做饭。'))
