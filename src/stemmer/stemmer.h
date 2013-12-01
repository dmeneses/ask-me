/* 
 * File:   stemmer.h
 * Author: dann
 *
 * Created on November 28, 2013, 5:17 PM
 */

#ifndef STEMMER_H
#define	STEMMER_H

#include <string>
#include "libstemmer.h"

/**
 * Will apply Porter stemming algorithm to words.
 */
class Stemmer
{
public:
    /**
     * Creates a stemmer for the specified language.
     * 
     * @param language Language to steam words. Must be in lower case.
     */
    Stemmer(const std::string& language);
    
    ~Stemmer();
    
    /**
     * Apply stemming to a word.
     * 
     * @param word Word to stem.
     * @return The stemmed word.
     */
    std::string stem(const std::string& word);

private:
    void copyToBaseStruct(const std::string& word);
    
    sb_symbol* toStem_;
    unsigned int toStemSize_;
    sb_stemmer* stemmer_;
};

#endif	/* STEMMER_H */

