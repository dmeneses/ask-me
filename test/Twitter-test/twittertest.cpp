#include "gtest/gtest.h"
#include "twittercrawler.h"
#include "string"

TEST(TwitterCarwler, validateTweets)
{
    std::string firstTweet = "Trabajando!!!!";
    std::string secondTweet = "Por fin acabe... Es hora de hacer pruebas...";
    
    TwitterCrawler crawler;
    Location location;
    location.latitude_ = -17.365963;
    location.longitude_ = -66.175467;
    SocialInformationList tweets = crawler.collect(location, 1);
    short counter = 0;
            
    for(std::vector<SocialInformation>::iterator i = tweets.begin(); i != tweets.end(); i++)
    {
        SocialInformation tweet = (SocialInformation)*i;
        if(tweet.message_ == firstTweet)
        {
            counter++;
        }
        else if(tweet.message_ == secondTweet)
        {
            counter++;
        }
    }
    
    ASSERT_TRUE(counter == 2);
}