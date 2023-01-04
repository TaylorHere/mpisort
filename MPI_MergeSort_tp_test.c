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
      printf ("mpirun MPI_mergeSort_tp_test <number size>");
      return -1;
    }

  MPI_Init (&argc, &argv);

  int rank;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);

  int size = atoi (argv[1]);
  int *arr = NULL;

  if (rank == 0)
    {
      arr = randint (size);
//      printarr (arr, size, "randint");
    }

  MPI_MergeSort_tp (arr, &size);

  if (rank == 0)
    {
//      printarr (arr, size, "sorted");
      free (arr);
    }
  return MPI_Finalize ();
}
