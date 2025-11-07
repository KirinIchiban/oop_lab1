#include "include/trapeze.h"
#include "include/rhomb.h"      
#include "include/array.h"      
#include "include/pentagon.h"
#include <iostream>
#include <limits>


int main() {
    Array shapes;
    int ch;

    while (true) {
        std::cout << "1. Add Trapeze\n"
                     "2. Add Rhomb\n"
                     "3. Add Pentagon\n"
                     "4. Print array\n"
                     "5. Print centers\n"
                     "6. Area\n"
                     "7. Remove\n"
                     "0. Exit\n"
                     "-> ";

        if (!(std::cin >> ch)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Uncorrect. Try again\n";
            continue;
        }

        switch (ch) {
            case 0:
                return 0;

            case 1: {
                Trapeze* trapez = new Trapeze();
                std::cout << "Enter 4 points: ";
                std::cin >> *trapez;
                shapes.Add(trapez);
                break;
            }

            case 2: { 
                Rhomb* rb = new Rhomb();  
                std::cout << "Enter 4 points of rhomb: ";
                std::cin >> *rb;
                shapes.Add(rb);
                break;
            }

            case 3: { 
                Pentagon* pent = new Pentagon();  
                std::cout << "Enter pentagon: ";
                std::cin >> *pent;
                shapes.Add(pent);
                break;
            }

            case 4: {
                shapes.Print();
                break;
            }

            case 5: {
                shapes.Centers();
                break;
            }

            case 6: {
                std::cout << "Total squeare: " << shapes.All_squeare() << "\n";
                break;
            }

            case 7: {
                size_t idx;
                std::cout << "Index: ";
                if (std::cin >> idx) {
                    try {
                        shapes.Remove(idx);
                    } catch (const std::exception& my_err) {
                        std::cerr << "Error: " << my_err.what() << "\n";
                    }
                } else {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid index.\n";
                }
                break;
            }

            default:
                std::cout << "Invalid ch. Try again.\n";
                break;
        }
    }
    return 0;
}