#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "smartuniq_methods.h"

int main(int argc, char *argv[])
{
    if( (argc > 4))
    {
        printf("Usage: %s -i [case_sensitive] -c [count]\n",argv[0]);
        return -1;
    }

     int case_sensitive = 0;
     int count = 0;
     int opt = 0;
     char* args = argv[1];

     while ((opt = getopt(argc, argv, "ic:")) != -1) {
         switch(opt) {
         case 'i':
             case_sensitive = 1;
             break;
         case 'c':
             count = 1;
             break;
         }
     }

     args = argv[argc - 1];

     int input_fd = 0; // stdin file descriptor

     if (argc > 1)
     {
         input_fd = open(args, O_RDONLY);
         if (input_fd == -1)
         {
             perror("Error opening file");
             return 1;
         }

         char **lines = NULL;
         size_t num_lines = 0;

         read_input(input_fd, &lines, &num_lines, case_sensitive, count);
         close(input_fd);
         // Process lines ...

         return 0;

     }
}
