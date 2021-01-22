#include "uart.h"
#include "stdint.h"

#ifdef fl   // define as Makefile argument -Dfl for floating point calculation
typedef float type;
#define SCALE 1.
#else
typedef int32_t type;
#define SCALE 1000
#endif

struct cpl {type re;type im;};

struct cpl mulcomp(struct cpl in1,struct cpl in2)
{struct cpl tmp;
 tmp.re=in1.re*in2.re-in1.im*in2.im;
 tmp.im=in1.re*in2.im+in1.im*in2.re;
 tmp.re/=SCALE;
 tmp.im/=SCALE;
// tmp.re>>=10;
// tmp.im>>=10;
 return(tmp);
}

struct cpl addcomp(struct cpl in1,struct cpl in2)
{struct cpl tmp;
 tmp.re=in1.re+in2.re;
 tmp.im=in1.im+in2.im;
 return(tmp);
}

type modcomp(struct cpl in1)
{type tmp;
 tmp=in1.re*in1.re+in1.im*in1.im;
 return(tmp/SCALE);
// return(tmp>>10);
}

int main()
{volatile struct cpl tmp;
 volatile struct cpl current;
 volatile int n; 
 volatile int compte; // benchmark
 type zr,zi,seuil;
 seuil=(type)(10.*SCALE);
 clock_setup();
 usart_setup();
//gpio_clear(GPIOD,GPIO15|GPIO12); // benchmark with GPIO toggle
#ifdef fl
mon_putchar('y');
#else
mon_putchar('x');
#endif
 for (compte=0;compte<3;compte++)  // benchmark
{
 for (zi=(type)(-1.2*SCALE);zi<(type)(1.2*SCALE);zi+=(type)(0.02*SCALE))
   {for (zr=(type)(-2.0*SCALE);zr<(type)(.85*SCALE);zr+=(type)(.02*SCALE))
     {n=0;
      current.re=zr;
      current.im=zi;
      tmp.re=zr;
      tmp.im=zi;
      do {
          tmp=addcomp(current,mulcomp(tmp,tmp));
          n++; 
         }
      while ((modcomp(tmp)<seuil)&&(n<16));
//      if (n<16) mon_putchar('0'+n); else mon_putchar(' ');  // benchmark
     }
//   mon_putchar('\n'); 
   }
}
#ifdef fl
mon_putchar('Y');
#else
mon_putchar('X');
#endif
while (1) ;
}   
