// Program to copy the contents of the file given by the
// filename in first command line argument, to the file
// given by the filename in the second command line argument
#include <stdio.h>

int main(int argc, char *argv[])
{ 
   // check number of command-line arguments = 2
   if (argc != 3) {
      puts("Usage: mycopy infile outfile");
   } 
   else {
      FILE *inFilePtr; // input file pointer

      // try to open the input file in read mode
      if ((inFilePtr = fopen(argv[1], "r")) != NULL) {
         FILE *outFilePtr; // output file pointer

         // try to open the output file in write mode
         if ((outFilePtr = fopen(argv[2], "w")) != NULL) {
            int c; // holds characters read from source file

            // read from input and output characters to output file
            while ((c = fgetc(inFilePtr)) != EOF) {
               fputc(c, outFilePtr);
            } 

            fclose(outFilePtr); // close the output file
         }  
         else { // output file could not be opened
            printf("File \"%s\" could not be opened\n", argv[2]); 
         } 

         fclose(inFilePtr); // close the input file
      } 
      else { // input file could not be opened
         printf("File \"%s\" could not be opened\n", argv[1]);
      } 
   } 
} 

 

/**************************************************************************
 * (C) Copyright 1992-2015 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
