# MPI Sort Algorithms

cmake targets:

- **mergeSort_test**
- - origin mergeSort test case runs without MPI
- - the fast version for now
- **MPI_mergeSort_tp_test**
- - Task Parallel Version Merge Sort
- - just Scatter the random array to process, merge sort in process local then merge sort together
- - only reduce some data move ops, can not handle too much data because of the origin data will be double among all
      process.
- - slow than none-MPI version
- **MPI_MergeSort_recursive_test**
- - Recursive Version with MPI RMA(Remote Memory Access), the divide stage runs in every process, but conquer stage runs in (node % world_size == rank) process
- - results in every layer of merge process can be parallel running
- - and the memory used is smaller than Task Parallel Version
- - but creates a lot of RMA ops, that may slow down the speed
- - slow as fuck
- 
