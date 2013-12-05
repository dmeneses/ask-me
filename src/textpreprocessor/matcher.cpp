/* 
 * File:   TextMatcher.cpp
 * Author: dann
 * 
 * Created on December 1, 2013, 12:36 AM
 */

#include "matcher.h"
#include "../stemmer/stemmer.h"
#include <iostream>

Matcher::Matcher(Stemmer* stemmer)
{
    this->stemmer_ = stemmer;
}

Matcher::Matcher(const Matcher& orig)
{
}

Matcher::~Matcher()
{
}

bool Matcher::match(std::vector<std::string> splittedSentence, std::string wordToFind)
{
    std::vector<std::string>::iterator wordIterator = splittedSentence.begin();
    while (wordIterator != splittedSentence.end())
    {
        std::string stemmedWord = stemmer_->stem(*wordIterator);
        if ((stemmedWord).compare(wordToFind) == 0)
        {
            return true;
        }
        wordIterator++;
    }
    
    return false;
}

