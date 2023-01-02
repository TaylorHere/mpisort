cmake_minimum_required(VERSION 3.24)
project(mpisort C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER "mpicc")
find_package(MPI REQUIRED)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(mergeSort_test mergeSort_test.c mergeSort.c mergeSort.h)
target_link_libraries(mergeSort_test ${MPI_C_LIBRARIES})

add_executable(MPI_mergeSort_tp_test MPI_MergeSort_tp_test.c mergeSort.c mergeSort.h MPI_MergeSort.c MPI_MergeSort.h)
target_link_libraries(MPI_mergeSort_tp_test ${MPI_C_LIBRARIES})