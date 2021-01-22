#include <stdio.h>
//#define fl  // define floating point calculation in Makefile with -Dfl

#ifdef fl
typedef float type;
#define decimales 1.
#else 
typedef long long type;
#define decimales 1000
#endif

struct cpl {type re;type im;};

struct cpl divcomp(struct cpl in1,struct cpl in2) // (1+8i)/(-2-i)=-2-3i
{struct cpl tmp={0,0};
 type q=in2.re*in2.re+in2.im*in2.im; // denumerator (real)
 in1.re*=decimales;                  // adds decimals prior to dividing
 in1.im*=decimales;
 if (q!=0)
   {
    tmp.re=(in1.re*in2.re+in1.im*in2.im)/q; // numerator.re
    tmp.im=(in1.im*in2.re-in1.re*in2.im)/q; // numerator.im
   } 
 return(tmp);
}

struct cpl mulcomp(struct cpl in1,struct cpl in2)
{struct cpl tmp;
 tmp.re=in1.re*in2.re-in1.im*in2.im;
 tmp.im=in1.re*in2.im+in1.im*in2.re;
 tmp.re/=decimales;
 tmp.im/=decimales;
 return(tmp);
}

struct cpl addcomp(struct cpl in1,struct cpl in2)
{struct cpl tmp;
 tmp.re=in1.re+in2.re;
 tmp.im=in1.im+in2.im;
 return(tmp);
}

long long modcomp(struct cpl in1)
{type tmp;
 tmp=in1.re*in1.re+in1.im*in1.im;
 return(tmp/decimales);
}

int main()
{struct cpl num,denum;
 struct cpl current,tmp;
 int n;
 type zr,zi;
 type seuilsup=(type)(1.1*decimales);
 type seuilinf=(type)(0.9*decimales);
// num.re=decimales; num.im=8*decimales; denum.re=-2*decimales; denum.im=-1*decimales; 
// num=divcomp(num,denum); printf("%d %d\n",num.re,num.im);
// num.re=decimales; num.im=6*decimales; denum.re=-1*decimales; denum.im=-1*decimales; 
// num=divcomp(num,denum); printf("%d %d\n",num.re,num.im);
 for (zi=(type)(-0.8*decimales);zi<(type)(0.8*decimales);zi+=(type)(.02*decimales))
   {for (zr=(type)(-1.4*decimales);zr<(type)(1.45*decimales);zr+=(type)(.02*decimales))
     {n=0;
      tmp.re=zr;
      tmp.im=zi;
      do {
#if 1     // (2z^3+1)/(3z^2)
          denum=mulcomp(tmp,tmp);   // z^2
          num=mulcomp(denum,tmp);num.re*=2;num.im*=2;num.re+=decimales; // 2*z^3+1
          denum.re*=3;denum.im*=3;  // 3*z^2
          tmp=divcomp(num,denum);
#else
          denum.re=tmp.re*2; denum.re/=3; 
          denum.im=tmp.im*2; denum.im/=3; 
          tmp=mulcomp(tmp,tmp);
          num.re=1; num.im=0; tmp=divcomp(num,tmp);
          tmp.re=tmp.re/3; tmp.im=tmp.im/3;
          tmp=addcomp(tmp,denum);
 /*         denum.re=tmp.re*2; denum.re/=3; denum.re+=decimales/3;
          denum.im=tmp.im*2; denum.im/=3; 
          tmp.re-=decimales;    // -> 0
          num=mulcomp(tmp,tmp); // x^2
          denum=addcomp(num,denum);
          tmp.re=(tmp.re*2)/3; tmp.im=(tmp.im*2)/3;
          tmp=addcomp(tmp,denum);
*/
#endif
          n++; 
         }
      while (((modcomp(tmp)>seuilsup)||(modcomp(tmp)<seuilinf))&&(n<1000));
      if (n>=1000) printf("!");
         else {if (tmp.re>0) printf("0"); 
                  else if ((tmp.re<0) && (tmp.im>0)) printf("1"); 
                       else if ((tmp.re<0) && (tmp.im<0)) printf("2"); 
                            else printf("*");
              }
     }
    printf("\n");
   }
}   
