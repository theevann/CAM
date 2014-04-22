#include <iostream>
#include "include/solver.h"
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

        char grilleInt[4][5];
        char grille[4][4];

    /*
    grille[0] = {'m','e','d','d'};
    grille[1] = {'a','d','y','n'};
    grille[2] = {'r','g','e','s'};
    grille[3] = {'t','i','a','t'};
    */

    for(int i = 0 ; i < 4 ; i++)
    {
        cin >> grilleInt[i];
    }

    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            grille[i][j] = grilleInt[i][j];
        }
    }

    solver CAMSOLVER(grille, 5,true);

    cout << endl << "5 Lettres" << endl << "=========" << endl ;
    CAMSOLVER.resoudre();

    cout << endl << "6 Lettres" << endl << "=========" << endl ;
    CAMSOLVER.resoudre(6);

    cout << endl << "7 Lettres" << endl << "=========" << endl ;
    CAMSOLVER.resoudre(7);

    cout << endl << "8 Lettres" << endl << "=========" << endl ;
    CAMSOLVER.resoudre(8);

    cout << endl << "9 Lettres" << endl << "=========" << endl ;
    CAMSOLVER.resoudre(9);

    cout << endl << "10 Lettres" << endl << "=========" << endl ;
    CAMSOLVER.resoudre(10);

    //Decouper les dictionnaires ou faire toutes les recherches en mm temps
    //Optimiser pour qu'on ne cherche pas si les mots sont improbables dès 4 caractères

    system("PAUSE");
    return 0;
}
