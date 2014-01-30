#include "structs/trie.h"
#include <gtest/gtest.h>

TEST(TrieTest, SearchExistentWord)
{
    Trie* dictionary = new Trie();
    dictionary->addWord("Hola");
    
    EXPECT_TRUE(dictionary->searchWord("Hola"));
    delete dictionary;
}

TEST(TrieTest, SearchNonxistentWord)
{
    Trie* dictionary = new Trie();
    dictionary->addWord("Hola");
    
    EXPECT_FALSE(dictionary->searchWord("hola"));
    EXPECT_FALSE(dictionary->searchWord("Hol"));
    delete dictionary;
}

TEST(TrieTest, SearchExistentWord2)
{
    Trie* dictionary = new Trie();
    dictionary->addWord("Hola");
    dictionary->addWord("Hello");
    dictionary->addWord("Hell");
    
    EXPECT_TRUE(dictionary->searchWord("Hola"));
    EXPECT_TRUE(dictionary->searchWord("Hello"));
    EXPECT_TRUE(dictionary->searchWord("Hell"));
    delete dictionary;
}


