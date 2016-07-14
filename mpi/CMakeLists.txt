
find_package(MPI)
if (MPI_FOUND)
    set(CMAKE_C_COMPILER ${MPI_C_COMPILER})
endif (MPI_FOUND)

add_executable(write_shared_file write_shared_file.c)
add_test(10_nodes_write mpirun -np 10 ./write_shared_file)
add_test(3_nodes_write mpirun -np 3 ./write_shared_file)
