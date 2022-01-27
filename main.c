#include <stdio.h>
#include <stdlib.h>
#define MSWAIT 10

//see main()
//int test(int i)
//{
//  printf("PRE: %d\n", i);
//  return i;
//}

///questions:
//why is the rightmost (printf) argument executed first and leftmost last?
//What moves the cursor in a file?
//what happens to text files when they are moved from little endian to big endian system and vice versa?

//implementing argc and argv might be plausible
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
  if ((fo = fopen("/home/useraccname/Desktop/C_C++/test_c/file_to_write_to", "wb")) == NULL) //on failure NULL is returned and errno is set
    return -1;
  if ((fi = fopen("/home/useraccname/Desktop/C_C++/test_c/file_to_read_from", "rb")) == NULL)
    return -1;

////this code writes all the values of char to a file
//  unsigned char c;
//  for (c = 0; c < 0xFF; c++) {
//    putc(c, fo);
//  }
//  putc(c, fo);
//then this code reads the values
//int i;
//for (i = 0; i < 256; i++) {
//  printf("%d ", feof(fi));
//  printf("%x\n", fgetc(fi));
//}
//printf("%d\n", feof(fi));

///do not use multiple fgetc() in a command
//in this case the last fgetc()/test() gets executed and then it progressively gets to the first one
//who knows whether it's the opposite on other compilators
//printf("A %x %x %x %x B", test(0), test(1), test(2), test(3)); //test(3) executes first
//printf("A\n%x\n%x\n%x\n%x\nB", fgetc(fi), fgetc(fi), fgetc(fi), fgetc(fi)); //increasing/decreasing the number of fgetc will give us different output
//printf("%X %X %X", fi, fgetc(fi), fi); //fi doesn't get changed
//printf("%x ", fgetc(fi)); //using fgetc() separately doesn't affect the result
//printf("%x ", fgetc(fi));

///use of feof and fgetc
//both of these functions return int
//feof should be used in conditional statements,
//as it tells you whether or not to read with fgetc
//both of these treat bytes equaly in binary mode

  //this code should be used as a reference and should be edited to fit your needs
  int buffer;
  int parity;

  if ((buffer = fgetc(fi)) != EOF)
    while (1) { //feof() returns non-zero value when it encounters end of file
      parity = 0;
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
        if (++i < 8) {
          buffer >>= 1;
        }
        else {
          if (parity) //parity bit
            fputs("-1", fo);
          else
            fputs("-0", fo);
          printf("broke out");
          break;
        }
      }
      //wait MSWAIT

      fputs(" 1\n", fo); //the 10th bit has to be on

      if ((buffer = fgetc(fi)) != EOF)
        ;
        //wait MSWAIT * 11 to create spaces between pulses
      else
        break;
    }

  if ((fclose(fo) == EOF) || (fclose(fi) == EOF)) //on failure EOF is returned
    return -2;
  else
    return 0;


}
