#include "Product.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

namespace {
    const std::string PRODUCT_HEADER = "===== PRODUCT INFORMATION =====";
    const std::string PRODUCT_FOOTER = "===============================";
    const std::string DEFAULT_NAME = "Unknown";

    const std::string PRICE_NEGATIVE_ERROR = "Error: Price cannot be negative!";
    const std::string NAME_EMPTY_ERROR = "Error: Product name cannot be empty!";
    const std::string NAME_TOO_LONG_ERROR = "Error: Product name is too long (max 100 characters)!";
    const std::string SHELF_LIFE_NEGATIVE_ERROR = "Error: Shelf life cannot be negative!";

    const std::string MIX_NAME_PREFIX = "смесь ";
    const std::string MIX_NAME_INFIX = " и ";
    const std::string SELECT_NAME_PREFIX = "выбор ";
    const std::string SELECT_NAME_INFIX = " без ";
    const std::string PRESERVATIVE = "консервант Т1000";
}

bool Product::isValidName(const std::string& n) const {
    return !n.empty() && n.length() <= 100;
}

bool Product::isValidPrice(double p) const {
    return p >= 0.0;
}

bool Product::isValidShelfLife(int s) const {
    return s >= 0;
}

Product::Product()
    : name(DEFAULT_NAME), price(0.0), shelfLife(0) {
    std::cout << "Default constructor called\n";
}

Product::Product(const std::string& name, double price, int shelfLife,
    const std::vector<std::string>& composition)
    : composition(composition) {
    if (!setName(name))
        throw std::invalid_argument(NAME_EMPTY_ERROR); 
    if (!setPrice(price))
        throw std::invalid_argument(PRICE_NEGATIVE_ERROR);
    if (!setShelfLife(shelfLife))
        throw std::invalid_argument(SHELF_LIFE_NEGATIVE_ERROR);
    std::cout << "Full constructor called for: " << this->name << std::endl;
}

Product::Product(const Product& other)
    : name(other.name), price(other.price),
    shelfLife(other.shelfLife), composition(other.composition) {
    std::cout << "Copy constructor called for: " << name << std::endl;
}

Product::~Product() {
    composition.clear();  
    std::cout << "Destructor called for product: " << name << std::endl;
}

Product& Product::operator=(const Product& other) {
    if (this != &other) {
        name = other.name;
        price = other.price;
        shelfLife = other.shelfLife;
        composition = other.composition;
    }
    std::cout << "Copy assignment called for: " << name << std::endl;
    return *this;
}

std::string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
int Product::getShelfLife() const { return shelfLife; }
std::vector<std::string> Product::getComposition() const { return composition; }

bool Product::setName(const std::string& newName) {
    if (newName.empty()) {
        std::cerr << NAME_EMPTY_ERROR << std::endl;
        return false;
    }
    if (newName.length() > 100) {
        std::cerr << NAME_TOO_LONG_ERROR << std::endl;
        return false;
    }
    name = newName;
    return true;
}

bool Product::setPrice(double newPrice) {
    if (newPrice >= 0) {
        price = newPrice;
        return true;
    }
    std::cerr << PRICE_NEGATIVE_ERROR << std::endl;
    return false;
}

bool Product::setShelfLife(int newShelfLife) {
    if (newShelfLife >= 0) {
        shelfLife = newShelfLife;
        return true;
    }
    std::cerr << SHELF_LIFE_NEGATIVE_ERROR << std::endl;
    return false;
}

void Product::addIngredient(const std::string& ingredient) {
    composition.push_back(ingredient);
}

bool Product::removeIngredient(const std::string& ingredient) {
    auto it = std::find(composition.begin(), composition.end(), ingredient);
    if (it != composition.end()) {
        composition.erase(it);
        return true;
    }
    return false;
}

void Product::print() const {
    std::cout << "\n" << PRODUCT_HEADER << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << "\n";
    std::cout << "Shelf life: " << shelfLife << " days\n";
    std::cout << "Composition: ";
    if (composition.empty()) {
        std::cout << "(empty)";
    }
    else {
        for (size_t i = 0; i < composition.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << composition[i];
        }
    }
    std::cout << "\n" << PRODUCT_FOOTER << "\n" << std::endl;
}

Product Product::operator+(const Product& other) const {
    std::string newName = MIX_NAME_PREFIX + name + MIX_NAME_INFIX + other.name;

    double newPrice = (price + other.price) * 0.9;

    int newShelfLife = std::min(shelfLife, other.shelfLife);

    std::vector<std::string> newComposition = composition;
    for (const auto& ing : other.composition) {
        if (std::find(newComposition.begin(), newComposition.end(), ing) == newComposition.end()) {
            newComposition.push_back(ing);
        }
    }

    return Product(newName, newPrice, newShelfLife, newComposition);
}

Product Product::operator-(const Product& other) const {
    std::string newName = SELECT_NAME_PREFIX + name + SELECT_NAME_INFIX + other.name;

    double newPrice = price * 0.9;

    int newShelfLife = shelfLife - 2;
    if (newShelfLife < 0) newShelfLife = 0;

    std::vector<std::string> newComposition;
    for (const auto& ing : composition) {
        if (std::find(other.composition.begin(), other.composition.end(), ing) == other.composition.end()) {
            newComposition.push_back(ing);
        }
    }
    newComposition.push_back(PRESERVATIVE);

    return Product(newName, newPrice, newShelfLife, newComposition);
}

Product& Product::operator-=(const Product& other) {
    name = SELECT_NAME_PREFIX + name + SELECT_NAME_INFIX + other.name;

    price *= 0.9;

    shelfLife -= 2;
    if (shelfLife < 0) shelfLife = 0;

    std::vector<std::string> newComposition;
    for (const auto& ing : composition) {
        if (std::find(other.composition.begin(), other.composition.end(), ing) == other.composition.end()) {
            newComposition.push_back(ing);
        }
    }
    newComposition.push_back(PRESERVATIVE);
    composition = std::move(newComposition);

    return *this;
}