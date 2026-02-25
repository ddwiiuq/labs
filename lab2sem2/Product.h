#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>

class Product {
private:
    std::string name;
    double price;
    int shelfLife;               
    std::vector<std::string> composition;

public:
    Product();
    Product(const std::string& name, double price, int shelfLife,
        const std::vector<std::string>& composition);
    Product(const Product& other);         
    ~Product();                              

    Product& operator=(const Product& other);

    Product operator+(const Product& other) const;
    Product operator-(const Product& other) const;
    Product& operator-=(const Product& other);

    std::string getName() const;
    double getPrice() const;
    int getShelfLife() const;
    std::vector<std::string> getComposition() const;

    bool setName(const std::string& newName);
    bool setPrice(double newPrice);
    bool setShelfLife(int newShelfLife);
    void addIngredient(const std::string& ingredient);      
    bool removeIngredient(const std::string& ingredient);   

    void print() const;

private:
    bool isValidName(const std::string& n) const;
    bool isValidPrice(double p) const;
    bool isValidShelfLife(int s) const;
};

#endif