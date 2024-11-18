#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <numeric>
#include <algorithm>


template <class T>
using ELEM = std::vector<T>;

template <class T>
using VEC = std::vector<ELEM<T>>;

template <class T>
using action_t = T (*) (T);

template <class T>
using pred_t = bool (*) (T);

template <class T>
using map_t = T (*) (T, T);


template <class T>
void printElem(const ELEM<T> &v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i != v.size() - 1) std::cout << ", ";
    }
    std::cout << "]";
}

template <class T>
void initVec(VEC<T> &v, const ELEM<T> &cons) {
    v.push_back(cons);
}


template <class T>
void printVec(const VEC<T> &v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        printElem(v[i]);
        if (i != v.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

template <class T>
VEC<T> generate(int N, action_t<T> f) {
    VEC<T> vec;
    for (int i = 0; i < N; ++i) {
        ELEM<T> elem;
        elem.push_back(f(i));
        vec.push_back(elem);
    }
    return vec;
}



template <class T>
VEC<T> zip(const VEC<T>& v, const VEC<T>& w) {
    VEC<T> result;
    size_t rows = std::min(v.size(), w.size());
    for (size_t i = 0; i < rows; ++i) {
        ELEM<T> row;
        size_t cols = std::min(v[i].size(), w[i].size());
        for (size_t j = 0; j < cols; ++j) {
            row.push_back(v[i][j]);
            row.push_back(w[i][j]);
        }
        result.push_back(row);
    }
    return result;
}

template <class T>
VEC<T> filter(const VEC<T> &v, pred_t<T> f) {
    VEC<T> result;
    for (const auto &row : v) {
        if (f(row[0])) {
            result.push_back(row);
        }
    }
    return result;
}

template <class T>
VEC<T> map(const VEC<T> &v, action_t<T> f) {
    VEC<T> result;
    for (const auto &row : v) {
        ELEM<T> mappedRow;
        mappedRow.push_back(f(row[0]));
        result.push_back(mappedRow);
    }
    return result;
}

template <class T, class Callable>
ELEM<T> reduce(const VEC<T> &v, Callable f, ELEM<T> ident) { 
    for (const auto &row : v) {
        ident[0] = f(ident[0], row[0]);
    }
    return ident;
}


int square(int x) { return x * x; }
bool isPositive(int x) { return x > 0; }
int add(int a, int b) { return a + b; }
int toBinary(int x) { return x >= 0 ? 1 : 0; }

std::string concat(const std::string &a, const std::string &b) {
    return a + b;
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
    VEC<int> a = generate(10, square);
    printVec(a);

    VEC<int> y = filter(w, isPositive);
    printVec(y);

    VEC<int> u = map(w, toBinary);
    printVec(u);

    ELEM<int> e = reduce(u, add, ELEM<int>{0});
    printElem(e);

    std::cout << std::endl << std::string(10, '$') << std::endl;
    VEC<std::string> ws;
    initVec(ws, ELEM<std::string>{"hello", "there", "franco", "carlacci"});
    printVec(ws);

    ELEM<std::string> es = reduce(ws, concat, ELEM<std::string>{""});
    printElem(es);

    VEC<char> wc;
    initVec(wc, ELEM<char>{'a', 'b', 'c', 'd'});
    std::cout << std::endl << std::string(10, '$') << std::endl;
    printVec(wc);

    ELEM<char> ec = reduce(wc, [](char a, char b) { return a > b ? a : b; }, ELEM<char>{' '});
    std::cout << std::endl << std::string(10, '$') << std::endl;
    printElem(ec);

    return 0;
}
