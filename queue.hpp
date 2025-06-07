#include <array>
#include <iostream>
#include <stack>
using namespace std;

template <typename T, size_t MAX = 100>
class CircularQueue {
public:
    CircularQueue() : head_(0), tail_(0), count_(0) {}

    bool empty()  const { return count_ == 0; }
    bool full()   const { return count_ == MAX; }
    size_t size() const { return count_; }

    bool enqueue(const T& value) {
        if (full()) return false;
        data_[tail_] = value;
        tail_ = (tail_ + 1) % MAX;
        ++count_;
        return true;
    }

    bool dequeue(T& out) {
        if (empty()) return false;
        out = data_[head_];
        head_ = (head_ + 1) % MAX;
        --count_;
        return true;
    }

    void clear() { head_ = tail_ = count_ = 0; }

    void invert() {                      
        stack<T> aux;
        T tmp;
        while (dequeue(tmp)) aux.push(tmp);
        while (!aux.empty()) { enqueue(aux.top()); aux.pop(); }
    }

    void print() const {                
        for (size_t i = 0; i < count_; ++i) {
            size_t idx = (head_ + i) % MAX;
            cout << data_[idx] << ' ';
        }
        cout << '\n';
    }

private:
    array<T, MAX> data_;
    size_t head_, tail_, count_;
};
