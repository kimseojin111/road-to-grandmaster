class Book:
    def __init__(self, title, author):
        self.title = title
        self.author = author

    #q3-1.


class Member:
    MAX_BORROW = 3
    def __init__(self, name):
        self.name = name
        self.books = []

    def add_book(self, book):
        self.books.append(book)

    def printInfo(self):
        print(f"이름: {self.name}")
        print("보유 도서:")
        for b in sorted(self.books):
            print(f" - {b}")

    def can_borrow(self, book) -> bool:
        #q3-2.

    def remove_book(self, book) -> bool:
        #q3-3.


class Student(Member):
    MAX_BORROW = 5


class Library:
    def __init__(self):
        self.stock = []

    def add_book(self, book):
        self.stock.append(book)

    def printInfo(self):
        print("도서관 보유 도서:")
        for b in sorted(self.stock):
            print(f" - {b}")

    def lend_book(self, member, book) -> bool:
        for b in self.stock:
            if b == book:
                if not member.can_borrow(book):
                    return False
                # q3-2
        print(f"도서관은 {book.title}을 보유하고 있지 않습니다.")
        return False

    def return_book(self, member, book) -> bool:
        # q3-3. 


lib = Library()
books = [
    ("노인과 바다", "해밍웨이"),
    ("죄와 벌", "도스토예프스키"),
    ("데미안", "헤르만 헤세"),
    ("데미안", "헤르만 헤세"),
    ("동물 농장", "조지 오웰")
]

for t, a in books:
    lib.add_book(Book(t, a))

lib.printInfo()

alice = Member("Alice")
print("\n== 대여 시작 ==")
lib.lend_book(alice, Book("노인과 바다", "해밍웨이"))
lib.lend_book(alice, Book("노인과 바다", "해밍웨이")) 
lib.lend_book(alice, Book("죄와 벌", "도스토예프스키"))
lib.lend_book(alice, Book("위대한 개츠비", "스콧 피츠제럴드"))
lib.lend_book(alice, Book("데미안", "헤르만 헤세"))
lib.lend_book(alice, Book("동물 농장", "조지 오웰"))

print("\n== 대여 후 ==")
alice.printInfo()

print("\n== 반납 시작 ==")
lib.return_book(alice, Book("노인과 바다", "해밍웨이"))
lib.return_book(alice, Book("노인과 바다", "해밍웨이"))

print("\n== 반납 후 ==")
alice.printInfo()
lib.printInfo()
