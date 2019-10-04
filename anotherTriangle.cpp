#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
 
class Triangle
{
protected:
        double _a, _b, _c;
        const static double pi = 3.14159265;
public:
        Triangle() : _a(0), _b(0), _c(0) {}
        Triangle(double a, double b, double c) : _a(a), _b(b), _c(c) {}
        Triangle(const Triangle& other) : _a(other._a), _b(other._b), _c(other._c) {}
        // стороны
        const double a() const { return _a; }
        const double b() const { return _b; }
        const double c() const { return _c; }
 
        const double perimeter() const { return _a+_b+_c; }
        const double area() const
        {
                return (_b*_c*sin(A()))/2.0;
        }
        const bool is_possible() const { return ((_a+_b)>_c) || ((_b+_c)>_a) || ((_a+_c)>_b); }
        const bool is_right() const
        {
                return (((Ad()-90)<0.0001) || ((Bd()-90)<0.0001) || ((Cd()-90)<0.0001));
        }
 
        // углы, противолежащие соответствующим сторонам
        const double A() const
        {
                double p = (_b*_b + _c*_c - _a*_a) / (2.0*_c*_b);
                return acos(p-static_cast<int>(p));
        }
        const double B() const
        {
                double p = (-_b*_b + _c*_c + _a*_a) / (2.0*_a*_c);
                return acos(p-static_cast<int>(p));
        }
        const double C() const
        {
                double p = (_b*_b - _c*_c + _a*_a) / (2.0*_a*_b);
                return acos(p-static_cast<int>(p));
        }
 
        const double Ad() const { return A()/(pi/180.); }
        const double Bd() const { return B()/(pi/180.); }
        const double Cd() const { return C()/(pi/180.); }
 
        friend std::ostream& operator<< (std::ostream& o, const Triangle& T)
        {
                o << "a: " << T.a() << ", b: " << T.b() << ", c: " << T.c() << ". ";
                if (T.is_possible())
                        o << "Area: " << T.area();
                else
                        o << "Impossible triangle.";
                return o;
        }
};
 
class RightTriangle : public Triangle
{
public:
        const double hypotenuse() const { return _c; }
        RightTriangle(void) : Triangle(0, 0, 0) {}
        RightTriangle(double a, double b) : Triangle(a, b, pow(a*a+b*b, .5)){}
        RightTriangle& operator= (const Triangle& other)
        {
                if (this!=&other)
                {
                        if (other.is_right())
                        {
                                if (other.A()-90 < 0.0001)
                                {
                                        _a = other.c();
                                        _b = other.b();
                                        _c = other.a();
                                } else
                                if (other.B()-90 < 0.0001)
                                {
                                        _a = other.a();
                                        _b = other.c();
                                        _c = other.b();
                                } else
                                if (other.C()-90 < 0.0001)
                                {
                                        _a = other.a();
                                        _b = other.b();
                                        _c = other.c();
                                }
                        }
                        else
                                throw (std::runtime_error("Not a right triangle."));
                }
                return *this;
        }
 
        operator Triangle() const { return Triangle(_a, _b, _c); }
};
 
int main()
{
        srand(static_cast<unsigned int>(time(0)));
        int M = 10;
        int N = 10;
        std::vector<Triangle> T(M);
        std::vector<RightTriangle> R(N);
 
        std::cout << "Triangles: " << std::endl;
        double sum_of_areas = 0.;
        for (int i=0; i<T.size(); i++)
        {
                T[i] = Triangle((rand()%1000+500)/10., (rand()%1000+500)/10., (rand()%500+1)/10.);
                std::cout << T[i] << std::endl;
                sum_of_areas += T[i].area();
        }
        std::cout << "Average sum of areas: " << sum_of_areas/M << std::endl;
 
        int index = 0;
        std::cout << std::endl << "Right triangles: " << std::endl;
        for (int i=0; i<R.size(); i++)
        {
                R[i] = RightTriangle((rand()%1000+500)/10., (rand()%1000+500)/10.);
                std::cout << R[i] << std::endl;
                if (R[i].hypotenuse() > R[index].hypotenuse())
                        index = i;
        }
        std::cout << "Maximum hypotenuse has triangle number " << index << ": " << R[index].hypotenuse() << std::endl;
 
        return 0;
}
