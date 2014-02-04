/* 
 * File:   answer.h
 * Author: jorge
 *
 * Created on December 11, 2013, 12:50 PM
 */

#ifndef ANSWER_H
#define	ANSWER_H

#include <vector>
#include "textpreprocessor/textpreprocessor.h"
#include "crawlers/crawler.h"
#include "langrecognition/recognizer.h"

enum SocialSource
{
    TWITTER,
    FACEBOOK,
    FOURSQUARE
};

class Answer {
public:
    std::vector<Result> ask(const std::string word, const Location location, const float radio, 
            SocialSource source, bool enablePlacesLocation);
    Answer();
    ~Answer();
    std::vector<Result> ask(const std::string word, const Location location, const float radio, SocialSource source);
private:
    SocialInformationList recollect(const Location location, const float radio, SocialSource crawler);
    Recognizer* reconizer_;
};

#endif	/* ANSWER_H */

