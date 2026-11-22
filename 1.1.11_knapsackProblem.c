#include <stdio.h>
#include <stdlib.h>

// Helper function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n, w_capacity;

    if (scanf("%d", &n) != 1) return 1;

    int *values = (int *)malloc(n * sizeof(int));
    int *weights = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &values[i]) != 1) return 1;
    }
	
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &weights[i]) != 1) return 1;
    }

    
    if (scanf("%d", &w_capacity) != 1) return 1;

    int *dp = (int *)calloc(w_capacity + 1, sizeof(int));

    for (int i = 0; i < n; i++) {
		
        for (int j = w_capacity; j >= weights[i]; j--) {
            dp[j] = max(dp[j], dp[j - weights[i]] + values[i]);
        }
    }

  
    printf("%d\n", dp[w_capacity]);

    
    free(values);
    free(weights);
    free(dp);

    return 0;
}
