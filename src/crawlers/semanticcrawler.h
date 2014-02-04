/* 
 * File:   SemanticCrawler.h
 * Author: dann
 *
 * Created on January 20, 2014, 5:43 PM
 */

#ifndef SEMANTICCRAWLER_H
#define	SEMANTICCRAWLER_H

#include <set>
#include <vector>
#include <string>

class SemanticCrawler
{
public:

    virtual ~SemanticCrawler() {};
    virtual std::set<std::string> collectAllRelatedWords(const std::string& word, const std::vector<std::string>& wordList) = 0;
private:

};

#endif	/* SEMANTICCRAWLER_H */

