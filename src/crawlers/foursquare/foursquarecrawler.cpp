#include "foursquarecrawler.h"
#include <curl/curl.h>
#include <sstream>
#include <json/reader.h>
#include <algorithm>

#define CLIENT_ID "GESN13H3IDYIOCBBHVNJXYTLWSS5RVAJE0VLBS5IMKI1CBYL"
#define SECRED_ID "OSYPDRESM0LZ434ULGO1EBFGQG13YN4PR1ROZJM03AW41EAK"

using namespace std;

FoursquareCrawler::FoursquareCrawler()
{
}

SocialInformationList FoursquareCrawler::collect(Location location, float radius)
{
    string data = search(location, radius);
    return parse(data);
}

static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string FoursquareCrawler::buildUrl(Location location, float radius)
{
    stringstream stream;
    
    stream << "https://api.foursquare.com/v2/venues/search?";
    stream << "ll=" << location.latitude_ << "," << location.longitude_ << "&";
    stream << "radius=" << radius << "&";
    stream << "client_id=" << CLIENT_ID << "&"; 
    stream << "client_secret=" << SECRED_ID << "&"; 
    stream << "v=20140113";
    return stream.str();
}

string FoursquareCrawler::search(Location location, float radius)
{
    string data;
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, buildUrl(location, radius).c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    }

    res = curl_easy_perform(curl);
    
    if (res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    
    return data;
}

SocialInformationList FoursquareCrawler::parse(const string& information)
{
    SocialInformationList places;
    
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(information, root);
    if(parsingSuccessful)
    {
        Json::Value response = root["response"];
        Json::Value venues = response["venues"];
        Json::Value venue;

        for(unsigned int index = 0; index < venues.size(); ++index)
        {
            VenueInfo info;
            venue = venues[index];
            string name = venue["name"].asString();
            std::transform(name.begin(), name.end(), name.begin(), ::tolower);
            info.message_ = name;
            info.location_.latitude_ = venue["location"]["lat"].asDouble();
            info.location_.longitude_ = venue["location"]["lng"].asDouble();
            Json::Value categories = venue["categories"];
            for (unsigned int index = 0; index < categories.size(); index++)
            {
                info.categories.push_back(categories[index]["name"].asString());
            }
            info.source_ = "foursquare";
            places.push_back(info);
            printf("PLACE NAME %s",info.message_.c_str());
        }
    }
    else
    {
        printf("Error while parsing JSON file");
    }
    
    printf("Places size : %d\n", places.size());
    return places;
}
