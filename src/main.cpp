#include "stdafx.h"

#include "IOperation.h"
#include "GetNumberOperation.h"
#include "RandomOperation.h"

int main()
{
  std::unique_ptr<IOperation> operation(new GetNumberOperation(1));
    operation->evaluate();
    std::cout << operation->toString() << std::endl;
    
    operation.reset(new RandomOperation(6, 7));
    try
    {
        operation->evaluate();
    }
    catch (std::exception& e) { std::cout << e.what() << std::endl; }
    std::cout << operation->toString() << std::endl;

    return 0;
}