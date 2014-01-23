/* 
 * File:   wordnetinterface.cpp
 * Author: dann
 * 
 * Created on January 20, 2014, 3:20 PM
 */

#include "wordnetinterface.h"

using namespace wnb;

WordnetInterface::WordnetInterface() : wordnetManager_("/usr/local/WordNet-3.0/dict/"), language_("english")
{
    cleaner_ = new TextCleaner(language_);
    stemmer_ = new Stemmer(language_);
}

WordnetInterface::~WordnetInterface()
{
    if (cleaner_)
        delete cleaner_;

    if (stemmer_)
        delete stemmer_;

}

std::set<std::string> WordnetInterface::collectAllRelatedWords(const std::string& keyword,
                                                               const std::vector<std::string>& wordList)
{
    std::set<std::string> res;

    std::map<std::string, std::vector<synset> > relatedSynsets = getAllRelatedSynsets(wordList);
    std::list<ProcessedSynset> mainProcessedSynset = processSynset(relatedSynsets[keyword]);

    for (std::map<std::string, std::vector<synset> >::iterator it = relatedSynsets.begin(); it != relatedSynsets.end(); ++it)
    {
        if ((it->first).compare(keyword) != 0)
        {
            std::list<ProcessedSynset> secondaryProcessedSynset = processSynset(it->second);
            std::list<std::string> foundWords = getWordsForSimilarSenses(mainProcessedSynset, secondaryProcessedSynset);
            res.insert(foundWords.begin(), foundWords.end());
        }
    }

    return res;
}

std::list<ProcessedSynset> WordnetInterface::processSynset(const std::vector<synset>& synsets)
{
    std::list<ProcessedSynset> res;

    for (unsigned int i = 0; i < synsets.size(); i++)
    {
        synset aSynset = synsets.at(i);
        std::string textCleaned = cleaner_->clean(aSynset.gloss);
        std::string stemmedSentence = stemmer_->stemSentence(textCleaned);
        ProcessedSynset processedSynset(stemmedSentence, aSynset.words);
        res.push_back(processedSynset);
    }
    return res;
}

std::map<std::string, std::vector<synset> > WordnetInterface::getAllRelatedSynsets(const std::vector<std::string>& wordList)
{
    std::map < std::string, std::vector<synset> > res;
    for (unsigned int i = 0; i < wordList.size(); i++)
    {
        std::vector<synset> relatedSynsets = wordnetManager_.get_synsets(wordList.at(i));
        res.insert(std::pair<std::string, std::vector<synset> >(wordList.at(i), relatedSynsets));
    }

    return res;
}

std::list<std::string> WordnetInterface::getWordsForSimilarSenses(std::list<ProcessedSynset>& original, std::list<ProcessedSynset>& toCompare)
{
    std::list<std::string> res;
    std::list<std::string>::iterator resIterator = res.begin();

    for (std::list<ProcessedSynset>::iterator originalSynset = original.begin(); originalSynset != original.end(); ++originalSynset)
    {
        ProcessedSynset mainSynset = *originalSynset;

        for (std::list<ProcessedSynset>::iterator synsetToCompare = toCompare.begin(); synsetToCompare != toCompare.end(); ++synsetToCompare)
        {
            ProcessedSynset secondarySynset = *synsetToCompare;
            unsigned int index = 0;
            bool notFound = true;

            while (index < mainSynset.glossWords_.size() && notFound)
            {
                if (std::find(secondarySynset.glossWords_.begin(), secondarySynset.glossWords_.end(),
                              mainSynset.glossWords_.at(index)) != secondarySynset.glossWords_.end())
                {
                    res.insert(resIterator, secondarySynset.terms_.begin(), secondarySynset.terms_.end());
                    res.insert(resIterator, mainSynset.terms_.begin(), mainSynset.terms_.end());
                    notFound = false;
                }

                index++;
            }
        }
    }

    return res;
}