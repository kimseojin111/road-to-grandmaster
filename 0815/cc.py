import random

class Sort:
    def _quicksort(self, array: list, low: int, high: int):
        if low < high:
            p = self._partition(array, low, high)
            self._quicksort(array, low, p)
            self._quicksort(array, p + 1, high)

    def _partition(self, array: list, low: int, high: int) -> int:
        pivot = array[(low + high) // 2]
        i = low - 1
        j = high + 1
        while True:
            i += 1
            while array[i] < pivot:
                i += 1
            j -= 1
            while array[j] > pivot:
                j -= 1
            if i >= j:
                return j
            array[i], array[j] = array[j], array[i]

    def sort(self, array: list) -> list:
        if array:
            self._quicksort(array, 0, len(array) - 1)
        return array

def run_tests(trials=2000, n_min=5, n_max=7, key_range=50):
    rng = random.Random(20250816)
    sorter = Sort()

    for t in range(1, trials+1):
        n = rng.randint(n_min, n_max)
        arr = [rng.randint(0, key_range) for _ in range(n)]

        baseline_keys = sorted(arr)
        test_arr = arr[:]
        sorter.sort(test_arr)

        # 키 오름차순 여부
        key_sorted_ok = all(test_arr[i] <= test_arr[i+1] for i in range(len(test_arr)-1))
        # 파이썬 정렬한 키 순서와 동일한지
        same_as_python = (test_arr == baseline_keys)

        if not key_sorted_ok or not same_as_python:
            print(f"[FAIL] trial={t}, n={n}")
            print("original:", arr)
            print("sorted  :", test_arr)
            print("python  :", baseline_keys)
            print("key_sorted_ok =", key_sorted_ok)
            print("same_as_python=", same_as_python)
            return

    print(f"[PASS] All {trials} trials: 결과가 파이썬 정렬과 동일.")

if __name__ == "__main__":
    run_tests()
