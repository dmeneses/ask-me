/* 
 * File:   answer.cpp
 * Author: jorge
 * 
 * Created on December 11, 2013, 12:50 PM
 */

#include "answer.h"
#include "crawlers/Twitter/twittercrawler.h"
#include "crawlers/foursquare/foursquarecrawler.h"

Answer::Answer()
{
    this->reconizer_ = new Recognizer("../../src/langrecognition/language_classify.net");
}

Answer::~Answer()
{
    if (this->reconizer_)
        delete this->reconizer_;
}

std::vector<Result> Answer::ask(const std::string word, const Location location, const float radio,
                                SocialSource source, bool enablePlacesLocation)
{
    std::vector<SocialInformation> info = recollect(location, radio, source);
    TextPreprocessor processor(this-> reconizer_->recognize(word));

    if (enablePlacesLocation)
    {
        std::vector<SocialInformation> foursquareInfo = recollect(location, radio, FOURSQUARE);
        return processor.process(info, word, foursquareInfo);
    }

    return processor.process(info, word);
}

SocialInformationList Answer::recollect(const Location location, const float radio, SocialSource source)
{
    switch (source)
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
    case FOURSQUARE:
    {
        FoursquareCrawler foursquare;
        return foursquare.collect(location, radio);
    }
    default:
    {
        return std::vector<SocialInformation>();
    }
    }
}