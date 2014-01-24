/* 
 * File:   Recognizer.h
 * Author: jorge
 *
 * Created on January 23, 2014, 10:59 AM
 */

#ifndef RECOGNIZER_H
#define	RECOGNIZER_H

#include <string>

#define ENGLISH "english"
#define SPANISH "spanish"

class Recognizer {
public:
    Recognizer(const std::string& trainingFile);
    ~Recognizer();
    const std::string recognize(const std::string& text);
private:
    void generateFrequencies(const std::string& text, float *frequencies);
private:
    struct fann *ann_;
};

#endif	/* RECOGNIZER_H */

