#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <stdexcept>

// Константы для текстовых сообщений
const std::string PRODUCT_HEADER = "===== PRODUCT INFORMATION =====";
const std::string PRODUCT_FOOTER = "===============================";
const std::string DEFAULT_PRODUCT_NAME = "Unknown";
const std::string DEFAULT_DESCRIPTION = "No description";
const std::string DEFAULT_LOCATION = "Warehouse";
const std::string PRICE_ERROR = "Error: Price cannot be negative!";
const std::string NAME_ERROR = "Error: Product name cannot be empty!";
const std::string LOCATION_ERROR = "Error: Location cannot be empty!";
const std::string SHELF_LIFE_ERROR = "Error: Shelf life cannot be negative!";
const std::string REDUCE_DAYS_ERROR = "Error: Cannot reduce shelf life by negative days!";

class Product {
private:
    std::string name;
    std::string description;
    double price;
    int lifetime;
    std::string location;

protected:
    bool isValidName(const std::string& productName) const {
        return !productName.empty() && productName.length() <= 100;
    }

    bool isValidDescription(const std::string& productDescription) const {
        return productDescription.length() <= 500;
    }

    bool isValidLocation(const std::string& productLocation) const {
        return !productLocation.empty() && productLocation.length() <= 50;
    }

public:
    Product() : name(DEFAULT_PRODUCT_NAME),
        description(DEFAULT_DESCRIPTION),
        price(0.0),
        lifetime(0),
        location(DEFAULT_LOCATION) {
        std::cout << "Default constructor called" << std::endl;
    }

    Product(const std::string& productName,
        const std::string& productDescription,
        double productPrice,
        int productLifetime,
        const std::string& productLocation) {

        if (!setName(productName)) {
            throw std::invalid_argument(NAME_ERROR);
        }
        if (!setDescription(productDescription)) {
            throw std::invalid_argument("Error: Description is too long!");
        }
        if (!setPrice(productPrice)) {
            throw std::invalid_argument(PRICE_ERROR);
        }
        if (!setLifetime(productLifetime)) {
            throw std::invalid_argument(SHELF_LIFE_ERROR);
        }
        if (!setLocation(productLocation)) {
            throw std::invalid_argument(LOCATION_ERROR);
        }
        std::cout << "Full constructor called for: " << name << std::endl;
    }

    Product(const Product& other)
        : name(other.name),
        description(other.description),
        price(other.price),
        lifetime(other.lifetime),
        location(other.location) {
        std::cout << "Copy constructor called for: " << name << std::endl;
    }

    ~Product() {
        std::cout << "Destructor called for product: " << name << std::endl;
    }

    std::string getName() const {
        return name;
    }

    std::string getDescription() const {
        return description;
    }

    double getPrice() const {
        return price;
    }

    int getLifetime() const {
        return lifetime;
    }

    std::string getLocation() const {
        return location;
    }

    bool setPrice(double newPrice) {
        if (newPrice >= 0) {
            price = newPrice;
            return true;
        }
        std::cerr << PRICE_ERROR << std::endl;
        return false;
    }

    bool setName(const std::string& newName) {
        if (isValidName(newName)) {
            name = newName;
            return true;
        }
        std::cerr << NAME_ERROR << std::endl;
        return false;
    }

    bool setDescription(const std::string& newDescription) {
        if (isValidDescription(newDescription)) {
            description = newDescription;
            return true;
        }
        std::cerr << "Error: Description is too long (max 500 characters)!" << std::endl;
        return false;
    }

    bool setLifetime(int newLifetime) {
        if (newLifetime >= 0) {
            lifetime = newLifetime;
            return true;
        }
        std::cerr << SHELF_LIFE_ERROR << std::endl;
        return false;
    }

    bool setLocation(const std::string& newLocation) {
        if (isValidLocation(newLocation)) {
            location = newLocation;
            return true;
        }
        std::cerr << LOCATION_ERROR << std::endl;
        return false;
    }

    void printAllInfo() const {
        std::cout << "\n" << PRODUCT_HEADER << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Description: " << description << std::endl;
        std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << std::endl;
        std::cout << "Shelf life: " << lifetime << " days" << std::endl;
        std::cout << "Location: " << location << std::endl;
        std::cout << PRODUCT_FOOTER << "\n" << std::endl;
    }

    void printLocationInfo() const {
        std::cout << "Product \"" << name << "\" can be obtained at: " << location << std::endl;
    }

    bool reduceShelfLife(int days) {
        if (days >= 0) {
            lifetime -= days;
            if (lifetime < 0) {
                lifetime = 0;
                std::cout << "Warning: Shelf life has expired!" << std::endl;
            }
            return true;
        }
        std::cerr << REDUCE_DAYS_ERROR << std::endl;
        return false;
    }
};

int main() {
    std::cout << "=== DEMONSTRATION OF PRODUCT CLASS ===\n" << std::endl;

    std::cout << "Creating products: Water, Soda, Bread\n" << std::endl;

    std::cout << "--- Creating Water ---" << std::endl;
    try {
        Product water("Water", "Mineral water, 1.5L bottle", 0.99, 365, "Refrigerator A1");
        water.printAllInfo();
        water.printLocationInfo();

        std::cout << "Reducing shelf life of Water by 100 days..." << std::endl;
        std::cout << "Current shelf life: " << water.getLifetime() << " days" << std::endl;
        if (water.reduceShelfLife(100)) {
            std::cout << "New shelf life: " << water.getLifetime() << " days" << std::endl;
        }

        std::cout << "\nUsing getters for Water:" << std::endl;
        std::cout << "Name: " << water.getName() << std::endl;
        std::cout << "Description: " << water.getDescription() << std::endl;
        std::cout << "Price: $" << water.getPrice() << std::endl;
        std::cout << "Shelf Life: " << water.getLifetime() << " days" << std::endl;
        std::cout << "Location: " << water.getLocation() << std::endl;

    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Failed to create Water: " << e.what() << std::endl;
    }

    std::cout << "\n\n--- Creating Soda ---" << std::endl;
    try {
        Product soda("Soda", "Carbonated drink, 0.5L can", 1.49, 180, "Shelf B2");
        soda.printAllInfo();
        soda.printLocationInfo();

        std::cout << "Reducing shelf life of Soda by 30 days..." << std::endl;
        std::cout << "Current shelf life: " << soda.getLifetime() << " days" << std::endl;
        if (soda.reduceShelfLife(30)) {
            std::cout << "New shelf life: " << soda.getLifetime() << " days" << std::endl;
        }

    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Failed to create Soda: " << e.what() << std::endl;
    }

    std::cout << "\n\n--- Creating Bread ---" << std::endl;
    try {
        Product bread("Bread", "Whole wheat bread, 500g", 2.49, 5, "Bakery section");
        bread.printAllInfo();
        bread.printLocationInfo();

        std::cout << "Reducing shelf life of Bread by 3 days..." << std::endl;
        std::cout << "Current shelf life: " << bread.getLifetime() << " days" << std::endl;
        if (bread.reduceShelfLife(3)) {
            std::cout << "New shelf life: " << bread.getLifetime() << " days" << std::endl;
        }

        std::cout << "\n--- Demonstrating copy constructor with Bread ---" << std::endl;
        Product breadCopy = bread;
        breadCopy.setName("Fresh Bread");
        breadCopy.setPrice(3.49);
        breadCopy.setLifetime(2);

        std::cout << "\nOriginal Bread product:" << std::endl;
        bread.printAllInfo();

        std::cout << "Copied Bread product (modified):" << std::endl;
        breadCopy.printAllInfo();

    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Failed to create Bread: " << e.what() << std::endl;
    }

    std::cout << "\n\n=== ERROR HANDLING DEMONSTRATION ===" << std::endl;

    std::cout << "\nTrying to create product with invalid data..." << std::endl;
    try {
        Product invalidProduct("", "Test", -10, -5, "");
        invalidProduct.printAllInfo();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n--- Creating product with default constructor ---" << std::endl;
    Product milk;
    milk.setName("Milk");
    milk.setDescription("Fresh cow milk, 1 liter");
    if (!milk.setPrice(-1.99)) {
        std::cout << "Failed to set negative price (expected)" << std::endl;
    }
    milk.setPrice(1.99);
    milk.setLifetime(7);
    milk.setLocation("Refrigerator C3");
    milk.printAllInfo();

    std::cout << "\nDemonstrating invalid shelf life reduction..." << std::endl;
    Product testProduct("Test", "Test product", 1.0, 10, "Test location");
    if (!testProduct.reduceShelfLife(-3)) {
        std::cout << "Failed to reduce by negative days (expected)" << std::endl;
    }

    std::cout << "\n=== END OF DEMONSTRATION ===\n" << std::endl;

    return 0;
}