#include <gtest/gtest.h>
#include "stemmer/stemmer.h"

TEST(Stemmer, SimpleWord)
{
    Stemmer stemmer("spanish");
    std::string expectedWord = "abandon";
    std::string stemmedWord = stemmer.stem("abandonadas");
    ASSERT_EQ(expectedWord, stemmedWord);
}

TEST(Stemmer, WordWithAccents)
{
    Stemmer stemmer("spanish");
    std::string expectedWord = "abarrot";
    std::string stemmedWord = stemmer.stem("abarrotó");
    ASSERT_EQ(expectedWord, stemmedWord);
}
