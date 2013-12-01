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
    EXPECT_EQ(1, size);
    EXPECT_EQ("La comida de doña elena esta rica!!!", results.at(0).sentence);
    delete processor;
}

TEST(TextPreProcessor, GivenASeveralTweetsWithoutRootTerms)
{
    TextPreprocessor* processor = new TextPreprocessor();
    std::vector<Tweet> tweets;
    tweets.push_back(Tweet("Se bloquea todas la entradas en la universidad", 17, 65));
    tweets.push_back(Tweet("Tambien hay bloqueos en el prado", 17, 64));
    tweets.push_back(Tweet("Hubo una feria de comiditas en el correo!!", 17, 64));
    tweets.push_back(Tweet("Hoy juega Bilstermann", 17, 64));
    
    std::vector<Tweet> results = processor->process(tweets, "bloqueo");
    int size = results.size();
    EXPECT_EQ(2, size);
    EXPECT_EQ(tweets.at(0).sentence, results.at(0).sentence);
    EXPECT_EQ(tweets.at(1).sentence, results.at(1).sentence);
    delete processor;
}
