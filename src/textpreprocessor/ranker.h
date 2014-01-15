/* 
 * File:   ranker.h
 * Author: Luis Aguirre
 *
 * Created on 7 de enero de 2014, 11:19
 */

#ifndef RANKER_H
#define	RANKER_H

#include "textpreprocessor.h"

/**
 * Rank the social information by the matches or likes and shared counts
 * 
 * @param result1 Information 1
 * @param result2 Information 2
 * 
 * @return If the information 1 is before than the information 2
 */
bool rank(const Result& result1, const Result& result2)
{
    if(result1.matchesCount != result2.matchesCount)
        return result1.matchesCount > result2.matchesCount;
    
    if(result1.information.likesCount_ != result2.information.likesCount_)
        return result1.information.likesCount_ > result2.information.likesCount_;
    
    if(result1.information.sharedCount_ != result2.information.sharedCount_)
        return result1.information.sharedCount_ > result2.information.sharedCount_;
    
    return result1.matchesCount > result2.matchesCount;
}

#endif	/* RANKER_H */

