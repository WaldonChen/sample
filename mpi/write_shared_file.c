#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int file_open_error;
    MPI_File fh;
    char buf[1024];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    file_open_error =
        MPI_File_open(MPI_COMM_WORLD, "file.txt",
                      MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);
    if (file_open_error != MPI_SUCCESS) {
        char error_string[BUFSIZ];
        int len_err_str, err_class;

        MPI_Error_class(file_open_error, &err_class);
        MPI_Error_string(err_class, error_string, &len_err_str);
        printf("%3d: %s\n", rank, error_string);

        MPI_Abort(MPI_COMM_WORLD, file_open_error);
    }

    MPI_File_set_size(fh, 0LL);

    if (rank != 3) {
        int file_write_error;
        sprintf(buf, "I am rank %d, totally %d nodes.\n", rank, size);
        file_write_error = MPI_File_write_shared(
            fh, buf, strlen(buf), MPI_UNSIGNED_CHAR, MPI_STATUS_IGNORE);
        if (file_write_error != MPI_SUCCESS) {
            char error_string[BUFSIZ];
            int len_err_str, err_class;

            MPI_Error_class(file_open_error, &err_class);
            MPI_Error_string(err_class, error_string, &len_err_str);
            printf("%3d: %s\n", rank, error_string);
        }
    }

    MPI_File_close(&fh);

    MPI_Finalize();
    return 0;
}
