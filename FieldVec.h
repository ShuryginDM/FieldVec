/**
*@mainpage Библиотека работы с кольцом многочленов над кольцом вычетов из q элементов.
*@author Шурыгин Дмитрий Михайлович, 318 ВМК МГУ, 2017
*/


#include <vector>
#include <iostream>

/**
* Класс, используемый для того, чтобы показать тип исключения "кольцо вычетов по модулю 0"
*/
class NullField{};

/**
* OneField - Класс, используемый для того, чтобы показать тип исключения "кольцо вычетов по модулю 1"
*/
class OneField{};

/**
* Класс, используемый для того, чтобы показать тип исключения "не является полем вычетом"
*/
class NotPrimal{};

/**
* Класс, используемый для того, чтобы показать тип исключения "деление на 0"
*/
class DivisionOnZero{};


/**
* Основной класс. Реализует работу с кольцом многочленов над кольцом вычетов из q элементов
*/
class FieldVec{

public:

    /**
    * @var q статическая переменная. Возможна работа только с кольцом полиномов только над кольцом вычетов по одному модулю.
    * В начале программы явным образом должно быть прописано 
    * FieldVec::q = <Количество элементов кольца вычетов>; (без <>)
    * Программа может некорректно обрабатывать старые векторы при изменении q
    */
    static unsigned int q;
    
    /**
    * @function FieldVec(void) Конструктор. При таком создании полином представляется в виде 0 * x ^ 0
    * @throw NullField если при инициализации первой переменной класса FieldVec было подано значение p == 0
    * @throw OneField если при инициализации первой переменной класса FieldVec было подано значение p == 1
    */
    FieldVec(void){
        if(q == 0){
            throw NullField{};
        }
        if(q == 1){
            throw OneField{};
        }
        var.push_back(0);
    }

    /**
    * @function FieldVec(std::vector<unsigned int> v) Конструктор. Если в векторе v нет элементов, то полином представляется в виде 0 * x ^ 0,
    * иначе - коэффициентом при x^i будет v[i] 
    * @param[in] v Вектор коэффициентов. В v[i] коэффициент при x^i.
    * @throw NullField Если при инициализации первой переменной класса FieldVec было подано значение p == 0
    * @throw OneField Если при инициализации первой переменной класса FieldVec было подано значение p == 1
    */
    FieldVec(std::vector<unsigned int> &v){
        if(q == 0){
            throw NullField{};
        }
        if(q == 1){
            throw OneField{};
        }
        for(auto i = v.begin(); i < v.end(); i++){
            var.push_back(*i % q);
        }
        if(v.size() == 0){
            var.push_back(0);
        }
    }


    FieldVec(FieldVec const &v){
        var = v.var;
    }

    /**
    * @function push_back(unsigned int t) Функция расширения вектора коэффициентов полинома.
    * @param[in] t Если хранится полином с максимальной степенью s (перед которой коэффициент, возможно, равен 0), то
    * к этому полиному добавляется t * q ^ (s + 1).
    */
    void push_back(const unsigned int &t){
        var.push_back(t % q);
    }

    /**
    * @function size Показывает, сколько элементов находится в векторе коэффициентов
    * @return Максимальная степень x в этом многочлене (перед которой коэффициент, возможно, равен 0)
    */
    int size() const{
        return var.size();
    }

    /**
    * @param[in] t Степень монома x ^ t
    * @return lvalue коэффициент при x ^ t в полиноме. Если максимальная степень s (перед которой коэффициент, возможно, равен 0)
    *и s < t, то максимальная степень становиться равна t, а кожффициент при ней - 0.
    */
    unsigned int &operator[](const unsigned int &t){
        if(t > var.size()){
            for(unsigned int i = var.size(); i <= t; i++){
                var.push_back(0);
            }
        }
        return var[t];
    }

    /**
    * @function operator+ Оператор сложения полиномов в кольце полиномов над кольцом вычетов по модулю q
    */
    FieldVec operator+(const FieldVec &v){
	    FieldVec sum_ = v;      
	    unsigned int mn = sum_.size() < var.size() ? sum_.size() : var.size();
        for(unsigned int i = 0; i < mn; i++){
            sum_[i] = (sum_[i] + var[i]) % q;
        }
	    for(unsigned int i = mn; i < var.size(); i++){
	        sum_.var.push_back(var[i]);
	    }
        return sum_;
    }

    /**
    * @function operator+= Оператор сложения полиномов в кольце полиномов над кольцом вычетов по модулю q
    */
    FieldVec &operator+=(const FieldVec &v){
        unsigned int mn = v.size() < var.size() ? v.size() : var.size();
        for(unsigned int i = 0; i < mn; i++){
            var[i] = (var[i] + v.var[i]) % q;
        }
        for(unsigned int i = mn; i < v.var.size(); i++){
            var.push_back(v.var[i]);
        }
        return *this;
    }

    /**
    * @function operator* Оператор умножения полиномов в кольце полиномов над кольцом вычетов по модулю q
    */
    FieldVec operator*(const FieldVec &v){
        std::vector<unsigned int> z(v.size() + var.size() - 1, 0);
        FieldVec mul_(z);
        for(unsigned int i = 0; i < var.size(); i++){
            for(unsigned int j = 0; j < v.size(); j++){
                mul_.var[i + j] = (mul_[i + j] + var[i] * v.var[j]) % q;
            }
        }
        return mul_;
    }

    /**
    * @function operator*= Оператор умножения полиномов в кольце полиномов над кольцом вычетов по модулю q
    */
    FieldVec &operator*=(const FieldVec &v){
        std::vector<unsigned int> z(v.size() + var.size() - 1, 0);
        FieldVec mul_(z);
        for(unsigned int i = 0; i < var.size(); i++){
            for(unsigned int j = 0; j < v.size(); j++){
                mul_.var[i + j] = (mul_.var[i + j] + var[i] * v.var[j]) % q;
            }
        }
        var = mul_.var;
        return *this;
    }

    /**
    * @function operator== Оператор сравнение полиномов на равенство в кольце полиномов над кольцом вычетов по модулю q
    */
    bool operator==(const FieldVec &v){
        const FieldVec *mn_i, *mx_i;
        if(v.size() > var.size()){
            mn_i = this;
            mx_i = &v;    
        }else{
            mn_i = &v;
            mx_i = this;
        }
        const FieldVec &mn = *mn_i, &mx = *mx_i;
        for(unsigned int i = mx.var.size() - 1; i >= mn.var.size(); i--){
            if(mx.var[i]){
                return false;
            }
        }
        for(unsigned int i = 0; i < mn.var.size(); i++){
            if(mx.var[i] != mn.var[i]){
                return false;
            }
        }
        return true;
    }


    FieldVec operator-(){
        FieldVec neg_ = *this;
        for(unsigned int i = 0; i < neg_.size(); i++){
            neg_[i] = (q - neg_[i]) % q;
        }
        return neg_;
    }

    FieldVec operator-(const FieldVec &v){
        FieldVec sub_ = *this;
        for(unsigned int i = sub_.size(); i < v.size(); i++){
            sub_.push_back(0);
        }
        for(unsigned int i = 0; i < sub_.size(); i++){
            sub_[i] = (q + sub_[i] - v.var[i]) % q;
        }
        return sub_;
    }

    FieldVec &operator-=(const FieldVec &v){
        FieldVec sub_ = *this;
        for(unsigned int i = sub_.size(); i < var.size(); i++){
            var.push_back(0);
        }
        for(unsigned int i = 0; i < var.size(); i++){
            var[i] = (q + var[i] - v.var[i]) % q;
        }
        return *this;
    }


    /**
    * @function operator% Оператор вычисления остатка от деления полиномов в кольце полиномов над полем вычетов по модулю q
    * @throw NotPrimal если q - не простое число
    * @throw DivisionOnZero если v - вектор, состоящий из 0
    * @return остаток от деления на полином v
    */
    FieldVec operator%(const FieldVec &v){
        unsigned int max_coef = v.var[0];
        unsigned int max_coef_i = 0;
        for(unsigned int i = v.size() - 1; i > 0; i--){
            if(v.var[i]){
                max_coef = v.var[i];
                max_coef_i = i; 
                break;  
            }
        }
        std::vector<unsigned int> coefs(q, 0);
        unsigned int t_prev = 0, t_next;
        for(unsigned int i = 1; i < q; i++){
            t_next = (t_prev + max_coef) % q;
            coefs[t_next] = i;
            t_prev = t_next;
            if(!t_next){
                throw NotPrimal{};
            }
        }
        FieldVec rem_ = *this;
        unsigned int t;
        for(int i = rem_.size() - 1; i >= max_coef_i; i--){
            if(rem_[i]){
                for(unsigned int j = 0; j <= max_coef_i; j++){
                    t = (coefs[rem_[i]] * v.var[j]) % q;
                    if(rem_[i - max_coef_i + j] > t){
                        rem_[i - max_coef_i + j] -= t;
                    }else{
                        rem_[i - max_coef_i + j] = (q + rem_[i - max_coef_i + j] - t) % q;
                    }
                }
            }
        }
        return rem_;
    }

    /**
    * @function operator/ Оператор вычисления результата деления полиномов в кольце полиномов над полем вычетов по модулю q
    * @throw NotPrimal если q - не простое число
    * @throw DivisionOnZero если v - вектор, состоящий из 0
    * @return результат деления на полином v
    */
    FieldVec operator/(FieldVec &v){
        unsigned int max_coef = v.var[0];
        unsigned int max_coef_i = 0;
        for(int i = v.size() - 1; i > 0; i--){
            if(v.var[i]){
                max_coef = v.var[i];
                max_coef_i = i;   
                break;
            }
        }
        std::vector<unsigned int> coefs(q, 0);
        unsigned int t_prev = 0, t_next;
        for(unsigned int i = 1; i < q; i++){
            t_next = (t_prev + max_coef) % q;
            coefs[t_next] = i;
            t_prev = t_next;
            if(!t_next){
                throw NotPrimal{};
            }
        }
        if(max_coef_i > var.size()){
            FieldVec nl;
            return nl;
        }
        std::vector<unsigned int> z(var.size() - max_coef_i, 0);
        FieldVec div_(z);
        FieldVec rem_ = *this;
        unsigned int t;
        for(int i = var.size() - 1; i >= max_coef_i; i--){
            if(rem_[i]){
                for(unsigned int j = 0; j <= max_coef_i; j++){
                    t = (coefs[rem_[i]] * v.var[j]) % q;
                    if(rem_[i - max_coef_i + j] > t){
                        rem_[i - max_coef_i + j] -= t;
                    }else{
                        rem_[i - max_coef_i + j] = (q + rem_[i - max_coef_i + j] - t) % q;
                    }
                    div_[i - max_coef_i] = t;

                }
            }
        }
        return div_;
    }

    friend std::ostream& operator<<(std::ostream& os, const FieldVec &v){
        os << "(";
        for(int i = 0; i < v.size() - 1; i++){
            os << v.var[i] << ";";
        }
        os << v.var[v.size() - 1];
        os << ")";
        return os;
    }

private:
    /**
    * @var var - вектор коэффициентов. var[i] - коэффициент при x^i
    * Если не было явного объявления коэффициентов вектора, то в var лежит ровно одно значение:
    * var[0] == 0
    */
    std::vector<unsigned int> var;
    
};

unsigned int FieldVec::q = 0;