#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleSpinBox>
#include <QVector>
#include <QMutex>
#include <QDoubleValidator>

#include "equationsolver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_nInput_valueChanged(int n);

    void on_solveBtn_clicked();

private:
    QVector< QVector<double> > augMatrix;

    QDoubleValidator *doubleValidator;
    QLineEdit *newInputBox(QWidget* parent);
    void prepareAugmentedMatrix();

    Ui::MainWindow *ui;
    int dimension;
    QMutex gridMutex;
    void setupGrid();
    void clearGrid();

    EquationSolver solver;

};

#endif // MAINWINDOW_H
