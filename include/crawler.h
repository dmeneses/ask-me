#ifndef _CRAWLER_H
#define _CRAWLER_H

#include <vector>

#include "socialinformation.h"

typedef std::vector<SocialInformation> SocialInformationList;

class Crawler
{
public:
	
	virtual ~Crawler() {}

	virtual SocialInformationList collect(Location location, float radio) = 0;
};

#endif //_CRAWLER_H