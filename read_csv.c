#include <stdio.h>

int main ()
{
   FILE *csv;
   int c;

   csv = fopen("file.csv","r");
   while(1)
   {
      c = fgetc(fp);
      if( feof(csv) )
      {
          break ;
      }
      printf("%d", c);
   }
   fclose(csv);
   return(0);
}