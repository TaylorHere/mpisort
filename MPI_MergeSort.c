//
// Created by taylor on 23-1-3.
//

#include <stdlib.h>
#include <stdio.h>
#include "MPI_MergeSort.h"
#include "mergeSort.h"
#include "mpi.h"

void
pad (int* arr, int* size)
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
MPI_MergeSort_tp (int* arr, int* size)
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
  int* sub_arr = calloc (sub_size, sizeof (int));

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
