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
#include "socialinformation.h"

class TextPreprocessor
{
public:
    
    TextPreprocessor();
    
    std::vector<SocialInformation> process(std::vector<SocialInformation> tweets, std::string toFind);
    
private:
    
    TextCleaner* cleaner_;
    Matcher* matcher_;
    Stemmer* stemmer_;
};

#endif	/* TEXTPREPROCESSOR_H */

