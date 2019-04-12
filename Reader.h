//
// Created by msi on 06.04.2019.
//

#ifndef HW_READER_H
#define HW_READER_H

#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>
#include <list>
#include <fstream>
#include <iostream>


struct Book
{
    int ID;
    char writer[24]{'\0'};
    char book_name[32]{'\0'};
    char reader[24]{'\0'};
    bool is_free = true;
};

struct People
{
    char name[24]{'\0'};
    int age;
    char email[24]{'\0'};  //primary key
    std::list<Book> get_book;
};


class Library
{
private:
    struct temp_user
    {
        char name[24]{'\0'};
        int age;
        char email[24]{'\0'};
    };
    std::vector<Book> temp_book_for_load;
    std::vector<temp_user> temp_user_for_load;

    int ID = 1;
    std::map<std::string, std::vector<Book>> library_book;
    std::map<std::string, People> library_people;
    bool check_email(const std::string& email);
    void print_writer(const std::string& writer);
    Book* find_a_book(const std::string& writer, const std::string& book_name);
    Book* find_a_book(const std::string& book_name);
    Book* return_a_book(const std::string& writer, int ID);


public:
    Library() = default;
    Library(Library&) = delete;
    Library&operator=(Library&) = delete;

    void add_people();
    void add_book();
    void print_available_book();
    void print_readers();
    void get_book();
    void return_book();
    void show_people_getting_book();
    void save_DB();
    void load_DB();
};

#endif //HW_READER_H
