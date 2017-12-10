/**
* Задание 3.2 отсюда: http://mk.cs.msu.ru/images/d/d4/Ivdm-sem3.pdf
*/
/* 
* Задание - найти наибольший общий делитель f(x) и g(x) в F_q[x], если
* 1) q = 2; f(x) = x^4 + x^2 + 1; g(x) = x^2 + 1
* 2) q = 2; f(x) = x^6 + x^5 + x^4 + 1; g(x) = x^5 + x + 1
* 3) q = 2; f(x) = x^7 + 1; g(x) = x^5 + x^3 + x + 1
* 4) q = 3; f(x) = x^3 + 1; g(x) = 2x^2 + x + 1
* 5) q = 3; f(x) = x^4 + x^2 + x + 2; g(x) = x^2 + 2
* 6) q = 3; f(x) = x^8 + 2x^5 + x^3 + x^2 + 1; g(x) = 2x^6 + x^5 + 2x^3 + 2x^2 + 2
* 7) q = 5; f(x) = x^2 + 1; g(x) = x^2 + 4x + 3
* 8) q = 5; f(x) = x^3 + 4x + 1; g(x) = x^2 + x + 3
*/

#include "FieldVec.h"

BoolVec f_Euler(BoolVec f1, BoolVec f2){
    BoolVec VecNull;
    while(!(f2 % f1 == VecNull)){
        f1 = f2 % f1;
    }
    return f1;
}



/*задача 1)*/
void f1(){
    std::cout << "task 1)" << std::endl;

    BoolVec f(1);/*f == 1*/
    f.push_back(0);/*f == 0x + 1*/
    f.push_back(1);/*f == x^2 + 1*/
    f.push_back(0);/*f == 0x^3 + x^2 + 1*/
    f.push_back(1);/*f == x^4 + x^2 + 1*/

    BoolVec g(1);/*g == 1*/
    g.push_back(0);/*g == 0x + 1*/
    g.push_back(1);/*g == x^2 + 1*/

    std::cout << "f(x) = ";
    f.tex_print(std::cout);
    std::cout << std::endl << "g(x) = ";
    g.tex_print(std::cout);
    std::cout << std::endl << "gcd(f(x), g(x)) = ";
    (f_Euler(f, g)).tex_print(std::cout);
    std::cout << std::endl;
}

/*задача 2)*/
void f2(){
    std::cout << "task 2)" << std::endl;

    BoolVec f(113);/*f == x^6 + x^5 + x^4 + 1*/

    BoolVec g(35);/*g == x^5 + x + 1*/

    std::cout << "f(x) = ";
    f.tex_print(std::cout);
    std::cout << std::endl << "g(x) = ";
    g.tex_print(std::cout);
    std::cout << std::endl << "gcd(f(x), g(x)) = ";
    (f_Euler(f, g)).tex_print(std::cout);
    std::cout << std::endl;
}

int main(){
    f1();
    std::cout << "______________________________" << std::endl;
    f2();
    std::cout << "______________________________" << std::endl;
    return 0;
}