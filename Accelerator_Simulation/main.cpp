#include <iostream>
#include "Matrix.h"
#include "mkl.h"

int main()
{
    Matrix m1(2, 2),m2(2,2);
    double buffer[4] = {
        1.0,    2.0,
        3.0,    4.0
    };
    m1.InputMatrixBuffer(buffer, sizeof(buffer));
    m2.InputMatrixBuffer(buffer, sizeof(buffer));

    m1.show();
    m2.show();

    //m1.row_stack(m2);
    (m1 + m2).show();

    return 0;
}