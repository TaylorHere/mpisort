//
// Created by taylor on 23-1-6.
//

#include <malloc.h>
#include <stdlib.h>
#include "utils.h"
#include "mergeSort.h"

int
main (int argc, char **argv)
{

  if (argc < 2)
    {
      printf ("mergeSort_opm_test <number size>");
      return -1;
    }

  int size = atoi (argv[1]);
  int *arr = NULL;
  arr = randint (size);

//
//  if (rank == 0)
//    printarr (arr, size, "origin");
#pragma omp parallel default(none) shared(arr, size)
  mergeSortOMP (arr, 0, size - 1, 0);

//  printarr (arr, size, "sorted");

  free (arr);

  return 0;
}