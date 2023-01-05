//
// Created by taylor on 23-1-3.
//

#include <stdlib.h>
#include <stdio.h>
#include "MPI_MergeSort.h"
#include "mergeSort.h"
#include "mpi.h"
#include "utils.h"

void
pad (int *arr, int *size)
{

  int world_size;
  MPI_Comm_size (MPI_COMM_WORLD, &world_size);
  int padding = 0;
  if (world_size > 1)
    {
      int remainder = (*size % world_size);
      if (remainder != 0)
        {
          padding = world_size - remainder;
          *size = *size + padding;
          arr = realloc (arr, *size * sizeof (int));

          for (int i = *size - 1; *size - i <= padding; --i)
            {
              arr[i] = 0;
            }
        }
    }
}

/*
 * Task Parallel Version
 * just Scatter the random array to process, merge sort in process local then merge sort together
 * only reduce some data move ops, can not handle too much data because of the origin data will be double in all process.
 */
void
MPI_MergeSort_tp (int *arr, int *size)
{
  int world_size;
  MPI_Comm_size (MPI_COMM_WORLD, &world_size);

  int rank;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);

  if (rank == 0)
    {
      pad (arr, size);
    }

  MPI_Bcast (size, 1, MPI_INT, 0, MPI_COMM_WORLD);

  int sub_size = (*size / world_size);
  int *sub_arr = calloc (sub_size, sizeof (int));

  MPI_Scatter (arr, sub_size, MPI_INT, sub_arr, sub_size, MPI_INT, 0,
               MPI_COMM_WORLD);

  mergeSort (sub_arr, 0, sub_size - 1);

  MPI_Gather (sub_arr, sub_size, MPI_INT, arr, sub_size, MPI_INT, 0,
              MPI_COMM_WORLD);

  free (sub_arr);

  if (rank == 0)
    {
      mergeSort (arr, 0, *size - 1);
    }
}

/*
 * Recursive MPI MergeSort Version
 *
 */
void
MPI_MergeSort (int *arr, int l, int r, int node, MPI_Win win)
{
  int rank, world_size;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &world_size);

  MPI_Group group;
  MPI_Comm_group (MPI_COMM_WORLD, &group);

  if (node == 0)
    {
      MPI_Win_create (arr, (MPI_Aint) ((r + 1) * sizeof (int)),
                      sizeof (int), MPI_INFO_NULL, MPI_COMM_WORLD, &win);
    }

  if (l < r)
    {
      int m = l + (r - l) / 2;

      MPI_MergeSort (arr, l, m, 2 * node + 1, win);
      MPI_MergeSort (arr, m + 1, r, 2 * node + 2, win);

      MPI_Win_fence (0, win);
      if (node % world_size == rank)
        {

          int nl = m - l + 1;
          int nm = r - m;

          int L[nl], M[nm], T[nl + nm];

          MPI_Get (L, nl, MPI_INT, 0, l, nl, MPI_INT, win);
          MPI_Get (M, nm, MPI_INT, 0, m + 1, nm, MPI_INT, win);

          int i, j, k;
          i = 0;
          j = 0;
          k = 0;

          while (i < nl && j < nm)
            {
              if (L[i] <= M[j])
                {
                  T[k] = L[i];
                  i++;
                }
              else
                {
                  T[k] = M[j];
                  j++;
                }
              k++;
            }

          while (i < nl)
            {
              T[k] = L[i];
              i++;
              k++;
            }

          while (j < nm)
            {
              T[k] = M[j];
              j++;
              k++;
            }
          MPI_Put (&T, nl + nm, MPI_INT, 0, l, nl + nm, MPI_INT, win);
        }
      MPI_Win_fence (0, win);

    }

  if (node == 0)
    MPI_Win_free (&win);
}