#include "conceptnetcrawler.h"
#include <curl/curl.h>
#include <json/reader.h>
#include <algorithm>
#include "utils.h"

#define CONCEPT_NET_URL "http://conceptnet5.media.mit.edu/data/5.1/"
#define ENGLISH "english"
#define SPANISH "spanish"
#define ENGLISH_CODE "en"
#define SPANISH_CODE "es"

ConceptNetCrawler::ConceptNetCrawler(const std::string& language)
{
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
}

std::set<std::string> ConceptNetCrawler::collectAllRelatedWords(const std::string& word, const std::vector<std::string>& wordList)
{
    std::set<std::string> relations = collectRelationships(word);
    std::set<std::string> associations = collectAssociations(wordList);
    relations.insert(associations.begin(), associations.end());
    return relations;
}

std::set<std::string> ConceptNetCrawler::collectRelationships(const std::string& word)
{
    std::string request(CONCEPT_NET_URL);
    request += "c/" + languageCode_ + "/" + word;
    const char* jsonResult = retrieve(request);
    return parseRelationsData(jsonResult);
}

std::set<std::string> ConceptNetCrawler::collectAssociations(const std::vector<std::string>& words)
{
    std::string request(CONCEPT_NET_URL);
    request += "assoc/list/" + languageCode_ + "/" + getWordsAsSentence(words);
    const char* jsonResult = retrieve(request);
    return parseAssociationsData(jsonResult);
}

std::string ConceptNetCrawler::getWordsAsSentence(const std::vector<std::string>& words)
{
    std::string res;
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

const char* ConceptNetCrawler::retrieve(const std::string& request)
{
    iostring readData;
    init_string(&readData);
    CURL* curl = curl_easy_init();

    if (curl)
    {
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

std::set<std::string> ConceptNetCrawler::parseRelationsData(const char* relationsInfo)
{

    std::set<std::string> wordsList;
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(relationsInfo, root);

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

std::set<std::string> ConceptNetCrawler::parseAssociationsData(const char* associationsInfo)
{
    std::set<std::string> wordsList;
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(associationsInfo, root);

    if (parsingSuccessful)
    {
        Json::Value associations = root["similar"];
        for (unsigned int i = 0; i < associations.size(); ++i)
        {
            Json::Value edge = associations[i];
            std::string association = edge[(Json::Value::UInt)0].asString().c_str();
            double percentage = edge[(Json::Value::UInt)1].asDouble();
            std::string assocWord;
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