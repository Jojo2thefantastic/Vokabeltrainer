#include "database.hpp"
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <algorithm>

//helper function
void trim(std::string& word)
{
    // Remove leading whitespace
    word.erase(word.begin(), std::find_if(word.begin(), word.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));

    // Remove trailing whitespace
    word.erase(std::find_if(word.rbegin(), word.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), word.end());
}

void toLowerCase(std::string& word)
{
    std::transform(word.begin(), word.end(), word.begin(), [](unsigned char ch) {return std::tolower(ch);});
}

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


void vocabDB::insertWord(Word& word)
{
    trim(word.italWord);
    trim(word.gerWord);
    toLowerCase(word.italWord);
    toLowerCase(word.gerWord);

    if (checkForExistingWord(word)){
        throw std::runtime_error("Wort existiert bereits in der Datenbank");
    }

    SQLite::Statement query(db_, "INSERT INTO vocabulary (italWord, gerWord) VALUES (?, ?)");
    query.bind(1, word.italWord);
    query.bind(2, word.gerWord);
    query.exec();
}

std::string vocabDB::getItalWord(std::string germanWord)
{
    trim(germanWord);
    toLowerCase(germanWord);
    SQLite::Statement query(db_, "SELECT italWord FROM vocabulary WHERE gerWord = ?");
    query.bind(1, germanWord);
    if (query.executeStep()){
        return query.getColumn(0).getString();
    }
    else {
        return "Wort nicht gefunden";
    }
}

std::string vocabDB::getGerWord(std::string italianWord)
{
    trim(italianWord);
    toLowerCase(italianWord);
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





