#ifndef _SOCIALINFORMATION_H
#define _SOCIALINFORMATION_H

#include <string>
#include <map>

struct Location
{
	Location() : latitude_(0), longitude_(0){}

	double latitude_;
	double longitude_;
};

struct SocialInformation
{
        SocialInformation() : sharedCount_(0), likesCount_(0)
        {
        }
        
        SocialInformation(std::string message, double latitude, double longitude) : message_(message),
        sharedCount_(0), likesCount_(0)
        {
            location_.latitude_ = latitude;
            location_.longitude_ = longitude;
        }
	/***
	* Infomartion message i.e. "Delighting a piece of chessecake on Dumbo"
	*/
	std::string message_;

	/***
	* Cochabambas location latitude = 123123123 longitude = 1231.2131231
	*/
	Location location_;

	/***
	* Crawler soruce  i.e. "twitter", "facebook"
	*/
	std::string source_;
        
        /**
         * Shared count of the information.
         */
        int sharedCount_;
        
        /**
         * Likes count of the information.
         */
        int likesCount_;

	/***
	* Dictionary to provide extra information such as
	   nickname : botas
	   picture : binary str representation of pic...
	*/
	std::map<std::string, std::string> extraInformation_;
};

#endif //_SOCIALINFORMATION_H
