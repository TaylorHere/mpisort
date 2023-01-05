//
// Created by taylor on 23-1-3.
//

#ifndef _MERGESORT_H_
#define _MERGESORT_H_

void
mergeSort (int *arr, int l, int r);

void
merge (int *arr, int l, int m, int r);

void
mergeSortOMP (int *arr, int l, int r, int node);

#endif //_MERGESORT_H_
