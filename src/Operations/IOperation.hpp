#ifndef DICE_IOPERATION_H
#define DICE_IOPERATION_H

#include "../stdafx.hpp"
#include "DiceRoll/Operations/RollResult.h"

//Base for a Decorator Pattern
class IOperation
{
protected:
    std::vector<int> _elements;
    int _count;
    IOperation *_componentOp;

    // Execute operation. All heavy lifting for object.
    virtual std::shared_ptr<RollResult> execute() = 0;

public:
    // Executes all operations.
    // By default, merges _componentOp's RollResult with its.
    virtual inline std::shared_ptr<RollResult> evaluate()
    {
	std::shared_ptr<RollResult> result = _componentOp->evaluate();
	result->append(result.get());
	return result;
    }
    virtual std::string toString() const 
    { 
        std::string result = "";
        for (auto& element : _elements)
            result += std::to_string(element) + " ";
        return result;
    }
    inline int getCount() const { return _count; }
    inline const std::vector<int> &getElements() const { return _elements; }
};

#endif //DICE_IOPERATION_H
