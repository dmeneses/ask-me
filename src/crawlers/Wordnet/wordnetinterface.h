/* 
 * File:   wordnetinterface.h
 * Author: dann
 *
 * Created on January 20, 2014, 3:20 PM
 */

#ifndef WORDNETINTERFACE_H
#define	WORDNETINTERFACE_H

#include "../semanticcrawler.h"
#include <boost/algorithm/string.hpp>
#include <wnb/core/wordnet.hh>
#include "../../textpreprocessor/textcleaner.h"
#include "../../stemmer/stemmer.h"

struct ProcessedSynset;

class WordnetInterface : public SemanticCrawler
{
public:
    WordnetInterface();
    ~WordnetInterface();

    std::set<std::string> collectAllRelatedWords(const std::string& keyword,
                                                 const std::vector<std::string>& wordList);

    std::map<std::string, std::vector< wnb::synset> > getAllRelatedSynsets(const std::vector<std::string>& wordList);
    std::list<std::string> getWordsForSimilarSenses(std::list<ProcessedSynset>& original, std::list<ProcessedSynset>& toCompare);
    std::list<ProcessedSynset> processSynset(const std::vector<wnb::synset>& synsets);
private:
    wnb::wordnet wordnetManager_;
    TextCleaner* cleaner_;
    Stemmer* stemmer_;
    std::string language_;

};

struct ProcessedSynset
{
    std::vector<std::string> glossWords_;
    std::vector<std::string> terms_;

    ProcessedSynset(const std::string& gloss, const std::vector<std::string>& terms) : terms_(terms)
    {
        boost::split(glossWords_, gloss, boost::is_any_of(" "));

        for (unsigned int i = 0; i < terms_.size(); i++)
        {
            std::replace(terms_.at(i).begin(), terms_.at(i).end(), '_', ' ');
        }
    }

};

#endif	/* WORDNETINTERFACE_H */

