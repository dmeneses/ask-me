/* 
 * File:   textpreprocessor.h
 * Author: luis
 *
 * Created on 28 de noviembre de 2013, 18:19
 */

#ifndef TEXTPREPROCESSOR_H
#define	TEXTPREPROCESSOR_H

#include <string>
#include <vector>
#include <set>

#include "textcleaner.h"
#include "matcher.h"
#include "../stemmer/stemmer.h"
#include "socialinformation.h"
#include "../crawlers/semanticcrawler.h"
#include "../crawlers/alchemyapp/alchemyappcrawler.h"
#include "../crawlers/foursquare/foursquarecrawler.h"
/**
 * Wrapper for the information found
 */
struct Result
{

    /**
     * Constructor for the wrapper
     * 
     * @param information Social information
     * @param matchesCount Matches count
     */
    Result(SocialInformation information, int matchesCount,std::vector<Entity> namedEntities) : information(information),
    matchesCount(matchesCount),namedEntities(namedEntities)
    {
    }

    Result(SocialInformation information, int matchesCount) : information(information),
    matchesCount(matchesCount)
    {
    }

    SocialInformation information;
    int matchesCount;
    std::vector<Entity> namedEntities;

    bool operator==(const std::string& message) const
    {
        return this->information.message_ == message;
    }
};

/**
 * Class to prepare the text for the search and match the valuable information.
 */
class TextPreprocessor
{
public:

    /**
     * Creates a preprocessor for the defined language in lower case.
     * For example: "spanish"
     */
    TextPreprocessor(const std::string& language);
    /**
     * Clean all the resources to process the text.
     */
    TextPreprocessor(AlchemyAppCrawler& alchemy);
    
    ~TextPreprocessor();

    /**
     * Process the information and returns it ranked.
     * 
     * @param messages Information messages
     * @param searchParam Sentence to match with the messages
     * @param language Language of the received messages and search parameter
     * @param foursquareInformation information for places at foursquare
     * 
     * @return A ranked list with the results
     */
    std::vector<Result> process(std::vector<SocialInformation> messages, std::string searchParam);
    
    std::vector<Result> processWithPlaces(std::vector<SocialInformation> messages, std::string searchParam, 
    std::vector<SocialInformation> foursquareInformation);
    
    
private:
    std::vector< std::set<std::string> > getStemmedWordsToMatch(const std::string& keyword);
    std::vector<std::string> preprocessSearchParameter(const std::string& searchParam);
    std::vector<Entity> getAllNamedEntities(std::string& socialInformationText,std::vector<SocialInformation> foursquareInformation);
    
    TextCleaner* cleaner_;
    Matcher* matcher_;
    Stemmer* stemmer_;
    SemanticCrawler* semanticCrawler_;
    AlchemyAppCrawler* alchemyCrawler_;
    FoursquareCrawler* foursquareCrawler_;    
};

#endif	/* TEXTPREPROCESSOR_H */

