# himanshushekhar-vlabs

This is a Qt5 Application to solve a system of Linear equations.

### Salient features:
* Implements Gauss' Elimination method for solving Ax = B.
* Flexible. Allows to enter any value for the number of equations, and redraws the GUI accordingly.
* Uses Qt5 and C++, making it cross-platform.

### Build instructions (for Ubuntu 16.04 and above):
* The binary is included as the file "linear-linear-equation".
* Install Qt5 ( manually or using 'install-requirements.sh' ).
* Compile the code ( using qmake or 'build.sh' ).
* Execute the code ( ./linear-equation-solver, or 'build-and-run.sh' ).
`
### Manual method:
```
sudo apt-get install qtbase5-dev qt5-qmake;
qmake;
make;
./linear-equation-solver
```
