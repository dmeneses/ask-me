#include <gtest/gtest.h>
#include "stemmer/stemmer.h"
#include <fstream>

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


TEST(Stemmer, FullTests)
{
    Stemmer stemmer("spanish");
    std::string inputWord = "";
    std::string expectedStemmedWord = "";
    std::string stemmedWord = "";
    std::ifstream inputFile;
    std::ifstream outputFile;

    inputFile.open("resources/stem.in");
    outputFile.open("resources/stem.out");

    while (!inputFile.eof())
    {
        getline(inputFile, inputWord);
        getline(outputFile, expectedStemmedWord);
        stemmedWord = stemmer.stem(inputWord);
        EXPECT_STREQ(expectedStemmedWord.c_str(), stemmedWord.c_str());
    }

    inputFile.close();
    outputFile.close();
}
