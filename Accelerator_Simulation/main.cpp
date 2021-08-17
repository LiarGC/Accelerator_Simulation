#include <iostream>
#include "Particle.h"
#include "Beam.h"

int main()
{
    Electron e1;
    //cout << e1.GetClassName() << endl;

    /*
    Particle* temp = (Particle*)ClassFactory::getInstance().getClassByName(e1.GetClassName());
    cout << temp->GetClassName() << endl;
    delete temp;
    */

    Proton p1;
    //cout << p1.GetClassName() << endl;

    /*
    temp = (Particle*)ClassFactory::getInstance().getClassByName(p1.GetClassName());
    cout << temp->GetClassName() << endl;
    delete temp;
    */

    system("pause");
    return 0;
}