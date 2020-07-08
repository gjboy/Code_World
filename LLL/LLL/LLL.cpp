// LLL.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>
#include "stdlib.h"
#include "stdio.h"

double delta = 0.75;
double intermulti(double *A, double *B,int n)
{
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += A[i] * B[i];
	}
	return sum;
}

void add(double *IN1, double *IN2, double *OUT, int n)
{
	for (int i = 0; i < n; i++)
	{
		OUT[i] = IN1[i] + IN2[i];
	}
}

void minus(double *IN1, double *IN2, double *OUT, int n)
{
	for (int i = 0; i < n; i++)
	{
		OUT[i] = IN1[i] - IN2[i];
	}
}

void multiply(double IN1, double *IN2, double *OUT, int n)
{
	for (int i = 0; i < n; i++)
	{
		OUT[i] = IN1*IN2[i];
	}
}

double mui(double *A, double *B, int n)
{
	double a, b;
	a = intermulti(A, B, n);
	b = intermulti(B, B, n);
	return a / b;
}

void vetor(int num, double *IN, double *OUT, int col,int row)
{
	if (num > row) return;
	for (int i = 0; i <col; i++)
	{
		OUT[i] = IN[(num - 1)*col + i];
	}
}

void Vetor_to_Array(double *Ve, double *Ar, int col, int row, int n)
{
	for (int i = 0; i < col; i++)
	{
		Ar[(n - 1)*col + i] = Ve[i];
	}
}

void Schmidt(double *IN, double *OUT, int col, int row)
{
	double k, *a, *b; int q;
	a = (double *)calloc(col, sizeof(double));
	b = (double *)calloc(col, sizeof(double));
	for (int i = 0; i < col*row; i++)
	{
		if (i/col)
		{
			k = IN[i];
			vetor(i / col + 1, IN, a, col, row);
			for (q = 0; q < i/col; q++)
			{
				vetor(q + 1, OUT, b, col, row);
				k -= mui(a,b,col)*OUT[q+(i%col)];
			}
			OUT[i] = k;
		}
		else
		{
			OUT[i] = IN[i];
		}
	}
	free(a);
	free(b);
}

void swap_vetor(double *IN, int col, int row, int A, int B)
{
	double temp;
	for (int i = 0; i < col; i++)
	{
		temp = IN[(A-1)*col + i];
		IN[(A - 1)*col + i] = IN[(B - 1)*col + i];
		IN[(B - 1)*col + i] = temp;
	}
}

int Is_Fail_lovaszCondition(double *IN,double *IN_sch, int col, int row,int K)
{
	double *a, *b, *c, *d; int count = 0;
	a = (double *)calloc(col, sizeof(double));
	b = (double *)calloc(col, sizeof(double));
	c = (double *)calloc(col, sizeof(double));
	d = (double *)calloc(col, sizeof(double));


	for (int i = 1; i < row; i++)
	{
		vetor(i + 1, IN, a, col, row);
		vetor(i, IN_sch, b, col, row);
		vetor(i + 1, IN_sch, c, col, row);
		multiply(mui(a, b, col), b, d, col);
		add(d, c, d, col);
		if (delta*intermulti(b, b, col)>intermulti(d, d, col))
		{
			++count;
			swap_vetor(IN, col, row, i, i + 1);
		}
	}
	free(a);
	free(b);
	free(c);
	free(d);
	return count;
}

void Vetor_Change(double *Ar, double *Ar_sch, int I1, int J1, int col, int row)
{
	double *a, *b,*b_sch, *d;
	double c;
	a = (double *)calloc(col, sizeof(double));
	b = (double *)calloc(col, sizeof(double));
	b_sch = (double *)calloc(col, sizeof(double));
	d = (double *)calloc(col, sizeof(double));
	vetor(I1, Ar, a, col, row);
	vetor(J1, Ar, b, col, row);
	vetor(J1, Ar_sch, b_sch, col, row);

	c = round(mui(a,b_sch,col));
	multiply(c, b, d, col);
	minus(a, d, d, col);
	Vetor_to_Array(d, Ar, col, row, I1);

	free(a);
	free(b);
	free(b_sch);
	free(d);
}

void LLL(double *IN, double *OUT, int col, int row)
{
	double *a, *a_sch;
	int k = 1, i, miu = 0;
	a = (double *)calloc(col*row, sizeof(double));
	a_sch = (double *)calloc(col*row, sizeof(double));

	for ( i = 0; i <col*row ; i++)
	{
		a[i] = IN[i];
	}

	while (1)
	{
		Schmidt(a, a_sch, col, row);
		for ( i = 1; i <= row; i++)
		{
			for (int j = i - 1; j >= 0; j--)
			{
				Vetor_Change(a, a_sch, i, j, col, row);
			}
		}

		if (!Is_Fail_lovaszCondition(a, a_sch, col, row, k))
		{
			//k = k - 1 > 1 ? k - 1 : 1;
			break;
		}
	}

	for ( i = 0; i < col*row; i++)
	{
		OUT[i] = a[i];
	}
	free(a);
	free(a_sch);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int col = 3,
		row = 3;
	double input[9] = { 11, 17, 29, 21, 17, 19, 71, 37, -8 };
	//double input[9] = { 11,21,71,17,17,37,29,19,-8 };
	double output[9] = { 0 };
	LLL(input, output, col, row);
	for (int i = 0; i < col*row; i++)
	{
		printf("%f ", output[i]);
	}
	return 0;
}

