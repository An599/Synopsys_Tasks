#include <iostream>
#include <string>
#include "SimpleMap.h"

int main() {
    SimpleMap<std::string, int> ageMap; 
    int choice;
    std::string name;
    int age;

    while (true) {
        std::cout << "\n=== SimpleMap Demo ===\n";
        std::cout << "1. Add/Update Age\n";
        std::cout << "2. Lookup Age\n";
        std::cout << "3. Check if Name Exists\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::cout << "Enter name: ";
            std::cin >> name;
            std::cout << "Enter age: ";
            std::cin >> age;
            ageMap.insert(name, age); 
            std::cout << "Updated " << name << "'s age to " << age << ".\n";
            break;
        }

        case 2: {
            std::cout << "Enter name to lookup: ";
            std::cin >> name;
            try {
                int retrievedAge = ageMap.at(name); 
                std::cout << name << "'s age is " << retrievedAge << ".\n";
            }
            catch (const std::out_of_range& e) {
                std::cerr << "Error: " << name << " not found!\n";
            }
            break;
        }

        case 3: {
            std::cout << "Enter name to check: ";
            std::cin >> name;
            if (ageMap.contains(name)) {
                std::cout << name << " exists in the map.\n";
            }
            else {
                std::cout << name << " does NOT exist.\n";
            }
            break;
        }

        case 4: {
            std::cout << "Exiting...\n";
            return 0;
        }

        default:
            std::cerr << "Invalid choice. Try again.\n";
        }
    }
}
