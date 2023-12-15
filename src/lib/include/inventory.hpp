
#include "book.hpp"
class inventory
{
     
    public:
    void saveToDatabase(mysqlx::Table &tablebook, mysqlx::Table &tablebookDetails);
    std::vector<Book> loadFromDatabaseISBN (mysqlx::Table &tablebookDetails, const std::string ISBN);
    std::vector<Book> loadFromDatabaseTitle (mysqlx::Table &tablebookDetails, const std::string title);

    inline void addBook(Book book)
    {
        books.push_back(book);
    }
    inline std::vector<Book> getBooks ()const
    {
        return books;
    }
    // int addBookfromFile(std::string filename);
    // int addbook(Author a);

    private:
    std::vector <Book> books;
};