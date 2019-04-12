#include "Reader.h"

bool operator==(const Book& a, const Book& b)
{
    return (a.ID == b.ID);
}

bool Library::check_email(const std::string &email) //return false if email is already exist
{
    return (library_people.count(email) == 0);
}

void Library::print_writer(const std::string &writer)
{
    std::cout << writer << " :" << std::endl;
    for(const auto &book : library_book[writer])
    {
        if (book.is_free)
        {
            std::cout << std::setw(writer.size()) << '\t'
                      <<"ID - " << book.ID << "  \"" << book.book_name << "\"" << std::endl;
        }
    }
    std::cout << std::endl;
}

Book *Library::find_a_book(const std::string &writer, const std::string &book_name)
{
    for(auto& book : library_book[writer])
    {
        if(book.book_name == book_name && book.is_free)
        {
            return &book;
        }
    }
    return nullptr;
}

Book *Library::find_a_book(const std::string &book_name)
{
    for(auto& item : library_book)
    {
        for(auto& book : item.second)
        {
            if(book.book_name == book_name && book.is_free)
            {
                return &book;
            }
        }
    }
    return nullptr;
}

Book *Library::return_a_book(const std::string &writer, int ID)
{
    for(auto& book : library_book[writer])
    {
        if(book.ID == ID)
        {
            return &book;
        }
    }
    return nullptr;
}

void Library::add_people()
{
    People temp_people;
    std::cout << "Input name(1 word)" << std::endl;
    std::cin >> temp_people.name;
    std::cout << "Input email" << std::endl;
    std::cin >> temp_people.email;
    std::cout << "Input age" << std::endl;
    std::cin >> temp_people.age;
    std::cin.ignore(3, '\n');
    if(check_email(temp_people.email))
    {

        std::string t_email(temp_people.email);
        library_people.emplace(std::pair<std::string, People>(t_email, temp_people));
        std::cout << temp_people.name << " is added" << std::endl;

    }else
    {
        std::cout << "This email is already used" << std::endl;
    }
}

void Library::add_book()
{
    Book temp_book;
    temp_book.ID = ID++;
    std::cout << "Input writer" << std::endl;
    std::cin.getline(temp_book.writer, 24);
    std::cout << "Input name of the book" << std::endl;
    std::cin.getline(temp_book.book_name, 32);
    std::string t_writer(temp_book.writer);
    library_book[t_writer].emplace_back(temp_book);
    std::cout << "The book is added" << std::endl;
}

void Library::print_available_book()
{
    for(const auto &item : library_book)
    {
        std::cout << item.first << std::endl;
        for(const auto &book : item.second)
        {
            if (book.is_free)
            {
                std::cout << std::setw(item.first.size()) << '\t'
                          <<"ID - " << book.ID << "  \"" << book.book_name << "\"" << std::endl;
            }
        }
        std::cout << std::endl;
    }
}

void Library::print_readers()
{
    for(auto item : library_people)
    {
        std::cout << item.first << " | " << item.second.name << " | " << "age: " << item.second.age;
        if(item.second.get_book.size() > 0)
        {
            std::cout << " | Has " << item.second.get_book.size() << " books";
        }
        std::cout << std::endl;
    }
}

void Library::get_book()
{
    std::string user_email;
    std::cout << "Input user email, that want to get book." << std::endl;
    std::cin >> user_email;
    std::cin.ignore();
    if(library_people.count(user_email) > 0)
    {
        int input = -1;
        while (input)
        {
            std::cout << "Do you know: "
                         "\n\twriter - 1"
                         "\n\tthe book name - 2"
                         "\n\tnothing - 3"
                         "\n input 0 to exit." << std::endl;
            std::cin >> input;
            std::cin.ignore();
            switch (input)
            {
                case 0:
                {
                    std::cout << "exit" << std::endl;
                    break;
                }
                case 1:
                {
                    std::string writer;
                    std::cout << "Input the writer:" << std::endl;
                    std::getline(std::cin, writer);
                    if (library_book.count(writer) > 0)
                    {
                        print_writer(writer);
                        std::string book_name;
                        std::cout << "input the name of book:" << std::endl;
                        std::getline(std::cin, book_name);
                        if(Book* ptr = find_a_book(writer, book_name); ptr != nullptr)
                        {
                            ptr->is_free = false;
                            strcpy(ptr->reader,  user_email.c_str());
                            Book t_book;
                            t_book.ID = ptr->ID;
                            strcpy(t_book.writer, ptr->writer);
                            strcpy(t_book.book_name, ptr->book_name);
                            strcpy(t_book.reader, ptr->reader);
                            library_people[user_email].get_book.emplace_back(t_book);
                            std::cout << "All is ok" << std::endl;
                        }else
                        {
                            std::cout << "Your input is invalid" << std::endl;
                        }
                    } else
                    {
                        std::cout << "Sorry but we have not this writer in our library" << std::endl;
                    }
                    break;
                }
                case 2:
                {
                    std::string book_name;
                    std::cout << "Input the name of book:" << std::endl;
                    std::getline(std::cin, book_name);
                    if(Book*ptr = find_a_book(book_name); ptr != nullptr)
                    {
                        ptr->is_free = false;
                        strcpy(ptr->reader,  user_email.c_str());
                        Book t_book;
                        t_book.ID = ptr->ID;
                        strcpy(t_book.writer, ptr->writer);
                        strcpy(t_book.book_name, ptr->book_name);
                        strcpy(t_book.reader, ptr->reader);
                        library_people[user_email].get_book.emplace_back(t_book);
                        std::cout << "All is ok" << std::endl;
                    }else
                    {
                        std::cout << "We have no such book" << std::endl;
                    }
                    break;
                }
                case 3:
                {
                    print_available_book();
                    break;
                }
                default:
                {
                    std::cout << "this switch is so large but you are not to give up=)" << std::endl;
                }
            }
        }
    }
    else
    {
        std::cout << "We have no such user" << std::endl;
    }
}

void Library::return_book()
{
    std::string user_email;
    std::cout << "Input user email, that want to get book." << std::endl;
    std::cin >> user_email;
    std::cin.ignore();
    if(!check_email(user_email))
    {
        std::string writer, book_name;
        int ID;
        std::cout << "Enter writer " << std::endl;
        std::getline(std::cin, writer);
        std::cout << "Input ID" << std::endl;
        std::cin >> ID;
        std::cin.ignore();
        if(Book* ptr_to_book_in_lib = return_a_book(writer, ID); ptr_to_book_in_lib != nullptr)
        {
            unsigned int temp_size = library_people[user_email].get_book.size();
            Book t_book;
            t_book.ID = ptr_to_book_in_lib->ID;
            library_people[user_email].get_book.remove(t_book);

            if(temp_size == library_people[user_email].get_book.size() + 1)
            {
                ptr_to_book_in_lib->is_free = true;
                memset(ptr_to_book_in_lib->reader, '\0', 24);
                std::cout << "All is done" << std::endl;
            }else
            {
                std::cout << "It seems to me that something wrong, and I could not delete this book from reafers list" << std::endl;
            }
        }else
        {
            std::cout << "Something wrong, we have no such writer or such book" << std::endl;
        }

    }else
    {
        std::cout << "We have no such email in our database" << std::endl;
    }
}

void Library::show_people_getting_book()
{
    std::string user_email;
    std::cout << "Input user email:" << std::endl;
    std::cin >> user_email;
    std::cin.ignore();
    if (library_people.count(user_email))
    {
        if (library_people[user_email].get_book.size() > 0)
        {
            for(auto item : library_people[user_email].get_book)
            {
                std::cout << item.writer << '\t' <<"ID - " << item.ID << " | " << item.book_name << std::endl;
            }
        } else
        {
            std::cout << "The user has no book" << std::endl;
        }
    }else
    {
        std::cout << "We have no such user" << std::endl;
    }
}

void Library::save_DB()
{
    std::ofstream save_to_file_book("../book.dat", std::ios::binary);
    if(save_to_file_book.is_open())
    {
        for(auto item : library_book)
        {
            for(auto book : item.second)
            {
                save_to_file_book.write(reinterpret_cast<char *>(&book), sizeof(Book));
            }
        }
    }else
    {
        std::cout << "I could not open file to save books" << std::endl;
    }
    save_to_file_book.flush();
    save_to_file_book.close();

    std::ofstream save_to_file_users("../users.dat", std::ios::binary);
    if(save_to_file_users.is_open())
    {
        for (const auto &item : library_people)
        {
            temp_user t_user;
            t_user.age = item.second.age;
            strcpy(t_user.name, item.second.name);
            strcpy(t_user.email, item.second.email);
            save_to_file_users.write(reinterpret_cast<char *>(&t_user), sizeof(temp_user));
        }
    }else
    {
        std::cout << "I could not open file to save users" << std::endl;
    }
    save_to_file_users.flush();
    save_to_file_users.close();
}

void Library::load_DB()
{
    std::ifstream read_from_file_book("../book.dat", std::ios::in | std::ios::binary);
    if(read_from_file_book.is_open())
    {
        Book t_book;
        while(read_from_file_book.read(reinterpret_cast<char*>(&t_book), sizeof(Book)))
        {
            temp_book_for_load.push_back(t_book);
        }
    }else
    {
        std::cout << "I could not open file to load books" << std::endl;
    }
    read_from_file_book.close();

    std::ifstream read_from_file_users("../users.dat", std::ios::in | std::ios::binary);
    if(read_from_file_users.is_open())
    {
        temp_user t_user;
        while (read_from_file_users.read(reinterpret_cast<char*>(&t_user), sizeof(temp_user)))
        {
            temp_user_for_load.push_back(t_user);
        }
    }else
    {
        std::cout << "I could not open file to load users" << std::endl;
    }
    read_from_file_users.close();

    ID = 1;
    library_book.clear();
    for(const auto& item : temp_book_for_load)
    {
        library_book[item.writer].emplace_back(item);
        if(item.ID >= ID)
        {
            ID = item.ID + 1;
        }
    }

    library_people.clear();
    for(const auto& item : temp_user_for_load)
    {
        People t_user;
        t_user.age = item.age;
        strcpy(t_user.name, item.name);
        strcpy(t_user.email, item.email);
        library_people.insert(std::pair<std::string, People>(t_user.email, t_user));
    }
    for(const auto& pair : library_book)
    {
        for(const auto& book : pair.second)
        {
            if(book.reader[0] != '\0')
            {
                library_people[book.reader].get_book.emplace_back(book);
            }
        }
    }
}
