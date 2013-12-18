/* 
 * File:   TextMatcher.cpp
 * Author: dann
 * 
 * Created on December 1, 2013, 12:36 AM
 */

#include "matcher.h"
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

int Matcher::match(const std::string& sentence,
                   const std::vector< std::set<std::string> >& wordsToMatch)
{
    int res = 0;

    for (std::vector< std::set<std::string> >::const_iterator wordSet = wordsToMatch.begin();       
            wordSet != wordsToMatch.end(); wordSet++)
    {
        for (std::set<std::string>::iterator word = wordSet->begin(); word != wordSet->end(); word++)
        {
            int partialMatch = 0;
            unsigned int index = 0;
            unsigned int newIndex = 0;
            while ((newIndex = sentence.find(*word, index)) != std::string::npos)
            {
                //TODO: Match whole word.
                index += newIndex + word->size();
                printf("MATCH: %s\n", word->c_str());
                partialMatch++;
            }

            res += partialMatch;
        }
    }

    return res / wordsToMatch.size();
}

