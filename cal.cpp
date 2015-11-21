#include "cal.h"
#include <cmath>
#include <tuple>
#include <unordered_map>
#include <cctype>
//#include <iostream>

//size of memory
const int N=1024*128;

using std::tuple;
using std::tie;
using std::make_tuple;

//memory
std::unordered_map<double,double> memory;

//constructor
cal::calc_exp::calc_exp(std::string s):expr(s),result(0),done(false)
{}

//getter and setter for expr
int cal::calc_exp::set_exp(std::string s){expr=s;done=false;return 0;}

std::string cal::calc_exp::get_exp(){return expr;}

//skip space, tab and \n
void next(char* &c){
  while(isspace(*c))c++;
}

//Binary operators
tuple<double, char*> eval(tuple<double,char*>,int);

//Unary operators
tuple<double,char*> num(char* c){next(c);
  double r=0;
  switch(c[0]){
  case '(':c++;tie(r,c)=eval(num(c),0);if(c[0]==')')c++;break;
  //P means \pi
  case 'P':c++;r=M_PI;break;
  //E means e
  case 'E':c++;r=M_E;break;
  //e() means exp
  case 'e':c++;tie(r,c)=num(c);r=std::exp(r);break;
  //s() means sin
  case 's':c++;tie(r,c)=num(c);r=std::sin(r);break;
  //l() means log
  case 'l':c++;tie(r,c)=num(c);r=std::log(r);break;
  //c() means cos
  case 'c':c++;tie(r,c)=num(c);r=std::cos(r);break;
  //$() read from memory
  case '$':c++;tie(r,c)=num(c);r=memory[r];break;    
  //L() means loop, i.e. evaluating the part in () until the result is zero
  case 'L':c++;{
      double r0;
      char*c0=c;
      do{
	tie(r0,c)=num(c0);
      }while(r0);
      r=r0;}break;
  //negative sign
  case '-':c++;tie(r,c)=num(c);r*=-1;break;
  default: while(c[0]>='0'&&c[0]<='9'){
      r=r*10+(c[0]-'0');c++;}
  double dec=1;
  if(c[0]=='.'){
    c++;
    while(c[0]>='0'&&c[0]<='9'){
      dec/=10;r+=dec*(c[0]-'0');
      c++;}
  }}
  next(c);
  return make_tuple(r,c);}

//precedence of binary operators
inline int oplev(char c){
  switch(c){
  case '?':return 0;
  case ';':return 0;
  case ':':return 1;//assignment operator: value:address
  case '>':return 2;
  case '<':return 2;
  case '+':return 3;
  case '-':return 3;
  case '*':return 4;
  case '/':return 4;
  case '%':return 4;
  case '^':return 5;
  default: return -1;}
}

//Parsing binary operators with recursive descent
tuple<double,char*> eval(tuple<double,char*> cur,int lev)
{
  char* c;
  double r;
  tie(r,c)=cur;
  next(c);
  while(lev<=oplev(c[0]))
    {char op=c[0];c++;
      double rhs;
	tie(rhs,c)=num(c);
    while(oplev(c[0])>oplev(op))
      tie(rhs,c)=eval(make_tuple(rhs,c),oplev(c[0]));
    switch(op){
    case '+':r+=rhs;break;
    case '-':r-=rhs;break;
    case '*':r*=rhs;break;
    case '/':r/=rhs;break;
    case '^':r=std::pow(r,rhs);break;
    case '%':r=((long)r)%((long)rhs);break;
    case '>':r=(r>rhs);break;
    case '<':r=(r<rhs);break;
    case ':':memory[rhs]=r; break;
    case ';':r=rhs;break;
    }
}
  next(c);
  return make_tuple(r,c);  
}

//main calculation function
double cal::calc_exp::calc(){
  //lazy eval
  if(done)return result;
  done=true;
  double result=std::get<0>(eval(num((char*)expr.c_str()),0));
  return result;
}

 
