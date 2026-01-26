#include <ibex/ibex.hpp>
#include <gtest/gtest.h>

static constexpr double EPS = 1e-12;

using namespace ibex;

TEST(TokensTest, OnePlusTwoTest)
{
    Token one{Token::Type::INT, "1", 0};
    Token plus{Token::Type::PLUS, "+", 0};
    Token two{Token::Type::INT, "2", 0};
    EXPECT_EQ(tokenize("1 + 2"), std::vector<Token>({one, plus, two}));
}

TEST(TokensTest, ScientificTest)
{
    EXPECT_NEAR(evaluate("1e3"), 1000, EPS);
    EXPECT_NEAR(evaluate("3.5e2"), 350, EPS);
    EXPECT_NEAR(evaluate("1e0"), 1, EPS);
    EXPECT_NEAR(evaluate("2.375e-2"), 0.02375, EPS);
    EXPECT_NEAR(evaluate("1e-12"), 1e-12, EPS);
}

TEST(PostfixTest, OnePlusTwoTest)
{
    Token one{Token::Type::INT, "1", 0};
    Token plus{Token::Type::PLUS, "+", 0};
    Token two{Token::Type::INT, "2", 0};
    EXPECT_EQ(generate_postfix(tokenize("1 + 2")), std::vector<Token>({one, two, plus}));
}

TEST(PipelineTest, SimplePipelineTest1)
{
    EXPECT_NEAR(evaluate("2^3^2"), 512, EPS);
    EXPECT_NEAR(evaluate("2+3*4"), 14, EPS);
    EXPECT_NEAR(evaluate("0.5"), 0.5, EPS);
    EXPECT_NEAR(evaluate("1/2"), 0.5, EPS);
    EXPECT_NEAR(evaluate("pi"), M_PI, EPS);
    EXPECT_NEAR(evaluate("1-0.99"), 0.01, EPS);
    EXPECT_NEAR(evaluate("-12.5"), -12.5, EPS);
    EXPECT_NEAR(evaluate("--13.5"), 13.5, EPS);
}

TEST(PipelineTest, LogicalOperatorsTest)
{
    EXPECT_EQ(evaluate("5 == 5"), 1);
    EXPECT_EQ(evaluate("5 != 5"), 0);
    EXPECT_EQ(evaluate("5 == 7"), 0);
    EXPECT_EQ(evaluate("5 != 7"), 1);
    EXPECT_EQ(evaluate("5 < 7"), 1);
    EXPECT_EQ(evaluate("5 > 7"), 0);
    EXPECT_EQ(evaluate("5 <= 5 && 5 != 7"), 1);
    EXPECT_EQ(evaluate("0 || 1"), 1);
}

TEST(PipelineTest, SimplePipelineTest2)
{
    EXPECT_NEAR(evaluate("(1+2)*(3+4)"), 21, EPS);
    EXPECT_NEAR(evaluate("(1 + 1/10000)^10000"), 2.71814592682, 1e-6);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
