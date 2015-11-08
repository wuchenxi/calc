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
  //P means \pi
  else if(c[0]=='P'){c++;r=M_PI;}
  //E means e
  else if(c[0]=='E'){c++;r=M_E;}
  //e() means exp
  else if(c[0]=='e'){c++;r=std::exp(num());}
  //s() means sin
  else if(c[0]=='s'){c++;r=std::sin(num());}
  //l() means log
  else if(c[0]=='l'){c++;r=std::log(num());}
  //c() means cos
  else if(c[0]=='c'){c++;r=std::cos(num());}
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

inline int oplev(char c){
  switch(c){
  case '+':return 0;
  case '-':return 0;
  case '*':return 1;
  case '/':return 1;
  case '%':return 1;
  case '^':return 2;
  default: return -1;}
}

double eval(double r,int lev)
{while(lev<=oplev(c[0]))
      {char op=c[0];c++;
    double rhs=num();
    while(oplev(c[0])>oplev(op))
      rhs=eval(rhs,oplev(c[0]));
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

 
