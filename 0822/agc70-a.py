import random
from typing import List, Tuple

# ----- Card, Deck, Hand -----
class Card:
    suits = ["♠", "♥", "♦", "♣"]
    ranks = ["2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"]

    def __init__(self, rank: str, suit: str):
        self.rank = rank
        self.suit = suit

    def __str__(self):
        # to implement 


        ###

    def rank_value(self) -> int:
        return self.ranks.index(self.rank)
    
    def suit_value(self) -> int:
        return self.suits.index(self.suit)

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, Card):
            return NotImplemented 
        # to implement 


        ###

    def __lt__(self, other: object) -> bool: 
        if not isinstance(other, Card):
            return NotImplemented 
        # to implement 


        ###


class Deck:
    def __init__(self):
        self.cards = [Card(r, s) for s in Card.suits for r in Card.ranks]
        random.shuffle(self.cards)

    def draw(self, n: int) -> List[Card]:
        # to implement 


        ###


class Hand:
    def __init__(self, cards: List[Card]):
        self.cards = cards

    def __str__(self):
        return " ".join(str(c) for c in self.cards)

    def evaluate(self) -> Tuple[int, List[int]]:
        # rank by poker rules
        values = sorted([c.rank_value() for c in self.cards], reverse=True)
        counts = {v: values.count(v) for v in values}
        is_flush = len(set(c.suit for c in self.cards)) == 1
        is_straight = all(values[i] - 1 == values[i+1] for i in range(len(values)-1))

        if is_straight and is_flush:
            return (8, values)  # Straight flush
        elif 4 in counts.values():
            return (7, values)  # Four of a kind
        elif sorted(counts.values()) == [2, 3]:
            return (6, values)  # Full house
        elif is_flush:
            return (5, values)  # Flush
        elif is_straight:
            return (4, values)  # Straight
        elif 3 in counts.values():
            return (3, values)  # Three of a kind
        elif list(counts.values()).count(2) == 2:
            return (2, values)  # Two pair
        elif 2 in counts.values():
            return (1, values)  # One pair
        else:
            return (0, values)  # High card

# ----- Player & Dealer -----

class Player:
    def __init__(self, name: str, bankroll: int):
        self.name = name
        self.bankroll = bankroll

    def bet(self, amount: int):
        if amount > self.bankroll:
            raise ValueError("Not enough funds")
        self.bankroll -= amount
        return amount

    def win(self, amount: int):
        self.bankroll += amount



    # player 도 hand 를 갖게 확장성을 위해서 

class Dealer(Player):
    def __init__(self):
        super().__init__("Dealer", bankroll=99999999)

# ----- Game -----
class PokerGame:
    def __init__(self):
        self.player = Player("You", 100)
        self.dealer = Dealer()

    def print_player_state(self):
        # to implement 

        ###

    def player_dealer_split_hand(self):
        # player 랑 dealer 가 각각 hand 를 갖게됨 

    def play_round(self):
        print_player_state() 
        player_dealer_split_hand() 

        # 내 상태 표시하고 (이떄 sort 를 해주고) 내 배팅을 받음 (0원부터 20원) 

        # reveal 
        # 돈 받기 


    def run(self):
        print("=== Single Player Poker ===")
        while self.player.bankroll > 0:
            self.play_round()
            if input("Play another round? (y/n): ") == 'n':
                break
        print("Game over.")

if __name__ == "__main__":
    random.seed()
    PokerGame().run()
