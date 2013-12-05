#include "textpreprocessor.h"
#include <boost/algorithm/string.hpp>

using namespace std;

TextPreprocessor::TextPreprocessor()
{
    cleaner_ = new TextCleaner();
    stemmer_ = new Stemmer("spanish");
    matcher_ = new Matcher(stemmer_);
}

std::vector<SocialInformation> TextPreprocessor::process(std::vector<SocialInformation> tweets, 
        std::string toFind)
{
    vector<SocialInformation> results;
    vector<SocialInformation>::iterator messagesIt;
    string wordToFind = stemmer_->stem(toFind);
    
    for (messagesIt = tweets.begin(); messagesIt != tweets.end(); messagesIt++)
    {
        string textcleaned = cleaner_->clean(messagesIt->message_);
        std::vector<std::string> splittedMessages;
        boost::split(splittedMessages, textcleaned, boost::is_any_of("\t "));
        if(matcher_->match(splittedMessages, wordToFind)){
            results.push_back(*messagesIt);
        }
    }

    return results;
}

