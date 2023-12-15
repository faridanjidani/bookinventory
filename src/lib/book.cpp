
#include "book.hpp"



    std::vector<Author> Book::getAuthor()const{
        return bookAuthors;
    }
    float Book::getPrice()const
    {
        return price;
    }
    std::string Book::getTitle()const
    {
        return title;
    }
    std::string Book::getISBN()const
    {
        return ISBN;
    }
    int Book::getQuanity()const
    {
        return quantity;
    }


    void Book::saveToDatabase(mysqlx::Table &tablebook, mysqlx::Table &tablebookDetails) const
    {

        try 
        {

            // Use std::accumulate to concatenate the strings with commas
            std::string authorsName = std::accumulate(
            bookAuthors.begin(),
            bookAuthors.end(),
            std::string(),  // Initial value is an empty string
            [](const std::string& a, const Author& b) -> std::string {
                return a.empty() ? b.getName() : a + "," + b.getName();
                }
            );

            // Use a prepared statement to prevent SQL injection
            tablebook.insert(
                "isbn", "title", "authors").values(ISBN, title, authorsName ).execute();


            auto myResult = tablebookDetails.select("isbn").where("isbn like :param").bind("param", ISBN).execute();
             // Gets the row and prints the first column
            mysqlx::Row row = myResult.fetchOne();
        

            // if the row exists, update the quantity
            if (row) {
                int quantity_ = quantity;
                tablebookDetails.update().set("quantity", mysqlx::expr("quantity + " + std::to_string(quantity_)) ).where("isbn = :isbn")
                .bind("isbn", ISBN).execute();
            } else {
            //     // If the book does not exist, insert a new row
                tablebookDetails.insert("isbn", "quantity", "price").values(ISBN, quantity, price).execute();
            }
        


        } catch (mysqlx::Error &e) {
            std::cerr << "SQLException: " << e.what() << std::endl;
        }

    }

    void Book::updatePrice(mysqlx::Table &tablebookDetails, float price)
    {
        this->price = price;
        try 
        {
        tablebookDetails.update().set("price", mysqlx::expr(std::to_string(price))).where("isbn = :isbn")
            .bind("isbn", ISBN).execute();   

        } catch (mysqlx::Error &e) {
            std::cerr << "SQLException: " << e.what() << std::endl;
        }

    }

    // Book Book::loadfromDatabasetitle(sql::Connection* conn, std::string title)const
    // {
    // }
    // Book Book::loadfromDatabaseISBN(sql::Connection* conn, std::string ISBN)const
    // {}
    // std::vector<Book> Book::loadfromDatabaseAuthor(sql::Connection* conn, std::string author)const
    // {}