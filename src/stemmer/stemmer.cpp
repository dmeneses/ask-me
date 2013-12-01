#include "stemmer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TO_STEM_WORD_SIZE 10

Stemmer::Stemmer(const std::string& language)
{
    stemmer_ = sb_stemmer_new(language.c_str(), NULL);
    toStemSize_ = TO_STEM_WORD_SIZE;
    toStem_ = new sb_symbol[toStemSize_];
}

Stemmer::~Stemmer()
{
    if(toStem_){
        delete toStem_;
        toStem_ = 0;
    }
    
    sb_stemmer_delete(stemmer_);
}

std::string Stemmer::stem(const std::string& word)
{
    copyToBaseStruct(word);
    const sb_symbol* stemmed = sb_stemmer_stem(stemmer_, toStem_, word.size());
    std::string result((char*) stemmed);
    return result;
}

void Stemmer::copyToBaseStruct(const std::string& word)
{
    if (word.size() > toStemSize_)
    {
        delete toStem_;
        toStem_ = new sb_symbol[word.size() + 1];
    }

    strcpy((char*) toStem_, word.c_str());
}

