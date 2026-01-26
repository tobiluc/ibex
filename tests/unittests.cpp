#include <ibex/ibex.hpp>
#include <gtest/gtest.h>

static constexpr double EPS = 1e-12;

TEST(PipelineTest, SimplePipelineTest1)
{
    EXPECT_NEAR(ibex::evaluate("2^3^2"), 512, EPS);
    EXPECT_NEAR(ibex::evaluate("2+3*4"), 14, EPS);
    EXPECT_NEAR(ibex::evaluate("0.5"), 0.5, EPS);
    EXPECT_NEAR(ibex::evaluate("1/2"), 0.5, EPS);
    EXPECT_NEAR(ibex::evaluate("pi"), M_PI, EPS);
    EXPECT_NEAR(ibex::evaluate("1-0.99"), 0.01, EPS);
}

TEST(PipelineTest, SimplePipelineTest2)
{
    EXPECT_NEAR(ibex::evaluate("(1+2)*(3+4)"), 21, EPS);
    EXPECT_NEAR(ibex::evaluate("(1 + 1/10000)^10000"), 2.71814592682, 1e-6);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
