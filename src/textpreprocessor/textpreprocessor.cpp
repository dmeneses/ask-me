#include "textpreprocessor.h"
#include <string>
#include <algorithm>
#include <stdio.h>     
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
                                              std::string toFind)
{
    vector<Result> results;
    vector<SocialInformation>::iterator messagesIt;
    set<string> stemmedWordsToMatch = getStemmedWordsToMatch(toFind);

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

set<std::string> TextPreprocessor::getStemmedWordsToMatch(const std::string& keyword)
{
    ConceptNetCrawler conceptCrawler;
    std::set<std::string> relatedWords = conceptCrawler.collectRelatedWords(keyword, "es");
    std::set<std::string> stemmedResult;

    for (set<string>::iterator sentenceIt = relatedWords.begin();
            sentenceIt != relatedWords.end(); sentenceIt++)
    {
        stemmedResult.insert(stemmer_->stemSentence(*sentenceIt));        
    }

    return stemmedResult;
}
