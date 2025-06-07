#pragma once
#include <array>
#include <iostream>
#include <type_traits>
using namespace std;

template <typename T, size_t MAX = 100>
class StaticStack {
public:
    StaticStack() : top_(0) {}

    bool empty()  const { 
        return top_ == 0; 
    }

    bool full()   const { 
        return top_ == MAX; 
    }

    size_t size() const { 
        return top_; 
    }

    bool push(const T& value) {
        if (full()) return false;
        data_[top_++] = value;
        return true;
    }

    bool pop(T& out) {
        if (empty()) return false;
        out = data_[--top_];
        return true;
    }

    bool peek(T& out) const {           
        if (empty()) return false;
        out = data_[top_-1];
        return true;
    }

    void clear() { top_ = 0; }

    void print() const {
        for (size_t i = top_; i-- > 0; )  
            cout << data_[i] << ' ';
        cout << '\n';
    }

    template <typename Pred>
    void remove_if(Pred pred) {
        StaticStack<T, MAX> aux;
        T tmp;
        while (pop(tmp)) {
            if (!pred(tmp)) aux.push(tmp);   
        }
        while (aux.pop(tmp)) push(tmp);
    }

    void remove_odds() {
        static_assert(std::is_integral_v<T>, "remove_odds só faz sentido para tipos inteiros");
        remove_if([](const T& v){
             return v % 2 != 0; 
            
        });
    }

    bool equals(const StaticStack& other) const {
        if (size() != other.size()) return false;
        for (size_t i = 0; i < top_; ++i)
            if (data_[i] != other.data_[i]) return false;
        return true;
    }

    bool append(StaticStack& other) {
        if (size() + other.size() > MAX) return false;
        StaticStack<T, MAX> aux;    
        T t;
        while (other.pop(t)) aux.push(t);
        while (aux.pop(t)) push(t);
        return true;
    }

private:
    array<T, MAX> data_;
    size_t top_;   
};
