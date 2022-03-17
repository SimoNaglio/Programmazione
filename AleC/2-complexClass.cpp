/* 
TO-DO:
    improve tests
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <stdexcept>
#include<string>

class Complex{
        double m_r;
        double m_i;
    public:
        explicit Complex(double x = 0., double y = 0.): m_r{x}, m_i{y} {}

        double real() const {return m_r;} //reading functions
        double imag() const {return m_i;}

        double real(double val){ //writing functions
            m_r = val;
            return m_r;
        }
        double imag(double val){
            m_i = val;
            return m_i;
        }
};

std::string cartesian(Complex z){ //returns polar coords in string "a + bi" form
    return std::to_string(z.real()) + " + " + std::to_string(z.imag()) + "i";
}

std::ostream& operator<< (std::ostream& os, const Complex& value) { //to print by just writing var name ("<< val"), allows doctest to print wrong values
    os << cartesian(value);
    return os;
}

bool operator==(Complex const& lhs, Complex const& rhs){ //equality operator
    return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
}

bool operator!=(Complex const& lhs, Complex const& rhs){ //inequality operator
    return !(lhs == rhs); //implemented w/ ==
}

Complex operator+=(Complex& lhs, Complex const& rhs){ 
    lhs.real(lhs.real() + rhs.real()); //writing function with reading functions in the parentheses
    lhs.imag(lhs.imag() + rhs.imag());
    return lhs;
}

Complex operator+(Complex const& lhs, Complex const& rhs){
    Complex result{lhs};
    result += rhs; //implemented in terms of +=; -,* and / are analogous
    return result;
}

Complex operator-(Complex const& rhs){ //unary minus: allows you to say "-z"
    Complex result{rhs};
    result.real(-rhs.real());
    result.imag(-rhs.imag());
    return result;
}

Complex operator-=(Complex& lhs, Complex const& rhs){
    lhs.real(lhs.real() - rhs.real());
    lhs.imag(lhs.imag() - rhs.imag());
    return lhs;
}

Complex operator-(Complex const& lhs, Complex const& rhs){ //subtraction
    Complex result{lhs};
    result -= rhs;
    return result;
}

Complex operator*=(Complex& lhs, Complex const& rhs){
    double lhsReal = lhs.real();
    lhs.real(lhs.real() * rhs.real() - lhs.imag() * rhs.imag());
    lhs.imag(lhsReal  * rhs.imag() + lhs.imag() * rhs.real());
    return lhs;
}

Complex operator*(Complex const& lhs, Complex const& rhs){
    Complex result{lhs};
    result *= rhs;
    return result;
}

double norm2(Complex const& z){
    return z.real() * z.real() + z.imag() * z.imag();
}

Complex operator/=(Complex& lhs, Complex const& rhs){
    if(norm2(rhs) == 0) {throw std::runtime_error{"Division by 0"};} //can't divide by 0!
    double rhsReal = rhs.real();
    lhs = lhs * Complex(rhs.real()/norm2(rhs), -(rhs.imag()/norm2(rhs)));
    return lhs;
}

Complex operator/(Complex const& lhs, Complex const& rhs){
    Complex result{lhs};
    result /= rhs; //if rhs==0, exception is thrown by /=
    return result;
}

Complex conj(Complex const& z){ //complex conjugate
    return Complex(z.real(), -z.imag());
}

//============= bunch of tests, probably need to extend them =============
TEST_CASE("Testing constructor"){
    Complex c1{1., 2.};
    Complex c2 = Complex(1., 2.);
    Complex c3{1.};
    Complex c4 = Complex(1.);
    Complex c5{};
}

 TEST_CASE("Testing =="){
    Complex test{1., 2.};
    CHECK(test == Complex(1., 2.));
    CHECK_FALSE(test == Complex(1., 0.));
}  

TEST_CASE("Testing !="){
    Complex test{1., 2.};
    CHECK(test != Complex(0., 2.));
    CHECK_FALSE(test != Complex(1.,2.));
}

TEST_CASE("Testing norm2"){
    Complex test{1., 2.};
    CHECK(norm2(test) == 5.);
    test = Complex(-1., 3.);
    CHECK(norm2(test) == 10.);
    test = Complex(1., -3.);
    CHECK(norm2(test) == 10.);
}

TEST_CASE("Testing +="){
    Complex test{1., 2.};
    test += Complex(0., 1.);
    CHECK(test == Complex(1., 3.));
    test += Complex(1., 0.);
    CHECK(test == Complex(2., 3.));
    test += Complex(2., 2.);
    CHECK(test == Complex(4., 5.));
}

TEST_CASE("Testing +"){
    Complex test{1., 2.};
    CHECK(test + Complex(0., 1.) == Complex(1., 3.));
    CHECK(Complex(0., 1.) + test == Complex(1., 3.));
    CHECK(test + Complex(1., 0.) == Complex(2., 2.));
    CHECK(Complex(1., 0.) + test == Complex(2., 2.));
    CHECK(test + Complex(1., 1.) == Complex(2., 3.));
    CHECK(Complex(1., 1.) + test == Complex(2., 3.));
}

TEST_CASE("Testing unary -"){
    Complex test{1., 2.};
    CHECK(-test == Complex(-1., -2.));
    test = Complex(-1., 2.);
    CHECK(-test == Complex(1., -2.));
    test = Complex(1., -2.);
    CHECK(-test == Complex(-1., 2.));
    CHECK(-(-test) == test); //why is this a problem if i pass by nonconst reference?
}

TEST_CASE("Testing -="){
    Complex test{1., 2.};
    test -= Complex(0., 1.);
    CHECK(test == Complex(1., 1.));
    test -= Complex(1., 0.);
    CHECK(test == Complex(0., 1.));
    test -= Complex(2., 2.);
    CHECK(test == Complex(-2., -1.));
}

TEST_CASE("Testing -"){
    Complex test{1., 2.};
    CHECK(test - Complex(0., 1.) == Complex(1., 1.));
    CHECK(Complex(0., 1.) - test == Complex(-1., -1.));
    CHECK(test - Complex(1., 0.) == Complex(0., 2.));
    CHECK(Complex(1., 0.) - test == Complex(0., -2.));
    CHECK(test - Complex(1., 1.) == Complex(0., 1.));
    CHECK(Complex(1., 1.) - test == Complex(0., -1.));
}

TEST_CASE("Testing *="){
    Complex test{1.,2.};
    test *= Complex(-3., 2.); 
    CHECK(test == Complex(-7., -4.));
    test *= Complex(0.2, -0.7);
    CHECK(test == Complex(-4.2, 4.1));
}

TEST_CASE("Testing *"){
    Complex test{1.,2.};
    CHECK(test * Complex(6., 7.7) == Complex(-9.4, 19.7));
}

TEST_CASE("Testing /="){
    Complex test{1., 2.};
    test /= Complex(2., -1.);
    CHECK(test == Complex(0., 1.));
    CHECK_THROWS((test /= Complex()));
}

TEST_CASE("Testing /"){
    Complex test{1., 2.};
    CHECK(test / Complex(2., -1.) == Complex(0., 1.));
    CHECK_THROWS(test / Complex() == Complex());
}

TEST_CASE("Testing conj") {
    Complex test{1., 2.};
    CHECK(conj(test) == Complex(1., -2.));
    CHECK(conj(conj(test)) == test);
}
