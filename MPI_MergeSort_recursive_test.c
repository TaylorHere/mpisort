//
// Created by taylor on 23-1-4.
//
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "MPI_MergeSort.h"
#include "mergeSort.h"
#include "utils.h"

int
main (int argc, char **argv)
{

  if (argc < 2)
    {
      printf ("mpirun MPI_mergeSort_recursive_test <number size>");
      return -1;
    }

  MPI_Init (&argc, &argv);

  int rank;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);

  int size = atoi (argv[1]);
  int *arr = NULL;
  if (rank == 0)
    arr = randint(size);
  else
    arr = malloc (0);
//
//  if (rank == 0)
//    printarr (arr, size, "origin");


  MPI_MergeSort (arr, 0, size - 1, 0, NULL);

//  if (rank == 0)
//    printarr (arr, size, "sorted");

  free (arr);

  return MPI_Finalize ();
}
