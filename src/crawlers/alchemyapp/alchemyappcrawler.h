/*
 * File:   alchemyappcrawler.h
 * Author: quique
 *
 * Created on January 21 20:01
 */

#ifndef ALCHEMYAPPCRAWLER_H
#define ALCHEMYAPPCRAWLER_H

#include <set>
#include <cstdio>
#include <string>

using namespace std;

enum SentimentLabel{
    POSITIVE,NEGATIVE,NEUTRAL
};

struct SentimentAnalysis{

    SentimentAnalysis(){
        
    }
    SentimentAnalysis(SentimentLabel label, float score): score_(score){
        this->label_ = label;
    }
    SentimentLabel label_;
    float score_;
    

    void parseLabel(std::string& label){
        if(label.compare("positive")){
            this->label_ = POSITIVE;
        }
        else if(label.compare("negative")){
            this->label_ = NEGATIVE;
        }
        else if(label.compare("neutral")){
             this->label_ = NEUTRAL;
        }
        else{
            printf("ERROR INCORRECT LABEL");
        }
    }
    void makeScorePercentage(float score){
        this->score_ = score*100;
    }
};
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
    std::set<std::string> collectAllNamedEntities(std::string& text);

     /**
     * Process text to make sentiment analysis.
     *
     * @param text to be evaluated.
     *
     * @return SentimentAnalysis that contains label and a score made by the analysis.
     */
    SentimentAnalysis makeSentimentAnalysis(std::string& text);

private:

    /**
     * Retrieve the given request and save the answer content in the given file.
     *
     * @param request Url to make the request and retrieve information.
     *
     * @return True if the request was successful in other case will return false.
     */
    const char* retrieve(const std::string& request);

    /**
     * Function to parse the json file returned by the query to alchmyapp.
     *
     * @param path Json file path.
     * @return Set of named entities found in the file.
     */
    std::set<std::string> parseNamedEntitiesFile(const char* namedEntitiesInfo);

    /**
     * Function to parse the json file returned by the query to alchmyapp sentiment.
     *
     * @param path Json file path.
     * @return SentimentAnalysis struct.
     */

    SentimentAnalysis parseSentimentsFile(const char* sentimentInfo);
    

    /**
     * Process text to make the query to alchemyapp
     *
     * @param text to be processed.
     */

    std::string processTextToMakeRequest(std::string text);

};

#endif // ALCHEMYAPPCRAWLER_H
