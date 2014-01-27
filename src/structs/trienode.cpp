#include "trienode.h"

TrieNode::TrieNode() : content_(' '), marker_(false)
{
}

char TrieNode::content()
{
    return content_;
}

void TrieNode::setContent(char c)
{
    content_ = c;
}

bool TrieNode::wordMarker()
{
    return marker_;
}

void TrieNode::setWordMarker()
{
    marker_ = true;
}

TrieNode* TrieNode::findChild(char c)
{
    for (unsigned int i = 0; i < chidren_.size(); i++)
    {
        TrieNode* tmp = chidren_.at(i);
        if (tmp->content() == c)
        {
            return tmp;
        }
    }

    return NULL;
}

void TrieNode::appendChild(TrieNode* child)
{
    chidren_.push_back(child);
}

std::vector<TrieNode*> TrieNode::children()
{
    return chidren_;
}

