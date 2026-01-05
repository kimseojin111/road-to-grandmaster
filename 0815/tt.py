class Sort:
    def _quicksort(self, array: list, low: int, high: int):
        if low < high:
            pivot = self._partition(array, low, high)
            self._quicksort(array, low, pivot)
            self._quicksort(array, pivot + 1, high)

    def _partition(self, a: list, low: int, high: int) -> int:
        print(a,low,high)
        pivot = a[(high + low) // 2]
        i = low-1
        j = high+1

        while True:
            i+=1
            while a[i] < pivot:
                i+=1 
            j -= 1 
            while a[j] > pivot:
                j-=1
            if i>=j: 
                print(i,j)
                return i 
            a[i], a[j] = a[j], a[i]

    def sort(self, array: list) -> list:
        self._quicksort(array, 0, len(array) - 1)
        return array

s = Sort() 
print(Sort().sort([1,1]))
