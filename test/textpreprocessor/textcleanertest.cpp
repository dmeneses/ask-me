#include "textpreprocessor/textcleaner.h"
#include "gtest/gtest.h"

using namespace std;

TEST(TextCleaner, removeSymbolsAndNumbers1)
{
    TextCleaner* cleaner = new TextCleaner();
    string text = "Hello word!!!!";
    string expected = "Hello word";
    cleaner->removeSymbolsAndNumbers(text);
    
    EXPECT_EQ(expected, text);
    delete cleaner;
}

TEST(TextCleaner, removeSymbolsAndNumbers2)
{
    TextCleaner* cleaner = new TextCleaner();
    string text = "Hell2o word12345";
    string expected = "Hello word";
    cleaner->removeSymbolsAndNumbers(text);
    
    EXPECT_EQ(expected, text);
    delete cleaner;
}

TEST(TextCleaner, removeSymbolsAndNumbers3)
{
    TextCleaner* cleaner = new TextCleaner();
    string text = "Hell98,.o wo096,._-rd!!!";
    string expected = "Hello word";
    cleaner->removeSymbolsAndNumbers(text);
    
    EXPECT_EQ(expected, text);
    delete cleaner;
}

TEST(TextCleaner, removeStopWords)
{
    TextCleaner* cleaner = new TextCleaner();
    string text = "me gusta las hamburguesas";
    string expected = "gusta hamburguesas";
    string result = cleaner->removeStopWords(text);
    
    EXPECT_EQ(expected, result);
    delete cleaner;
}

TEST(TextCleaner, removeStopWords2)
{
    TextCleaner* cleaner = new TextCleaner();
    string text = "hay bloqueos en la zona central de cochabamba";
    string expected = "bloqueos zona central cochabamba";
    string result = cleaner->removeStopWords(text);
    
    EXPECT_EQ(expected, result);
    delete cleaner;
}

TEST(TextCleaner, clean)
{
    TextCleaner* cleaner = new TextCleaner();
    string text = "hay bloqueos!!! en la zona,@ central de cochabamba22";
    string expected = "bloqueos zona central cochabamba";
    string result = cleaner->clean(text);
    
    EXPECT_EQ(expected, result);
    delete cleaner;
}
