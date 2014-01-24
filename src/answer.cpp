/* 
 * File:   answer.cpp
 * Author: jorge
 * 
 * Created on December 11, 2013, 12:50 PM
 */

#include "answer.h"
#include "twittercrawler.h"
#include "crawlers/foursquare/foursquarecrawler.h"

#define DEFAULT_LANGUAGE "english"

std::vector<Result> Answer::ask(const std::string word, const Location location, const float radio, SocialSource source)
{
    std::vector<SocialInformation> info = recollect(location, radio, source);
    std::vector<SocialInformation> foursquareInfo = recollectFromFoursquare(location,radio);
    TextPreprocessor processor(DEFAULT_LANGUAGE);
    
    return processor.process(info, word, foursquareInfo);
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

SocialInformationList Answer::recollectFromFoursquare(Location location, const float radio){
     FoursquareCrawler foursquare;
     return foursquare.collect(location,radio);
}