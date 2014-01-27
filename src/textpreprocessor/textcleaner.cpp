#include "textcleaner.h"
#include <boost/regex.hpp>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;
#define STOP_WORDS_ENGLISH "../src/resources/stopwords-english.txt"
#define STOP_WORDS_SPANISH "../src/resources/stopwords-spanish.txt"
#define SPANISH "spanish"

TextCleaner::TextCleaner(const std::string& language)
{
    loadStopWords(language);
}

string TextCleaner::clean(string text)
{
    //Tolower
    transform(text.begin(), text.end(), text.begin(), ::tolower);
    string textCleaned = removeStopWords(text);
    removeSymbolsAndNumbers(textCleaned);
    return textCleaned;
}

void TextCleaner::loadStopWords(const std::string& language)
{
    stopWords_ = new Trie();
    ifstream reader;
    
    if (language.compare(SPANISH) == 0)
    {
        reader.open(STOP_WORDS_SPANISH);
    }
    else
    {
        reader.open(STOP_WORDS_ENGLISH);
    }

    string word;

    while (getline(reader, word))
    {
        stopWords_->addWord(word);
    }
}

string TextCleaner::removeStopWords(string& text)
{
    stringstream stream(text);
    string word;
    string result;

    while (stream >> word)
    {
        if (!stopWords_->searchWord(word))
        {
            result.append(word);
            result.append(" ");
        }
    }
    result.erase(result.size() - 1);
    return result;
}

void TextCleaner::removeSymbolsAndNumbers(string& text)
{
    boost::regex e("[^ a-z|^ A-Z]");
    text = boost::regex_replace(text, e, "");
}
