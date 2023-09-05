#include <stdio.h>
#include <mpi.h>

double f(double x) {
    return 4.0 / (1.0 + x * x);
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int num_rectangles = 1000000;
    double total_sum = 0.0;
    double local_sum = 0.0;

    int local_start = (num_rectangles / size) * rank;
    int local_end = (num_rectangles / size) * (rank + 1);

    for (int i = local_start; i < local_end; ++i) {
        double x = (i + 0.5) / num_rectangles;
        local_sum += f(x);
    }

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double pi = total_sum / num_rectangles;
        printf("Approximated value of π: %f\n", pi);
    }

    MPI_Finalize();
    return 0;
}
