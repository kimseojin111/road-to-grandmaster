n,a,b = map(int,input().split()) 
l = a*(n-1)+b
r = b*(n-1)+a 
print(max(r-l+1,0))