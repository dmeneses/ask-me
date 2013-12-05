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

class Matcher
{
public:
    Matcher(Stemmer* stemmer);
    Matcher(const Matcher& orig);
    virtual ~Matcher();
    bool match(std::vector<std::string>, std::string);
private:
    Stemmer* stemmer_;
};

#endif	/* TEXTMATCHER_H */

