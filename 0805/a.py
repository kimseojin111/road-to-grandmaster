import random 
r = open('input.txt','w') 
r.write('1\n')
r.write('200000 1\n')
for i in range(200000):
    x = random.randrange(1,1000000)
    r.write(f"{x} ")