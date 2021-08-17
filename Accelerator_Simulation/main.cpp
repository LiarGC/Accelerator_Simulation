#include <iostream>
#include "Matrix.h"
using namespace std;
int main()
{
    Matrix m1(2,2);
    double buffer[4] = {
        0.,1.,2.,3.
    };
    m1.InputMatrixBuffer(buffer, sizeof(buffer));
    m1.show();
    m1.Transpose().show();
    m1.col_stack(m1).col_stack(m1).show();

    system("pause");
    return 0;
}