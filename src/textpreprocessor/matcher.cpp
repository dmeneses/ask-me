/* 
 * File:   TextMatcher.cpp
 * Author: dann
 * 
 * Created on December 1, 2013, 12:36 AM
 */

#include "matcher.h"
#include "../stemmer/stemmer.h"
#include <stdio.h>

Matcher::Matcher()
{
}

Matcher::Matcher(const Matcher& orig)
{
}

Matcher::~Matcher()
{
}

int Matcher::match(const std::string& sentence, const std::set<std::string>& wordsToMatch)
{
    int res = 0;
    for (std::set<std::string>::iterator it = wordsToMatch.begin(); it != wordsToMatch.end(); it++)
    {
        int partialMatch = 0;
        unsigned int index = 0;
        unsigned int newIndex = 0;
        while ((newIndex = sentence.find(*it, index)) != std::string::npos)
        {
            //TODO: Match whole word.
            index += newIndex + it->size();
            printf("MATCH: %s\n", it->c_str());
            partialMatch++;
        }

        res += partialMatch;
    }

    return res;
}

