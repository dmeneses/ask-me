#include "alchemyappcrawler.h"
#include <json/reader.h>
#include <cstdio>
#include <stdio.h>
#include <fstream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <cstdlib>
#include <string.h>
#include <algorithm>

#define ALCHEMYAPP_URL "http://access.alchemyapi.com/calls/text/SEARCHPARAMETER?outputMode=json&apikey=0d752536a9762c9ae2fb868d57e4beaade74f1a2&text="
#define ENTITY_EXTRACTION_KEYWORD "TextGetNamedEntities"
#define SENTIMENT_EXTRACTION_KEYWORD "TextGetTextSentiment"
#define JSON_OUTPUT_MODE "outputMode=json&"
#define API_KEY "apikey=0d752536a9762c9ae2fb868d57e4beaade74f1a2&"
#define JSON_FILE_NAMED_ENTITY "namedentities.json"
#define JSON_FILE_SENTIMENT_ANALYSIS "sentiment.json"
#define QUERY_SPACE_TOKEN "%20"
#define JSON_FILE_NAME_LENGTH 19
#define SEARCH_PARAMETER_POSITION 40
#define SEARCH_PARAMETER_SIZE 15
AlchemyAppCrawler::AlchemyAppCrawler()
{
    this->namedEntitiesFile_ = new char[JSON_FILE_NAME_LENGTH];
    strcpy(namedEntitiesFile_, JSON_FILE_NAMED_ENTITY);
    this->sentimentFile_ = new char[15];
    strcpy(sentimentFile_,JSON_FILE_SENTIMENT_ANALYSIS);
}


AlchemyAppCrawler::~AlchemyAppCrawler()
{
    if (this->namedEntitiesFile_)
           delete[] namedEntitiesFile_;
    if(this->sentimentFile_)
           delete this->sentimentFile_;
}


set<string> AlchemyAppCrawler::collectAllNamedEntities(std::string& text)
{
    string request(ALCHEMYAPP_URL);

    request.replace(SEARCH_PARAMETER_POSITION,SEARCH_PARAMETER_SIZE,ENTITY_EXTRACTION_KEYWORD);
    string processedText =processTextToMakeRequest(text);
    request += processedText;

       set<string> collectedWords;

       if (retrieve(request, namedEntitiesFile_))

       {
           collectedWords = parseNamedEntitiesFile();
           deleteCreatedFile(namedEntitiesFile_);
       }

       return collectedWords;
}

float AlchemyAppCrawler::makeSentimentAnalysis(std::string& text){
    float score = 0;
    string request(ALCHEMYAPP_URL);

    request.replace(SEARCH_PARAMETER_POSITION,SEARCH_PARAMETER_SIZE,SENTIMENT_EXTRACTION_KEYWORD);
    string processedText =processTextToMakeRequest(text);
    request += processedText;

       if (retrieve(request, sentimentFile_))

       {
           score = parseSentimentsFile();
           deleteCreatedFile(sentimentFile_);
       }

       return score;
}

bool AlchemyAppCrawler::retrieve(const string& request, const char* filename)
{
    bool res = false;
    FILE *file;
    CURLcode curlRes;
    CURL* curl = curl_easy_init();

    if (curl)
    {
        file = fopen(filename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, request.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        curlRes = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(file);
        res = true;
    }

    return res;
}

set<string> AlchemyAppCrawler::parseNamedEntitiesFile()
{
    set<string> namedEntityList;
    Json::Value root;
    Json::Reader reader;
    std::ifstream jsonContent(namedEntitiesFile_, std::ifstream::binary);
    bool parsingSuccessful = reader.parse(jsonContent, root);

    if (parsingSuccessful)
    {
        Json::Value entities = root["entities"];
        for (unsigned int i = 0; i < entities.size(); ++i)
        {
            Json::Value entity = entities[i];
            Json::Value entityName = entity["text"];
            printf("NAMED ENTITY: %s\n", entityName.asString().c_str());
            string entityNameToLower = entityName.asString();
            std::transform(entityNameToLower.begin(), entityNameToLower.end(), entityNameToLower.begin(), ::tolower);
            namedEntityList.insert(entityNameToLower);
        }
    }
    else
    {
        printf("Error while parsing JSON file");
    }

    return namedEntityList;
}

float AlchemyAppCrawler::parseSentimentsFile(){
    float score = 0;
    Json::Value root;
    Json::Reader reader;
    std::ifstream jsonContent(sentimentFile_, std::ifstream::binary);
    bool parsingSuccessful = reader.parse(jsonContent, root);

    if (parsingSuccessful)
    {
        Json::Value sentimentAnalysis = root["docSentiment"];
            Json::Value score1 = sentimentAnalysis["score"];
            printf("SCORE: %s\n", score1.asString().c_str());
            score = ::atof(score1.asString().c_str());
    }
    else
    {
        printf("Error while parsing JSON file");
    }

    return score;


}
void AlchemyAppCrawler::deleteCreatedFile(const char* filename)
{
    if (remove(filename) != 0)
        perror("Error deleting file");
    else
        puts("File successfully deleted");
}

string AlchemyAppCrawler::processTextToMakeRequest(std::string& text){

    for(int i=0; i< text.size(); i++) {
           if(text.at(i) == ' ') {
               text.replace( i, 1, QUERY_SPACE_TOKEN);
           }
       }

    return text;
}
