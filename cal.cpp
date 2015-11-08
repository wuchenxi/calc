#include "cal.h"
#include <cmath>

cal::calc_exp::calc_exp(std::string s):expr(s),result(0),done(false)
{}

int cal::calc_exp::set_exp(std::string s){expr=s;done=false;return 0;}

std::string cal::calc_exp::get_exp(){return expr;}

char* c;

double eval(double,int);

double num(){
  double r=0;
  if(c[0]=='('){c++;r=eval(num(),0);c++;}
  else if(c[0]=='-'){c++;r=-num();}
  else while(c[0]>='0'&&c[0]<='9'){
      r=r*10+(c[0]-'0');c++;}
  double dec=1;
  if(c[0]=='.'){
    c++;
    while(c[0]>='0'&&c[0]<='9'){
      dec/=10;r+=dec*(c[0]-'0');
      c++;}
  }
  return r;}
  

double eval(double r,int lev)
{while((lev==0&&(c[0]=='+'||c[0]=='-'))||(lev<=1&&(c[0]=='*'||c[0]=='/'||c[0]=='%')||(lev<=2&&c[0]=='^')))
      {char op=c[0];c++;
    double rhs=num();
    while((op=='+'||op=='-')&&(c[0]=='*'||c[0]=='/'||c[0]=='%'))
      rhs=eval(rhs,1);
    while((op=='+'||op=='-')&&c[0]=='^')
      rhs=eval(rhs,2);
    while((op=='*'||op=='/'||op=='%')&&(c[0]=='^'))
      rhs=eval(rhs,2);
    if(op=='+')r+=rhs;
    else if(op=='-')r-=rhs;
    else if(op=='*')r*=rhs;
    else if(op=='/')r/=rhs;
    else if(op=='^')r=std::pow(r,rhs);
    else if(op=='%')r=((long)r)%((long)rhs);
      }
return r;  
}

double cal::calc_exp::calc(){
  //lazy eval
  if(done)return result;
  done=true;
  c=(char*)expr.c_str();
  result=eval(num(),0);
  return result;
}

 
