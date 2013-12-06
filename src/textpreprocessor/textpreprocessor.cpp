#include "textpreprocessor.h"
#include <boost/algorithm/string.hpp>

using namespace std;

TextPreprocessor::TextPreprocessor()
{
    cleaner_ = new TextCleaner();
    stemmer_ = new Stemmer("spanish");
    matcher_ = new Matcher(stemmer_);
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
    string wordToFind = stemmer_->stem(toFind);
    
    for (messagesIt = tweets.begin(); messagesIt != tweets.end(); messagesIt++)
    {
        string textcleaned = cleaner_->clean(messagesIt->message_);
        std::vector<std::string> splittedMessages;
        boost::split(splittedMessages, textcleaned, boost::is_any_of("\t "));
        int matches = matcher_->match(splittedMessages, wordToFind);
        if(matches > 0)
        {
            results.push_back(Result(*messagesIt, matches));
        }
    }
    sort(results.begin(), results.end(), rank);
    return results;
}

