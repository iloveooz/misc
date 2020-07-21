#include <iostream>

class Coord2D {
public:
    Coord2D() {
        m_x = 0;
        m_y = 0;
        std::cout << "Coord2D(x = " << m_x << ", y = " << m_y << ") created." << std::endl;
    }

    Coord2D(int x, int y) {
        m_x = x;
        m_y = y;
        std::cout << "Coord2D(x = " << m_x << ", y = " << m_y << ") created." << std::endl;
    }
    
    Coord2D(const Coord2D& object) {
		m_x = object.m_x;
		m_y = object.m_y;
		std::cout << "Coord2D(x = " << m_x << ", y = " << m_y << ") copied." << std::endl;
	}
	
	Coord2D(Coord2D&& obj) { // move constructor
        m_x = obj.m_x;
        m_y = obj.m_y;
        std::cout << "Coord2D(x = " << m_x << ", y = " << m_y << ") moved" << std::endl;
    }
	
	Coord2D& operator = (const Coord2D& obj) {
        m_x = obj.m_x;
        m_y = obj.m_y;
        std::cout << "Coord2D(x = " << m_x << ", y = " << m_y << ") copy-assigned" << std::endl;
        return *this;
    }
    
    Coord2D& operator = (Coord2D&& obj) {
        m_x = obj.m_x;
        m_y = obj.m_y;
        std::cout << "Coord2D(x = " << m_x << ", y = " << m_y << ") move-assigned" << std::endl;
        return *this;
    }    

    template<class T>
    friend Coord2D operator + (T&& a, const Coord2D& b) {
        std::cout << "Creating `Coord2D t`..." << std::endl;
        Coord2D t(std::forward<T>(a));
        std::cout << "`Coord2D t` created!" << std::endl;

        return t.setX(t.getX() + b.getX()).setY(t.getY() + b.getY());
    }

    template<class T>
    friend Coord2D operator - (T&& a, const Coord2D& b) {
        std::cout << "Creating `Coord2D t`..." << std::endl;
        Coord2D t(std::forward<T>(a));
        std::cout << "`Coord2D t` created!" << std::endl;

        return t.setX(t.getX() - b.getX()).setY(t.getY() - b.getY());
    }


    ~Coord2D() {
        std::cout << "Coord2D(x = " << m_x << ", y = " << m_y << ") destroyed." << std::endl;
    }

    int getX() const { 
		return m_x; 
	}
	
    int getY() const { 
		return m_y;
	}
    
    Coord2D& setX(int x) { 
		m_x = x; 
		return *this; 
	}
	
    Coord2D& setY(int y) { 
		m_y = y; 
		return *this;
	}

    // Coord2D(Coord2D const &) = delete;
    // void operator=(Coord2D const &) = delete;
private:
    int m_x, m_y;
};



Coord2D id(Coord2D x) {
    std::cout << "id called" << std::endl;
    return x;
}

int main() {
	// 1 ---
    // Coord2D c0;
    // Coord2D c1(1, 1);
    
    // Coord2D c2 = c1;
    // Coord2D c3(c1);
    
    // c2 = c3;
    
    // 2 ---
    // Coord2D c4 = id(Coord2D(4, 4));
    // c4.setX(-4);
    
    // 3 ---
    // Coord2D c1(1,2);
    // c1 = Coord2D(4,5);
    
    // 4 ---
    // Coord2D c1(std::move(Coord2D(1,2).setX(5)));
    
    // 5 ---
    Coord2D c1(1,1), c2(2,2), c3(3,3);
    Coord2D c4 = c1 + c2 + c3;

    std::cout << "Hi!" << std::endl;
}

// Чтобы заработало Coord2D c1(Coord2D(1,2).setX(5)); нужно написать:
// Coord2D&& setX(int x) && { _x = x; return std::move(*this); }

// Лучше использовать списки инициализации:
// Coord2D(Coord2D const & obj) : _x(obj._x), _y(obj._y) {...}
// При использовании списков инициализации сразу вызывается конструктор копирования без дополнительных промежуточных действий;

// Лучше использовать списки инициализации вида:
// Coord2D(Coord2D && obj) : _x(std::move(obj._x)), _y(std::move(obj._y)) {...}
