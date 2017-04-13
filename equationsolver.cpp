#include "equationsolver.h"

#include <cmath>
#include <cstdio>
#include <iostream>


// function to swap two rows in the matrix
void EquationSolver::swap_row(int i, int j)
{
    double temp;
    for (int k = 0; k <= dim; k++) {
        temp = mat[i][k];
        mat[i][k] = mat[j][k];
        mat[j][k] = temp;
    }
}

EquationSolver::EquationSolver()
{
}

void EquationSolver::printMatrix()
{
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            printf("%lf ", mat[i][j]);
        }
        printf(" | %lf \n", mat[i][N]);
    }
}

QVector<double> EquationSolver::solve(QVector< QVector<double> >A, int N)
{
    mat = A;
    printMatrix(N);

    // reduction to RREF
    int isSingular = toRREF(N);

    // check if the system is solvable or not
    if (isSingular != -1)
    {
        printf("Singular Matrix.\n");

        if (mat[isSingular][N])
            printf("Inconsistent System.");
        else
            printf("May have infinitely many "
                    "solutions.");

        return {};
    }

    /* get solution to system and print it using
       backward substitution */
    return backwardSubstitution(N);
}



// function to reduce matrix to r.e.f.
int EquationSolver::toRREF(int N)
{
    for (int k = 0; k < dim; k++) {
        // Find the apt row for pivot position
        int i_max = k;
        int v_max = mat[i_max][k];

        for (int i = k+1; i < N; i++)
            if (abs(mat[i][k]) > v_max)
                v_max = mat[i][k], i_max = i;

        // if the principal diagonal element is 0, then matrix is singular
        if (!mat[k][i_max])
            return k;

        // swap the current row and the greatest row found
        if (i_max != k)
            swap_row(k, i_max);

        for (int i=k+1; i<N; i++)
        {
            // factor to be multiplied with k th row
            // and then subtracted from i th row
            double f = mat[i][k]/mat[k][k];

            // subtract
            for (int j=k+1; j<=N; j++)
                mat[i][j] -= mat[k][j]*f;

            // zero the lower triangular matrix
            mat[i][k] = 0;
        }
    }

    printMatrix(N);
    return -1;
}

// function to calculate the values of the unknowns
QVector<double> EquationSolver::backwardSubstitution(int N)
{
    // solution
    QVector<double> sol(N);

    // starting from the last equation
    for (int i = N-1; i >= 0; i--)
    {
        sol[i] = mat[i][N];

        // Initialize j to i+1 since matrix is upper triangular
        for (int j=i+1; j<N; j++)
        {
            /* subtract lhs values already calculated
             * as if a * x1 + b * x2 = c, and
             * x2 is calculated, then
             * c -= b * x2, and this loops
             */
            sol[i] -= mat[i][j] * sol[j];
        }

        /* divide the RHS by the coefficient of the variable being calculated
         * a * x3 = b3, then x3 = b3 / a;
         */
        sol[i] = sol[i]/mat[i][i];
    }

    // debugging
    printMatrix();
    return sol;
}
