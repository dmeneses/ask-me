/* 
 * File:   TextMatcher.h
 * Author: dann
 *
 * Created on December 1, 2013, 12:36 AM
 */

#ifndef TEXTMATCHER_H
#define	TEXTMATCHER_H
#include <vector>
#include <string>
#include "../stemmer/stemmer.h"
#include <set>

class Matcher
{
public:
    Matcher(Stemmer* stemmer);
    Matcher(const Matcher& orig);
    virtual ~Matcher();
    int match(std::vector<std::string>, std::string);
    int matchWholeWords(std::set<std::string> words, const std::string& sentence);
private:
    Stemmer* stemmer_;
};

#endif	/* TEXTMATCHER_H */

