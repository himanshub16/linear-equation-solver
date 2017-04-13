#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>

#include <cfloat>
#include <QLineEdit>
#include <iostream>

QLineEdit* MainWindow::newInputBox(QWidget *parent)
{
    auto wid = new QLineEdit(parent);
    (*wid).setValidator(doubleValidator);
    (*wid).setFixedWidth(100);
    return wid;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dimension = 0;
    gridMutex.unlock();
    doubleValidator = new QDoubleValidator();
    doubleValidator->setDecimals(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_nInput_valueChanged(int n)
{
    clearGrid();
    dimension = n;
    setupGrid();
}


void MainWindow::setupGrid()
{
    gridMutex.lock();
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            ui->grid->addWidget(newInputBox(this), i, j);
        }
        ui->layoutB->addWidget(newInputBox(this));
        ui->layoutX->addWidget(newInputBox(this));
    }
    ui->grid->update();
    ui->layoutB->update();
    ui->layoutX->update();
    gridMutex.unlock();
}

void MainWindow::clearGrid()
{
    gridMutex.lock();
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            ui->grid->itemAtPosition(i, j)->widget()->deleteLater();
        }
        ui->layoutB->itemAt(i)->widget()->deleteLater();
        ui->layoutX->itemAt(i)->widget()->deleteLater();
    }
    ui->grid->update();
    ui->layoutB->update();
    ui->layoutX->update();
    gridMutex.unlock();
}

void MainWindow::on_solveBtn_clicked()
{
    augMatrix.erase(augMatrix.begin(), augMatrix.end());
    augMatrix.resize(dimension);
    for (int i = 0; i < dimension; i++) {
        augMatrix[i].resize(dimension+1);
    }

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            auto wid = ui->grid->itemAtPosition(i, j)->widget();
            augMatrix[i][j] = ((QLineEdit*) wid )->text().toDouble();

            std::cout << augMatrix[i][j] << ' ';
        }
        auto wid = ui->layoutB->itemAt(i)->widget();
        augMatrix[i][dimension] = ((QLineEdit*) wid )->text().toDouble();
        std::cout << " | " << augMatrix[i][dimension] << std::endl;
    }

    QVector<double> solution = solver.solve(augMatrix, dimension);
    for (int i = 0; i < dimension; i++) {
        auto wid = (QLineEdit*) (ui->layoutX->itemAt(i)->widget());
        wid->setText(QString::number(solution[i]));
        std::cout << "at i = " << i << ':' << solution[i] << std::endl;
    }
}
