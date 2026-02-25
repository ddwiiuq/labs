#include "Commission.h"
#include "Product.h"
#include <iostream>
#include <algorithm>

Commission::Commission() : address("Unknown"), inspectionDate(0) {}

Commission::Commission(const std::string& address, const std::vector<std::string>& banned, int inspectionDate)
    : address(address), bannedIngredients(banned), inspectionDate(inspectionDate) {
}

Commission::Commission(const Commission& other)
    : address(other.address), bannedIngredients(other.bannedIngredients), inspectionDate(other.inspectionDate) {
}

Commission::~Commission() {}

std::string Commission::getAddress() const { return address; }
std::vector<std::string> Commission::getBannedIngredients() const { return bannedIngredients; }
int Commission::getInspectionDate() const { return inspectionDate; }

void Commission::setAddress(const std::string& addr) { address = addr; }
void Commission::setBannedIngredients(const std::vector<std::string>& banned) { bannedIngredients = banned; }
void Commission::setInspectionDate(int date) { inspectionDate = date; }

bool Commission::checkProduct(const Product& product) const {
    if (product.getProductionDate() + product.getShelfLife() < inspectionDate)
        return false;

    for (const auto& ing : product.getIngredients()) {
        if (std::find(bannedIngredients.begin(), bannedIngredients.end(), ing.name) != bannedIngredients.end())
            return false;
    }
    return true;
}

void Commission::print() const {
    std::cout << "\n===== COMMISSION INFO =====\n";
    std::cout << "Address: " << address << "\n";
    std::cout << "Inspection date: " << inspectionDate << "\n";
    std::cout << "Banned ingredients: ";
    for (size_t i = 0; i < bannedIngredients.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << bannedIngredients[i];
    }
    std::cout << "\n===========================\n" << std::endl;
}