#include <iostream>
#include "Product.h"

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "=== PRODUCT CLASS DEMONSTRATION (VARIANT 5) ===\n\n";

    std::vector<std::string> compA = { "water", "sugar", "citric acid" };
    std::vector<std::string> compB = { "water", "sugar", "flavor", "color" };

    try {
        Product lemonade("Lemonade", 100.0, 50, compA);
        Product soda("Soda", 100.0, 30, compB);

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

        std::cout << "--- Edge case: product with duplicate ingredients in composition ---\n";
        std::vector<std::string> compDup = { "a", "b", "a" }; 
        Product dupProduct("DuplicateTest", 50.0, 10, compDup);
        dupProduct.print();

        Product mixDup = dupProduct + soda;
        std::cout << "Mix with duplicate product (should have unique ingredients across products, but keep internal duplicates):\n";
        mixDup.print();

        std::cout << "--- Trying to set invalid values (error messages expected) ---\n";
        if (!dupProduct.setPrice(-5.0))
            std::cout << "Setting negative price failed as expected.\n";
        if (!dupProduct.setName(""))
            std::cout << "Setting empty name failed as expected.\n";
        if (!dupProduct.setName(std::string(150, 'a'))) 
            std::cout << "Setting too long name failed as expected.\n";
        if (!dupProduct.setShelfLife(-3))
            std::cout << "Setting negative shelf life failed as expected.\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== END OF DEMONSTRATION ===\n";
    return 0;
}