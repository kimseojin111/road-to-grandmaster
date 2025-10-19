class Account:
    def __init__(self, owner, balance=0):
        self.owner = owner
        self.balance = balance

    def __add__(self, other):
        if not isinstance(other, Account):
            return NotImplemented
        return Account(f"{self.owner}&{other.owner}", self.balance + other.balance)

    def __eq__(self, other):
        return isinstance(other, Account) and self.balance == other.balance

    def __str__(self):
        return f"{self.owner}: {self.balance}₩"

class SavingsAccount(Account):
    def __init__(self, owner, balance=0, interest=0.02):
        super().__init__(owner, balance)
        self.interest = interest

    def apply_interest(self):
        self.balance += int(self.balance * self.interest)

    def __str__(self):
        return f"[Savings] {super().__str__()} (+{int(self.interest*100)}%)"

class LimitedAccount(Account):
    def __init__(self, owner, balance=0, limit=1000000):
        super().__init__(owner, balance)
        self.limit = limit

    def __add__(self, other):
        total = self.balance + other.balance
        capped = min(total, self.limit)
        return LimitedAccount(f"{self.owner}&{other.owner}", capped, self.limit)

    def __str__(self):
        return f"[Limited] {self.owner}: {self.balance}₩ (limit: {self.limit}₩)"

a = Account("Alice", 300000)
b = Account("Bob", 500000)
c = a + b
print(c)

s = SavingsAccount("Sue", 1000000, interest=0.05)
s.apply_interest()
print(s)

a = SavingsAccount("A", 100000)
b = LimitedAccount("B", 200000)
c = a + b
print(c)
print(type(c))

print(Account("X", 1000) == Account("Y", 1000))
print(Account("X", 1000) == SavingsAccount("X", 1000))
