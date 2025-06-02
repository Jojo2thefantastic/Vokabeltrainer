#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>

//helper functions
void trim(std::string& word);
void toLowerCase(std::string& word);

struct Word {
    std::string gerWord;
    std::string italWord;
};

class vocabDB {
public:
    vocabDB(std::string filepath);
    void insertWord(Word& word);
    void deleteWord(std::string word);
    bool checkForExistingWord(const Word& word);
    std::string getItalWord(std::string germanWord);
    std::string getGerWord(std::string italianWord);
    std::vector<Word> getAllWords();
    SQLite::Database& getDB() { return db_; }

private:
    SQLite::Database db_;

};

#endif
