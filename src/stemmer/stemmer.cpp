#include "stemmer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Stemmer::Stemmer(const std::string& language) : language_(language)
{

}

std::string Stemmer::stem(const std::string& word)
{
    sb_stemmer* stemmer = sb_stemmer_new(language_.c_str(), NULL);
    sb_symbol * b = convertToUnsignedChar(word);
    const sb_symbol* stemmed = sb_stemmer_stem(stemmer, b, word.size());
    std::string result((char*) stemmed);
    sb_stemmer_delete(stemmer);
    delete b;
    return result;
}

sb_symbol* Stemmer::convertToUnsignedChar(const std::string& word)
{
    sb_symbol * result = new sb_symbol[word.size() + 1];
    strcpy((char*) result, word.c_str());
    return result;
}

