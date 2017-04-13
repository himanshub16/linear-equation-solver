#ifndef EQUATIONSOLVER_H
#define EQUATIONSOLVER_H

#include <QVector>

class EquationSolver
{
public:
    EquationSolver();
    QVector<double> solve(QVector< QVector<double> >A, int dim);
    void swap_row(int i, int j);

private:
    QVector< QVector<double> > mat;
    int dim;

    int toRREF();
    QVector<double> backwardSubstitution();

    void printMatrix();

};

#endif // EQUATIONSOLVER_H
