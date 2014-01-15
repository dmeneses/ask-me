/* 
 * File:   textcleaner.h
 * Author: luis
 *
 * Created on 28 de noviembre de 2013, 13:22
 */

#ifndef TEXTCLEANER_H
#define	TEXTCLEANER_H

#include <string>
#include "../structs/trie.h"

class TextCleaner
{
public:
    
    TextCleaner();
    
    std::string clean(std::string text);
    
    void removeSymbolsAndNumbers(std::string& text);
    
    std::string removeStopWords(std::string& text);
    
private:
    
    Trie* stopWords_;
    
    void loadStopWords();
};


#endif	/* TEXTCLEANER_H */

