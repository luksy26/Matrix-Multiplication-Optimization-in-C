/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double *my_solver(int N, double *A, double *B)
{
	double *C = calloc(N * N, sizeof(double));
	double *BA = calloc(N * N, sizeof(double));
	double *TMP = calloc(N * N, sizeof(double));

	// TMP = At x B
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			// when k > i, A[k][i] is zero
			for (int k = 0; k <= i; ++k)
			{
				// TMP[i][j] += A[k][i] * B[k][j] (since A[i][k] is for regular A, we want At)
				*(TMP + i * N + j) += *(A + k * N + i) * (*(B + k * N + j));
			}
		}
	}

	// B x A
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			// when k > j, A[k][j] is zero
			for (int k = 0; k <= j; ++k)
			{
				// BA[i][j] += B[i][k] * A[k][j] (nothing special here)
				*(BA + i * N + j) += *(B + i * N + k) * (*(A + k * N + j));
			}
		}
	}

	// TMP = At x B + B x A

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			// TMP[i][j] += BA[i][j] (just adding TMP and BA)
			*(TMP + i * N + j) += *(BA + i * N + j);
		}
	}

	// C = TMP X Bt = (At x B + B x A) x Bt

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			for (int k = 0; k < N; ++k)
			{
				// C[i][j] += TMP[i][k] * B[j][k] (since B[k][j] is for regular B, we need Bt)
				*(C + i * N + j) += *(TMP + i * N + k) * (*(B + j * N + k));
			}
		}
	}

	// free memory used by intermediary matrices
	free(TMP);
	free(BA);

	// calculation result stored in C
	return C;
}
