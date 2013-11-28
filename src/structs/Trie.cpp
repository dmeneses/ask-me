#include "Trie.h"

Trie::Trie()
{
    root_ = new TrieNode();
}

void Trie::addWord(std::string s)
{
    TrieNode* current = root_;

    if (s.length() == 0)
    {
        current->setWordMarker(); // an empty word
        return;
    }

    for (int i = 0; i < s.length(); i++)
    {
        TrieNode* child = current->findChild(s[i]);
        if (child != NULL)
        {
            current = child;
        }
        else
        {
            TrieNode* tmp = new TrieNode();
            tmp->setContent(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if (i == s.length() - 1)
            current->setWordMarker();
    }
}

bool Trie::searchWord(std::string s)
{
    TrieNode* current = root_;

    while (current != NULL)
    {
        for (int i = 0; i < s.length(); i++)
        {
            TrieNode* tmp = current->findChild(s[i]);
            if (tmp == NULL)
                return false;
            current = tmp;
        }

        if (current->wordMarker())
            return true;
        else
            return false;
    }

    return false;
}

