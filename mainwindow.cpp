#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>

#include <cfloat>
#include <QLineEdit>
#include <QMessageBox>
#include <iostream>


// create a new input box for entry
QLineEdit* MainWindow::newInputBox(QWidget *parent)
{
    auto wid = new QLineEdit(parent);
    (*wid).setValidator(doubleValidator);
    (*wid).setFixedWidth(60);
    return wid;
}


// the constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
    ui->verticalLayout  ->setSizeConstraint(QLayout::SetFixedSize);
    ui->inputAreaLayout ->setSizeConstraint(QLayout::SetFixedSize);
    ui->grid            ->setSizeConstraint(QLayout::SetFixedSize);
    ui->layoutB         ->setSizeConstraint(QLayout::SetFixedSize);
    ui->layoutX         ->setSizeConstraint(QLayout::SetFixedSize);

    this->window()->layout()->setSizeConstraint(QLayout::SetFixedSize);

    dimension = 0;
    gridMutex.unlock();
    doubleValidator = new QDoubleValidator();
    doubleValidator->setDecimals(10);
}

// destructor
MainWindow::~MainWindow()
{
    delete ui;
}


// slot to handle change in dimension
void MainWindow::on_nInput_valueChanged(int n)
{
    clearGrid();
    dimension = n;
    setupGrid();
}


// sets up the matrix A and B
void MainWindow::setupGrid()
{
    gridMutex.lock();

    // set up the grid
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            // for A[i][j]
            ui->grid->addWidget(newInputBox(this), i, j);
        }
        // for B[i]
        ui->layoutB->addWidget(newInputBox(this));

        // for X[i]
        auto wid = newInputBox(this);
        wid->setEnabled(false);
        ui->layoutX->addWidget(wid);
    }

    ui->grid->update();
    ui->layoutB->update();
    ui->layoutX->update();

    gridMutex.unlock();
}


// clear the grid
void MainWindow::clearGrid()
{
    gridMutex.lock();
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            // A[i][j]
            ui->grid->itemAtPosition(i, j)->widget()->deleteLater();
        }
        ui->layoutB->itemAt(i)->widget()->deleteLater(); // B[i]
        ui->layoutX->itemAt(i)->widget()->deleteLater(); // X[i]
    }
    ui->grid->update();
    ui->layoutB->update();
    ui->layoutX->update();
    gridMutex.unlock();
}


// helper to set up the augmented matrix from grid values
void MainWindow::prepareAugmentedMatrix()
{
    // set up the augmented matrix vector
    augMatrix.erase(augMatrix.begin(), augMatrix.end());
    augMatrix.resize(dimension);
    for (int i = 0; i < dimension; i++) {
        augMatrix[i].resize(dimension+1);
    }

    // fill the augmented matrix
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            // A[i][j]
            auto wid = ui->grid->itemAtPosition(i, j)->widget();
            augMatrix[i][j] = ((QLineEdit*) wid )->text().toDouble();

            std::cout << augMatrix[i][j] << ' ';
        }

        // B[i]
        auto wid = ui->layoutB->itemAt(i)->widget();
        augMatrix[i][dimension] = ((QLineEdit*) wid )->text().toDouble();
        std::cout << " | " << augMatrix[i][dimension] << std::endl;
    }

    // solve and catch exception for singular matrix
    try {
        QVector<double> solution = solver.solve(augMatrix, dimension);

        // display the solution
        for (int i = 0; i < dimension; i++) {
            auto wid = (QLineEdit*) (ui->layoutX->itemAt(i)->widget());
            wid->setText(QString::number(solution[i]));  // X[i]
            std::cout << "at i = " << i << ':' << solution[i] << std::endl;
        }

    } catch (const char *err) {
        QMessageBox msgBox(this);
        msgBox.setText("<b>Singular Matrix</b>");
        msgBox.setInformativeText(QString(err));
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
}

void MainWindow::on_solveBtn_clicked()
{
    prepareAugmentedMatrix();
    try {
       solver.solve(augMatrix, dimension);
    } catch (...) {

    }
}
