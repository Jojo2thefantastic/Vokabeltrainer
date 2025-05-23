#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>

struct Word {
    std::string gerWord;
    std::string italWord;
};

class vocabDB {
public:
    vocabDB(std::string filepath);
    void insertWord(const Word& word);
    bool checkForExistingWord(const Word& word);
    std::string getItalWord(const std::string& germanWord);
    std::string getGerWord(const std::string& italianWord);
    std::vector<Word> getAllWords();
    SQLite::Database& getDB() { return db_; }
private:
    SQLite::Database db_;

};

#endif
