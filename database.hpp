#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <SQLiteCpp/SQLiteCpp.h>

struct Word {
    std::string gerWord;
    std::string italWord;
};

class vocabDB {
public:
    vocabDB(std::string filepath);
    void insertWord(const Word& word);
    SQLite::Database& getDB() { return db_; }
private:
    SQLite::Database db_;

};

#endif
