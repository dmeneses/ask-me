#include "textpreprocessor.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <stdio.h>     
#include <conceptnetcrawler.h>
        
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
    ConceptNetCrawler concept;
    set<string> relatedWordsSet = concept.collectRelatedWords(toFind, "es");
    string wordToFind = stemmer_->stem(toFind);

    for (messagesIt = tweets.begin(); messagesIt != tweets.end(); messagesIt++)
    {
        int matches = matcher_->matchWholeWords(relatedWordsSet, messagesIt->message_);
        string textcleaned = cleaner_->clean(messagesIt->message_);
        std::vector<std::string> splittedMessages = split(textcleaned);
        matches += matcher_->match(splittedMessages, wordToFind);
        
        if (matches > 0)
        {
            printf("Information found : %s\n", textcleaned.c_str());
            results.push_back(Result(*messagesIt, matches));
        }
    }
    sort(results.begin(), results.end(), rank);
    return results;
}

std::vector<std::string> TextPreprocessor::split(std::string text)
{
    string buffer;
    stringstream stream(text);
    vector<string> tokens;
    while (stream >> buffer)
        tokens.push_back(buffer);
    return tokens;
}
