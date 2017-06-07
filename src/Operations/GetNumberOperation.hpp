#ifndef DICE_GETNUMBEROPERATION_H
#define DICE_GETNUMBEROPERATION_H

#include "IOperation.hpp"

class GetNumberOperation : public IOperation
{
    const int _number;

protected:
    void execute();
    
public:
    GetNumberOperation(int);

    void evaluate();
};

#endif //DICE_GETNUMBEROPERATION_H