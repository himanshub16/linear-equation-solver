#ifndef EQUATIONSOLVER_H
#define EQUATIONSOLVER_H

#include <QVector>

class EquationSolver
{
public:
    EquationSolver();
    QVector<double> solve(QVector< QVector<double> >A, int dim);

private:
    QVector< QVector<double> > mat;
    int dim;

    int toRREF(int N);
    QVector<double> backwardSubstitution(int N);

    void printMatrix();

};

#endif // EQUATIONSOLVER_H
