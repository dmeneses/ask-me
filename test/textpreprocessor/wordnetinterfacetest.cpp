#include "crawlers/Wordnet/wordnetinterface.h"
#include <gtest/gtest.h>

TEST(Wordnet, TestRelationships)
{
    WordnetInterface wi;
    std::vector<std::string> other;
    other.push_back("cancer");
    other.push_back("disease");
    std::set<std::string> res = wi.collectAllRelatedWords("cancer", other);
    for (std::set<std::string>::iterator it = res.begin(); it != res.end(); ++it)
        std::cout << ' ' << *it << std::endl;

    std::cout << '\n';
}

//TEST(Wordnet, test2)
//{
//    wnb::wordnet wn("/usr/local/WordNet-3.0/dict/");
//    std::vector<wnb::synset> relatedWords = wn.get_synsets("dog");
//
//    for (unsigned int i = 0; i < relatedWords.size(); i++)
//    {
//        std::cout << "ID: " << relatedWords.at(i).id << std::endl;
//        std::cout << "GLOSS: " << relatedWords.at(i).gloss << std::endl;
//        std::vector<std::string> foundWords = relatedWords.at(i).words;
//        std::cout << "WORDS: " << std::endl;
//        for (unsigned int j = 0; j < foundWords.size(); j++)
//        {
//            std::cout << foundWords.at(j) << "|";
//        }
//        std::cout << std::endl << "-----------------------------" << std::endl;
//    }
//}
