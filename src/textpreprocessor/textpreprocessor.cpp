#include "textpreprocessor.h"
#include "textcleaner.h"

using namespace std;

TextPreprocessor::TextPreprocessor()
{
}

vector<Tweet> TextPreprocessor::process(vector<Tweet> tweets)
{
    vector<Tweet> textProcessed;
    vector<Tweet>::iterator it;
    TextCleaner* cleaner = new TextCleaner();
    
    for(it = tweets.begin(); it != tweets.end(); it++)
    {
        string textcleaned = cleaner->clean(it->sentence);
        //text minning
        //Matches
        
        textProcessed.push_back(Tweet(textcleaned, it->latitude, it->longitude));
    }
    
    return textProcessed;
}
