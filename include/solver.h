#ifndef SOLVER_H
#define SOLVER_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>


class solver
{
    public:
        solver(char test[][4], int, bool);
        virtual ~solver();
        void resoudre();
        void resoudre(int);
        void chercher(int posL, int posC, int tailleMot);
        void reinitGrille();
        bool check(int);
        bool dansGrille(int , int );
        bool dejaVu();
        unsigned int Getm_letter() { return m_letter; }
        void Setm_letter(unsigned int val) { m_letter = val; }
    protected:
    private:
        unsigned int ligneEnCours, colonneEnCours;
        unsigned int m_tailleMot;
        unsigned int m_letter;
        char m_grilleLettre [4][4];
        bool m_grille [4][4];
        char * m_motActuel;
        bool m_grand;
        std::ifstream fichier;
        std::list<std::string> motsTrouves;
};

#endif // SOLVER_H
