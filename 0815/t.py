total_call = 0 

def quicksort(arr, low, high, k):
    global total_call 

    pivot = arr[high]
    m, n = low-1, high 
    print(m,n)
    while True: 
        while True:
            m += 1 
            if m>= len(arr):
                print('wtf') 
                print(arr,len(arr),low,high,m)
                raise
            if m>=high or arr[m] > pivot: 
                break 
        while True: 
            n -= 1
            if n<low or arr[n] < pivot: 
                break 
        if m<n: 
            arr[m], arr[n] = arr[n], arr[m] 
        else : 
            break 
    arr[m], arr[high] = arr[high], arr[m] 
    if k==m+1:
        return arr[m]
    elif k<m+1: 
        return quicksort(arr,low,m-1,k) 
    else : 
        return quicksort(arr,m+1,high,k)

L = [-9,-8,0,1,2,3,4]
print(quicksort(L,0,len(L)-1,3))
