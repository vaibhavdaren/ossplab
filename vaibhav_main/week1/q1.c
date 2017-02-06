#include <stdio.h>

int main( int argc, char *argv[] )  {

      int i;
      printf("Welcome to linux \n");
   
      printf("NO of Arg : %d\n",argc);

      for(i=0;i<argc;i++)
   {
      printf(" argument no: %d  VALUE %s.\n",i+1,argv[i]);
   }
}