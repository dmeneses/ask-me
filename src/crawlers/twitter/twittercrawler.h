#ifndef _TWITTERCRAWLER_H
#define _TWITTERCRAWLER_H

#include "crawler.h"

class TwitterCrawler : public Crawler
{
public:
	SocialInformationList collect(Location location, float radio);
};

#endif //_TWITTERCRAWLER_H