#ifndef _SOCIALINFORMATION_H
#define _SOCIALINFORMATION_H

#include <string>
#include <map>

struct Location
{
	Location() : latitude_(0), longitude_(0){}

	float latitude_;
	float longitude_;
};

struct SocialInformation
{
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

	/***
	* Dictionary to provide extra information such as
	   nickname : botas
	   picture : binary str representation of pic...
	*/
	std::map<std::string, std::string> extraInformation_;
};

#endif //_SOCIALINFORMATION_H
