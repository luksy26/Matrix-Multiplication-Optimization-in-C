/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
double *my_solver(int N, double *A, double *B)
{
	double *C = calloc(N * N, sizeof(double));
	double *BA = calloc(N * N, sizeof(double));
	double *TMP = calloc(N * N, sizeof(double));

	// TMP = At x B
	for (register int i = 0; i < N; ++i)
	{
		register double *TMP_orig = TMP + i * N; // &TMP[i][0]
		for (register int k = 0; k <= i; ++k)
		{
			register double Aki = *(A + k * N + i); // A[k][i]
			register double *TMP_p = TMP_orig;		// &TMP[i][0]
			register double *B_p = B + k * N;		// &B[k][0]
			// when k > i, A[k][i] is zero
			for (register int j = 0; j < N; ++j)
			{
				// TMP[i][j] += A[k][i] * B[k][j] (since A[i][k] is for regular A, we want At)
				*(TMP_p) += Aki * (*(B_p));
				++TMP_p; // next column in TMP
				++B_p;	 // next column in B
			}
		}
	}

	// B x A
	for (register int i = 0; i < N; ++i)
	{
		register double *BA_orig = BA + i * N; // &BA[i][0]
		for (register int k = 0; k < N; ++k)
		{
			register double Bik = *(B + i * N + k); // B[i][k]
			register double *BA_p = BA_orig + k;	// &BA[i][k]
			register double *A_p = A + k * N + k;	// &A[k][k]
			// when k > j, A[k][j] is zero
			for (int j = k; j < N; ++j)
			{
				// BA[i][j] += B[i][k] * A[k][j] (nothing special here)
				*(BA_p) += Bik * (*A_p);
				++BA_p; // next column in BA
				++A_p;	// next column in A
			}
		}
	}

	// TMP = At x B + B x A

	for (register int i = 0; i < N; ++i)
	{
		register double *TMP_p = TMP + i * N; // &TMP[i][0]
		register double *BA_p = BA + i * N;	  // &BA[i][0]
		for (int j = 0; j < N; ++j)
		{
			// TMP[i][j] += BA[i][j] (just adding TMP and BA)
			*(TMP_p) += *(BA_p);
			++TMP_p; // next column in TMP;
			++BA_p;	 // next column in BA;
		}
	}

	// C = TMP X Bt = (At x B + B x A) x Bt

	for (register int i = 0; i < N; ++i)
	{
		register double *TMP_orig = TMP + i * N; // &TMP[i][0]
		register double *C_p = C + i * N;		 // &C[i][0]
		for (register int j = 0; j < N; ++j)
		{
			register double sum = 0;
			register double *TMP_p = TMP_orig; // &TMP[i][0]
			register double *B_p = B + j * N;  // &B[j][0]
			for (int k = 0; k < N; ++k)
			{
				// C[i][j] += TMP[i][k] * B[j][k] (since B[k][j] is for regular B, we need Bt)
				sum += *(TMP_p) * (*(B_p));
				++TMP_p; // next column in TMP
				++B_p;	 // next column in B
			}
			*(C_p) += sum;
			++C_p; // next column in C
		}
	}

	// free memory used by intermediary matrices
	free(TMP);
	free(BA);

	// calculation result stored in C
	return C;
}
