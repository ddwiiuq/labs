#include <iostream>
#include <clocale>
#include "Product.h"
#include "Commission.h"

void printPersonalAssessment() {
    std::cout << "\n===== PERSONAL ASSESSMENT =====\n";
    std::cout << "Интерес: 8/10\n";
    std::cout << "Наполненность: 9/10.\n";
    std::cout << "Сложность: 7/10\n";
    std::cout << "================================\n" << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "=== LAB 3: PRODUCT AND COMMISSION DEMONSTRATION ===\n\n";

    std::vector<Ingredient> compLemonade = {
        {"water", 1.5},
        {"sugar", 0.2},
        {"citric acid", 0.05}
    };

    std::vector<Ingredient> compSoda = {
        {"water", 1.0},
        {"sugar", 0.3},
        {"flavor", 0.1},
        {"color", 0.02}
    };

    try {
        Product lemonade("Lemonade", "Sparkling lemonade", 100.0, 50, 100, "Aisle 5", compLemonade);
        Product soda("Soda", "Cola drink", 100.0, 30, 100, "Aisle 3", compSoda);

        std::cout << "\n--- Original products ---\n";
        lemonade.print();
        soda.print();

        std::cout << "--- Using operator+ to create a mix ---\n";
        Product mix = lemonade + soda;
        mix.print();

        std::cout << "--- Using operator- to create selection (Lemonade without Soda) ---\n";
        Product selection = lemonade - soda;
        selection.print();

        std::cout << "--- Using operator-= on Lemonade (modifies original) ---\n";
        lemonade -= soda;
        lemonade.print();

        std::cout << "--- Copy constructor (creating a copy of the modified Lemonade) ---\n";
        Product lemonadeCopy = lemonade;
        lemonadeCopy.print();

        std::cout << "--- Assignment operator (assigning Soda to another product) ---\n";
        Product anotherProduct;
        anotherProduct = soda;
        anotherProduct.print();

        std::cout << "\n=== COMMISSION DEMONSTRATION ===\n";

        std::vector<std::string> banned = { "color", "preservative" };
        Commission commission("Main Street 10", banned, 120);
        commission.print();

        std::cout << "Checking products legality:\n";
        std::cout << "Lemonade (modified) is " << (commission.checkProduct(lemonade) ? "LEGAL" : "ILLEGAL") << "\n";
        std::cout << "Soda is " << (commission.checkProduct(soda) ? "LEGAL" : "ILLEGAL") << "\n";
        std::cout << "Mix is " << (commission.checkProduct(mix) ? "LEGAL" : "ILLEGAL") << "\n";
        std::cout << "Selection is " << (commission.checkProduct(selection) ? "LEGAL" : "ILLEGAL") << "\n";

        std::cout << "\n--- Reducing shelf life of Soda by 20 days ---\n";
        soda.reduceShelfLife(20);
        std::cout << "New shelf life of Soda: " << soda.getShelfLife() << " days\n";
        std::cout << "Soda is now " << (commission.checkProduct(soda) ? "LEGAL" : "ILLEGAL") << " (should be illegal if expired)\n";

        std::cout << "\n--- Trying to set invalid values (error messages expected) ---\n";
        if (!lemonade.setPrice(-10))
            std::cout << "Setting negative price failed as expected.\n";
        if (!lemonade.setName(""))
            std::cout << "Setting empty name failed as expected.\n";
        if (!lemonade.setName(std::string(150, 'a'))) 
            std::cout << "Setting too long name failed as expected.\n";
        if (!lemonade.setShelfLife(-3))
            std::cout << "Setting negative shelf life failed as expected.\n";

        std::cout << "\n--- Edge case: product with duplicate ingredients in composition ---\n";
        std::vector<Ingredient> compDup = {
            {"a", 1.0},
            {"b", 2.0},
            {"a", 3.0}  
        };
        Product dupProduct("DuplicateTest", "Test with duplicates", 50.0, 10, 100, "Test location", compDup);
        dupProduct.print();

        Product mixDup = dupProduct + soda;
        std::cout << "Mix with duplicate product (should have unique ingredients across products, but keep internal duplicates):\n";
        mixDup.print();

    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    printPersonalAssessment();

    std::cout << "\n=== END OF DEMONSTRATION ===\n";
    return 0;
}