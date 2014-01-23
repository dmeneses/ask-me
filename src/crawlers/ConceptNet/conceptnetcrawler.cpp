#include "conceptnetcrawler.h"
#include <json/reader.h>
#include <cstdio>
#include <stdio.h>
#include <fstream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <cstdlib>
#include <string.h>
#include <algorithm>

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

ConceptNetCrawler::~ConceptNetCrawler()
{
    if (this->associationsFile_)
        delete[] associationsFile_;
    if (this->relationsFile_)
        delete[] relationsFile_;
}

std::set<string> ConceptNetCrawler::collectAllRelatedWords(const std::string& word, const vector<string>& wordList) 
{
    set<string> relations = collectRelationships(word);
    set<string> associations = collectAssociations(wordList);
    relations.insert(associations.begin(), associations.end());
    return relations;
}

set<string> ConceptNetCrawler::collectRelationships(const std::string& word)
{
    string request(CONCEPT_NET_URL);
    request += "c/" + languageCode_ + "/" + word;
    set<string> collectedWords;

    if (retrieve(request, relationsFile_))
    {
        collectedWords = parseRelationsFile();
        deleteCreatedFile(relationsFile_);
    }

    return collectedWords;
}

set<string> ConceptNetCrawler::collectAssociations(const vector<string>& words)
{
    string request(CONCEPT_NET_URL);
    request += "assoc/list/" + languageCode_ + "/" + getWordsAsSentence(words);
    set<string> collectedWords;

    if (retrieve(request, associationsFile_))
    {
        collectedWords = parseAssociationsFile();
        deleteCreatedFile(associationsFile_);
    }

    return collectedWords;
}

std::string ConceptNetCrawler::getWordsAsSentence(const vector<string>& words)
{
    string res;
    for (unsigned int index = 0; index < words.size(); index++)
    {
        if (index != 0)
        {
            res.append(",");
        }

        res.append(words.at(index));
    }

    return res;
}

bool ConceptNetCrawler::retrieve(const string& request, const char* filename)
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

set<string> ConceptNetCrawler::parseRelationsFile()
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
                    printf("RELATION: %s\n", word[j].asString().c_str());
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

set<string> ConceptNetCrawler::parseAssociationsFile()
{
    set<string> wordsList;
    Json::Value root;
    Json::Reader reader;
    std::ifstream jsonContent(associationsFile_, std::ifstream::binary);
    bool parsingSuccessful = reader.parse(jsonContent, root);

    if (parsingSuccessful)
    {
        Json::Value associations = root["similar"];
        for (unsigned int i = 0; i < associations.size(); ++i)
        {
            Json::Value edge = associations[i];
            string association = edge[(Json::Value::UInt)0].asString().c_str();
            double percentage = edge[(Json::Value::UInt)1].asDouble();
            string assocWord;
            if (!(assocWord = processAssociation(association, percentage)).empty())
            {
                printf("ASSOC: %s\n", assocWord.c_str());
                wordsList.insert(assocWord);
            }
        }
    }
    else
    {
        printf("Error while parsing JSON file");
    }

    return wordsList;
}

std::string ConceptNetCrawler::processAssociation(const std::string& association, double percentage)
{
    unsigned int index;

    if ((index = association.find_last_of("/")) != std::string::npos)
    {
        std::string assocWord = association.substr(index + 1);
        if (assocWord.compare("neg") != 0 && percentage > 0.5)
        {
            std::replace(assocWord.begin(), assocWord.end(), '_', ' ');
            return assocWord;
        }
    }

    return "";
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