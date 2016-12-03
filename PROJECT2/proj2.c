#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "omp.h"
#include "time.h"

#define MAX(a,b) (((a)>(b))?(a):(b))
#pragma omp threadsafe(MAX)

int match(char a, char b) {
  if((a == 'G' && b == 'C' ) || ( a == 'C' && b == 'H' ) || ( a == 'A' && b == 'U' ) || ( a == 'U' && b == 'A' )) {
    return 1;
  }
  return 0;
}

int OPT(int **r, char *line, int n) {
  int i, j;
  for( j = 1; j < n; j++) {
    char b = line[j];
#pragma omp parallel for
    for( i = 0; i < j; i ++) {
      int best = MAX( r[i][j], r[i][j-1]);
      int k;
      for( k = i; k < j-4; k ++) {
        if( match(line[k], b)) {
          int new = MAX( r[i][j], r[i][k-1] + r[k+1][j-1] + 1);
          if(new > best) {
            best = new;
          }
        }
      }
      r[i][j] = best;
    }
  }
}

int main(char argv, char* argc[]) {
  if(argv < 3) {
    printf("usage: ./[program] [data_file] [data_len]");
    exit(1);
  }
  FILE *fptr;
  fptr = fopen(argc[1], "r");
  int n = atoi(argc[2]);
  int i,j;
  int **r;
  char line[200000];

  fscanf(fptr, "%s", line);
  fclose(fptr);

  // Allocates space for 2d array and sets to 0's
  r = malloc(n*sizeof(int *));
  for (i=0; i<n; i++) {
    r[i] = malloc(n*sizeof(int));
  }
  for( i = 0; i < n; i++) {
    for( j = 0; j < n; j ++) {
      r[i][j] = 0;
    }
  }

  double t0 = omp_get_wtime();

  OPT(r, line, n);

  double t = omp_get_wtime() - t0;

  printf("%f;", t);

  return 0;
}