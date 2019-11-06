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

class GenericPlayer : public Hand {
	friend std::ostream& operator << (std::ostream& os, const GenericPlayer& aGenericPlayer);
public:
	GenericPlayer(const std::string& name = "");
	virtual ~GenericPlayer();
	// показывает, хочет ли игрок продолжать брать карты
	virtual bool IsHitting() const = 0;
	// возвращает значение, если игрок имеет перебор - сумму очков, большую 21
	bool IsBusted() const;
	// объявляет, что игрок имеет перебор
	void Bust() const;
protected:
	std::string m_Name;
};

GenericPlayer::GenericPlayer(const std::string& name): m_Name(name) {}

GenericPlayer::~GenericPlayer() {}

bool GenericPlayer::IsBusted() const {
return (GetTotal() > 21);
}

void GenericPlayer::Bust() const {
	std::cout << m_Name << " busts.\n";
}

class Player : public GenericPlayer {
public:
	Player(const std::string& name = "");
	virtual ~Player();
	// показывает, хочет ли игрок продолжать брать карты
	virtual bool IsHitting() const;
	// объявляет, что игрок победил
	void Win() const;
	// объявляет, что игрок проиграл
	void Lose() const;
	// объявляет ничью
	void Push() const;
};

Player::Player (const std::string& name) : GenericPlayer(name) {}

Player::~Player() {}

bool Player::IsHitting() const {
	std::cout << m_Name << ". Do you want a hit? (Y/N): ";
	char response;
	std::cin >> response;
	return (response == 'y' || response == 'Y');
}

void Player::Win() const {
	std::cout << m_Name << " wins. \n";
}

void Player::Lose() const {
	std::cout << m_Name << " loses. \n";
}

void Player::Push() const {
	std::cout << m_Name << " pushes. \n";
}

class House : public GenericPlayer {
public:
	House(const std::string& name = "House");
	virtual ~House();
	// показывает, хочет ли игрок продолжать брать карты
	virtual bool IsHitting() const;
	// переворачивает первую карту
	void FlipFirstCard();
};

House::House(const std::string& name) : GenericPlayer(name) {}

House::~House() {}

bool House::IsHitting() const {
return (GetTotal() <= 16);
}

void House::FlipFirstCard() {
	if (!m_Cards.empty()) {
		m_Cards[0]->Flip();
	}
	else {
		std::cout << "No card to flip!\n";
	}
}

class Deck : public Hand {
public:
	Deck();
	virtual ~Deck();
	// создает стандартную колоду из 52 карт
	void Populate();
	// тасует карты
	void Shuffle();
	// раздает одну карту в руку
	void Deal(Hand& aHand);
	// дает дополнительные карты игроку
	void AdditionalCards(GenericPlayer& aGenericPlayer);
};

Deck::Deck() {
	m_Cards.reserve(52);
	Populate();
}

Deck::~Deck() {}

void Deck::Populate() {
	Clear();
	// создает стандартную колоду
	for (int s = Card::CLUBS; s <= Card::SPADES; ++s) {
		for (int r = Card::АСЕ; r <= Card::KING; ++r) {
			Add(new Card(static_cast<Card::rank>(r), static_cast<Card::suit>(s)));
		}
	}
}

void Deck::Shuffle() {
	std::random_shuffle(m_Cards.begin(), m_Cards.end());
}

void Deck::Deal(Hand& aHand) {
	if (!m_Cards.empty()) {
		aHand.Add(m_Cards.back());
		m_Cards.pop_back();
	}
	else {
		std::cout << "Out of cards. Unable to deal.";
	}
}

void Deck::AdditionalCards(GenericPlayer& aGenericPlayer) {
	std::cout << std::endl;
	// продолжает раздавать карты до тех пор, пока у игрока не случается перебор или пока он хочет взять еще одну карту
	while (!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting()) {
		Deal(aGenericPlayer);
		std::cout << aGenericPlayer << std::endl;
		if (aGenericPlayer.IsBusted()) {
			aGenericPlayer.Bust();
		}
	}
}

class Game {
public:
	Game(const std::vector<std::string>& names);
	~Game();
	// проводит игру в Blackjack
	void Plау();
private:
	Deck m_Deck;
	House m_House;
	std::vector<Player> m_Players;
};

Game::Game(const std::vector<std::string>& names) {
	// создает вектор игроков из вектора с именами
	std::vector<std::string>::const_iterator pName;
	for (pName = names.begin(); pName != names.end(); ++pName) {
		m_Players.push_back(Player(*pName));
	}
	// засевает генератор случайных чисел
	srand(static_cast<unsigned int>(time(0)));
	m_Deck.Populate();
	m_Deck.Shuffle();
}

Game::~Game() {}

void Game::Plау() {
	// раздает каждому по две стартовые карты
	std::vector<Player>::iterator pPlayer;
	for (int i = 0; i < 2; ++i) {
		for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
			m_Deck.Deal(*pPlayer);
		}
		m_Deck.Deal(m_House);
	}
	// прячет первую карту дилера
	m_House.FlipFirstCard();
	// открывает руки всех игроков
	for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
			std::cout << *pPlayer << std::endl;
	}
	std::cout << m_House << std::endl;
	// раздает игрокам дополнительные карты
	for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
		m_Deck.AdditionalCards(*pPlayer);
	}
	// показывает первую карту дилера
	m_House.FlipFirstCard();
	std::cout << std::endl << m_House;
	// раздает дилеру дополнительные карты
	m_Deck.AdditionalCards(m_House);

	if (m_House.IsBusted()) {
		// все, кто остался в игре, побеждают
		for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
			if (!pPlayer->IsBusted()) {
				pPlayer->Win();
			}
		}
	}
	else {
		// сравнивает суммы очков всех оставшихся игроков с суммой очков дилера
		for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
			if (!pPlayer->IsBusted()) {
				if (pPlayer->GetTotal() > m_House.GetTotal()) {
					pPlayer->Win();
				}
				else if (pPlayer->GetTotal() < m_House.GetTotal()) {
					pPlayer->Lose();
				}
				else {
					pPlayer->Push();
				}
			}
		}
	}
	// очищает руки всех игроков
	for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
		pPlayer->Clear();
	}
	m_House.Clear();
}


// прототипы функций
std::ostream& operator<<(std::ostream& os, const Card& aCard);
std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer);

int main() {
	std::cout << "\t\tWelcome to Blackjack!\n\n";
	int numPlayers = 0;
	while (numPlayers < 1 || numPlayers > 7) {
		std::cout << "How many players? (1 - 7): ";
		std::cin >> numPlayers;
	}
	std::vector<std::string> names;
	std::string name;
	for (int i = 0; i < numPlayers; ++i) {
		std::cout << "Enter player name: ";
		std::cin >> name;
		names.push_back(name);
	}
	std::cout << std::endl;
	// игровой цикл
	Game aGame(names);
	char again = 'y';
	while (again != 'n' && again != 'N') {
		aGame.Plау();
		std::cout << "\nDo you want to play again? (Y/N): ";
		std::cin >> again;
	}
	return 0;
}

	
// перегружает оператор <<, чтобы получить возможность отправить объект типа Card в поток std::cout
std::ostream& operator << (std::ostream& os, const Card& aCard) {
	const std::string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	const std::string SUITS[] = { "c", "d", "h", "s" };
	if (aCard.m_IsFaceUp) {
		os << RANKS[aCard.m_Rank] << SUITS[aCard.m_Suit];
	}
	else {
		os << "XX";
	}
	return os;
}

// перегружает оператор <<, чтобы получить возможность отправить объект типа GenericPlayer в поток std::cout
std::ostream& operator << (std::ostream& os, const GenericPlayer& aGenericPlayer) {
	os << aGenericPlayer.m_Name << ":\t";
	std::vector<Card *>::const_iterator pCard;
	if (!aGenericPlayer.m_Cards.empty()) {
		for (pCard = aGenericPlayer.m_Cards.begin(); pCard != aGenericPlayer.m_Cards.end();	++pCard) {
			os << *(*pCard) << "\t";
		}
		if (aGenericPlayer.GetTotal() != 0) {
			std::cout << "(" << aGenericPlayer.GetTotal() << ")";
		}
	}
	else {
		os << "<empty>";
	}
	return os;
}
