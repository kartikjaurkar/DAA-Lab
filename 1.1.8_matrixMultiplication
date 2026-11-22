#include <stdio.h>
#include <stdlib.h>

// Helper function to find the next power of 2 greater than or equal to n
int nextPowerOfTwo(int n) {
    int count = 1;
    while (count < n) {
        count *= 2;
    }
    return count;
}

// Dynamically allocates a square matrix of size N x N filled with zeros
int** allocateMatrix(int n) {
    int** matrix = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)calloc(n, sizeof(int));
    }
    return matrix;
}

// Frees the dynamically allocated matrix memory
void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Standard matrix addition: C = A + B
int** addMatrix(int** A, int** B, int n) {
    int** C = allocateMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Standard matrix subtraction: C = A - B
int** subtractMatrix(int** A, int** B, int n) {
    int** C = allocateMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Recursive Strassen's algorithm for NxN square matrices where N is a power of 2
int** strassen(int** A, int** B, int n) {
    int** C = allocateMatrix(n);

    // Base case: 1x1 matrix
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    // Base case optimization: standard multiplication for small dimensions
    if (n <= 2) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return C;
    }

    int mid = n / 2;

    // Allocate sub-matrices for quadrants
    int** A11 = allocateMatrix(mid);
    int** A12 = allocateMatrix(mid);
    int** A21 = allocateMatrix(mid);
    int** A22 = allocateMatrix(mid);
    
    int** B11 = allocateMatrix(mid);
    int** B12 = allocateMatrix(mid);
    int** B21 = allocateMatrix(mid);
    int** B22 = allocateMatrix(mid);

    // Divide A and B into 4 quadrants
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mid];
            A21[i][j] = A[i + mid][j];
            A22[i][j] = A[i + mid][j + mid];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mid];
            B21[i][j] = B[i + mid][j];
            B22[i][j] = B[i + mid][j + mid];
        }
    }

    // Temporary matrices for calculation
    int** temp1 = addMatrix(A11, A22, mid);
    int** temp2 = addMatrix(B11, B22, mid);
    int** M1 = strassen(temp1, temp2, mid);
    freeMatrix(temp1, mid); freeMatrix(temp2, mid);

    temp1 = addMatrix(A21, A22, mid);
    int** M2 = strassen(temp1, B11, mid);
    freeMatrix(temp1, mid);

    temp2 = subtractMatrix(B12, B22, mid);
    int** M3 = strassen(A11, temp2, mid);
    freeMatrix(temp2, mid);

    temp2 = subtractMatrix(B21, B11, mid);
    int** M4 = strassen(A22, temp2, mid);
    freeMatrix(temp2, mid);

    temp1 = addMatrix(A11, A12, mid);
    int** M5 = strassen(temp1, B22, mid);
    freeMatrix(temp1, mid);

    temp1 = subtractMatrix(A21, A11, mid);
    temp2 = addMatrix(B11, B12, mid);
    int** M6 = strassen(temp1, temp2, mid);
    freeMatrix(temp1, mid); freeMatrix(temp2, mid);

    temp1 = subtractMatrix(A12, A22, mid);
    temp2 = addMatrix(B21, B22, mid);
    int** M7 = strassen(temp1, temp2, mid);
    freeMatrix(temp1, mid); freeMatrix(temp2, mid);

    // Combine M1..M7 into final quadrants
    int** tC11 = addMatrix(M1, M4, mid);
    int** tC12 = subtractMatrix(tC11, M5, mid);
    int** C11 = addMatrix(tC12, M7, mid);
    freeMatrix(tC11, mid); freeMatrix(tC12, mid);

    int** C12 = addMatrix(M3, M5, mid);
    int** C21 = addMatrix(M2, M4, mid);

    tC11 = addMatrix(M1, M3, mid);
    tC12 = subtractMatrix(tC11, M2, mid);
    int** C22 = addMatrix(tC12, M6, mid);
    freeMatrix(tC11, mid); freeMatrix(tC12, mid);

    // Group quadrants into final matrix C
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mid] = C12[i][j];
            C[i + mid][j] = C21[i][j];
            C[i + mid][j + mid] = C22[i][j];
        }
    }

    // Free all remaining dynamic buffers allocated at this level
    freeMatrix(A11, mid); freeMatrix(A12, mid); freeMatrix(A21, mid); freeMatrix(A22, mid);
    freeMatrix(B11, mid); freeMatrix(B12, mid); freeMatrix(B21, mid); freeMatrix(B22, mid);
    freeMatrix(M1, mid);  freeMatrix(M2, mid);  freeMatrix(M3, mid);  freeMatrix(M4, mid);
    freeMatrix(M5, mid);  freeMatrix(M6, mid);  freeMatrix(M7, mid);
    freeMatrix(C11, mid); freeMatrix(C12, mid); freeMatrix(C21, mid); freeMatrix(C22, mid);

    return C;
}

int main() {
    int rA, cA, rB, cB;

    if (scanf("%d %d", &rA, &cA) != 2) return 0;

    int** A = (int**)malloc(rA * sizeof(int*));
    for (int i = 0; i < rA; i++) {
        A[i] = (int*)malloc(cA * sizeof(int));
        for (int j = 0; j < cA; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    if (scanf("%d %d", &rB, &cB) != 2) return 0;

    if (cA != rB) {
        printf("Invalid input\n");
        for (int i = 0; i < rA; i++) free(A[i]);
        free(A);
        return 0;
    }

    int** B = (int**)malloc(rB * sizeof(int*));
    for (int i = 0; i < rB; i++) {
        B[i] = (int*)malloc(cB * sizeof(int));
        for (int j = 0; j < cB; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    int max_dim = rA;
    if (cA > max_dim) max_dim = cA;
    if (rB > max_dim) max_dim = rB;
    if (cB > max_dim) max_dim = cB;
    
    int N = nextPowerOfTwo(max_dim);

    int** padded_A = allocateMatrix(N);
    int** padded_B = allocateMatrix(N);

    for (int i = 0; i < rA; i++) {
        for (int j = 0; j < cA; j++) {
            padded_A[i][j] = A[i][j];
        }
    }

    for (int i = 0; i < rB; i++) {
        for (int j = 0; j < cB; j++) {
            padded_B[i][j] = B[i][j];
        }
    }

    int** padded_C = strassen(padded_A, padded_B, N);

    // Display the product with trailing spaces matching the test case format
    for (int i = 0; i < rA; i++) {
        for (int j = 0; j < cB; j++) {
            printf("%d ", padded_C[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rA; i++) free(A[i]);
    free(A);
    for (int i = 0; i < rB; i++) free(B[i]);
    free(B);
    
    freeMatrix(padded_A, N);
    freeMatrix(padded_B, N);
    freeMatrix(padded_C, N);

    return 0;
}
