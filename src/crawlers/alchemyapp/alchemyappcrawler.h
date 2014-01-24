/*
 * File:   alchemyappcrawler.h
 * Author: quique
 *
 * Created on January 21 20:01
 */

#ifndef ALCHEMYAPPCRAWLER_H
#define ALCHEMYAPPCRAWLER_H

#include <set>
#include <string>

using namespace std;

class AlchemyAppCrawler
{
public:
    AlchemyAppCrawler();
    ~AlchemyAppCrawler();

    /**
     * Collect all the named entities given some text.
     *
     * @param text to search for named entities.
     *
     * @return Collection of named entities from the text.
     */
    std::set<string> collectAllNamedEntities(std::string& text);

     /**
     * Process text to make sentiment analysis.
     *
     * @param text to be evaluated.
     *
     * @return float score made by the analysis.
     */
    float makeSentimentAnalysis(std::string& text);

private:

    /**
     * Retrieve the given request and save the answer content in the given file.
     *
     * @param request Url to make the request and retrieve information.
     * @param filename Filename where the retrieved information will be saved.
     *
     * @return True if the request was successful in other case will return false.
     */
    bool retrieve(const string& request, const char* filename);

    /**
     * Function to parse the json file returned by the query to alchmyapp.
     *
     * @param path Json file path.
     * @return Set of named entities found in the file.
     */
    std::set<string> parseNamedEntitiesFile();

    /**
     * Function to parse the json file returned by the query to alchmyapp sentiment.
     *
     * @param path Json file path.
     * @return score of the sentiment analysis.
     */

    float parseSentimentsFile();
    /**
     * Delete the json file after parsing.
     *
     * @param filename File name to delete.
     */
    void deleteCreatedFile(const char* filename);

    /**
     * Process text to make the query to alchemyapp
     *
     * @param text to be processed.
     */

    string processTextToMakeRequest(std::string& text);

    char* namedEntitiesFile_;
    char* sentimentFile_;
};

#endif // ALCHEMYAPPCRAWLER_H
