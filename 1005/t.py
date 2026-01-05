def f(x):
    re = 0 
    while x:
        re += x%10 
        x /= 10 
    return re 

arr = [f(pow(5,i)) for i in range(1,51)] 

for i in range(49): 
    if arr[i]>arr[i+1]:
        print(i)