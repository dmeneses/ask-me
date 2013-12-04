#include "textpreprocessor/textpreprocessor.h"
#include <gtest/gtest.h>

TEST(TextPreProcessor, GivenAOneTweet)
{
    TextPreprocessor* processor = new TextPreprocessor();
    std::vector<SocialInformation> tweets;
    tweets.push_back(SocialInformation("La comida de doña elena estaba rica!!!", 17, 65));
    
    std::vector<SocialInformation> results = processor->process(tweets, "comida");
    int size = results.size();
    EXPECT_EQ(1, size);   
    delete processor;
}

TEST(TextPreProcessor, GivenASeveralTweets)
{
    TextPreprocessor* processor = new TextPreprocessor();
    std::vector<SocialInformation> tweets;
    tweets.push_back(SocialInformation("La comida de doña elena esta rica!!!", 17, 65));
    tweets.push_back(SocialInformation("Hay bloqueos en el prado", 17, 64));
    tweets.push_back(SocialInformation("Hubo un accidente en la terminal... es un caos!!", 17, 64));
    tweets.push_back(SocialInformation("Hoy juega Bilstermann", 17, 64));
    
    std::vector<SocialInformation> results = processor->process(tweets, "comida");
    int size = results.size();
    EXPECT_EQ(1, size);
    EXPECT_EQ("La comida de doña elena esta rica!!!", results.at(0).message_);
    delete processor;
}

TEST(TextPreProcessor, GivenASeveralTweetsWithoutRootTerms)
{
    TextPreprocessor* processor = new TextPreprocessor();
    std::vector<SocialInformation> tweets;
    tweets.push_back(SocialInformation("Se bloquea todas la entradas en la universidad", 17, 65));
    tweets.push_back(SocialInformation("Tambien hay bloqueos en el prado", 17, 64));
    tweets.push_back(SocialInformation("Hubo una feria de comiditas en el correo!!", 17, 64));
    tweets.push_back(SocialInformation("Hoy juega Bilstermann", 17, 64));
    
    std::vector<SocialInformation> results = processor->process(tweets, "bloqueo");
    int size = results.size();
    EXPECT_EQ(2, size);
    EXPECT_EQ(tweets.at(0).message_, results.at(0).message_);
    EXPECT_EQ(tweets.at(1).message_, results.at(1).message_);
    delete processor;
}
