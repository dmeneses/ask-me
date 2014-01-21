#include "textpreprocessor.h"
#include <string>
#include <algorithm>
#include <stdio.h>
#include <bits/stl_vector.h>     
#include "ranker.h"
#include "../crawlers/Wordnet/wordnetinterface.h"
#include "../crawlers/ConceptNet/conceptnetcrawler.h"

using namespace std;

TextPreprocessor::TextPreprocessor(const std::string& language)
{
    cleaner_ = new TextCleaner(language);
    stemmer_ = new Stemmer(language);
    matcher_ = new Matcher();

    if (language.compare("english") == 0)
    {
        semanticCrawler_ = new WordnetInterface();
    }
    else
    {
        semanticCrawler_ = new ConceptNetCrawler(language);
    }
}

TextPreprocessor::~TextPreprocessor()
{
    if (cleaner_)
        delete cleaner_;

    if (stemmer_)
        delete stemmer_;

    if (matcher_)
        delete matcher_;

    if (semanticCrawler_)
        delete semanticCrawler_;
}

std::vector<Result> TextPreprocessor::process(std::vector<SocialInformation> messages,
                                              std::string searchParam)
{
    vector<Result> results;
    vector<SocialInformation>::iterator messagesIt;
    std::vector< std::set<std::string> > stemmedWordsToMatch = getStemmedWordsToMatch(searchParam);

    for (messagesIt = messages.begin(); messagesIt != messages.end(); messagesIt++)
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


    std::vector<std::string> keywords = preprocessSearchParameter(searchParam);

    for (unsigned int i = 0; i < keywords.size(); i++)
    {
        std::string keyword = keywords.at(i);
        std::set<std::string> relatedWords = semanticCrawler_->collectAllRelatedWords(keyword, keywords);
        relatedWords.insert(keyword);

        std::set<std::string> stemmedRelatedWords;

        for (set<string>::iterator sentenceIt = relatedWords.begin();
                sentenceIt != relatedWords.end(); sentenceIt++)
        {
            cout << "KEYWORD: " << keyword << " | related: " << *sentenceIt << endl;
            string stemmedSentence = stemmer_->stemSentence(*sentenceIt);
            if (stemmedSentence.size() > 2)
                stemmedRelatedWords.insert(stemmedSentence);
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