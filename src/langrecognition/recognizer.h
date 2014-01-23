/* 
 * File:   Recognizer.h
 * Author: jorge
 *
 * Created on January 23, 2014, 10:59 AM
 */

#ifndef RECOGNIZER_H
#define	RECOGNIZER_H

#include <string>

enum LANG 
{
    ENGLISH, SPANISH
};

class Recognizer {
public:
    Recognizer(const std::string& trainingFile);
    LANG recognize(const std::string& text);
private:
    void generateFrequencies(const std::string& text, float *frequencies);
};

#endif	/* RECOGNIZER_H */

