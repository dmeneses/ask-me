/* 
 * File:   Recognizer.cpp
 * Author: jorge
 * 
 * Created on January 23, 2014, 10:59 AM
 */

#include "recognizer.h"
#include <vector>
#include <ctype.h>

Recognizer::Recognizer(const std::string& trainingFile) {
}

LANG Recognizer::recognize(const std::string& text)
{
    return ENGLISH;
}

void Recognizer::generateFrequencies(const std::string& text, float *frequencies)
{
    std::vector<unsigned int> letter_count(26, 0);
    unsigned int num_characters = 0;
    char c;
   
    for(unsigned int i = 0; i < text.size(); i++)
    {
        c = tolower(text.at(i));
        if (c >= 'a' && c <= 'z')
        {
            letter_count[c - 'a']++;
            num_characters++;
        }
    }
   
   
    for (unsigned int i = 0; i != 26; i++)
    {
        frequencies[i] = letter_count[i] / (double) num_characters;
    }
}