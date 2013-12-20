#include "conceptnetcrawler.h"
#include <json/reader.h>
#include <cstdio>
#include <stdio.h>
#include <fstream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <cstdlib>
#include <string.h>

#define JSON_FILE_REL "retrievedRelations.json"
#define JSON_FILE_ASSO "retrievedAssociations.json"
#define JSON_PATH getJsonFilePath()
#define HOME "HOME"
#define CONCEPT_NET_URL "http://conceptnet5.media.mit.edu/data/5.1/"
#define ENGLISH "english"
#define SPANISH "spanish"
#define ENGLISH_CODE "en"
#define SPANISH_CODE "es"

ConceptNetCrawler::ConceptNetCrawler(const std::string& language)
{
    const char* text = getJsonFilePath(JSON_FILE_REL);
    this->relationsFile_ = new char[strlen(text) + 1];
    strcpy(relationsFile_, text); 
    
    const char* text2 = getJsonFilePath(JSON_FILE_ASSO);
    this->associationsFile_ = new char[strlen(text2) + 1];
    strcpy(associationsFile_, text2); 
    //TODO: if no language found throw an exception.
    languageCode_ = getLanguageCode(language);
}

std::string ConceptNetCrawler::getLanguageCode(const std::string& language)
{
    if (language.compare(SPANISH) == 0) return SPANISH_CODE;

    return ENGLISH_CODE;
}

ConceptNetCrawler::~ConceptNetCrawler() {
    if(this->associationsFile_)
        delete[] associationsFile_;
    if(this->relationsFile_)
        delete[] relationsFile_;
}

set<string> ConceptNetCrawler::collectRelatedWords(string word)
{
    string request = "c/" + languageCode_ + "/" + word;
    bool connected = retrieveRelations(request);
    set<string> collectedWords = parseJsonFile();
    deleteCreatedFile(relationsFile_);
    return collectedWords;
}

bool ConceptNetCrawler::retrieveRelations(string request)
{

    bool res = false;
    FILE *file;
    CURLcode curlRes;
    string url = CONCEPT_NET_URL + request;
    CURL* curl = curl_easy_init();

    if (curl)
    {
        file = fopen(relationsFile_, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        curlRes = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(file);
        res = true;
    }

    return res;
}

set<string> ConceptNetCrawler::parseJsonFile()
{

    set<string> wordsList;
    Json::Value root;
    Json::Reader reader;
    std::ifstream jsonContent(relationsFile_, std::ifstream::binary);
    bool parsingSuccessful = reader.parse(jsonContent, root);

    if (parsingSuccessful)
    {
        Json::Value edges = root["edges"];
        for (unsigned int i = 0; i < edges.size(); ++i)
        {
            Json::Value edge = edges[i];
            Json::Value relation = edge["rel"];

            if (relation.asString().compare("/r/TranslationOf") != 0)
            {
                Json::Value word = edge["text"];
                for (unsigned int j = 0; j < word.size(); ++j)
                {
                    wordsList.insert(word[j].asString());
                }
            }
        }
    }
    else
    {
        printf("Error while parsing JSON file");
    }

    return wordsList;
}

void ConceptNetCrawler::deleteCreatedFile(const char* filename)
{
    if (remove(filename) != 0)
        perror("Error deleting file");
    else
        puts("File successfully deleted");
}

const char* ConceptNetCrawler::getJsonFilePath(const char* filename)
{
    string res = getenv(HOME);
    res.append("/");
    res.append(filename);
    return res.c_str();
}