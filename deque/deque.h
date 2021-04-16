#include <type_traits>
#include <vector>

template<typename T>
class Deque {
public:
    template<bool IsConst>
    class common_iterator {
    public:
        std::vector<T *> &data_;
        size_t index_;


        common_iterator(const size_t index, std::vector<T *> &data) : data_(data), index_(index) {
        }

        common_iterator(const common_iterator<false> &iterator) : data_(iterator.data_), index_(iterator.index_) {
        }

        template<bool IsConst2>
        common_iterator(const common_iterator<IsConst2> &iterator) : data_(iterator.data_), index_(iterator.index_) {
        }


        std::conditional_t<IsConst, const T &, T &> operator*(void) {
            return data_[index_ / length_][index_ % length_];
        }

        std::conditional_t<IsConst, const T *, T *> operator->(void) {
            return &data_[index_ / length_][index_ % length_];
        }

        common_iterator<IsConst> &operator++(void) {
            ++index_;
            return *this;
        }

        common_iterator<IsConst> &operator--(void) {
            --index_;
            return *this;
        }

        common_iterator operator+(int n) const {
            common_iterator<IsConst> iterator(index_ + n, data_);
            return iterator;
        }

        template<bool f>
        common_iterator<f> &operator=(const common_iterator<f> &iterator) {
            data_ = iterator.data_;
            index_ = iterator.index_;
            return *this;
        }

        common_iterator &operator=(const common_iterator<false> &it) {
            data_ = it.data_;
            index_ = it.index_;
            return *this;
        }

        common_iterator<IsConst> &operator-(int n) {
            index_ -= n;
            return *this;
        }

        bool operator==(const common_iterator<IsConst> &another) const {
            return index_ == another.index_;
        }

        bool operator!=(const common_iterator<IsConst> &another) const {
            return index_ != another.index_;
        }

        bool operator<(const common_iterator<IsConst> &another) const {
            return index_ < another.index_;
        }

        bool operator<=(const common_iterator<IsConst> &another) const {
            return index_ <= another.index_;
        }

        bool operator>(const common_iterator<IsConst> &another) const {
            return index_ > another.index_;
        }

        bool operator>=(const common_iterator<IsConst> &another) const {
            return index_ >= another.index_;
        }

        size_t operator-(const common_iterator<IsConst> &another) const {
            if (index_ > another.index_) {
                return index_ - another.index_;
            }
            if (index_ == another.index_) {
                return 0;
            }
            return -index_ + another.index_ + 1;
        }

        void operator+=(int n) {
            index_ += n;
        }


    };

    using iterator = common_iterator<false>;
    using const_iterator = common_iterator<true>;

private:
    const static size_t length_ = 20;
    std::vector<T *> data_;
    size_t capacity_;
    iterator start_, end_;

    void reserve_begin(size_t i);

public:
    /************
     * Constructors
     ************/

    Deque(void);

    Deque(const Deque &d);

    Deque(int n);

    Deque(int n, const T &val);

    /************
     * ez func
     ************/

    size_t size(void) const;

    T &operator[](size_t n);

    const T &operator[](size_t number) const;

    T &at(int n);

    const T &at(int n) const;


    Deque<T> &operator=(const Deque<T> &another);

    /************
     * hard func
     ************/

    void push_back(const T &val);

    void pop_back(void);

    void push_front(const T &val);

    void pop_front(void);

    void erase(iterator iterator);

    void insert(iterator it, const T &val);

    /************
     * iterators
     ************/

    iterator begin(void) {
        return start_;
    }

    const_iterator begin(void) const {
        return const_iterator(start_);
    }

    iterator end(void) {
        return end_;
    }

    const_iterator end(void) const {
        return const_iterator(end_);
    }

    const_iterator cbegin(void) const {
        return const_iterator(start_);
    }

    const_iterator cend(void) const {
        return const_iterator(end_);
    }
};

template<typename T>
void Deque<T>::reserve_begin(size_t i) {
//    bool f;
//    if (capacity_ == 0) {
//        f = true;
//    }
    std::vector<T *> new_data(capacity_ + i);

    for (size_t j = 0; j < i; ++j) {
        new_data[j] = reinterpret_cast<T *>(new int8_t[length_ * sizeof(T)]);
    }
    std::uninitialized_copy(data_.begin(), data_.end(), new_data.begin() + i); /// ??
    data_ = new_data;
    capacity_ += i;
    start_ += i * length_;
    end_ += i * length_;
//    if (f) {
//        --end_;
//    }
}

template<typename T>
Deque<T>::Deque(void) : start_(0, data_), end_(0, data_) {
    capacity_ = 0;
    reserve_begin(1);
    start_.index_ = 0;
    end_.index_ = 0;
}

template<typename T>
Deque<T>::Deque(const Deque &d) : start_(d.start_.index_, data_), end_(d.end_.index_, data_) {
    capacity_ = d.capacity_;
    data_.resize(capacity_);
    for (size_t i = 0; i < capacity_; ++i) {
        data_[i] = reinterpret_cast<T *>(new int8_t[length_ * sizeof(T)]);
        for (size_t j = 0; j < length_; ++j)
            data_[i][j] = d.data_[i][j];
    }
}

template<typename T>
Deque<T>::Deque(int n) : start_(0, data_), end_(n, data_) {
    capacity_ = n / length_ + 1;
    data_.resize(capacity_);
    for (size_t i = 0; i < capacity_; ++i) {
        data_[i] = reinterpret_cast<T *>(new int8_t[length_ * sizeof(T)]);
    }
}

template<typename T>
Deque<T>::Deque(int n, const T &val) : start_(0, data_), end_(n, data_) {
    capacity_ = n / length_ + 1;
    data_.resize(capacity_);
    for (size_t i = 0; i < capacity_; ++i) {
        data_[i] = reinterpret_cast<T *>(new int8_t[length_ * sizeof(T)]);
        for (size_t j = 0; j < length_; ++j) {
            new(data_[i] + j) T(val);
        }
    }
}

template<typename T>
size_t Deque<T>::size(void) const {
    return start_ - end_ - 1;
}

template<typename T>
T &Deque<T>::operator[](size_t n) {
    iterator it = start_ + n;
    return *it;
}

template<typename T>
const T &Deque<T>::operator[](size_t n) const {
    iterator it = start_ + n;
    return *it;
}

template<typename T>
T &Deque<T>::at(int n) {
    iterator iter(n, data_);
    if (iter >= end_ || iter < start_) {
        throw std::out_of_range("out of range");
    }
    return *(iterator(n, data_));
}

template<typename T>
const T &Deque<T>::at(int n) const {
    iterator iter(n, data_);

    if (iter >= end_ || iter < start_) {
        throw std::out_of_range("out of range");
    }

    // return *iter;
}

template<typename T>
Deque<T> &Deque<T>::operator=(const Deque<T> &another) {
    capacity_ = another.capacity_;
    data_.resize(capacity_);
    for (size_t i = 0; i < capacity_; ++i) {
        data_[i] = reinterpret_cast<T *>(new int8_t[length_ * sizeof(T)]);
        for (size_t j = 0; j < capacity_; ++j)
            data_[i][j] = another.data_[i][j];
    }
    start_ = another.start_;
    end_ = another.end_;
    return *this;
}

template<typename T>
void Deque<T>::push_back(const T &val) {
    if (end_.index_ % length_ == 0 && start_ != end_) {
        data_.push_back(reinterpret_cast<T *>(new int8_t[length_ * sizeof(T)]));
        new(data_[capacity_]) T(val);
        ++capacity_;
        ++end_;
    } else {
        new(end_.operator->()) T(val);
        ++end_;
    }
}

template<typename T>
void Deque<T>::pop_back(void) {
    --end_;
}

template<typename T>
void Deque<T>::push_front(const T &val) {
    if (start_.index_ == 0) {
        reserve_begin((capacity_ + 1) / 2);
    }
    if (size() != 0) {
        --start_;
    }
    new(start_.operator->()) T(val);
}

template<typename T>
void Deque<T>::pop_front(void) {
    ++start_;
}

template<typename T>
void Deque<T>::erase(Deque::iterator iterator) {
    for (Deque::iterator i = iterator; i != end() - 1; ++i) {
        std::swap(*i, *(i + 1));
    }
    pop_back();
}

template<typename T>
void Deque<T>::insert(Deque::iterator iterator, const T &val) {
    T elem = const_cast<T &>(val);

    while (iterator != end()) {
        /* swap over the end */
        T tmp = *iterator;
        *iterator = elem;
        elem = tmp;
        ++iterator;
    }
    push_back(elem);
}
