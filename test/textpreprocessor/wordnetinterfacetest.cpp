#include "crawlers/Wordnet/wordnetinterface.h"
#include <gtest/gtest.h>

TEST(Wordnet, test1)
{
    WordnetInterface wi;
    std::vector<std::string> other;
    std::set<std::string> res = wi.collectAllRelatedWords("dog", other);
    for (std::set<std::string>::iterator it = res.begin(); it != res.end(); ++it)
        std::cout << ' ' << *it << std::endl;

    std::cout << '\n';
}
