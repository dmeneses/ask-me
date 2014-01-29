/* 
 * File:   ranker.h
 * Author: Luis Aguirre
 *
 * Created on 7 de enero de 2014, 11:19
 */

#ifndef RANKER_H
#define	RANKER_H

#include "textpreprocessor.h"
#include <typeinfo>

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
    
    //To know if the information is a tweet.
    if(typeid(result1.information) == typeid(TweetInfo) &&
       typeid(result2.information) == typeid(TweetInfo))
    {
        //Casting the information to tweet infos.
        const TweetInfo* tweet1 = reinterpret_cast<const TweetInfo*>(&result1.information);
        const TweetInfo* tweet2 = reinterpret_cast<const TweetInfo*>(&result2.information);
        
        if(tweet1->likesCount_ != tweet2->likesCount_)
            return tweet1->likesCount_ > tweet2->likesCount_;
    
        if(tweet1->sharedCount_ != tweet2->sharedCount_)
            return tweet1->sharedCount_ > tweet2->sharedCount_;
    }
    
    return result1.matchesCount > result2.matchesCount;
}

#endif	/* RANKER_H */

