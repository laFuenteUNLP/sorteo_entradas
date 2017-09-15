#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
extern int errno;

const char* getfield(char* line, int num)
{
  const char* tok;

  for (tok = strtok(line, ";"); tok && *tok; tok = strtok(NULL, ";\n"))
  {
    if (!--num)
    {
      return tok;
    }
  }

  return NULL;
}

int numero_aleatorio(int ini, int fin)
{
  srand(time(NULL));
  
  return (ini+(int)(((fin-ini+1.0)*rand())/(RAND_MAX+1.0)));
}

int main(int argc, char *argv[])
{
  FILE *fp;
  char buf[1024] = "EKO";
  int i = 1;

  //Empieza desde 2 para no leer cabecera
  //Hasta el número de inscritos.
  int aleatorio = numero_aleatorio(2, 180);
  //printf("%d\n", aleatorio);

  if (argc==2)
  {
    if ((fp = fopen(argv[1], "rb")))
    {
      while (fgets(buf, sizeof(buf), fp) != NULL)
      {
        //printf ("Linea %4d: %s", i, buf);
        
        if (i == aleatorio)
        {
          printf("Alumno: %d - %s\n", aleatorio, getfield(buf, 2));
        }

        i++;
      }

      fclose(fp);
    }

    else
    {
      printf("ERROR al abrir %s:=> %s\n", argv[1], strerror(errno));
    }
  }

  else
  {
    printf("Ingrese archivo EKOPARTY\n");
  }

  return 0;
}