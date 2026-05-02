#define _CRT_SECURE_NO_WARNINGS

#include "HospitalSystem.h"
#include "SFML_UI.h"
#include <iostream>
using namespace std;

int main()
{
    HospitalSystem system;
    system.loadAllData();

    runSFMLUI(system);

    return 0;
}