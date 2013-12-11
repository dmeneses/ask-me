/* 
 * File:   answer.cpp
 * Author: jorge
 * 
 * Created on December 11, 2013, 12:50 PM
 */

#include "answer.h"

std::vector<Result> Answer::ask(const std::string word, const Location location, const float radius, SocialSource source)
{
    SocialInformationList info;
    switch(source)
    {
        case TWITTER:
            info = recollect(location, radius);
            break;
        case FACEBOOK:
            //Not implemented
            break;
    }
    TextPreprocessor processor;
    
    return processor.process(info, word);
}


SocialInformationList Answer::recollect(const Location location, const float radius)
{
    SocialInformationList info;
    
    return info;
}
