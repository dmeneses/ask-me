#include "textpreprocessor.h"
#include <string>
#include <algorithm>
#include <stdio.h>
#include <bits/stl_vector.h>     
#include "../ConceptNet/conceptnetcrawler.h"

using namespace std;

TextPreprocessor::TextPreprocessor()
{
    cleaner_ = new TextCleaner();
    stemmer_ = new Stemmer("spanish");
    matcher_ = new Matcher();
}

bool rank(const Result& result1, const Result& result2)
{
    return result1.matchesCount > result2.matchesCount;
}

std::vector<Result> TextPreprocessor::process(std::vector<SocialInformation> tweets,
                                              std::string searchParam)
{
    vector<Result> results;
    vector<SocialInformation>::iterator messagesIt;
    std::vector< std::set<std::string> > stemmedWordsToMatch = getStemmedWordsToMatch(searchParam);

    for (messagesIt = tweets.begin(); messagesIt != tweets.end(); messagesIt++)
    {
        std::string textCleaned = cleaner_->clean(messagesIt->message_);
        std::string stemmedSentence = stemmer_->stemSentence(textCleaned);
        int matches = matcher_->match(stemmedSentence, stemmedWordsToMatch);

        if (matches > 0)
        {
            printf("Information found : %s\n", stemmedSentence.c_str());
            results.push_back(Result(*messagesIt, matches));
        }
    }

    sort(results.begin(), results.end(), rank);
    return results;
}

std::vector< std::set<std::string> > TextPreprocessor::getStemmedWordsToMatch(const std::string& searchParam)
{
    std::vector< std::set<std::string> > result;
    
    ConceptNetCrawler conceptCrawler;
    std::vector<std::string> keywords = preprocessSearchParameter(searchParam);

    for (unsigned int i = 0; i < keywords.size(); i++)
    {
        std::string keyword = keywords.at(i);
        std::set<std::string> relatedWords = conceptCrawler.collectRelatedWords(keyword, "es");
        relatedWords.insert(keyword);

        std::set<std::string> stemmedRelatedWords;

        for (set<string>::iterator sentenceIt = relatedWords.begin();
                sentenceIt != relatedWords.end(); sentenceIt++)
        {
            stemmedRelatedWords.insert(stemmer_->stemSentence(*sentenceIt));
        }
        
        result.push_back(stemmedRelatedWords);
    }

    return result;
}


std::vector<std::string> TextPreprocessor::preprocessSearchParameter(const std::string& searchParam)
{
     std::string textCleaned = cleaner_->clean(searchParam);
     return stemmer_->split(textCleaned);
}