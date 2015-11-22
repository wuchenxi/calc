#include <iostream>
#include "cal.h"

int main(int argc, char* argv[])
{
  std::string expr;
  cal::calc_exp calculator(expr);
  while(true){
    std::getline(std::cin,expr);
    if(expr[0]=='#')break;
    calculator.set_exp(expr);
    std::cout<<calculator.calc()<<std::endl;
  }
  return 0;
}
