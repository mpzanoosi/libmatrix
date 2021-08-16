#include "file.h"

int file_content_set(char *filename, char *content)
{
   FILE *fp = fopen(filename, "w+");
   fprintf(fp, "%s", content);
   fclose(fp);
   return 0;
}