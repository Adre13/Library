#include <iostream>
#include "Reader.h"

void work_with_lib(Library& library);

int main()
{
    int first_choise = 0;
    std::cout << "If you want to start with fresh library - input 1"
                 "\nIf you have save files and want to continue - input 2"
                 "\ninput 0 if you want to exit." << std::endl;
    std::cin >> first_choise;
    std::cin.ignore();
    switch (first_choise)
    {
        case 1:
        {
            Library library;
            work_with_lib(library);
            break;
        }
        case 2:
        {
            Library library;
            library.load_DB();
            work_with_lib(library);
            break;
        }
        case 0:
        {
            std::cout << "Bye=)" << std::endl;
            break;
        }
        default:
            std::cout << "Bye=)" << std::endl;
    }

    return 0;
}

void work_with_lib(Library& library)
{
    int choice = -1;
    while (choice)
    {
        std::cout << "1 - add book\n"
                     "2 - add user\n"
                     "3 - get book\n"
                     "4 - return book\n"
                     "5 - see available book\n"
                     "6 - see library's users\n"
                     "7 - see users that have books\n"
                     "8 - save DB\n"
                     "0 - exit" << std::endl;
        std::cin >> choice;
        std::cin.ignore();
        switch (choice)
        {
            case 1:
            {
                library.add_book();
                break;
            }
            case 2:
            {
                library.add_people();
                break;
            }
            case 3:
            {
                library.get_book();
                break;
            }
            case 4:
            {
                library.return_book();
                break;
            }
            case 5:
            {
                library.print_available_book();
                break;
            }
            case 6:
            {
                library.print_readers();
                break;
            }
            case 7:
            {
                library.show_people_getting_book();
                break;
            }
            case 8:
            {
                library.save_DB();
                break;
            }
            case 0:
            {
                std::cout << "Bye=)" << std::endl;
            }
            default:
                std::cout << "I do not know what you want" << std::endl;
        }
    }
}