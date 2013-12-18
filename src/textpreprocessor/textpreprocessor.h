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
    Result(SocialInformation information, int matchesCount) : information(information),
    matchesCount(matchesCount)
    {
    }

    SocialInformation information;
    int matchesCount;

    bool operator==(const std::string& message) const
    {
        return this->information.message_ == message;
    }
};

/**
 * Class to prepare the text for the search and matchs the valuable information.
 */
class TextPreprocessor
{
public:

    /**
     * Constructor
     */
    TextPreprocessor();

    /**
     * Process the information and returns it ranked.
     * 
     * @param tweets Information messages
     * @param toFind Word or words to find in the messages
     * 
     * @return A ranked list with the results
     */
    std::vector<Result> process(std::vector<SocialInformation> tweets, std::string toFind);

private:
    std::vector<std::string> split(std::string text);
    std::vector< std::set<std::string> > getStemmedWordsToMatch(const std::string& keyword);
    std::vector<std::string> preprocessSearchParameter(const std::string& searchParam);
    TextCleaner* cleaner_;
    Matcher* matcher_;
    Stemmer* stemmer_;
};

#endif	/* TEXTPREPROCESSOR_H */

