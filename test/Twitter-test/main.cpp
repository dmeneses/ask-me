#include <iostream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "twittercrawler.h"

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
