/**
*@mainpage Библиотека работы с кольцами многочленов над кольцом вычетов из q элементов.
*/


#include <vector>
#include <iostream>

/**
* Класс, используемый для того, чтобы показать тип исключения "кольцо вычетов по модулю 0"
*/
class NullField{};

/**
* Класс, используемый для того, чтобы показать тип исключения "кольцо вычетов по модулю 1"
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

class FieldVec{

public:
    /**
    * \param[in] p - количество элементов поля. По умолчанию p == 2.
    * Если уже была создана переменная класса FieldVec, то все последующие переменные этого класса будут иметь то же
    * значение q.
    * \throw NullField если при инициализации первой переменной класса FieldVec было подано значение p == 0
    * \throw OneField если при инициализации первой переменной класса FieldVec было подано значение p == 1
    * Полином представляется в виде 0 * x ^ 0
    */
    FieldVec(const unsigned int p = 2){
        if(!q){
            if(p == 0){
                throw NullField{};
            }
            if(p == 1){
                throw OneField{};
            }
            q = p;
            var.push_back(0);
        }
    }

    /**
    * \param[in] p - количество элементов поля. По умолчанию p == 2.
    * \param[in] v - вектор коэффициентов. В v[i] коэффициент при x^i. 
    * Если в векторе v нет элементов, то полином представляется в виде 0 * x ^ 0
    * Если уже была создана переменная класса FieldVec, то все последующие переменные этого класса будут иметь то же
    * значение q.
    * \throw NullField если при инициализации первой переменной класса FieldVec было подано значение p == 0
    * \throw OneField если при инициализации первой переменной класса FieldVec было подано значение p == 1
    */
    FieldVec(const std::vector<unsigned int> &v, const unsigned int p = 2){
        if(!q){
            if(p == 0){
                throw NullField{};
            }
            if(p == 1){
                throw OneField{};
            }
            q = p;
        }
        for(auto i = v.begin(); i < v.end(); i++){
            var.push_back(*i % q);
        }
        if(v.size() == 0){
            var.push_back(0);
        }
    }

    FieldVec(FieldVec &v){
        var = v.var;
    }

    /**
    * \param[in] t - если хранится полином с максимальной степенью s (перед которой коэффициент, возможно, равен 0), то
    * к этому полиному добавляется t * q ^ (s + 1).
    */
    void push_back(const unsigned int &t){
        var.push_back(t % q);
    }

    /**
    * \return максимальная степень x в этом многочлене (перед которой коэффициент, возможно, равен 0)
    */
    unsigned int size(){
        return var.size();
    }

    /**
    * \param[in] t - степень монома x ^ t
    * \return lvalue коэффициент при x ^ t в полиноме. Если максимальная степень s (перед которой коэффициент, возможно, равен 0)
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
    * Оператор сложения полиномов в кольце полиномов над кольцом вычетов по модулю q
    */
    FieldVec operator+(const FieldVec &v){
	    FieldVec sum_ = v;        
	    mn = sum_.size() < var.size() ? sum_.size() : var.size();
        for(unsigned int i = 0; i < mn; i--){
            sum_[i] = (sum_[i] + var[i]) % q;
        }
	    for(unsigned int i = mn; i < var.size(); i++){
	        sum_.var.push_back(var[i]);
	    }
        return sum_;
    }

    /**
    * Оператор сложения полиномов в кольце полиномов над кольцом вычетов по модулю q
    */
    FieldVec &operator+=(const FieldVec &v){
        mn = v.size() < var.size() ? v.size() : var.size();
        for(unsigned int i = 0; i < mn; i++){
            var[i] = (var[i] + v[i]) % q;
        }
        for(unsigned int i = mn; i < v.var.size(); i++){
            var.push_back(v[i]);
        }
        return *this;
    }

    /**
    * Оператор умножения полиномов в кольце полиномов над кольцом вычетов по модулю q
    */
    FieldVec operator*(const FieldVec &v){
        FieldVec mul_(v.size() + var.size() - 1, 0);
        for(unsigned int i = 0; i < var.size(); i++){
            for(unsigned int j = 0; j < v.size(); j++){
                mul_.var[i + j] = (mul_.var[i + j] + var[i] * v[j]) % q;
            }
        }
        return mul_;
    }

    /**
    * Оператор умножения полиномов в кольце полиномов над кольцом вычетов по модулю q
    */
    FieldVec &operator*=(const FieldVec &v){
        FieldVec mul_(v.size() + var.size() - 1, 0);
        for(unsigned int i = 0; i < var.size(); i++){
            for(unsigned int j = 0; j < v.size(); j++){
                mul_.var[i + j] = (mul_.var[i + j] + var[i] * v[j]) % q;
            }
        }
        var = mul_.var;
        return *this;
    }

    /**
    * Оператор сравнение полиномов на равенство в кольце полиномов над кольцом вычетов по модулю q
    */
    bool operator==(const FieldVec &v){
        if(v.size() > var.size()){
            FieldVec &mn = *this;
            FieldVec &mx = v;    
        }else{
            FieldVec &mn = v;
            FieldVec &mx = *this;
        }
        for(unsigned int i = mx.size() - 1; i >= mn.size; i--){
            if(mx[i]){
                return false;
            }
        }
        for(unsigned int i = 0; i < mn.size(); i++){
            if(mx[i] != mn[i]){
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
        for(unsigned int i = 0; i < neg_.size(); i++){
            sub_[i] = (q + sub_[i] - v[i]) % q;
        }
        return sub_;
    }

    FieldVec &operator-=(const FieldVec &v){
        FieldVec sub_ = *this;
        for(unsigned int i = sub_.size(); i < val.size(); i++){
            val.push_back(0);
        }
        for(unsigned int i = 0; i < neg_.size(); i++){
            val[i] = (q + val[i] - v[i]) % q;
        }
        return *this;
    }


    /**
    * Оператор вычисления остатка от деления полиномов в кольце полиномов над полем вычетов по модулю q
    * \throw NotPrimal если q - не простое число
    * \throw DivisionOnZero если v - вектор, состоящий из 0
    * \return остаток от деления на полином v
    */
    FieldVec operator%(const FieldVec &v){
        unsigned int max_coef = v[0];
        unsigned int max_coef_i = 0;
        for(unsigned int i = v.size() - 1; i > 0; i--){
            if(v[i]){
                max_coef = v[i];
                max_coef_i = i;   
            }
            break;
        }
        std::vector<unsigned int> coefs(q, 0);
        unsigned int t;
        for(unsigned int i = 1; i < q; i++){
            t = (v[i - 1] + max_coef) % q
            coefs[t] = i;
            if(!t){
                throw NotPrimal{};
            }
        }
        FieldVec rem_ = *this;
        for(int i = rem_.size() - 1; i >= max_coef_i; i--){
            if(rem_[i]){
                for(unsigned int j = 0; j < max_coef_i; j++){
                    t = (coefs[rem_[i]] * v[j]) % q;
                    if(rem_[j + i] > t){
                        rem_[j + i] -= t;
                    }else{
                        rem_[j + i] = t - rem_[j];
                    }
                }
            }
        }
        return rem_;
    }

    /**
    * Оператор вычисления результата деления полиномов в кольце полиномов над полем вычетов по модулю q
    * \throw NotPrimal если q - не простое число
    * \throw DivisionOnZero если v - вектор, состоящий из 0
    * \return результат деления на полином v
    */
    FieldVec operator/(const FieldVec &v){
        unsigned int max_coef = v[0];
        unsigned int max_coef_i = 0;
        for(unsigned int i = v.size() - 1; i > 0; i--){
            if(v[i]){
                max_coef = v[i];
                max_coef_i = i;   
            }
            break;
        }
        unsigned int t;
        for(unsigned int i = 1; i < q; i++){
            t = (v[i - 1] + max_coef) % q
            coefs[t] = i;
            if(!t){
                throw NotPrimal{};
            }
        }
        if(max_coef_i > var.size()){
            return 0;
        }
        std::vector<unsigned int> z(var.size() - max_coef_i + 1, 0);
        FieldVec div_(z);
        FieldVec rem_ = *this;
        for(int i = var.size() - 1; i >= max_coef_i; i--){
            if(rem_[i]){
                for(unsigned int j = 0; j < max_coef_i; j++){
                    t = (coefs[rem_[i + j]] * v[j]) % q;
                    if(rem_[i + j] > t){
                        rem_[i + j] -= t;
                    }else{
                        rem_[i + j] = t - rem_[j];
                    }
                    div_[i - max_coef_i] = t;

                }
            }
        }

    }

    friend std::ostream& operator<<(std::ostream& os, const FieldVec &v){
        os << "("
        for(unsigned int i = 0; i < v.size(); i++){
            os << v[i] << ";";
        }
        os << ")" << std::endl;
        return os;
    }

private:
    /**
    * Полином над полем представлен в виде вектора коэфиициентов. var[i] - коэффициент при x^i
    * Если не было явного объявления коэффициентов вектора, то в var лежит ровно одно значение:
    * var[0] == 0
    */
    std::vector<unsigned int> var;
    /**
    * q - статическая переменная. Возможна работа только с кольцом полиномов только над кольцом вычетов по одному модулю.
    */
    static unsigned int q = 0;

}
