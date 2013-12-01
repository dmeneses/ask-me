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

    /**
     * Apply stemming to a word.
     * 
     * @param word Word to stem.
     * @return The stemmed word.
     */
    std::string stem(const std::string& word);

private:
    sb_symbol* convertToUnsignedChar(const std::string& word);
    std::string convertToString(const sb_symbol* word);
    
    const std::string language_;
};

#endif	/* STEMMER_H */

