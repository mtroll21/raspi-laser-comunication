#include <stdio.h>
#include <stdlib.h>
#define MSWAIT 10

int main()
{
  /*
  Return values:
    -1 for failing to open a file
    -2 for failing to close a file
  Description:
    This program was created for converting bytes into
    transmittable one-way signal without a sync signal.
  Constants:
    MSWAIT - tells us how long to wait before sending next bit
  */


  FILE *fo; //file out; used for writing the output
  FILE *fi; //file in; used for reading the input
  if ((fo = fopen("/home/useraccname/Desktop/C_C++/test_c/file_to_write_to", "wb")) == NULL) //opening the file
    return -1;
  if ((fi = fopen("/home/useraccname/Desktop/C_C++/test_c/file_to_read_from", "rb")) == NULL)
    return -1;

  
  //this code should be used as a reference and should be edited to fit your needs
  int buffer;
  int parity;

  if ((buffer = fgetc(fi)) != EOF) //checking whether the file is empty before transmitting
    while (1) { 
      parity = 0; //resetting parity
      fprintf(fo, "[%c] 1 ", (char) buffer);
  //    fputs("1 ", fo); //the first bit has to be on

      //wait MSWAIT
      for (int i = 0;;) { //reading 8 bits + parity
        if (buffer & 0x01) { //the bit is true
          parity = !parity;
          fputs("1", fo);
        }
        else //the bit is false
          fputs("0", fo);

        //wait MSWAIT
        if (++i < 8) { //there's a next bit to read
          buffer >>= 1;
        }
        else { //there'sn't a next bit to read
          if (parity) //parity bit
            fputs("-1", fo);
          else
            fputs("-0", fo);
          break;
        }
      }
      //wait MSWAIT

      fputs(" 1\n", fo); //the 10th bit has to be on

      if ((buffer = fgetc(fi)) != EOF) //wait in between the 11 bits
        ;
        //wait MSWAIT * 11 to create spaces between pulses
      else
        break;
    }

  if ((fclose(fo) == EOF) || (fclose(fi) == EOF)) //closing the file
    return -2;
  else
    return 0;


}
