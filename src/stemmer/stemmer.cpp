#include "stemmer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <vector>

#define TO_STEM_WORD_SIZE 10

Stemmer::Stemmer(const std::string& language)
{
    //TODO: Throw and exception if the stemmer is null.
    stemmer_ = sb_stemmer_new(language.c_str(), NULL);
    toStemSize_ = TO_STEM_WORD_SIZE;
    toStem_ = new sb_symbol[toStemSize_];
}

Stemmer::~Stemmer()
{
    if (toStem_)
    {
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

std::vector<std::string> Stemmer::split(std::string text)
{
    std::string buffer;
    std::stringstream stream(text);
    std::vector<std::string> tokens;
    while (stream >> buffer)
        tokens.push_back(buffer);
    return tokens;
}

std::string Stemmer::stemSentence(const std::string& sentence)
{
    std::vector<std::string> words = split(sentence);
    std::stringstream newSentence;

    for (unsigned int i = 0; i < words.size(); i++)
    {
        if (i != 0)
            newSentence << " ";
        
        newSentence << stem(words.at(i));
    }

    return newSentence.str();
}
