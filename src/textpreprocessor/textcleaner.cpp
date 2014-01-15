#include "textcleaner.h"
#include <boost/regex.hpp>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

TextCleaner::TextCleaner()
{
    loadStopWords();
}

string TextCleaner::clean(string text)
{
    removeSymbolsAndNumbers(text);
    //Tolower
    transform(text.begin(), text.end(), text.begin(), ::tolower);
    string textCleaned = removeStopWords(text);
    return textCleaned;
}

void TextCleaner::loadStopWords()
{
    stopWords_ = new Trie();
    ifstream reader("../src/resources/stopwords.txt");
    string word;
    
    while(getline(reader, word))
    {
        stopWords_->addWord(word);
    }
}

string TextCleaner::removeStopWords(string& text)
{
    stringstream stream(text);
    string word;
    string result;
    
    while(stream >> word)
    {
        if(!stopWords_->searchWord(word))
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
