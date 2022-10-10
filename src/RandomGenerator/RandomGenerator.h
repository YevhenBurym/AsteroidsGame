//
// Created by Евгений on 10.10.2022.
//

#pragma once
#include <random>
#include <chrono>

class RandGenerator {
private:
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution;
public:
    RandGenerator();
    double getRandNumber();
};
