/*
* Задание 3.5 отсюда: http://mk.cs.msu.ru/images/d/d4/Ivdm-sem3.pdf
*/
/* 
* Является ли кольцо F_q[x]/(f) полем, если
* 1) q = 2; f(x) = x^3 + x + 1
* 2) q = 2; f(x) = x^4 + x + 1
* 3) q = 3; f(x) = x^3 + 2x + 1
* 4) q = 3; f(x) = x^4 + x + 2
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



/*задача 1)*/
void f1(){
    std::cout << "task 1)" << std::endl;

    BoolVec f(11);/*f == x^3 + x + 1*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl;
    bool b = is_primal(f);
    if(b){std::cout << "f(x) is primal" << std::endl;}
}

/*задача 2)*/
void f2(){
    std::cout << "task 2)" << std::endl;

    BoolVec f(19);/*f == x^4 + x + 1*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl;
    bool b = is_primal(f);
    if(b){std::cout << "f(x) is primal" << std::endl;}
}

/*задача 3)*/
void f3(){
    std::cout << "task 3)" << std::endl;
    FieldVec::q = 3;
    FieldVec f(34);/*f == x^3 + 2x + 1*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl;
    bool b = is_primal(f);
    if(b){std::cout << "f(x) is primal" << std::endl;}
}

/*задача 4)*/
void f4(){
    std::cout << "task 4)" << std::endl;
    FieldVec::q = 3;
    FieldVec f(86);/*f == x^4 + x + 2*/

    std::cout << "f(x) = ";
    f.tex_print();
    std::cout << std::endl;
    bool b = is_primal(f);
    if(b){std::cout << "f(x) is primal" << std::endl;}
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
    return 0;
}