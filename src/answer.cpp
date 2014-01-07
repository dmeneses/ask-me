/* 
 * File:   answer.cpp
 * Author: jorge
 * 
 * Created on December 11, 2013, 12:50 PM
 */

#include "answer.h"
#include "twittercrawler.h"

#define DEFAULT_LANGUAGE "english"

std::vector<Result> Answer::ask(const std::string word, const Location location, const float radio, SocialSource source)
{
    std::vector<SocialInformation> info = recollect(location, radio, source);
    TextPreprocessor processor(DEFAULT_LANGUAGE);
    
    return processor.process(info, word);
}


SocialInformationList Answer::recollect(const Location location, const float radio, SocialSource& source)
{
    switch(source)
    {
        case TWITTER:
        {
            TwitterCrawler twitterCrawler;
            return twitterCrawler.collect(location, radio);
        }
        case FACEBOOK:
        {
            return std::vector<SocialInformation>();
        }
        default:
        {
            return std::vector<SocialInformation>();
        }
    }
}
