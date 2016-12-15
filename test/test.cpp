#include <gtest/gtest.h>
#include "expression.h"

TEST(EXPression, test_on_smoke)
{
	expression input("5+5-1");
}

TEST(EXPression, test_on_easy_input)
{
	expression a("5+5*2^5-7");
}

TEST(EXPression, test_on_normal_input)
{
	expression a("2-(5+5)^2*2");
}

TEST(EXPression, test_on_hard_input)
{
	expression a("2-(d+5)^a*l a=5 d=0 l=2");
}


int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}