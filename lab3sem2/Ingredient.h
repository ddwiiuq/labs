#ifndef INGREDIENT_HPP
#define INGREDIENT_HPP

#include <string>

struct Ingredient {
    std::string name;
    double volume;

    Ingredient() : name(""), volume(0.0) {}
    Ingredient(const std::string& name, double volume) : name(name), volume(volume) {}
};

#endif