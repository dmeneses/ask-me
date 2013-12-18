/* 
 * File:   stemmer.h
 * Author: dann
 *
 * Created on November 28, 2013, 5:17 PM
 */

#ifndef STEMMER_H
#define	STEMMER_H

#include <string>
#include <vector>
#include <set>

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

    /**
     * Apply stemming to each word in a sentence and keeps the sentence order.
     * @param sentence Sentence to stem.
     * 
     * @return Stemmed sentence.
     */
    std::string stemSentence(const std::string& sentence);

    /**
     * Split text by spaces.
     * @param text Text to split.
     * 
     * @return Vector containing each part of the text.
     */
    std::vector<std::string> split(std::string text);
private:
    void copyToBaseStruct(const std::string& word);

    sb_symbol* toStem_;
    unsigned int toStemSize_;
    sb_stemmer* stemmer_;
};

#endif	/* STEMMER_H */

