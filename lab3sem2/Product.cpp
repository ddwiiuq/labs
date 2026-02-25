#include "Product.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

namespace {
    const std::string PRODUCT_HEADER = "===== PRODUCT INFORMATION =====";
    const std::string PRODUCT_FOOTER = "===============================";
    const std::string DEFAULT_NAME = "Unknown";
    const std::string DEFAULT_DESCRIPTION = "No description";
    const std::string DEFAULT_LOCATION = "Warehouse";

    const std::string PRICE_NEGATIVE_ERROR = "Error: Price cannot be negative!";
    const std::string NAME_EMPTY_ERROR = "Error: Product name cannot be empty!";
    const std::string NAME_TOO_LONG_ERROR = "Error: Product name is too long (max 100 characters)!";
    const std::string DESCRIPTION_TOO_LONG_ERROR = "Error: Description is too long (max 500 characters)!";
    const std::string SHELF_LIFE_NEGATIVE_ERROR = "Error: Shelf life cannot be negative!";
    const std::string LOCATION_EMPTY_ERROR = "Error: Location cannot be empty!";
    const std::string LOCATION_TOO_LONG_ERROR = "Error: Location is too long (max 50 characters)!";
    const std::string PRODUCTION_DATE_NEGATIVE_ERROR = "Error: Production date cannot be negative!";
    const std::string REDUCE_DAYS_ERROR = "Error: Cannot reduce shelf life by negative days!";

    const std::string MIX_NAME_PREFIX = "смесь ";
    const std::string MIX_NAME_INFIX = " и ";
    const std::string SELECT_NAME_PREFIX = "выбор ";
    const std::string SELECT_NAME_INFIX = " без ";
    const std::string PRESERVATIVE = "консервант Т1000";
    const double PRESERVATIVE_VOLUME = 1.0;
}

bool Product::isValidName(const std::string& n) const {
    return !n.empty() && n.length() <= 100;
}

bool Product::isValidDescription(const std::string& d) const {
    return d.length() <= 500;
}

bool Product::isValidPrice(double p) const {
    return p >= 0.0;
}

bool Product::isValidShelfLife(int s) const {
    return s >= 0;
}

bool Product::isValidLocation(const std::string& loc) const {
    return !loc.empty() && loc.length() <= 50;
}

Product::Product()
    : name(DEFAULT_NAME), description(DEFAULT_DESCRIPTION), price(0.0),
    shelfLife(0), productionDate(0), location(DEFAULT_LOCATION) {
    std::cout << "Default constructor called\n";
}

Product::Product(const std::string& name, const std::string& description, double price,
    int shelfLife, int productionDate, const std::string& location,
    const std::vector<Ingredient>& ingredients)
    : ingredients(ingredients) {
    if (!setName(name))
        throw std::invalid_argument(NAME_EMPTY_ERROR);
    if (!setDescription(description))
        throw std::invalid_argument(DESCRIPTION_TOO_LONG_ERROR);
    if (!setPrice(price))
        throw std::invalid_argument(PRICE_NEGATIVE_ERROR);
    if (!setShelfLife(shelfLife))
        throw std::invalid_argument(SHELF_LIFE_NEGATIVE_ERROR);
    if (!setProductionDate(productionDate))
        throw std::invalid_argument(PRODUCTION_DATE_NEGATIVE_ERROR);
    if (!setLocation(location))
        throw std::invalid_argument(LOCATION_EMPTY_ERROR);
    std::cout << "Full constructor called for: " << this->name << std::endl;
}

Product::Product(const Product& other)
    : name(other.name), description(other.description), price(other.price),
    shelfLife(other.shelfLife), productionDate(other.productionDate),
    location(other.location), ingredients(other.ingredients) {
    std::cout << "Copy constructor called for: " << name << std::endl;
}

Product::~Product() {
    ingredients.clear();
    std::cout << "Destructor called for product: " << name << std::endl;
}

Product& Product::operator=(const Product& other) {
    if (this != &other) {
        name = other.name;
        description = other.description;
        price = other.price;
        shelfLife = other.shelfLife;
        productionDate = other.productionDate;
        location = other.location;
        ingredients = other.ingredients;
    }
    std::cout << "Copy assignment called for: " << name << std::endl;
    return *this;
}

std::string Product::getName() const { return name; }
std::string Product::getDescription() const { return description; }
double Product::getPrice() const { return price; }
int Product::getShelfLife() const { return shelfLife; }
int Product::getProductionDate() const { return productionDate; }
std::string Product::getLocation() const { return location; }
std::vector<Ingredient> Product::getIngredients() const { return ingredients; }

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

bool Product::setDescription(const std::string& newDescription) {
    if (newDescription.length() <= 500) {
        description = newDescription;
        return true;
    }
    std::cerr << DESCRIPTION_TOO_LONG_ERROR << std::endl;
    return false;
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

bool Product::setProductionDate(int newDate) {
    if (newDate >= 0) {
        productionDate = newDate;
        return true;
    }
    std::cerr << PRODUCTION_DATE_NEGATIVE_ERROR << std::endl;
    return false;
}

bool Product::setLocation(const std::string& newLocation) {
    if (newLocation.empty()) {
        std::cerr << LOCATION_EMPTY_ERROR << std::endl;
        return false;
    }
    if (newLocation.length() > 50) {
        std::cerr << LOCATION_TOO_LONG_ERROR << std::endl;
        return false;
    }
    location = newLocation;
    return true;
}

void Product::addIngredient(const Ingredient& ing) {
    ingredients.push_back(ing);
}

bool Product::removeIngredient(const std::string& ingName) {
    auto it = std::find_if(ingredients.begin(), ingredients.end(),
        [&](const Ingredient& ing) { return ing.name == ingName; });
    if (it != ingredients.end()) {
        ingredients.erase(it);
        return true;
    }
    return false;
}

bool Product::reduceShelfLife(int days) {
    if (days >= 0) {
        shelfLife -= days;
        if (shelfLife < 0) shelfLife = 0;
        return true;
    }
    std::cerr << REDUCE_DAYS_ERROR << std::endl;
    return false;
}

void Product::print() const {
    std::cout << "\n" << PRODUCT_HEADER << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Description: " << description << "\n";
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << "\n";
    std::cout << "Shelf life: " << shelfLife << " days\n";
    std::cout << "Production date: " << productionDate << "\n";
    std::cout << "Location: " << location << "\n";
    std::cout << "Ingredients:\n";
    if (ingredients.empty()) {
        std::cout << "  (none)\n";
    }
    else {
        for (const auto& ing : ingredients) {
            std::cout << "  - " << ing.name << " (volume: " << ing.volume << ")\n";
        }
    }
    std::cout << PRODUCT_FOOTER << "\n" << std::endl;
}

Product Product::operator+(const Product& other) const {
    std::string newName = MIX_NAME_PREFIX + name + MIX_NAME_INFIX + other.name;
    double newPrice = (price + other.price) * 0.9;
    int newShelfLife = std::min(shelfLife, other.shelfLife);
    int newProductionDate = productionDate;
    std::string newLocation = location;

    std::vector<Ingredient> newIngredients = ingredients;
    for (const auto& ing2 : other.ingredients) {
        auto it = std::find_if(newIngredients.begin(), newIngredients.end(),
            [&](const Ingredient& ing) { return ing.name == ing2.name; });
        if (it != newIngredients.end()) {
            it->volume += ing2.volume;
        }
        else {
            newIngredients.push_back(ing2);
        }
    }

    return Product(newName, description, newPrice, newShelfLife, newProductionDate, newLocation, newIngredients);
}

Product Product::operator-(const Product& other) const {
    std::string newName = SELECT_NAME_PREFIX + name + SELECT_NAME_INFIX + other.name;
    double newPrice = price * 0.9;
    int newShelfLife = shelfLife - 2;
    if (newShelfLife < 0) newShelfLife = 0;
    int newProductionDate = productionDate;
    std::string newLocation = location;

    std::vector<Ingredient> newIngredients;
    for (const auto& ing : ingredients) {
        auto it = std::find_if(other.ingredients.begin(), other.ingredients.end(),
            [&](const Ingredient& ing2) { return ing2.name == ing.name; });
        if (it == other.ingredients.end()) {
            newIngredients.push_back(ing);
        }
    }
    newIngredients.push_back(Ingredient(PRESERVATIVE, PRESERVATIVE_VOLUME));

    return Product(newName, description, newPrice, newShelfLife, newProductionDate, newLocation, newIngredients);
}

Product& Product::operator-=(const Product& other) {
    name = SELECT_NAME_PREFIX + name + SELECT_NAME_INFIX + other.name;
    price *= 0.9;
    shelfLife -= 2;
    if (shelfLife < 0) shelfLife = 0;

    std::vector<Ingredient> newIngredients;
    for (const auto& ing : ingredients) {
        auto it = std::find_if(other.ingredients.begin(), other.ingredients.end(),
            [&](const Ingredient& ing2) { return ing2.name == ing.name; });
        if (it == other.ingredients.end()) {
            newIngredients.push_back(ing);
        }
    }
    newIngredients.push_back(Ingredient(PRESERVATIVE, PRESERVATIVE_VOLUME));
    ingredients = std::move(newIngredients);

    return *this;
}