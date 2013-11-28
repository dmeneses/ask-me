#include <iostream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "twittercrawler.h"

int main(int argc, char **argv)
{
    TwitterCrawler c;
    Location lo;
    lo.latitude_ = 234324;
    lo.longitude_ = 234324;
    c.collect(lo, 121);
}
