/* 
 * File:   TrieNode.h
 * Author: Luis Aguirre
 *
 * Created on 22 de noviembre de 2013, 14:19
 */

#ifndef TRIENODE_H
#define	TRIENODE_H

#include <string>
#include <iostream>
#include <vector>

/**
 * Node for the trie structure
 */
class TrieNode
{
public:

    /**
     * Constructor
     */
    TrieNode();

    /**
     * Get the data of the node
     * 
     * @return Data of the node
     */
    char content();

    /**
     * Change the content of the node
     * 
     * @param c New value for the data
     */
    void setContent(char c);

    /**
     * Get true if the node is a word marker
     * 
     * @return true if the node is a word marker
     */
    bool wordMarker();

    /**
     * Change the node to a word marker
     */
    void setWordMarker();

    /**
     * Find a child
     * 
     * @param c Value that will be found
     * 
     * @return The node that contains c if it does not find return NULL
     */
    TrieNode* findChild(char c);

    /**
     * Add a child
     * 
     * @param child Trie node that will be added
     */
    void appendChild(TrieNode* child);

    /**
     * Get the children of the node
     * 
     * @return The children of the node
     */
    std::vector<TrieNode*> children();

private:
    /**
     * data of the node
     */
    char content_;
    
    /**
     * Word marker
     */
    bool marker_;
    
    /**
     * Children of the node
     */
    std::vector<TrieNode*> chidren_;
};

#endif	/* TRIENODE_H */

