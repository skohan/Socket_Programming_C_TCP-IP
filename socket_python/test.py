name = raw_input()
list = name.split('.')
if name == 'yo.txt':
    print('oh yeah!')
print(list)
print(list[0]+'.'+list[1])
f = open('yo.txt','rb')

with open(name,"rb") as f:
    byte = f.read(1)
    while byte != "":
        print(byte)
        byte = f.read(1)
f.close()
