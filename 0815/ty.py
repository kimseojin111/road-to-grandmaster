import re

class greedy_calculator:
    pattern = re.compile(r'\d+|[+\-*/]')

    def div(self, ans, val):
        # ans 을 val 로 나누는 함수이다.
        # try 문법으로 나누기를 시도하며 실패할 경우 error 을 호출한다.
        try:
            return ans / val
        except ZeroDivisionError:
            raise ZeroDivisionError("0으로 나눌 수 없음")

    def calculate(self, expr: str) -> float:
        tokens = self.pattern.findall(expr)  # ['3', '*', '6', '+', '2', '/', '3']

        it = iter(tokens)
        ans = float(next(it))
        while True:
            try:  # op 와 val 에 알맞은 값을 받고 만약 못받을 경우 return 을 해준다.
                op = next(it)
                val = float(next(it))
            except StopIteration:
                return ans

            if op == '+':
                ans += val
            elif op == '-':
                ans -= val
            elif op == '*':
                ans *= val
            elif op == '/':
                ans = self.div(ans, val)
            else:
                raise ValueError("알 수 없는 연산자")

# 예시
print(greedy_calculator().calculate("3*6+2/3"))  # 6.666666666666667
