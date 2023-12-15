

#include "book.hpp"
#include <iostream>
#include <fstream>

int main()
{
    using namespace mysqlx;
    Book b1("Kafka on the Shore", "123", "Haruki Murakami", 10, 20.0);
    std::cout<< b1.getTitle()<<std::endl;
    std::string filePath = "../../../mycode.txt";

    // Open the file
    std::ifstream file(filePath);

    // Check if the file is open
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1; // Return an error code
    }

    // Read the contents of the file (assuming it contains a single line with the password)
    std::string password;
    std::getline(file, password);

    // Close the file
    file.close();
    Session session(SessionOption::HOST, "localhost",
                        SessionOption::PORT, 33060,
                        SessionOption::USER, "root",
                        SessionOption::PWD, password); /// change the password


    session.sql ("CREATE DATABASE IF NOT EXISTS booksdb").execute();

    Schema myDb= session.getSchema("booksdb");
    
    session.sql ("USE booksdb").execute();
    // Create a new table

    session.sql ("CREATE TABLE IF NOT EXISTS books ("
                           "title VARCHAR(255),"
                           "isbn VARCHAR(255),"
                           "authors VARCHAR(255)"
                           ")").execute();
    session.sql ("CREATE TABLE IF NOT EXISTS booksDetails ("
                           "isbn VARCHAR(255),"
                           "quantity INT,"
                           "price FLOAT"
                           ")").execute();


        // Execute the SQL query

    
    Table tableBooks = myDb.getTable("books");
    Table tableBookDetails = myDb.getTable("booksDetails");    
    b1.saveToDatabase(tableBooks, tableBookDetails);
            // Select the database
  
    b1.updatePrice(tableBookDetails, 30.0);


    return 0;
}