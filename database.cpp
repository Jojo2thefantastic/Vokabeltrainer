#include "database.hpp"
#include <iostream>
#include <stdexcept>

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

bool vocabDB::checkForExistingWord(const Word& word)
{
    SQLite::Statement query(db_, "SELECT count(*) FROM vocabulary WHERE italWord = ? OR gerWord = ? ");
    query.bind(1, word.italWord);
    query.bind(2, word.gerWord);

    query.executeStep();
    int count = query.getColumn(0).getInt();
    return count > 0;
}


void vocabDB::insertWord(const Word& word)
{
    if (checkForExistingWord(word)){
        throw std::runtime_error("Wort existiert bereits in der Datenbank");
    }

    SQLite::Statement query(db_, "INSERT INTO vocabulary (italWord, gerWord) VALUES (?, ?)");
    query.bind(1, word.italWord);
    query.bind(2, word.gerWord);
    query.exec();
}

std::string vocabDB::getItalWord(const std::string& germanWord)
{
    SQLite::Statement query(db_, "SELECT italWord FROM vocabulary WHERE gerWord = ?");
    query.bind(1, germanWord);
    if (query.executeStep()){
        return query.getColumn(0).getString();
    }
    else {
        return "Wort nicht gefunden";
    }
}

std::string vocabDB::getGerWord(const std::string& italianWord)
{
    SQLite::Statement query(db_, "SELECT gerWord FROM vocabulary WHERE italWord = ?");
    query.bind(1, italianWord);
    if (query.executeStep()){
        return query.getColumn(0).getString();
    }
    else {
        return "Wort nicht gefunden";
    }
}

std::vector<Word> vocabDB::getAllWords()
{
    std::vector<Word> words;
    SQLite::Statement query(db_, "SELECT gerWord, italWord FROM vocabulary");
    while (query.executeStep()){
        Word word;
        word.gerWord = query.getColumn(0).getString();
        word.italWord = query.getColumn(1).getString();
        words.push_back(word);
    }
    return words;
}





