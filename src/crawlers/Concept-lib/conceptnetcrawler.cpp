#include "conceptnetcrawler.h"
#include <json/reader.h>
#include <cstdio>
#include <stdio.h>
#include <fstream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <cstdlib>
#include <string.h>

#define JSON_FILE_NAME "retrieved.json"
#define JSON_PATH getJsonFilePath()
#define HOME "HOME"
#define CONCEPT_NET_URL "http://conceptnet5.media.mit.edu/data/5.1/c/"

ConceptNetCrawler::ConceptNetCrawler() {
    const char* text = getJsonFilePath();
    this->jsonPath_ = new char[strlen(text) + 1];
    strcpy(jsonPath_, text);
}

ConceptNetCrawler::ConceptNetCrawler(const ConceptNetCrawler& orig) {
}

ConceptNetCrawler::~ConceptNetCrawler() {
    if(this->jsonPath_)
        delete[] jsonPath_;
}

set<string> ConceptNetCrawler::collectRelatedWords(string word, string language) {
    string request = language + "/" + word;
    bool connected = connect(request);
    set<string> collectedWords = parseJsonFile();
    deleteCreatedFile();
    return collectedWords;
}

bool ConceptNetCrawler::connect(string request) {

    FILE *file;
    CURLcode res;
    string url = CONCEPT_NET_URL + request;
    CURL* curl = curl_easy_init();

    if (curl) {
        file = fopen(this->jsonPath_, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(file);
        return true;
    }
    
    return false;
}

set<string> ConceptNetCrawler::parseJsonFile() {

    set<string> wordsList;
    Json::Value root;
    Json::Reader reader;
    std::ifstream jsonContent(this->jsonPath_, std::ifstream::binary);
    bool parsingSuccessful = reader.parse(jsonContent, root);

    if (parsingSuccessful) {
        Json::Value edges = root["edges"];
        for (unsigned int i = 0; i < edges.size(); ++i) {
            Json::Value edge = edges[i];
            Json::Value relation = edge["rel"];

            if (relation.asString().compare("/r/TranslationOf") != 0) {
                Json::Value word = edge["text"];
                for (unsigned int j = 0; j < word.size(); ++j) {
                    wordsList.insert(word[j].asString());
                }
            }
        }
    } else {
        printf("Error while parsing JSON file");
    }

    return wordsList;
}

void ConceptNetCrawler::deleteCreatedFile() {
    if (remove(this->jsonPath_) != 0)
        perror("Error deleting file");
    else
        puts("File successfully deleted");
}

const char* ConceptNetCrawler::getJsonFilePath() {
    string res = getenv(HOME);
    res.append("/");
    res.append(JSON_FILE_NAME);
    return res.c_str();
}