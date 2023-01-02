//
// Created by taylor on 23-1-3.
//

#include <stdlib.h>
#include <stdio.h>
#include "mergeSort.h"

int
main (int argc, char** argv)
{
  if (argc < 2)
    {
      printf ("mergeSort_test <number size>");
      return -1;
    }

  int size = atoi (argv[1]);
  int* arr = randint (size);
  mergeSort (arr, 0, size - 1);
  for (int i = 0; i < size - 1; ++i)
    {
      printf ("%d, ", arr[i]);
    }
  free (arr);
}