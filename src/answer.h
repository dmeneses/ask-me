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
#include "crawler.h"

class Answer {
public:
    std::vector<Result> ask(const std::string word,const Location location,const float radius,Crawler& crawler);
};

#endif	/* ANSWER_H */

