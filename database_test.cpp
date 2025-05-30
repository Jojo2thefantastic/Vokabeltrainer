#include "database.hpp"
#include <string>
#include <filesystem>

#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_case_sensitive.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>


TEST_CASE("Testing Database", "[testingDB]")
{
    std::string file_path = "vokabeltrainer.db";
    if (std::filesystem::exists(file_path))
    {
        std::filesystem::remove(file_path);
    }
    vocabDB db(file_path);

    SECTION("Insert new word into DB", "[insert]")
    {
        Word word = { "hund", "cane" };
        REQUIRE_NOTHROW(db.insertWord(word));
        std::string german = db.getGerWord("cane");
        std::string italian = db.getItalWord("hund");
        REQUIRE(german == "hund");
        REQUIRE(italian == "cane");
    }

    SECTION("Insert new word with whitespace into DB", "[whitespace]")
    {
        Word word = {"    hund", "cane    "};
        REQUIRE_NOTHROW(db.insertWord(word));
        std::string german = db.getGerWord("cane    ");
        std::string italian = db.getItalWord("    hund");
        REQUIRE(german == "hund");
        REQUIRE(italian == "cane");
    }

    SECTION("Insert new word with uppercase into DB", "[caseSensitivity]")
    {
        Word word = {"HuND", "cANe"};
        REQUIRE_NOTHROW(db.insertWord(word));
        std::string german = db.getGerWord("cANe");
        std::string italian = db.getItalWord("HuND");
        REQUIRE(german == "hund");
        REQUIRE(italian == "cane");
    }
    SECTION("Insert same word into DB that already exists", "existingWord")
    {
        Word word = {"hund", "cane"};
        REQUIRE_NOTHROW(db.insertWord(word));
        REQUIRE_THROWS(db.insertWord(word));
    }
}
