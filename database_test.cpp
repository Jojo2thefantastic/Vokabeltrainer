#include "database.hpp"
#include <string>
#include <filesystem>

#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_case_sensitive.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

using Catch::CaseSensitive;
using Catch::Matchers::Equals;

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
        Word word = { " Cane ", "  Hund" };
        REQUIRE_NOTHROW(db.insertWord(word));
        std::string german = db.getGerWord("cane");
        REQUIRE(german == "hund");
    }
}
