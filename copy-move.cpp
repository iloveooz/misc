#include <iostream>

class Coord2D {
public:
    Coord2D() {
        m_x = 0;
        m_y = 0;
        std::cout << "Coord2D(x = " << m_x << ", y = " << m_y << ") created" << std::endl;
    }

    Coord2D(int x, int y) {
        m_x = x;
        m_y = y;
        std::cout << "Coord2D(x = " << m_x << ", y = " << m_y << ") created" << std::endl;
    }

    ~Coord2D() {
        std::cout << "Coord2D(x = " << m_x << ", y = " << m_y << ") destroyed" << std::endl;
    }

    int getX() const { return m_x; }
    int getY() const { return m_y; }
    
    Coord2D& setX(int x) { 
		m_x = x; 
		return *this; 
	}
	
    Coord2D& setY(int y) { 
		m_y = y; 
		return *this;
	}

    Coord2D(Coord2D const &) = delete;
    void operator=(Coord2D const &) = delete;
private:
    int m_x, m_y;
};

int main() {
    Coord2D c1;
    Coord2D c2(1, 2);

    std::cout << "Hi!" << std::endl;
}
