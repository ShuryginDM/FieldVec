/*
* Задание 3.1 отсюда: http://mk.cs.msu.ru/images/d/d4/Ivdm-sem3.pdf
*/
/* 
* Задание - поделить с остатком многочлен f(x) на многочлен g(x) при заданном q
* 1) q = 2; f(x) = x^3 + x + 1; g(x) = x + 1
* 2) q = 2; f(x) = x^4 + x^2 + x; g(x) = x^2 + x + 1
* 3) q = 2; f(x) = x^4 + 1; g(x) = x^2 + 1
* 4) q = 2; f(x) = x^5 + x^4 + x^2; g(x) = x^3 + x + 1
* 5) q = 3; f(x) = 2x^2 + x + 2; g(x) = x + 2
* 6) q = 3; f(x) = x^3 + 2x^2 + x + 2; g(x) = x^2 + 2
* 7) q = 5; f(x) = 4x^2 + 3x + 2; g(x) = 3x + 2
* 8) q = 5; f(x) = 3x^3 + 4x^2 + 2x + 1; g(x) = 2x^2 + 3
*/

#include "FieldVec.h"

/*задача 1)*/
void f1(){
    std::cout << "task 1)" << std::endl;

    BoolVec f(1);/*f == 1*/
    f.push_back(1);/*f == x + 1*/
    f.push_back(0);/*f == x + 1*/
    f.push_back(1);/*f == x^3 + x + 1*/

    BoolVec g(1);/*g == 1*/
    g.push_back(1);/*g == x + 1*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl << "g(x) = ";
    g.tex_print();
    std::cout << std::endl << "f(x) / g(x) = ";
    (f/g).tex_print();
    std::cout << std::endl << "f(x) % g(x) = ";
    (f % g).tex_print();
    std::cout << std::endl;
}

/*задача 2)*/
void f2(){
    std::cout << "task 2)" << std::endl;

    BoolVec f;/*f == 0*/
    f.push_back(1);/*f == x*/
    f.push_back(1);/*f == x^2*/
    f.push_back(0);/*f == x^2 + x*/
    f.push_back(1);/*f == x^4 + x^2 + x*/

    BoolVec g(1);/*g == 1*/
    g.push_back(1);/*g == x + 1*/
    g.push_back(1);/*g == x^2 + x + 1*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl << "g(x) = ";
    g.tex_print();
    std::cout << std::endl << "f(x) / g(x) = ";
    (f/g).tex_print();
    std::cout << std::endl << "f(x) % g(x) = ";
    (f % g).tex_print();
    std::cout << std::endl;
}

/*задача 3)*/
void f3(){
    std::cout << "task 3)" << std::endl;

    BoolVec f(17);/*f == x^4 + 1*/

    BoolVec g(5);/*g == x^2 + 1*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl << "g(x) = ";
    g.tex_print();
    std::cout << std::endl << "f(x) / g(x) = ";
    (f/g).tex_print();
    std::cout << std::endl << "f(x) % g(x) = ";
    (f % g).tex_print();
    std::cout << std::endl;
}

/*задача 4)*/
void f4(){
    std::cout << "task 4)" << std::endl;

    BoolVec f(52);/*f == x^5 + x^4 + x^2*/

    BoolVec g(11);/*g == x^3 + x + 1*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl << "g(x) = ";
    g.tex_print();
    std::cout << std::endl << "f(x) / g(x) = ";
    (f/g).tex_print();
    std::cout << std::endl << "f(x) % g(x) = ";
    (f % g).tex_print();
    std::cout << std::endl;
}

/*задача 5)*/
void f5(){
    std::cout << "task 5)" << std::endl;
    FieldVec::q = 3;
    BoolVec f(2);/*f == 2*/
    f.push_back(1);/*f == x + 2*/
    f.push_back(2);/*f == 2x^2 + x + 2*/

    BoolVec g(1);/*g == 1*/
    g.push_back(1);/*g == x + 1*/
    g.push_back(1);/*g == x^2 + x + 1*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl << "g(x) = ";
    g.tex_print();
    std::cout << std::endl << "f(x) / g(x) = ";
    (f/g).tex_print();
    std::cout << std::endl << "f(x) % g(x) = ";
    (f % g).tex_print();
    std::cout << std::endl;
}

/*задача 6)*/
void f6(){
    std::cout << "task 6)" << std::endl;
    FieldVec::q = 3;
    BoolVec f(2);/*f == 2*/
    f.push_back(1);/*f == x + 2*/
    f.push_back(2);/*f == 2x^2 + x + 2*/
    f.push_back(1);/*f == x^3 + 2x^2 + x + 2;*/

    BoolVec g(2);/*g == 2*/
    g.push_back(0);/*g == 2*/
    g.push_back(1);/*g == x^2 + 2*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl << "g(x) = ";
    g.tex_print();
    std::cout << std::endl << "f(x) / g(x) = ";
    (f/g).tex_print();
    std::cout << std::endl << "f(x) % g(x) = ";
    (f % g).tex_print();
    std::cout << std::endl;
}

/*задача 7)*/
void f7(){
    std::cout << "task 7)" << std::endl;
    FieldVec::q = 5;
    BoolVec f(2);/*f == 2*/
    f.push_back(3);/*f == 3x + 2*/
    f.push_back(4);/*f == 4x^2 + 3x + 2*/

    BoolVec g(2);/*g == 2*/
    g.push_back(3);/*g == 3x + 2*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl << "g(x) = ";
    g.tex_print();
    std::cout << std::endl << "f(x) / g(x) = ";
    (f/g).tex_print();
    std::cout << std::endl << "f(x) % g(x) = ";
    (f % g).tex_print();
    std::cout << std::endl;
}

/*задача 8)*/
void f8(){
    std::cout << "task 8)" << std::endl;
    FieldVec::q = 5;
    BoolVec f(1);/*f == 1*/
    f.push_back(2);/*f == 2x + 1*/
    f.push_back(4);/*f == 4x^2 + 2x + 1*/
    f.push_back(3);/*f == 3x^3 + 4x^2 + 2x + 1*/

    BoolVec g(3);/*g == 3*/
    g.push_back(0);/*g == 3*/
    g.push_back(2);/*g == 2x^2 + 3*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl << "g(x) = ";
    g.tex_print();
    std::cout << std::endl << "f(x) / g(x) = ";
    (f/g).tex_print();
    std::cout << std::endl << "f(x) % g(x) = ";
    (f % g).tex_print();
    std::cout << std::endl;
}

int main(){
    f1();
    std::cout << "_______________________________________________"  << std::endl;
    f2();
    std::cout << "_______________________________________________"  << std::endl;
    f3();
    std::cout << "_______________________________________________"  << std::endl;
    f4();
    std::cout << "_______________________________________________"  << std::endl;
    f5();
    std::cout << "_______________________________________________"  << std::endl;
    f6();
    std::cout << "_______________________________________________"  << std::endl;
    f7();
    std::cout << "_______________________________________________"  << std::endl;
    f8();
    std::cout << "_______________________________________________"  << std::endl;
}
