r = open('input.txt','w') 
import random 
r.write('100000\n')
for i in range(100000):
    r.write(f"{random.randrange(1,1000000)} ")