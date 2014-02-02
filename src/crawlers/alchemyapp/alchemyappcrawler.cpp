#include "alchemyappcrawler.h"
#include <json/reader.h>
#include <fstream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string.h>
#include <algorithm>
#include "../utils.h"

#define ALCHEMYAPP_URL "http://access.alchemyapi.com/calls/text/SEARCHPARAMETER?outputMode=json&apikey=0d752536a9762c9ae2fb868d57e4beaade74f1a2&text="
#define ENTITY_EXTRACTION_KEYWORD "TextGetNamedEntities"
#define SENTIMENT_EXTRACTION_KEYWORD "TextGetTextSentiment"
#define JSON_OUTPUT_MODE "outputMode=json&"
#define API_KEY "apikey=0d752536a9762c9ae2fb868d57e4beaade74f1a2&"
#define QUERY_SPACE_TOKEN "%20"
#define JSON_FILE_NAME_LENGTH 19
#define SEARCH_PARAMETER_POSITION 40
#define SEARCH_PARAMETER_SIZE 15

AlchemyAppCrawler::AlchemyAppCrawler() {

}

AlchemyAppCrawler::~AlchemyAppCrawler() {

}

set<std::string> AlchemyAppCrawler::collectAllNamedEntities(std::string& text) {
    std::string request(ALCHEMYAPP_URL);
    request.replace(SEARCH_PARAMETER_POSITION, SEARCH_PARAMETER_SIZE, ENTITY_EXTRACTION_KEYWORD);
    string processedText = processTextToMakeRequest(text);
    request += processedText;

    set<string> collectedWords;


    collectedWords = parseNamedEntitiesFile(retrieve(request));


    return collectedWords;
}

SentimentAnalysis AlchemyAppCrawler::makeSentimentAnalysis(std::string& text) {
    std::string request(ALCHEMYAPP_URL);
    SentimentAnalysis sentimentAnalysis;
    request.replace(SEARCH_PARAMETER_POSITION, SEARCH_PARAMETER_SIZE, SENTIMENT_EXTRACTION_KEYWORD);
    std::string processedText = processTextToMakeRequest(text);
    request += processedText;

    sentimentAnalysis = parseSentimentsFile(retrieve(request));

    return sentimentAnalysis;
}

const char* AlchemyAppCrawler::retrieve(const std::string& request) {
    iostring readData;
    init_string(&readData);
    CURL* curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &readData);
        curl_easy_setopt(curl, CURLOPT_URL, request.c_str());
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }

    return readData.ptr;
}

set<std::string> AlchemyAppCrawler::parseNamedEntitiesFile(const char* namedEntitiesInfo) {
    set<std::string> namedEntityList;
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(namedEntitiesInfo, root);

    if (parsingSuccessful) {
        Json::Value entities = root["entities"];
        for (unsigned int i = 0; i < entities.size(); ++i) {
            Json::Value entity = entities[i];
            Json::Value entityName = entity["text"];
            printf("NAMED ENTITY: %s\n", entityName.asString().c_str());
            std::string entityNameToLower = entityName.asString();
            std::transform(entityNameToLower.begin(), entityNameToLower.end(), entityNameToLower.begin(), ::tolower);
            namedEntityList.insert(entityNameToLower);
        }
    } else {
        printf("Error while parsing JSON file");
    }

    return namedEntityList;
}

SentimentAnalysis AlchemyAppCrawler::parseSentimentsFile(const char* sentimentInfo) {
    SentimentAnalysis analysis;
    Json::Value root;
    Json::Reader reader;
    float score = 0; 
    bool parsingSuccessful = reader.parse(sentimentInfo, root);

    if (parsingSuccessful) {
        if (root["status"].asString().compare("OK") == 0) {
            Json::Value sentimentAnalysis = root["docSentiment"];
            Json::Value retrievedStringScore = sentimentAnalysis["score"];
            printf("SCORE: %s\n", retrievedStringScore.asString().c_str());
            score = ::atof(retrievedStringScore.asString().c_str());
            analysis.makeScorePercentage(score);
            Json::Value retrievedLabel = sentimentAnalysis["type"];
            std::string label = retrievedLabel.asString();
            analysis.parseLabel(label);

        } else if(root["language"].asString().compare("english") != 0){
            
            printf("LANGUAGE NOT SUPPORTED BY SENTIMENT ANALYSIS\n");
            analysis.score_ = 0;
        }
        else{
            printf("RETRIEVED DATA ERROR\n");
        }
    } else {
        printf("Error while parsing JSON file\n");
    }

    return analysis;
}

std::string AlchemyAppCrawler::processTextToMakeRequest(std::string text) {

    for (int i = 0; i < text.size(); i++) {
        if (text.at(i) == ' ') {
            text.replace(i, 1, QUERY_SPACE_TOKEN);
        }
    }

    return text;
}
