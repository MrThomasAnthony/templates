#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template <class T>
using ELEM = std::vector<T>;

template <class T>
using VEC = std::vector<ELEM<T>>;

template <class T>
using action_t = T (*) (int);

template <class T>
using pred_t = bool (*) (T);

template <class T>
using map_t = T (*) (T,T);

template <class T>
void printElem(ELEM<T> &v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i < v.size() - 1) std::cout << ",";
    }
    std::cout << "]";
}

template <class T>
void initVec(VEC<T> &v, ELEM<T> &&cons) {
    v.push_back(cons);
}

template <class T>
void printVec(VEC<T> &v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        printElem(v[i]);
        if (i < v.size() - 1) std::cout << ",";
    }
    std::cout << "]" << std::endl;
}

template <class T>
VEC<T> generate(int N, action_t<T> f) {
    VEC<T> result;
    for (T i = 1; i < N; ++i) {
        result.push_back(ELEM<T>{f(i)});
    }
    return result;
}

template <class T>
VEC<T> zip(VEC<T>& v, VEC<T>& w) {
    VEC<T> result;
    for (auto i = 0; i < v.size() && i < w.size(); ++i) {
        result.push_back({});
        for (auto j = 0; j < v[i].size() && j < w[i].size(); ++j) {
            result[i].push_back(v[i][j]);
            result[i].push_back(w[i][j]);
        }
    }
    return result;
}

template <class T>
VEC<T> filter(VEC<T>& v, pred_t<T> f) {
    VEC<T> result;
    for (auto& elem : v) {
        ELEM<T> temp;
        for (auto& val : elem) {
            if (f(val)) temp.push_back(val);
        }
        if (!temp.empty())
            result.push_back(temp);
    }
    return result;
}

template <class T>
VEC<T> map(VEC<T>& v, action_t<T> f) {
    VEC<T> result;
    for (auto& elem : v) {
        ELEM<T> temp;
        for (auto& val : elem) {
            temp.push_back(f(val));
            
        }
        result.push_back(temp); 
    }
    return result;
}

template <class T>
ELEM<T> reduce(VEC<T>& v, map_t<T> f, ELEM<T> ident) {
    ELEM<T> result = ident;
    for (auto& elem : v) {
        for (auto& val : elem) {
            result[0] = f(result[0], val);
        }
    }
    return result;
}

template<class T>
T k(T i, T j) {
    return i + j;
}

//Test functions
bool g(int x) {
    return x > 0;
}

int h(int x) {
    return x > 0 ? 1 : 0;
}

int f(int a) {
    return a * a;
}

int main() {
    VEC<int> v;
    initVec(v, ELEM<int>{1, 2, 3, 4});

    VEC<int> w;
    initVec(w, ELEM<int>{-1, 3, -3, 4});

    printVec(v);
    std::cout << std::string(10, '*') << std::endl;
    printVec(w);
    std::cout << std::string(10, '*') << std::endl;

    VEC<int> z = zip(v, w);
    printVec(z);
    std::cout << std::string(10, '*') << std::endl;

    VEC<int> x = zip(z, z);
    printVec(x);
    std::cout << std::string(10, '*') << std::endl;

    VEC<int> a = generate(10, f);
    printVec(a);

    VEC<int> y = filter(w, g);
    printVec(y);

    VEC<int> u = map(w, h);
    printVec(u);

    ELEM<int> e = reduce(u, k, ELEM<int>{0});
    printElem(e);

    std::cout << std::endl << std::string(10, '$') << std::endl;

    VEC<std::string> ws;
    initVec(ws, ELEM<std::string>{"hello", "there", "franco", "carlacci"});
    printVec(ws);

    ELEM<std::string> es = reduce(ws, k, ELEM<std::string>{""});
    printElem(es);

    VEC<char> wc;
    initVec(wc, ELEM<char>{'a', 'b', 'c', 'd'});
    std::cout << std::endl << std::string(10, '$') << std::endl;
    printVec(wc);

    ELEM<char> ec = reduce(wc, k, ELEM<char>{' '});
    std::cout << std::endl << std::string(10, '$') << std::endl;
    printElem(ec);

    return 0;
}
