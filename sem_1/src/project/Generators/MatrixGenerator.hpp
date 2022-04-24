//
// Created by Карим Вафин on 14.04.2022.
//

#ifndef MY_PROJECT_MATRIXGENERATOR_HPP
#define MY_PROJECT_MATRIXGENERATOR_HPP

#include "project/utility/Triplet.hpp"
#include <set>
#include <chrono>
#include <random>
#include <exception>
#include <stdexcept>

std::default_random_engine r_engine = std::default_random_engine(std::chrono::steady_clock::now().time_since_epoch().count());

int getRandomInt(int min, int max) {
    if (min > max)
        throw std::invalid_argument("MIN/MAX MISMATCH IN getRandomInt");
    std::uniform_int_distribution<int> d(min, max);
    return d(r_engine);
}

double getRandomDouble(double min, double max) {
    if (min > max)
        throw std::invalid_argument("MIN/MAX MISMATCH IN getRandomDouble");
    std::uniform_real_distribution<double> d(min, max);
    return d(r_engine);
}


template<typename T>
std::set<Triplet<T>> GenerateMatrix(const size_t& size, const T &a, const T &b){
    std::set<Triplet<T>> out;
    for(size_t i = 0; i < size; ++i){
        for(size_t j = 0; j < size; ++j){
            out.insert({i, j, static_cast<T>(getRandomDouble(a, b))});
        }
    }
    return out;
}

#endif //MY_PROJECT_MATRIXGENERATOR_HPP
