#include <iostream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "twittercrawler.h"

int main(int argc, char **argv)
{
    TwitterCrawler c;
    Location lo;
    lo.latitude_ = -17.365978;
    lo.longitude_ = -66.175462;
    c.collect(lo, 1);
}
