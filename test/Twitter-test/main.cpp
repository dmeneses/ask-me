#include <iostream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "twittercrawler.h"

int main(int argc, char **argv)
{
    TwitterCrawler c;
    Location lo;
    lo.latitude_ = -17.369828;
    lo.longitude_ = -66.176915;
    printf("Tweets amound: %d", c.collect(lo, 1).size());
}
