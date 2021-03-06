#include "gtest/gtest.h"

#include "DiceRoll/Operations/DiscardOperation.hpp"
#include "DiceRoll/Operations/GetNumberOperation.hpp"
#include "DiceRoll/Operations/RepeatOperation.h"
#include "DiceRoll/RollCompare/Comparators.hpp"
#include "DiceRoll/Operations/IOperation.hpp"

using namespace DiceRoll;

class MultiMockOperation : public IOperation {
  std::unique_ptr<RollResult> execute() {
    return std::make_unique<RollResult>();
  }
 public:
  MultiMockOperation() {}

  std::unique_ptr<RollResult> evaluate() {
    auto result = std::make_unique<RollResult>();
    result->setFullResult("(3 2 4 1)");
    result->setShortResult(std::vector<int>({3, 2, 4, 1}));
    return result;
  }
};

TEST(DiscardOperationTest, WorkWithSingularValueOperation)
{
  DiceRoll::PrioritizeHigher comp;
  GetNumberOperation numOp(5);

  // Will fall out of scope;
  ASSERT_NO_THROW(DiscardOperation disOp(&numOp, 1, &comp));

  DiscardOperation disOp(&numOp, 1, &comp);
  auto result = disOp.evaluate();

  EXPECT_EQ(result->getShortResult(), std::vector<int>({5}));
  EXPECT_EQ(result->getFullResult(), "5");
}

TEST(DiscardOperationTest, WorkWithMultipleValue)
{
  DiceRoll::PrioritizeHigher comp;
  MultiMockOperation mulOp;

  // Will fall out of scope;
  ASSERT_NO_THROW(DiscardOperation disOp(&mulOp, 1, &comp));

  DiscardOperation disOp(&mulOp, 1, &comp);
  auto result = disOp.evaluate();

  EXPECT_EQ(result->getShortResult(), std::vector<int>({4}));
  EXPECT_EQ(result->getFullResult(), "(4 : dis[1, >](3 2 4 1))");
}

TEST(DiscardOperationTest, DontChangeOnLeaveMoreThanInResult)
{
  DiceRoll::PrioritizeHigher comp;
  MultiMockOperation mulOp;  // has 4-value result

  DiscardOperation disOp(&mulOp, 10, &comp);
  auto result = disOp.evaluate();

  EXPECT_EQ(result->getShortResultSize(), 4);
  EXPECT_EQ(result->getFullResult(), "(3 2 4 1)");
}
