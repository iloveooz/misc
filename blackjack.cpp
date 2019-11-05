// Blackjack
// Играет упрощенную версию игры Blackjack: от одного до семи игроков
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

class Card {
public:
	enum rank { АСЕ = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
	enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };
	// перегружаем оператор <<, чтобы можно было отправить объект типа Card в стандартный поток вывода
	friend std::ostream& operator << (std::ostream& os, const Card& aCard);
	Card(rank r = АСЕ, suit s = SPADES, bool ifu = true);
	// возвращает значение карты. от 1 до //
	int GetValue() const;
	// переворачивает карту: карта. лежащая лицом вверх.
	// переворачивается лицом вниз и наоборот
	void Flip();
private:
	rank m_Rank;
	suit m_Suit;
	bool m_IsFaceUp;
};

Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) {}

int Card::GetValue() const {
	// если карта перевернута лицом вниз. ее значение равно О
	int value = 0;
	if (m_IsFaceUp)	{
		// значение - это число. указанное на карте
		value = m_Rank;
		// значение равно 10 для открытых карт
		if (value > 10) {
			value = 10;
		}
	}
	return value;
}

void Card::Flip() {
	m_IsFaceUp = !(m_IsFaceUp);
}
