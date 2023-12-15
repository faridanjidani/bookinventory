
#include "inventory.hpp"

void inventory::saveToDatabase(sql::Connection* conn)
{
    for (const auto& book : books)
    {
        book.saveToDatabase(conn);
    }
}