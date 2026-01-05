import random 
def f(n):
    re = 0 
    while n:
        re += n%10 
        n //= 10 
    return re 

def get(x):
    arr = [f(pow(5,i)*x) for i in range(0,51)] 
    return arr 

arr = [0 for _ in range(51)] 
ans = []

def ran():
    x = 2*random.randint(1,10)+1
    xxx = 1<<random.randint(5,10) # 012345
    t = random.randint(0,1) 
    if t==0: return x 
    if t==1: return xxx 

while True: 
    x = ran()
    #print(x)
    a = get(x) 
    #print(x,a)
    ans.append(x) 
    for i in range(51):
        arr[i] += a[i]
    #print(arr)
    # f(x) > f(2x) ... x = 5^50 t, f(5^50t) > ... f(5) 
    flag = True
    cnt = 0 
    for i in range(50):
        if arr[i]>=arr[i+1]:
            flag = False 
            #print(i,arr[i],arr[i+1])
            cnt += 1 
    #print(cnt)
    if flag or len(ans)>200:
        print(ans,len(ans)) 
        d = ""
        #print(len(ans))
        for x in ans:
            d += str(x*pow(5,50)) + str(0)*100 
        print(d)
        break 
        
 