#include <iostream>
#include <fstream>  //文件流库函数
#include "Matrix.h"
#include "Accelerator_Element.h"
#include "Beam.h"
#include "Particle.h"

int main()
{
    const unsigned int num = 10000;
    Electron IdealElectron;
    Beam b(IdealElectron);
    double sigma = 0.2;
    b.GenerateParticlesInNormalDistribution(num, sigma);

    /*
    ofstream outfile;
    outfile.open("D:\\Code\\Anaconda\\Plot\\data\\test.txt", ios::app);
    if (!outfile.is_open())
        cout << "Open file failure" << endl;
    for (int i = 0; i < num; ++i)
    {
        outfile << b.v_particles[i].GetMomentum() << endl;
    }
    outfile.close();
    //*/

    //system("pause");

    //*
    SBend s1(0.871792);
    Proton p1;
    Beam b1(p1);
    s1.SetBeam(b1);
    s1.SetTheta(0.7853981);
    s1.Set_g(2.29581);
    s1.GetTransferMatrix().show();

    printf("hello");
    //*/
    return 0;
}