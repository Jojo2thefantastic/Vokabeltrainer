#include "database.hpp"
#include <iostream>

vocabDB::vocabDB(std::string filepath)
:db_(filepath, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE)
{
 try {
     db_.exec("DROP TABLE IF EXISTS vocabulary");
     db_.exec("CREATE TABLE vocabulary(wordID INTERGER PRIMARY KEY, word TEXT)");
     std::cout << "database initialized" << std::endl;
}
catch (std::exception& e) {
    std::cout << "Exception occured: " << e.what() << std::endl;
}
}

