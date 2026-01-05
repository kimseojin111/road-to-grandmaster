class Book:
    def __init__(self, title, author):
        self.title = title
        self.author = author

    def __str__(self):
        return f"제목:{self.title}, 작가:{self.author}"

    def __lt__(self, other):
        return (self.title, self.author) < (other.title, other.author)

    def __eq__(self, other):
        return isinstance(other, Book) and self.title == other.title and self.author == other.author


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
        if book in self.books:
            print(f"{self.name}님은 이미 {book.title}을 보유하고 있습니다.")
            return False
        if len(self.books) >= self.MAX_BORROW:
            print(f"{self.name}님의 대여한도 {self.MAX_BORROW}권에 도달하였습니다.")
            return False
        return True

    def remove_book(self, book) -> bool:
        if book in self.books:
            self.books.remove(book)
            return True
        print(f"{self.name}님은 {book.title}을 보유하고 있지 않습니다.")
        return False


class Student(Member):
    MAX_BORROW = 5


class Library:
    def __init__(self):
        self.stock = {}

    def add_book(self, book: Book):
        self.stock[book] += 1

    def delete_book(self, book: Book):
        self.stock[book] -= 1

    def printInfo(self):
        print("도서관 보유 도서:")
        for b in sorted(self.stock):
            print(f" - {b}")

    def lend_book(self, member, book) -> bool:
        for b in self.stock:
            if b == book:
                if not member.can_borrow(book):
                    return False
                self.stock.remove(b)
                member.add_book(b)
                return True
        print(f"도서관은 {book.title}을 보유하고 있지 않습니다.")
        return False

    def return_book(self, member, book) -> bool:
        if member.remove_book(book):
            self.add_book(book)
            return True
        return False


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
