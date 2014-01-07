#include "twittercrawler.h"
#include "base64.h"
#include "utils.h"
#include <curl/curl.h>
#include <json/reader.h>

TwitterCrawler::TwitterCrawler()
{
    this->token_ = 0;
}

TwitterCrawler::~TwitterCrawler()
{
    if(token_)
    {
        delete token_;
        token_ = 0;
    }
}

SocialInformationList TwitterCrawler::collect(Location location, float radio) 
{
    if(!this->token_)
    {
        connect();
    }
    
    return search(location, radio);
}

void TwitterCrawler::connect()
{
    std::string encodedConsumerKey = encodeRFC1738("mg1I8Wqs8s189NndH3t6GQ");
    std::string encodedConsumerSecret = encodeRFC1738("NmQBAQf3v5WmWhyKuO5hVFAHzTwoFyhHfgQ3yOz9M");

    std::string bearerToken = encodedConsumerKey + ":" + encodedConsumerSecret;
    std::string encodedBearerToken = base64_encode((unsigned char*) bearerToken.c_str(), bearerToken.size());
    std::string url = "https://api.twitter.com/oauth2/token/";

    struct curl_slist *chunk = NULL;
    chunk = curl_slist_append(chunk, "POST /oauth2/token HTTP/1.1");
    chunk = curl_slist_append(chunk, "Host: api.twitter.com");
    chunk = curl_slist_append(chunk, "User-Agent: TweetsFound App v0.1");
    std::string authoization = "Authorization: Basic ";
    authoization += encodedBearerToken;
    chunk = curl_slist_append(chunk, authoization.c_str());
    chunk = curl_slist_append(chunk, "Content-Type: application/x-www-form-urlencoded;charset=UTF-8");
    chunk = curl_slist_append(chunk, "Content-Length: 29");

    std::string readData;
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, TwitterCrawler::writeRequestData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&readData);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    curl_easy_setopt(curl, CURLOPT_HEADER, 0);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "grant_type=client_credentials");

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
        printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

    curl_easy_cleanup(curl);
    
    setBearerToken(readData);
}

SocialInformationList TwitterCrawler::search(Location location, float radio)
{
    std::string url = stringFormat("https://api.twitter.com/1.1/search/tweets.json?q=&geocode=%f,%f,%fkm&lang=es&count=100", 
            location.latitude_, location.longitude_, radio);
    struct curl_slist *chunk = 0;
    chunk = curl_slist_append(chunk, "GET /1.1/search/tweets.json?q=&geocode=%f,%f,%fkm&lang=es");
    chunk = curl_slist_append(chunk, "Host: api.twitter.com");
    chunk = curl_slist_append(chunk, "User-Agent: TweetsFound App v0.1");
    std::string authoization = stringFormat("Authorization: %s %s", this->token_->type_.c_str(), this->token_->token_.c_str());
    chunk = curl_slist_append(chunk, authoization.c_str());

    string readData;
    init_string(&readData);
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&readData);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    curl_easy_setopt(curl, CURLOPT_HEADER, 0);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
        printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

    curl_easy_cleanup(curl);
    
    return parse(readData.ptr);;
}

SocialInformationList TwitterCrawler::parse(const char* jsonFile)
{
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(jsonFile, root);
    SocialInformationList tweets;
    
    if(parsingSuccessful)
    {
        const Json::Value plugins = root["statuses"];
        Json::Value tweet;
        
        for ( unsigned int index = 0; index < plugins.size(); ++index )
        {
            tweet = plugins[index];
            SocialInformation info;
            info.message_ =  tweet["text"].asCString();
            Json::Value location = tweet["coordinates"]["coordinates"];
            info.location_.longitude_ = location[0u].asDouble();
            info.location_.latitude_ = location[1u].asDouble();
            info.source_ = "twitter";
            tweets.push_back(info);
        }
    }
    else
    {
        printf("Error while parsing JSON file");
    }
    
    printf("Tweets size : %d\n", tweets.size());
    return tweets;
}

const std::string TwitterCrawler::encodeRFC1738(const std::string str) 
{
    return str;
}

std::size_t TwitterCrawler::writeRequestData(void *ptr, std::size_t size, std::size_t nmemb, void *data) 
{
    std::string *memory = (std::string *)data;
    memory->append((char*) ptr);

    return memory->size();
}

void TwitterCrawler::setBearerToken(const std::string& json)
{
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(json, root );
    
    if(parsingSuccessful)
    {
        token_ = new BearerToken(root["access_token"].asString(), root["token_type"].asString());
    }
    else
    {
        printf("Error while parsing JSON file");
    }

}
