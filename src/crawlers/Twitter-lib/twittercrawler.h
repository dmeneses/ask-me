#ifndef _TWITTERCRAWLER_H
#define _TWITTERCRAWLER_H

#include "crawler.h"
#include <string>

struct BearerToken
{
    BearerToken(const std::string token, const std::string type): token_(token), type_(type){}
    std::string token_;
    std::string type_;
};

class TwitterCrawler : public Crawler
{
public:
    SocialInformationList collect(Location location, float radio);
private:
    void connect();
    SocialInformationList search();
    SocialInformation parse(const std::string jsonFile);
    const std::string encodeRFC1738(const std::string str);
    static std::size_t writeRequestData(void *ptr, std::size_t size, std::size_t nmemb, void *data);
    void setBearerToken(const std::string& json);
private:
    BearerToken* token_;
};

#endif //_TWITTERCRAWLER_H