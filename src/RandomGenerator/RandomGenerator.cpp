//
// Created by Евгений on 10.10.2022.
//

#include "RandomGenerator.h"

RandGenerator::RandGenerator(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    this->generator = std::default_random_engine(seed);
    this->distribution = std::uniform_real_distribution<double>(0,1);
}

double RandGenerator::getRandNumber() {
    return this->distribution(this->generator);
}