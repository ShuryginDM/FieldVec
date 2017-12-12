/*
* Задание 3.4 отсюда: http://mk.cs.msu.ru/images/d/d4/Ivdm-sem3.pdf
*/
/* 
* Найти все неприводимые многочлены f(x) = a_0 + a_1 * x + ... + a_{n-1} * x^{n-1} + x^n над F_q[x]
* 1) q = 2; n = 2
* 2) q = 2; n = 3
* 3) q = 2; n = 4; a_0 = 1
* 4) q = 2; n = 4; a_3 = 0
* 5) q = 3; n = 2
* 6) q = 3; n = 3; a_0 = 1
* 7) q = 5; n = 2; a_1 = 1
* 8) q = 5; n = 2; a_0 = 2
*/

#include "FieldVec.h"

void all_primal(int q, int n, bool additional = false, int index = 0, int val = 0){
    if(q == 2){
        std::vector<BoolVec> v;
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
                if(r.size() == n + 1 && (!additional || r[index] == val)){
                    r.tex_print();
                    std::cout << std::endl;
                }
            }
            r++;
        }
        return;
    }
    FieldVec::q = q;
    std::vector<FieldVec> v;
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
            if(r.size() == n + 1 && (!additional || r[index] == val)){
                r.tex_print();
                std::cout << std::endl;
            }
        }
        r++;
    }
}

/*задача 1)*/
void f1(){
    std::cout << "task 1)" << std::endl;

    all_primal(2, 2);
}

/*задача 2)*/
void f2(){
    std::cout << "task 2)" << std::endl;

    all_primal(2, 3);
}

/*задача 3)*/
void f3(){
    std::cout << "task 3)" << std::endl;

    all_primal(2, 4, true, 0, 1);
}

/*задача 4)*/
void f4(){
    std::cout << "task 4)" << std::endl;

    all_primal(2, 4, true, 3, 0);
}

/*задача 5)*/
void f5(){
    std::cout << "task 5)" << std::endl;
    
    all_primal(3, 2);
}

/*задача 6)*/
void f6(){
    std::cout << "task 6)" << std::endl;
    
    all_primal(3, 3, true, 0, 1);
}

/*задача 7)*/
void f7(){
    std::cout << "task 7)" << std::endl;
    
    all_primal(5, 2, true, 1, 1);
}

/*задача 8)*/
void f8(){
    std::cout << "task 8)" << std::endl;
    
    all_primal(5, 2, true, 0, 2);
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
    return 0;
}
