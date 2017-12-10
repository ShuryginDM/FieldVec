/**
* Вывод всех неприводимых многочленов над кольцом вычетов из mod степени не выше n
*/
/*
* Пример использования библиотеки FieldVec.
* Строит все возможные неприводимые многочлены над кольцом вычетов из mod степени не выше n
* (при непростом mod делает throw NotPrimal{}. Поэтому можно сказать, что над полем вычетов из mod)
*/

#include <iostream>
#include "FieldVec.h"

int main(){

    unsigned int mod; /* Кольцо многочленов над кольцом вычетов из mod */
    std::cout << "enter module of residue field modulo" << std::endl;
    std:: cin >> mod;
    
    if(mod == 0 || mod == 1){
        std::cout << "cannot create with 0 or 1 element" << std::endl;
	return 0;
    }

    unsigned int n; /* Интересуют многочлены степени не выше n*/
    std::cout << "enter degree of a polynomial" << std::endl;
    std::cin >> n;

    if(mod == 2){/* BoolVec лучше оптимизирован. Поэтому при mod == 2 лучше использовать его*/

        std::vector<BoolVec> v;/* сюда записываются все неприводимые многочлены по модулю 2 степени не выше n*/
        BoolVec r; /* будет пробегать все многочлены от x до x ^ {n + 1} */
        bool b;  /* Показывает, были ли делители среди предыдущих неприводимых многочленов */
        BoolVec nl; /* Нулевой многочлен */ 
        r.push_back(true); /* минимальный из рассматриваемых многочленов - x*/

        while(r.size() - 1 <= n){ /** В r.size() учитывается также и свободный коэффициент */
            b = false;
            for(int i = 0; i < v.size(); i++){
                if(v[i].size() * 2 > n + 2){ /* достаточно просмотреть многочлены, степень квадрата которых не превышает данную*/
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

        for(int i = 0; i < v.size(); i++){
            v[i].tex_print(std::cout);
            std::cout << std::endl;
        }

        return 0;

    }

    FieldVec::q = mod;/* Необходимо инициализировать перед первой инициаоизацией объекта класса FieldVec */
    std::vector<FieldVec> v;/* сюда записываются все неприводимые многочлены по модулю mod степени не выше n*/
    FieldVec r; /* будет пробегать все многочлены от x до x ^ {n + 1} */
    bool b; /* Показывает, были ли делители среди предыдущих неприводимых многочленов */
    FieldVec nl; /* Нулевой многочлен */ 
    r.push_back(1); /* минимальный из рассматриваемых многочленов - x*/

    while(r.size() - 1 <= n){ /* В r.size() учитывается также и свободный коэффициент */
        b = false;
        for(int i = 0; i < v.size(); i++){
            if(v[i].size() * 2 > n + 2){ /* достаточно просмотреть многочлены, степень квадрата которых не превышает данную*/
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

    for(int i = 0; i < v.size(); i++){
        v[i].tex_print(std::cout);
        std::cout << std::endl;
    }
    return 0;
}
