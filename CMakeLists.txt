cmake_minimum_required(VERSION 3.24)
project(mpisort C)

set(CMAKE_C_STANDARD 11)


add_executable(mergeSort_test mergeSort_test.c mergeSort.c mergeSort.h utils.c utils.h)
target_link_libraries(mergeSort_test ${MPI_C_LIBRARIES})

find_package(MPI)
if (MPI_FOUND)
    set(CMAKE_C_COMPILER "mpicc")
    include_directories(SYSTEM ${MPI_INCLUDE_PATH})

    add_executable(MPI_mergeSort_tp_test MPI_MergeSort_tp_test.c mergeSort.c mergeSort.h MPI_MergeSort.c MPI_MergeSort.h utils.c utils.h)
    target_link_libraries(MPI_mergeSort_tp_test ${MPI_C_LIBRARIES})

    add_executable(MPI_MergeSort_recursive_test MPI_MergeSort_recursive_test.c mergeSort.c mergeSort.h MPI_MergeSort.c MPI_MergeSort.h utils.c utils.h)
    target_link_libraries(MPI_MergeSort_recursive_test ${MPI_C_LIBRARIES})
endif()

find_package(OpenMP)
if (OpenMP_FOUND)
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    include_directories(SYSTEM ${OpenMP_C_INCLUDE_DIRS})

    add_executable(mergeSort_omp_test mergeSort.c mergeSort.h utils.c utils.h mergeSort_omp_test.c)
    target_link_libraries(mergeSort_omp_test ${MPI_C_LIBRARIES})
endif()
