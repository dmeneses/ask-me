#include "textpreprocessor.h"
#include <boost/algorithm/string.hpp>

using namespace std;

TextPreprocessor::TextPreprocessor()
{
    cleaner_ = new TextCleaner();
    stemmer_ = new Stemmer("spanish");
    matcher_ = new Matcher(stemmer_);
}

vector<Tweet> TextPreprocessor::process(vector<Tweet> tweets, string toFind)
{
    vector<Tweet> results;
    vector<Tweet>::iterator tweetIterator;
    string wordToFind = stemmer_->stem(toFind);
    for (tweetIterator = tweets.begin(); tweetIterator != tweets.end(); tweetIterator++)
    {
        string textcleaned = cleaner_->clean(tweetIterator->sentence);
        std::vector<std::string> splittedTweet;
        boost::split(splittedTweet, textcleaned, boost::is_any_of("\t "));
        if(matcher_->match(splittedTweet, wordToFind)){
            results.push_back(*tweetIterator);
        }
    }

    return results;
}

