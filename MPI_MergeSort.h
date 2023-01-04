//
// Created by taylor on 23-1-3.
//

#ifndef _MPI_MERGESORT_H_
#define _MPI_MERGESORT_H_

#include <mpi.h>
void
MPI_MergeSort_tp (int *arr, int *size);

void
MPI_MergeSort (int *arr, int l, int r, int node, MPI_Win win);
#endif //_MPI_MERGESORT_H_
