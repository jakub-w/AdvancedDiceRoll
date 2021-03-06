#include "gtest/gtest.h"

#include "DiceRoll/Operations/RollResult.h"
#include "DiceRoll/Operations/RepeatOperation.h"
#include "DiceRoll/Operations/RandomOperation.hpp"

using namespace DiceRoll;

class MockOperation : public IOperation
{
    std::unique_ptr<RollResult> execute()
	{ return std::make_unique<RollResult>(); }

public:
    static int count;

    // For each evaluate() static int count is incrementing.
    std::unique_ptr<RollResult> evaluate()
	{
	    auto result = std::make_unique<RollResult>();
	    result->setFullResult(std::to_string(++count));
	    result->setShortResult(count);
	    return result;
	}
};
int MockOperation::count = 0;
MockOperation baseOp;

// Test to check if repeating even works (without the same result).
TEST(RepeatOperationTest, EvaluateWithPositiveCount)
{
    MockOperation::count = 0;
    RepeatOperation repeatOp(&baseOp , 3);
    
    auto result = repeatOp.evaluate();
    EXPECT_EQ("(1 2 3)", result->getFullResult());
    
    EXPECT_EQ(std::vector<int>({1, 2, 3}), result->getShortResult());
    EXPECT_FALSE(result->hasErrors());
}

TEST(RepeatOperationTest, CantInitializeWithCountLowerThan2)
{
  MockOperation::count = 0;

  ASSERT_ANY_THROW(RepeatOperation(&baseOp, 1));
  ASSERT_ANY_THROW(RepeatOperation(&baseOp, -1));
}

TEST(RepeatOperationTest, RepeatRandomOperation)
{
    RandomOperation op(10);
    RepeatOperation repeatOp(&op, 100);
    auto result = repeatOp.evaluate();

    ASSERT_EQ(100, result->getShortResultSize());
    for(auto item: result->getShortResult()) {
	EXPECT_GE(item, 1);
	EXPECT_LE(item, 10);
    }
}

TEST(RepeatOperationTest, CanRepeatRepeatOperation)
{
  MockOperation::count = 0;

  RepeatOperation repOp(&baseOp, 3);
  ASSERT_NO_THROW(RepeatOperation(&repOp, 3));
  RepeatOperation repOpFinal = RepeatOperation(&repOp, 3);
  auto result = repOpFinal.evaluate();

  EXPECT_EQ(result->getFullResult(), "((1 2 3) (4 5 6) (7 8 9))");
  EXPECT_EQ(result->getShortResult(),
            std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
}
