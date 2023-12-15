
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include "author.hpp"
#include <mysqlx/xdevapi.h>
class Book 
{

    public:
    Book (const std::string &title, const std::string& ISBN, const std::vector<Author>& author, int quantity, float price):
    title(title), ISBN(ISBN), bookAuthors(author), quantity(quantity), price(price){};
    Book (const std::string &title, const std::string& ISBN, const Author& author, int quantity, float price):
    title(title), ISBN(ISBN), bookAuthors({author}), quantity(quantity), price(price){};
    Book (const char* title, const char* ISBN, const char* author, int quantity, float price) :
    title(title), ISBN(ISBN), bookAuthors({Author(author)}), quantity(quantity), price(price) {};
    
    std::vector<Author> getAuthor()const;
    float getPrice()const;
    std::string getTitle()const;
    std::string getISBN()const;
    int getQuanity()const;

    void saveToDatabase(mysqlx::Table &collbook, mysqlx::Table &collbookDetails) const;
    // Book loadfromDatabasetitle(sql::Connection* conn, std::string title)const;
    // Book loadfromDatabaseISBN(sql::Connection* conn, std::string ISBN)const;
    // std::vector<Book> loadfromDatabaseAuthor(sql::Connection* conn, std::string author)const;
    void updatePrice(mysqlx::Table &tablebookDetails, float price);

    private:
    std::string title;
    std::string ISBN;
    int quantity;
    float price;
    std::vector<Author> bookAuthors;

};