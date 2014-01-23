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