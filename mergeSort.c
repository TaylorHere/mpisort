//
// Created by taylor on 23-1-3.
//

#include <omp.h>
#include <stdio.h>
#include "mergeSort.h"
#include "utils.h"

void
merge (int *arr, int l, int m, int r)
{

  int n1 = m - l + 1;
  int n2 = r - m;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[l + i];

  for (int j = 0; j < n2; j++)
    M[j] = arr[m + 1 + j];

  int i, j, k;
  i = 0;
  j = 0;
  k = l;

  while (i < n1 && j < n2)
    {
      if (L[i] <= M[j])
        {
          arr[k] = L[i];
          i++;
        }
      else
        {
          arr[k] = M[j];
          j++;
        }
      k++;
    }

  while (i < n1)
    {
      arr[k] = L[i];
      i++;
      k++;
    }

  while (j < n2)
    {
      arr[k] = M[j];
      j++;
      k++;
    }
}

void
mergeSort (int *arr, int l, int r)
{
  if (l < r)
    {

      int m = l + (r - l) / 2;

      mergeSort (arr, l, m);
      mergeSort (arr, m + 1, r);

      merge (arr, l, m, r);
    }
}

/*
 * Recursive OpenMP MergeSort Version
 *
 */
void
mergeSortOMP (int *arr, int l, int r, int node)
{

  if (l < r)
    {
      int m = l + (r - l) / 2;

      mergeSortOMP (arr, l, m, 2 * node + 1);
      mergeSortOMP (arr, m + 1, r, 2 * node + 2);
      if (node % omp_get_num_threads () == omp_get_thread_num ())
        merge (arr, l, m, r);
#pragma omp barrier
    }
}