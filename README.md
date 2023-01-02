# MPI Sort Algorithms

cmake targets:

- **mergeSort_test**
- - origin mergeSort test case runs without MPI
- **MPI_mergeSort_tp_test**
- - Task Parallel Version Merge Sort
- - just Scatter the random array to process, merge sort in process local then merge sort together
- - only reduce some data move ops, can not handle too much data because of the origin data will be double among all
      process.
