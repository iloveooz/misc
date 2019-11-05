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
	// возвращает значение карты, от 1 до 11
	int GetValue() const;
	// переворачивает карту: карта, лежащая лицом вверх, переворачивается лицом вниз и наоборот
	void Flip();
private:
	rank m_Rank;
	suit m_Suit;
	bool m_IsFaceUp;
};

Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) {}

int Card::GetValue() const {
	// если карта перевернута лицом вниз, ее значение равно 0
	int value = 0;
	if (m_IsFaceUp)	{
		// значение - это число, указанное на карте
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

class Hand {
public:
	Hand();
	virtual ~Hand();
	// добавляет карту в руку
	void Add(Card* pCard);
	// очищает руку от карт
	void Clear();
	// получает сумму очков карт в руке, присваивая тузу значение 1 или 11 в зависимости от ситуации
	int GetTotal() const;
protected:
	std::vector<Card*> m_Cards;
};

Hand::Hand() {
	m_Cards.reserve(7);
}

Hand::~Hand() {
	Clear();
}

void Hand::Add(Card* pCard) {
	m_Cards.push_back(pCard);
}

void Hand::Clear() {
	// проходит по вектору, освобождая всю память в куче
	std::vector<Card*>::iterator iter = m_Cards.begin();
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
		delete *iter;
		*iter = nullptr;
	}
	// очищает вектор указателей
	m_Cards.clear();
}

int Hand::GetTotal() const {
	// если карт в руке нет, возвращает значение 0
	if (m_Cards.empty()) {
		return 0;
	}
	// если первая карта имеет значение 0, то она лежит рубашкой вверх: вернуть значение 0
	if (m_Cards[0]->GetValue() == 0) {
		return 0;
	}
	// находит сумму очков всех карт, каждый туз дает 1 очко
	int total = 0;
	std::vector<Card *>::const_iterator iter;

	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
		total += (*iter)->GetValue();
	}
	// определяет, держит ли рука туз
	bool containsAce = false;
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
		if ((*iter)->GetValue() == Card::АСЕ) {
			containsAce = true;
		}
	}
	// если рука держит туз и сумма довольно маленькая, туз дает 11 очков
	if (containsAce && total <= 11)	{
		// добавляем только 10 очков, поскольку мы уже добавили за каждый туз по одному очку
		total += 10;
		return total;
	}
}