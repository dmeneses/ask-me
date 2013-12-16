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

int Matcher::match(std::vector<std::string> splittedSentence, std::string wordToFind)
{
    std::vector<std::string>::iterator wordIterator = splittedSentence.begin();
    int matches = 0;

    while (wordIterator != splittedSentence.end())
    {
        std::string stemmedWord = stemmer_->stem(*wordIterator);
        if ((stemmedWord).compare(wordToFind) == 0)
        {
            matches++;

        }
        wordIterator++;
    }

    return matches;
}

int Matcher::matchWholeWords(std::set<std::string> words, const std::string& sentence)
{
    int res = 0;

    for (std::set<std::string>::iterator it = words.begin(); it != words.end(); it++)
    {
        if (sentence.find(*it) != std::string::npos)
        {
            res++;
        }
    }

    return res;
}

