#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
#include <vector>
#include "Ingredient.h"

class Product {
private:
    std::string name;
    std::string description;
    double price;
    int shelfLife;               
    int productionDate;           
    std::string location;
    std::vector<Ingredient> ingredients;

public:
    Product();
    Product(const std::string& name, const std::string& description, double price,
        int shelfLife, int productionDate, const std::string& location,
        const std::vector<Ingredient>& ingredients);
    Product(const Product& other);
    ~Product();

    Product& operator=(const Product& other);

    Product operator+(const Product& other) const;
    Product operator-(const Product& other) const;
    Product& operator-=(const Product& other);

    std::string getName() const;
    std::string getDescription() const;
    double getPrice() const;
    int getShelfLife() const;
    int getProductionDate() const;
    std::string getLocation() const;
    std::vector<Ingredient> getIngredients() const;

    bool setName(const std::string& newName);
    bool setDescription(const std::string& newDescription);
    bool setPrice(double newPrice);
    bool setShelfLife(int newShelfLife);
    bool setProductionDate(int newDate);
    bool setLocation(const std::string& newLocation);
    void addIngredient(const Ingredient& ing);
    bool removeIngredient(const std::string& ingName);

    void print() const;

    bool reduceShelfLife(int days);

private:
    bool isValidName(const std::string& n) const;
    bool isValidDescription(const std::string& d) const;
    bool isValidPrice(double p) const;
    bool isValidShelfLife(int s) const;
    bool isValidLocation(const std::string& loc) const;
};

#endif