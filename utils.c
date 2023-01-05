//
// Created by taylor on 23-1-4.
//

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <mpi.h>
#include <omp.h>
#include "utils.h"

int *
randint (int size)
{
  srand (time (NULL));
  int *numbers = calloc (size, sizeof (int));
  for (int i = 0; i < size; ++i)
    {
      numbers[i] = rand () % size;
    }
  return numbers;
}

int *
seq (int size)
{
  int *numbers = calloc (size, sizeof (int));
  for (int i = 0; i < size; ++i)
    {
      numbers[i] = size - i;
    }
  return numbers;
}

int *
fill (int size, int j)
{
  int *numbers = calloc (size, sizeof (int));
  for (int i = 0; i < size; ++i)
    {
      numbers[i] = j;
    }
  return numbers;
}

int *
zeros (int size)
{
  int *numbers = calloc (size, sizeof (int));

  return numbers;
}

void
printarr (int *arr, int size, char *label)
{
  int rank;
  int use_mpi;
  MPI_Initialized (&use_mpi);

  if (use_mpi)
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  else
    rank = omp_get_thread_num ();

  printf ("%s@rank-%d: ", label, rank);
  for (int i = 0; i < size; ++i)
    {
      printf ("%d, ", arr[i]);
    }
  printf ("\r\n");
}

void
printRank ()
{
  int use_mpi;
  MPI_Initialized (&use_mpi);

  if (use_mpi)
    {
      int rank;
      MPI_Comm_rank (MPI_COMM_WORLD, &rank);
      printf ("rank: %d\r\n", rank);
    }
  else
    printf ("rank: %d\r\n", omp_get_thread_num ());
}


