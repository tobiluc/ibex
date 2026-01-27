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
    EXPECT_NEAR(eval("1e3"), 1000, EPS);
    EXPECT_NEAR(eval("3.5e2"), 350, EPS);
    EXPECT_NEAR(eval("1e0"), 1, EPS);
    EXPECT_NEAR(eval("2.375e-2"), 0.02375, EPS);
    EXPECT_NEAR(eval("1e-12"), 1e-12, EPS);
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
    EXPECT_NEAR(eval("2^3^2"), 512, EPS);
    EXPECT_NEAR(eval("2+3*4"), 14, EPS);
    EXPECT_NEAR(eval("0.5"), 0.5, EPS);
    EXPECT_NEAR(eval("1/2"), 0.5, EPS);
    EXPECT_NEAR(eval("3/(2*(10-4))"), 0.25, EPS);
    EXPECT_NEAR(eval("pi"), M_PI, EPS);
    EXPECT_NEAR(eval("1-0.99"), 0.01, EPS);
    EXPECT_NEAR(eval("-12.5"), -12.5, EPS);
    EXPECT_NEAR(eval("--13.5"), 13.5, EPS);
}

TEST(PipelineTest, AssignmentTest)
{
    Variables vars = common_variables();
    Functions funcs = common_functions();
    EXPECT_NEAR(eval("x = (y = 42) + 1", vars, funcs), 43, EPS);
    EXPECT_NEAR(vars["y"], 42, EPS);
    EXPECT_NEAR(vars["x"], 43, EPS);
}

TEST(PipelineTest, FunctionsTest)
{
    EXPECT_NEAR(eval("sin(0)"), 0.0, EPS);
    EXPECT_NEAR(eval("cos(0)"), 1.0, EPS);
    EXPECT_NEAR(eval("exp(2)"), 7.38905609893, EPS);
    EXPECT_NEAR(eval("min(4,7,2,4)"), 2.0, EPS);
    EXPECT_NEAR(eval("max(4,-7,2,4)"), 4.0, EPS);
    EXPECT_NEAR(eval("tan(x = pi)"), 0.0, EPS);
    EXPECT_NEAR(eval("pow(2,3)"), 8, EPS);
    EXPECT_NEAR(eval("pow(3,2)"), 9, EPS);
}

TEST(PipelineTest, ArgMaxTest)
{
    Variables vars = common_variables();
    Functions funcs = common_functions();
    funcs["argmax"] = [](const FunctionArgs& args) -> double {
        int argmax(0);
        for (int i = 0; i < args.size(); ++i) {
            if (args[i] > args[argmax]) {
                argmax = i;
            }
        }
        return argmax;
    };
    EXPECT_NEAR(eval("argmax(1,4,10,9)", vars, funcs), 2, EPS);
}

TEST(PipelineTest, LogicalOperatorsTest)
{
    EXPECT_EQ(eval("5 == 5"), 1);
    EXPECT_EQ(eval("5 != 5"), 0);
    EXPECT_EQ(eval("5 == 7"), 0);
    EXPECT_EQ(eval("5 != 7"), 1);
    EXPECT_EQ(eval("5 < 7"), 1);
    EXPECT_EQ(eval("5 > 7"), 0);
    EXPECT_EQ(eval("5 <= 5 && 5 != 7"), 1);
    EXPECT_EQ(eval("0 || 1"), 1);
}

TEST(PipelineTest, SimplePipelineTest2)
{
    EXPECT_NEAR(eval("(1+2)*(3+4)"), 21, EPS);
    EXPECT_NEAR(eval("(1 + 1/10000)^10000"), 2.71814592682, 1e-6);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
