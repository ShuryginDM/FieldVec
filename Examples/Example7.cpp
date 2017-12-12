/*
* Задание 3.6 отсюда: http://mk.cs.msu.ru/images/d/d4/Ivdm-sem3.pdf
*/
/* 
* Найти сумму и произведение элементов [r1] и [r2] в фактор-кольце F_q[x]/(f)
* и выяснить, является ли это кольцо полем, если
* 1) q = 2; f(x) = x^3 + x^2 + 1; r1(x) = x^2; r2(x) = x + 1
* 2) q = 2, f(x) = x^4 + x^3 + 1; r1(x) = x^3 + x^2; r2(x) = x^3 + 1
* 3) q = 2; f(x) = x^5 + x^2 + 1; r1(x) = x^4 + x^2 + 1; r2(x) = x^3 + x + 1
* 4) q = 2; f(x) = x^5 + x^4 + x^3 + x + 1; r1(x) = x^4; r2(x) = x^3 + x^2 + x + 1
* 5) q = 3; f(x) = x^4 + x^2 + 1; r1(x) = x^2; r2(x) = x + 1
* 6) q = 3; f(x) = x^4 + x + 2; r1(x) = x^3 + 2x^2 + 1; r2(x) = x^2 + 2x
* 7) q = 5; f(x) = x^3 + x^2 + 2; r1(x) = x^2 + 4x + 3; r2(x) = 3x^2 + 2x + 1
* 8) q = 5; f(x) = x^3 + 3x + 2; r1(x) = x^2 + 3x + 4; r2(x) = x^2 + 2
*/

#include "FieldVec.h"

bool is_primal(BoolVec f1){
    std::vector<BoolVec> v;
    int n = f1.actual_size() / 2;
    BoolVec r;
    bool b;
    BoolVec nl;
    r.push_back(true);
    while(r.size() - 1 <= n){
        b = false;
            for(int i = 0; i < v.size(); i++){
                if(nl == (r % v[i])){
                    b = true;
                    break;
                }
            }
            if(!b){
                v.push_back(r);
            }
            r++;
    }
    for(auto i = v.begin(); i < v.end(); i++){
        if((f1 % *i) == nl){
            return false;
        }
    }
    return true;
}

bool is_primal(FieldVec f1){
    std::vector<FieldVec> v;
    int n = f1.actual_size() / 2;
    FieldVec r; 
    bool b; 
    FieldVec nl;
    r.push_back(1);

    while(r.size() - 1 <= n){ 
        if(r[r.size() - 1] != 1){ 
            r[r.size() - 1] = 0;
            r.push_back(1);
            continue;
        }
        b = false;
        for(int i = 0; i < v.size(); i++){
            if((v[i].size()) * 2 > r.size() + 2){ 
                break;
            }
            if(nl == (r % v[i])){
                b = true;
                break;
            }
        }
        if(!b){
            v.push_back(r);
        }
        r++;
    }
    for(auto i = v.begin(); i < v.end(); i++){
        if((f1 % *i) == nl){
            std::cout << "divider: ";
            i -> tex_print();
            std::cout << std::endl;
            return false;
        }
    }
    return true;
}

void f1(){
    std::cout << "task 1)" << std::endl;
    BoolVec f(13);/* f == x^3 + x^2 + 1*/
    BoolVec r1(4);/* r1(x) = x^2*/
    BoolVec r2(3);/* r2(x) = x + 1*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl << "r1(x) = ";
    r1.tex_print();
    std::cout << std::endl << "r2(x) = ";
    r2.tex_print();
    std::cout << std::endl;

    std::cout << "[r1 + r2] = ";
    (r1 + r2).tex_print();
    std::cout << std::endl;
    std::cout << "[r1 * r2] = ";
    ((r1 * r2) % f).tex_print();
    std::cout << std::endl;

    bool b = is_primal(f);
    std::cout << (b ? "f(x) is primal" : "f(x) is not primal") << std::endl;
}

void f2(){
    std::cout << "task 2)" << std::endl;
    BoolVec f(25);/* f == x^4 + x^3 + 1*/
    BoolVec r1(12);/* r1(x) = x^3 + x^2*/
    BoolVec r2(9);/* r2(x) = x^3 + 1*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl << "r1(x) = ";
    r1.tex_print();
    std::cout << std::endl << "r2(x) = ";
    r2.tex_print();
    std::cout << std::endl;

    std::cout << "[r1 + r2] = ";
    (r1 + r2).tex_print();
    std::cout << std::endl;
    std::cout << "[r1 * r2] = ";
    ((r1 * r2) % f).tex_print();
    std::cout << std::endl;

    bool b = is_primal(f);
    std::cout << (b ? "f(x) is primal" : "f(x) is not primal") << std::endl;
}


void f3(){
    std::cout << "task 3)" << std::endl;
    BoolVec f(37);/* f == x^5 + x^2 + 1*/
    BoolVec r1(21);/* r1(x) = x^4 + x^2 + 1*/
    BoolVec r2(11);/* r2(x) = x^3 + x + 1*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl << "r1(x) = ";
    r1.tex_print();
    std::cout << std::endl << "r2(x) = ";
    r2.tex_print();
    std::cout << std::endl;

    std::cout << "[r1 + r2] = ";
    (r1 + r2).tex_print();
    std::cout << std::endl;
    std::cout << "[r1 * r2] = ";
    ((r1 * r2) % f).tex_print();
    std::cout << std::endl;

    bool b = is_primal(f);
    std::cout << (b ? "f(x) is primal" : "f(x) is not primal") << std::endl;
}


void f4(){
    std::cout << "task 4)" << std::endl;
    BoolVec f(59);/* f == x^5 + x^4 + x^3 + x + 1*/
    BoolVec r1(16);/* r1(x) = x^4*/
    BoolVec r2(15);/* r2(x) = x^3 + x^2 + x + 1*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl << "r1(x) = ";
    r1.tex_print();
    std::cout << std::endl << "r2(x) = ";
    r2.tex_print();
    std::cout << std::endl;

    std::cout << "[r1 + r2] = ";
    (r1 + r2).tex_print();
    std::cout << std::endl;
    std::cout << "[r1 * r2] = ";
    ((r1 * r2) % f).tex_print();
    std::cout << std::endl;

    bool b = is_primal(f);
    std::cout << (b ? "f(x) is primal" : "f(x) is not primal") << std::endl;
}

void f5(){
    std::cout << "task 5)" << std::endl;
    FieldVec::q = 3;
    FieldVec f(91);/* f == x^4 + x^2 + 1*/
    FieldVec r1(9);/* r1(x) = x^2*/
    FieldVec r2(4);/* r2(x) = x + 1*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl << "r1(x) = ";
    r1.tex_print();
    std::cout << std::endl << "r2(x) = ";
    r2.tex_print();
    std::cout << std::endl;

    std::cout << "[r1 + r2] = ";
    (r1 + r2).tex_print();
    std::cout << std::endl;
    std::cout << "[r1 * r2] = ";
    ((r1 * r2) % f).tex_print();
    std::cout << std::endl;
    
    bool b = is_primal(f);
    std::cout << (b ? "f(x) is primal" : "f(x) is not primal") << std::endl;

}

void f6(){
    std::cout << "task 6)" << std::endl;
    FieldVec::q = 3;
    FieldVec f(86);/* f == x^4 + x + 2*/
    FieldVec r1(46);/* r1(x) = x^3 + 2x^2 + 1*/
    FieldVec r2(15);/* r2(x) = x^2 + 2x*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl << "r1(x) = ";
    r1.tex_print();
    std::cout << std::endl << "r2(x) = ";
    r2.tex_print();
    std::cout << std::endl;

    std::cout << "[r1 + r2] = ";
    (r1 + r2).tex_print();
    std::cout << std::endl;
    std::cout << "[r1 * r2] = ";
    ((r1 * r2) % f).tex_print();
    std::cout << std::endl;
    
    bool b = is_primal(f);
    std::cout << (b ? "f(x) is primal" : "f(x) is not primal") << std::endl;

}

void f7(){
    std::cout << "task 7)" << std::endl;
    FieldVec::q = 5;
    FieldVec f(152);/* f == x^3 + x^2 + 2*/
    FieldVec r1(48);/* r1(x) = x^2 + 4x + 3*/
    FieldVec r2(86);/* r2(x) = 3x^2 + 2x + 1*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl << "r1(x) = ";
    r1.tex_print();
    std::cout << std::endl << "r2(x) = ";
    r2.tex_print();
    std::cout << std::endl;

    std::cout << "[r1 + r2] = ";
    (r1 + r2).tex_print();
    std::cout << std::endl;
    std::cout << "[r1 * r2] = ";
    ((r1 * r2) % f).tex_print();
    std::cout << std::endl;
    
    bool b = is_primal(f);
    std::cout << (b ? "f(x) is primal" : "f(x) is not primal") << std::endl;

}

void f8(){
    std::cout << "task 8)" << std::endl;
    FieldVec::q = 5;
    FieldVec f(142);/* f == x^3 + 3x + 2*/
    FieldVec r1(44);/* r1(x) = x^2 + 3x + 4*/
    FieldVec r2(27);/* r2(x) = x^2 + 2*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl << "r1(x) = ";
    r1.tex_print();
    std::cout << std::endl << "r2(x) = ";
    r2.tex_print();
    std::cout << std::endl;

    std::cout << "[r1 + r2] = ";
    (r1 + r2).tex_print();
    std::cout << std::endl;
    std::cout << "[r1 * r2] = ";
    ((r1 * r2) % f).tex_print();
    std::cout << std::endl;
    
    bool b = is_primal(f);
    std::cout << (b ? "f(x) is primal" : "f(x) is not primal") << std::endl;

}

int main(){
    f1();
    std::cout << "______________________________" << std::endl;
    f2();
    std::cout << "______________________________" << std::endl;
    f3();
    std::cout << "______________________________" << std::endl;
    f4();
    std::cout << "______________________________" << std::endl;
    f5();
    std::cout << "______________________________" << std::endl;
    f6();
    std::cout << "______________________________" << std::endl;
    f7();
    std::cout << "______________________________" << std::endl;
    f8();
    std::cout << "______________________________" << std::endl;
}