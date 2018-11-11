#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strutil.h"

int main(int argc, char *argv[]){

  char **datos = split(argv[1],',');
  char *archivos = join(datos,' ');
  char exec[20] = "EXEC = ";
  char *cc = "CC = gcc\n";
  char *cflags = "CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror\n";
  char *vflags = "VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes\n";
  char cfiles[100] = "CFILES = ";

  //concatenar
  strcat(exec,argv[2]);
  strcat(cfiles,archivos);

  FILE *f = fopen("makefile2","w");

  fputs(exec,f);
  fputs("\n",f);
  fputs(cc,f);
  fputs(cflags,f);
  fputs(vflags,f);
  fputs(cfiles,f);
  fputs("\n",f);
  fputs("all:\n",f);
  fputs("\t $(CC) $(CFLAGS) $(CFILES) -o $(EXEC)\n",f);
  fputs("run: all\n",f);
  fputs("\t./$(EXEC)\n",f);
  fputs("val: all\n",f);
  fputs("\tvalgrind $(VFLAGS) ./$(EXEC)\n",f);

  fclose(f);
  free_strv(datos);
  free(archivos);

  return 0;
}
