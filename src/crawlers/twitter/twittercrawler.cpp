#include "twittercrawler.h"
#include "base64.h"
#include <curl/curl.h>

SocialInformationList TwitterCrawler::collect(Location location, float radio) 
{
    SocialInformationList collectedInformation;

    return collectedInformation;
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
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "grant_type=client_credentials");

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
        printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

    curl_easy_cleanup(curl);
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