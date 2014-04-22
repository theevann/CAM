#include "..\include\solver.h"

solver::solver(char grille[][4], int taille, bool tailleDico):m_tailleMot(taille), m_grand(tailleDico)
{
    m_motActuel = new char[taille+1];
    m_motActuel[taille] = '\0';

    for(int i = 0 ; i <= 3 ; i++)
    {
        for(int j = 0 ; j <= 3 ; j++)
        {
            m_grilleLettre[i][j] = grille[i][j] ;
            m_grille[i][j] = false;
        }
    }

    /*
   fichier.open("dico0.txt", std::ios::in);  // on ouvre le fichier en lecture

    if(!fichier)  // si l'ouverture a r�ussi
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
    else
        std::cout << "Fichier ouvert !";
    //*/

}

solver::~solver()
{
    delete [] m_motActuel;
}

void solver::resoudre(int taille)
{
    m_tailleMot = taille;
    delete [] m_motActuel;
    m_motActuel = new char[taille+1];
    m_motActuel[taille] = '\0';
    reinitGrille();
    resoudre();
}

void solver::resoudre()
{
    std::ostringstream nomFichier;
    std::string taille = (m_grand?"Grand":"Petit");

    for(int i = 0 ; i <= 3 ; i++)
    {
        for(int j = 0 ; j <= 3 ; j++)
        {
            ligneEnCours = i;
            colonneEnCours = j;

            nomFichier.str("");
            nomFichier << taille << "Dicos/Dico_" << m_tailleMot << "/dico_" << m_grilleLettre[i][j] << ".txt";
            fichier.open(nomFichier.str().c_str(), std::ios::in);  // on ouvre le fichier en lecture

            if(!fichier){
                std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
            }
            else
            {
                reinitGrille();
                chercher(i,j,m_tailleMot);
                fichier.close();
            }

           //std::cout<< i << "  " << j << std::endl;
        }
    }
}

void solver::chercher(int posL, int posC, int tailleMot)
{
    //std::cout<< posL << " " << posC << " ? " << tailleMot << std::endl;
    m_grille[posL][posC] = true;
    m_motActuel[m_tailleMot-tailleMot] = m_grilleLettre[posL][posC];

    if(m_tailleMot-tailleMot == 2 && !check(3))
    {
        m_grille[posL][posC] = false;
        return;
    }

    if(m_tailleMot >= 7 && m_tailleMot-tailleMot == 4 && !check(5))
    {
        m_grille[posL][posC] = false;
        return;
    }

    if(tailleMot > 1)
    {
        if(dansGrille(posL-1,posC) && !m_grille[posL-1][posC])
            chercher(posL-1,posC, tailleMot-1);

        if(dansGrille(posL-1,posC+1) && !m_grille[posL-1][posC+1])
            chercher(posL-1,posC+1, tailleMot-1);

        if(dansGrille(posL,posC+1) && !m_grille[posL][posC+1])
            chercher(posL,posC+1, tailleMot-1);

        if(dansGrille(posL+1,posC+1) && !m_grille[posL+1][posC+1])
            chercher(posL+1,posC+1, tailleMot-1);

        if(dansGrille(posL+1,posC) && !m_grille[posL+1][posC])
            chercher(posL+1,posC, tailleMot-1);

        if(dansGrille(posL+1,posC-1) && !m_grille[posL+1][posC-1])
            chercher(posL+1,posC-1, tailleMot-1);

        if(dansGrille(posL,posC-1) && !m_grille[posL][posC-1])
            chercher(posL,posC-1, tailleMot-1);

        if(dansGrille(posL-1,posC-1) && !m_grille[posL-1][posC-1])
            chercher(posL-1,posC-1, tailleMot-1);
    }
    else
    {
        //std::cout << m_motActuel << std::endl;
        if(check(0) && !dejaVu()){
            std::cout << m_motActuel << "  (" << (ligneEnCours+1) << "," << (colonneEnCours+1) << ") "  << std::endl;
        }
    }

    m_grille[posL][posC] = false;
    return;
}

void solver::reinitGrille()
{
    for(int i = 0 ; i <= 3 ; i++)
    {
        for(int j = 0 ; j <= 3 ; j++)
        {
            m_grille[i][j] = false;
        }
    }
}

bool solver::check(int checker)
{
    std::string motEnCours(m_motActuel);
    std::string motDuFichier;
    fichier.clear();
    fichier.seekg(0, std::ios::beg); // Retour au d�but du fichier
    //std::cout<<"\nPASS " << fichier.tellg() <<"\n";

    if(checker != 0)
    {
        while(std::getline(fichier, motDuFichier))
        {
            if(motDuFichier.substr(0,checker) == motEnCours.substr(0,checker))
                return true;
        }
        return false;
    }
    else
    {
        while(std::getline(fichier, motDuFichier))
        {
          //std::cout<< motDuFichier << " ? " << motEnCours << std::endl;
            if(motDuFichier == motEnCours)
                return true;
        }
        return false;
    }
}

bool solver::dansGrille(int posL, int posC)
{
    return (posL >= 0 && posL < 4 && posC >= 0 && posC < 4);
}

bool solver::dejaVu()
{
     std::string motEnCours(m_motActuel);
     std::list<std::string>::iterator  i = motsTrouves.begin();

    while (i != motsTrouves.end())
    {
        if(*i == motEnCours)
            return true;
        ++i;
    }

    motsTrouves.push_back(motEnCours);
    return false;
}
