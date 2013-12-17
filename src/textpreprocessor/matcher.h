/* 
 * File:   TextMatcher.h
 * Author: dann
 *
 * Created on December 1, 2013, 12:36 AM
 */

#ifndef TEXTMATCHER_H
#define	TEXTMATCHER_H
#include <string>
#include "../stemmer/stemmer.h"

class Matcher
{
public:
    Matcher();
    Matcher(const Matcher& orig);
    virtual ~Matcher();
    int match(const std::string& sentence, const std::set<std::string>& wordsToMatch);
};

#endif	/* TEXTMATCHER_H */

