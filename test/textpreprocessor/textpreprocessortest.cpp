#include "textpreprocessor/textpreprocessor.h"
#include <gtest/gtest.h>

TEST(TextPreProcessor, GivenAOneTweet)
{
    TextPreprocessor* processor = new TextPreprocessor();
    std::vector<Tweet> tweets;
    tweets.push_back(Tweet("La comida de doña elena estaba rica!!!", 17, 65));
    
    std::vector<Tweet> results = processor->process(tweets, "comida");
    int size = results.size();
    EXPECT_EQ(1, size);
    //Improve test with mining and matches
    delete processor;
}

TEST(TextPreProcessor, GivenASeveralTweets)
{
    TextPreprocessor* processor = new TextPreprocessor();
    std::vector<Tweet> tweets;
    tweets.push_back(Tweet("La comida de doña elena esta rica!!!", 17, 65));
    tweets.push_back(Tweet("Hay bloqueos en el prado", 17, 64));
    tweets.push_back(Tweet("Hubo un accidente en la terminal... es un caos!!", 17, 64));
    tweets.push_back(Tweet("Hoy juega Bilstermann", 17, 64));
    
    std::vector<Tweet> results = processor->process(tweets, "comida");
    int size = results.size();
    EXPECT_EQ(4, size);
    //Improve test with mining and matches
    delete processor;
}
