#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class complex
{
    friend ostream & operator <<(ostream &out,complex c1);
    friend complex operator +(const complex &c1,const complex &c2);
    friend complex operator -(const complex &c1,const complex &c2);
    friend complex operator *(const complex &c1,const complex &c2);
    friend complex operator /(const complex &c1,const complex &c2);
public:
    class invalid{};
    complex(double r,double i):rpart(r),ipart(i){if(!is_valid()){throw invalid{};}};
    ~complex(){};
private:
    double rpart,ipart;
    bool is_valid();

};

bool complex::is_valid()
{
    if(!scanf){return false;}
    else {return true;}
}
complex operator +(const complex &c1,const complex &c2)
{
    return complex(c1.rpart+c2.rpart,c1.ipart+c2.ipart);
}
complex operator -(const complex &c1,const complex &c2)
{
    return complex(c1.rpart-c2.rpart,c1.ipart-c2.ipart);
}
complex operator *(const complex &c1,const complex &c2)
{
    return complex(c1.rpart*c2.rpart-c1.ipart*c2.ipart,c1.ipart*c2.rpart+c2.ipart*c1.rpart);
}
complex operator /(const complex &c1,const complex &c2)
{
    return complex((c1.rpart*c2.rpart+c1.ipart*c2.ipart)/(c2.rpart*c2.rpart+c2.ipart*c2.ipart),(c1.ipart*c2.rpart-c2.ipart*c1.rpart)/(c2.rpart*c2.rpart+c2.ipart*c2.ipart));
}
ostream & operator <<(ostream &out,complex c1)
{
    if(c1.ipart!=0) 
    {
        printf("%.3lf",c1.rpart);
        if(c1.ipart>0) cout<<"+";
        printf("%.3lfi",c1.ipart);
    }
    else printf("%.3lf",c1.rpart);
    return out;
}
void out(complex c1,char process, complex c2)
{
    switch (process)
    {
    case '+':
        cout<<c1+c2;
        break;
    case '-':
        cout<<(c1-c2);
        break;
    case '*':
        cout<<(c1*c2);
        break;
    case '/':
        cout<<(c1/c2);
        break;
    default:
        break;
    }
}
int main()
{
    try
    {
        double a,b,c,d;
        char process;
        scanf("%lf%lfi %c %lf%lfi",&a,&b,&process,&c,&d);
        complex c1(a,b),c2(c,d);
        out(c1,process,c2);
        return 0;
    }
    catch(complex::invalid)
    {
        //std::error("F**KING INPUT");
        return 1;
    }
}
