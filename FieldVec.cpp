#include "FieldVec.h"

unsigned int FieldVec::q = 0;

FieldVec::FieldVec(void){
    if(q == 0){
        throw NullField{};
    }
    if(q == 1){
        throw OneField{};
    }
    var.push_back(0);
}

FieldVec::FieldVec(std::vector<unsigned int> &v){
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


FieldVec::FieldVec(FieldVec const &v){
    var = v.var;
}

int FieldVec::size() const{
    return var.size();
}

void FieldVec::push_back(const unsigned int &t){
        var.push_back(t % q);
    }

unsigned int &FieldVec::operator[](const unsigned int &t){
    if(t > var.size()){
        for(unsigned int i = var.size(); i <= t; i++){
            var.push_back(0);
        }
    }
    return var[t];
}

FieldVec FieldVec::operator+(const FieldVec &v){
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

FieldVec FieldVec::operator*(const FieldVec &v){
    std::vector<unsigned int> z(v.size() + var.size() - 1, 0);
    FieldVec mul_(z);
    for(unsigned int i = 0; i < var.size(); i++){
        for(unsigned int j = 0; j < v.size(); j++){
            mul_.var[i + j] = (mul_[i + j] + var[i] * v.var[j]) % q;
        }
    }
    return mul_;
}

FieldVec &FieldVec::operator*=(const FieldVec &v){
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

bool FieldVec::operator==(const FieldVec &v){
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


FieldVec FieldVec::operator-(){
    FieldVec neg_ = *this;
    for(unsigned int i = 0; i < neg_.size(); i++){
        neg_[i] = (q - neg_[i]) % q;
    }
    return neg_;
}

FieldVec FieldVec::operator-(const FieldVec &v){
    FieldVec sub_ = *this;
    for(unsigned int i = sub_.size(); i < v.size(); i++){
        sub_.push_back(0);
    }
    for(unsigned int i = 0; i < sub_.size(); i++){
        sub_[i] = (q + sub_[i] - v.var[i]) % q;
    }
    return sub_;
}

FieldVec &FieldVec::operator-=(const FieldVec &v){
    FieldVec sub_ = *this;
    for(unsigned int i = sub_.size(); i < var.size(); i++){
        var.push_back(0);
    }
    for(unsigned int i = 0; i < var.size(); i++){
        var[i] = (q + var[i] - v.var[i]) % q;
    }
    return *this;
}

FieldVec FieldVec::operator%(const FieldVec &v){
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

FieldVec FieldVec::operator/(FieldVec &v){
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

void FieldVec::tex_print(std::ostream &os, const char *name){
    bool not_zero = false;
    for(int i = this->size() - 1; i > 0; i--){
        if(!(var[i])){
            continue;
        }
        if(not_zero){
            os << "+ ";
        }else{
            not_zero = true;
        }
        if(var[i] != 1){
            os << var[i] << " ";
        }
        os << name << " ";
        if(i != 1){
            os << "^ { " << i << " } ";
        }
    }
    if(var[0]){
        if(not_zero){
            os << "+ ";
        }else{
            not_zero = true;
        }
        os << var[0];
    }
    if(!not_zero){
        os << "0";
    }
}