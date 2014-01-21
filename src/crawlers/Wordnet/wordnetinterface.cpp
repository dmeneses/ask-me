/* 
 * File:   wordnetinterface.cpp
 * Author: dann
 * 
 * Created on January 20, 2014, 3:20 PM
 */

#include "wordnetinterface.h"

using namespace wnb;

WordnetInterface::WordnetInterface() : wordnetManager_("/usr/local/WordNet-3.0/dict/")
{
}

WordnetInterface::~WordnetInterface()
{
}

std::set<std::string> WordnetInterface::collectAllRelatedWords(const std::string& keyword,
                                             const std::vector<std::string>& wordList)
{
    wordnet wn("/usr/local/WordNet-3.0/dict/");
   
    std::set<std::string> res;
    std::vector<synset> relatedWords = wordnetManager_.get_synsets(keyword);

    for (unsigned int i = 0; i < relatedWords.size(); i++)
    {
        std::vector<std::string> foundWords = relatedWords.at(i).words;

        for (unsigned int j = 0; j < foundWords.size(); j++)
        {
            res.insert(foundWords.at(j));
        }
    }

    return res;
}
