#include "database.hpp"
#include <iostream>

vocabDB::vocabDB(std::string filepath)
:db_(filepath, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE)
{
 try {
     db_.exec("CREATE TABLE IF NOT EXISTS vocabulary(wordID INTEGER PRIMARY KEY AUTOINCREMENT, italWord TEXT, gerWord TEXT)");
     std::cout << "database initialized" << std::endl;
}
catch (std::exception& e) {
    std::cout << "Exception occured: " << e.what() << std::endl;
}
}

void vocabDB::insertWord(const Word& word)
{
    SQLite::Statement query(db_, "INSERT INTO vocabulary (italWord, gerWord) VALUES (?, ?)");
    query.bind(1, word.italWord);
    query.bind(2, word.gerWord);
    query.exec();
}


