/* 
 * File:   Trie.h
 * Author: Luis Aguirre
 *
 * Created on 22 de noviembre de 2013, 14:24
 */

#ifndef TRIE_H
#define	TRIE_H

#include "trienode.h"

/**
 * Trie structure that will be used to load the dictionary for the stop words.
 */
class Trie
{
    
public:
    
    /**
     * Constructor
     */
    Trie();
    
    /**
     * Add a new word to the dictionary
     * 
     * @param s New word that will be added
     */
    void addWord(std::string s);
    
    /**
     * Search a word in the dictionary
     * 
     * @param s Word to find
     * 
     * @return True if the dictionary contains the word
     */
    bool searchWord(std::string s);

private:
    
    /**
     * Root of the trie
     */
    TrieNode* root_;
};

#endif	/* TRIE_H */

