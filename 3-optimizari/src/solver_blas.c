/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include <string.h>
#include "utils.h"
#include "cblas.h"

/*
 * Add your BLAS implementation here
 */
double *my_solver(int N, double *A, double *B)
{
	double *C = calloc(N * N, sizeof(double));
	double *BA = calloc(N * N, sizeof(double));
	double *TMP = calloc(N * N, sizeof(double));

	// copy B in TMP
	memcpy(TMP, B, N * N * sizeof(double));

	// TMP = At x B
	cblas_dtrmm(	   // Y = alpha * op(X) x Y or Y = alpha * Y x op(X) (op tells us whether to tranpose or not)
		CblasRowMajor, // specifies memory layout of the matrices
		CblasLeft,	   // use first version, so op(X) x Y
		CblasUpper,	   // X is upper triangular
		CblasTrans,	   // use transpose(X)
		CblasNonUnit,  // indicates that the diagonal of X doesn't contain all 1's
		N,			   // number of rows in Y
		N,			   // number of columns in Y
		1.0,		   // alpha
		A,			   // X
		N,			   // leading dimension in X (depends on the memory layout)
		TMP,		   // Y
		N			   // leading dimension in Y (depends on the memory layout)
	);

	// copy B in BA
	memcpy(BA, B, N * N * sizeof(double));

	// B x A
	cblas_dtrmm(	   // Y = alpha * op(X) x Y or Y = alpha * Y * op(Y) (op tells us whether to tranpose or not)
		CblasRowMajor, // specifies memory layout of the matrices
		CblasRight,	   // use second version, so Y x op(X)
		CblasUpper,	   // X is upper triangular
		CblasNoTrans,  // use regular X
		CblasNonUnit,  // indicates that the diagonal of X doesn't contain all 1's
		N,			   // number of rows in Y
		N,			   // number of columns in Y
		1.0,		   // alpha
		A,			   // X
		N,			   // leading dimension in X (depends on the memory layout)
		BA,			   // Y
		N			   // leading dimension in Y (depends on the memory layout)
	);

	/*
		since we are simply adding we can just treat the matrices like vectors
		TMP = 1 * TMP + 1 * BA = At x B + B x A
	*/
	cblas_daxpy( // Y = alpha * X + Y
		N * N,	 // number of elements in input vector(s)
		1.0,	 // alpha
		BA,		 // X
		1,		 // storage spacing between elements of X
		TMP,	 // Y
		1		 // storage spacing between elements of Y
	);
	// incX and incY are 1 since we have contiguous memory

	// C = 1 * TMP x Bt + 0 * C = TMP x Bt = (At x B + B x A) x Bt
	cblas_dgemm(	   // Z = alpha * op(X) * op(Y) + beta * Z (op tells us whether to tranpose or not)
		CblasRowMajor, // specifies memory layout of the matrices
		CblasNoTrans,  // use regular X
		CblasTrans,	   // use transpose(Y)
		N,			   // number of rows in op(X) and Z
		N,			   // number of columns in op(B) and Z
		N,			   // number of columns in op(X) and number of rows in op(Y)
		1.0,		   // alpha
		TMP,		   // X
		N,			   // leading dimension of X (depends on the memory layout)
		B,			   // Y
		N,			   // leading dimension of Y (depends on the memory layout)
		0,			   // beta
		C,			   // Z
		N			   // leading dimension of Z (depends on the memory layout)
	);

	// free memory used by intermediary matrices
	free(TMP);
	free(BA);

	// calculation result stored in C
	return C;
}
