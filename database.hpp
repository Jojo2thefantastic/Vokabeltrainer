#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <SQLiteCpp/SQLiteCpp.h>

class vocabDB {
public:
    vocabDB(std::string filepath);
private:
    SQLite::Database db_;

};

#endif
