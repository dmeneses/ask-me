#ifndef _SOCIALINFORMATION_H
#define _SOCIALINFORMATION_H

#include <string>
#include <vector>
#include <map>

struct Location
{

    Location() : latitude_(0), longitude_(0)
    {
    }

    double latitude_;
    double longitude_;
};

struct SocialInformation
{

    SocialInformation()
    {
        sentiment_ = 0;
    }

    SocialInformation(std::string message, double latitude, double longitude) : message_(message)
    {
        location_.latitude_ = latitude;
        location_.longitude_ = longitude;
        sentiment_ = 0;
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

    /***
     * Dictionary to provide extra information such as
       nickname : botas
       picture : binary str representation of pic...
     */
    std::map<std::string, std::string> extraInformation_;

    int sentiment_;
};

struct TweetInfo : public SocialInformation
{

    TweetInfo() : sharedCount_(0), likesCount_(0)
    {
    }

    /**
     * Shared count of the information.
     */
    int sharedCount_;

    /**
     * Likes count of the information.
     */
    int likesCount_;
};

struct VenueInfo : public SocialInformation
{
    /**
     * Categories where the place could be i.e. "Arts, Restaurant, Movies, Stadium"
     */
    std::vector<std::string> categories;


};

struct Entity
{

    Entity(const std::string& name) : name_(name)
    {
        hasLocation_ = false;
    }

    /**
     * Places with locations and Name
     */
    Entity(Location location, const std::string& name) : location_(location), name_(name)
    {
        hasLocation_ = true;
    }
    
    Location location_;
    std::string name_;
    bool hasLocation_;

};

#endif //_SOCIALINFORMATION_H
