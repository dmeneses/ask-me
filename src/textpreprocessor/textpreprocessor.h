/* 
 * File:   textpreprocessor.h
 * Author: luis
 *
 * Created on 28 de noviembre de 2013, 18:19
 */

#ifndef TEXTPREPROCESSOR_H
#define	TEXTPREPROCESSOR_H

#include <string>
#include <vector>

#include "textcleaner.h"
#include "matcher.h"
#include "../stemmer/stemmer.h"

struct Tweet
{
    Tweet(std::string sentence, int latitude, int longitude) : sentence(sentence), latitude(latitude), 
    longitude(longitude)
    {
    }
    
    std::string sentence;
    int latitude;
    int longitude;
};

class TextPreprocessor
{
public:
    
    TextPreprocessor();
    
    std::vector<Tweet> process(std::vector<Tweet> tweets, std::string toFind);
    
    TextCleaner* cleaner_;
    Matcher* matcher_;
    Stemmer* stemmer_;
};

#endif	/* TEXTPREPROCESSOR_H */

