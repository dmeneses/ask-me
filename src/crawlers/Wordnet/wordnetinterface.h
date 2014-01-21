/* 
 * File:   wordnetinterface.h
 * Author: dann
 *
 * Created on January 20, 2014, 3:20 PM
 */

#ifndef WORDNETINTERFACE_H
#define	WORDNETINTERFACE_H

#include "../semanticcrawler.h"
#include <wnb/core/wordnet.hh>


class WordnetInterface : public SemanticCrawler
{
public:
    WordnetInterface();
    ~WordnetInterface();

    std::set<std::string> collectAllRelatedWords(const std::string& keyword,
                                                 const std::vector<std::string>& wordList);
private:
    wnb::wordnet wordnetManager_;


};

#endif	/* WORDNETINTERFACE_H */

