#include "textpreprocessor/textpreprocessor.h"
#include <gtest/gtest.h>
#include <algorithm>

TEST(TextPreProcessor, GivenAOneTweet)
{
    TextPreprocessor* processor = new TextPreprocessor("spanish");
    std::vector<SocialInformation> tweets;
    tweets.push_back(SocialInformation("La comida de doña elena estaba rica!!!", 17, 65));
    
    std::vector<Result> results = processor->process(tweets, "comida");
    int size = results.size();
    EXPECT_EQ(1, size);   
    delete processor;
}

TEST(TextPreProcessor, GivenASeveralTweets)
{
    TextPreprocessor* processor = new TextPreprocessor("spanish");
    std::vector<SocialInformation> tweets;
    tweets.push_back(SocialInformation("La comida de doña elena esta rica!!!", 17, 65));
    tweets.push_back(SocialInformation("Hay bloqueos en el prado", 17, 64));
    tweets.push_back(SocialInformation("Hubo un accidente en la terminal... es un caos!!", 17, 64));
    tweets.push_back(SocialInformation("Hoy juega Bilstermann", 17, 64));
    
    std::vector<Result> results = processor->process(tweets, "comida");
    int size = results.size();
    EXPECT_EQ(1, size);
    EXPECT_EQ("La comida de doña elena esta rica!!!", results.at(0).information.message_);
    delete processor;
}

TEST(TextPreProcessor, GivenASeveralTweetsWithoutRootTerms)
{
    TextPreprocessor* processor = new TextPreprocessor("spanish");
    std::vector<SocialInformation> tweets;
    tweets.push_back(SocialInformation("Se bloquea todas la entradas en la universidad", 17, 65));
    tweets.push_back(SocialInformation("Tambien hay bloqueos en el prado", 17, 64));
    tweets.push_back(SocialInformation("Hubo una feria de comiditas en el correo!!", 17, 64));
    tweets.push_back(SocialInformation("Hoy juega Bilstermann", 17, 64));
    
    std::vector<Result> results = processor->process(tweets, "bloqueo");
    int size = results.size();
    EXPECT_EQ(2, size);
    EXPECT_TRUE(std::find(results.begin(), results.end(), tweets.at(0).message_) != results.end());    
    EXPECT_TRUE(std::find(results.begin(), results.end(), tweets.at(1).message_) != results.end());    
    delete processor;
}

TEST(TextPreprocessor, Rank)
{
    TextPreprocessor* processor = new TextPreprocessor("spanish");
    std::vector<SocialInformation> tweets;
    tweets.push_back(SocialInformation("Ayer comi unos anticuchos buenisimos!", 17, 64));
    tweets.push_back(SocialInformation("La comidita que comimos ayer no se compara con la COMIDA!! q comimos hoy",
            17, 65));
    tweets.push_back(SocialInformation("La comida del estadio es malisima", 17, 64));
    tweets.push_back(SocialInformation("Hoy juega Bilstermann", 17, 64));
    
    std::vector<Result> results = processor->process(tweets, "comida");
    int size = results.size();
    EXPECT_EQ(3, size);
    EXPECT_EQ(tweets.at(1).message_, results.at(0).information.message_);
    EXPECT_EQ(tweets.at(0).message_, results.at(1).information.message_);
    EXPECT_EQ(tweets.at(2).message_, results.at(2).information.message_);
    delete processor;
}

TEST(TextPreprocessor, RelatedWords)
{
    TextPreprocessor* processor = new TextPreprocessor("spanish");
    std::vector<SocialInformation> tweets;
    tweets.push_back(SocialInformation("Ayer me compre un tostador para pan!", 17, 64));
    tweets.push_back(SocialInformation("La comidita que comimos ayer no se compara con la COMIDA!! q comimos hoy",
            17, 65));
    tweets.push_back(SocialInformation("La comida del estadio es malisima", 17, 64));
    tweets.push_back(SocialInformation("Hoy juega Bilstermann", 17, 64));
    
    std::vector<Result> results = processor->process(tweets, "tostada");
    int size = results.size();
    EXPECT_EQ(1, size);
    EXPECT_EQ(tweets.at(0).message_, results.at(0).information.message_);
    delete processor;
}

TEST(TextPreprocessor, RelatedWordsWithRanking)
{
    TextPreprocessor* processor = new TextPreprocessor("spanish");
    std::vector<SocialInformation> tweets;
    tweets.push_back(SocialInformation("Ayer me compre un tostador para pan!", 17, 64));
    tweets.push_back(SocialInformation("No tengo un tostador para hacer tostadas.", 17, 65));
    tweets.push_back(SocialInformation("La comida del estadio es malisima", 17, 64));
    tweets.push_back(SocialInformation("Hoy juega Bilstermann", 17, 64));
    
    std::vector<Result> results = processor->process(tweets, "tostada");
    int size = results.size();
    EXPECT_EQ(2, size);
    EXPECT_EQ(tweets.at(0).message_, results.at(1).information.message_);
    EXPECT_EQ(tweets.at(1).message_, results.at(0).information.message_);
    delete processor;
}

TEST(TextPreprocessor, RelatedWordsWithUpperCase)
{
    TextPreprocessor* processor = new TextPreprocessor("spanish");
    std::vector<SocialInformation> tweets;
    tweets.push_back(SocialInformation("Ayer me compre un tostador para pan!", 17, 64));
    tweets.push_back(SocialInformation("La comidita que comimos ayer no se compara con la COMIDA!! q comimos hoy",
            17, 65));
    tweets.push_back(SocialInformation("La comida del estadio es malisima", 17, 64));
    tweets.push_back(SocialInformation("Hoy juega Bilstermann", 17, 64));
    
    std::vector<Result> results = processor->process(tweets, "Tostada");
    int size = results.size();
    EXPECT_EQ(1, size);
    EXPECT_EQ(tweets.at(0).message_, results.at(0).information.message_);
    delete processor;
}

TEST(TextPreprocessor, RelatedWordsWithTwoWordsSearch)
{
    TextPreprocessor* processor = new TextPreprocessor("spanish");
    std::vector<SocialInformation> tweets;
    tweets.push_back(SocialInformation("Ayer me compre un tostador para pan!", 17, 64));
    tweets.push_back(SocialInformation("No tengo un tostador para hacer tostadas.", 17, 65));
    tweets.push_back(SocialInformation("La comida del estadio es malisima", 17, 64));
    tweets.push_back(SocialInformation("Hoy juega Bilstermann", 17, 64));
    
    std::vector<Result> results = processor->process(tweets, "tostada PAN");
    int size = results.size();
    EXPECT_EQ(2, size);
    EXPECT_EQ(tweets.at(0).message_, results.at(0).information.message_);
    EXPECT_EQ(tweets.at(1).message_, results.at(1).information.message_);
    delete processor;
}

TEST(TextPreprocessor, AssociatedWordsWithTwoWordsSearch)
{
    TextPreprocessor* processor = new TextPreprocessor("english");
    std::vector<SocialInformation> tweets;
    tweets.push_back(SocialInformation("Keep in cage your animals if they bite.", 17, 64));
    tweets.push_back(SocialInformation("All kind of animals need food to survive.", 17, 65));
    tweets.push_back(SocialInformation("Somewhat that doesn't seem to match.", 17, 64));
    
    std::vector<Result> results = processor->process(tweets, "DOG cat");
    int size = results.size();
    EXPECT_EQ(2, size);
    delete processor;
}