#include "textcleaner.h"
#include <boost/regex.hpp>
#include <fstream>

using namespace std;

TextCleaner::TextCleaner()
{
    loadStopWords();
}

void TextCleaner::clean(std::string text)
{
    
}

void TextCleaner::loadStopWords()
{
    ifstream reader("resources/StopWords");
}