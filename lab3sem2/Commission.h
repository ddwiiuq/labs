#ifndef COMMISSION_HPP
#define COMMISSION_HPP

#include <string>
#include <vector>

class Product; // предварительное объ€вление

class Commission {
private:
    std::string address;
    std::vector<std::string> bannedIngredients;
    int inspectionDate; 

public:
    Commission();
    Commission(const std::string& address, const std::vector<std::string>& banned, int inspectionDate);
    Commission(const Commission& other);
    ~Commission();

    std::string getAddress() const;
    std::vector<std::string> getBannedIngredients() const;
    int getInspectionDate() const;

    void setAddress(const std::string& addr);
    void setBannedIngredients(const std::vector<std::string>& banned);
    void setInspectionDate(int date);

    bool checkProduct(const Product& product) const;

    void print() const;
};

#endif