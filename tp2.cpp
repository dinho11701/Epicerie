/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2017 | TP2
    http://ericbeaudry.uqam.ca/INF3105/tp2/   

    AUTEUR(S):
     1) Chagnon, Lysanne CHAL65550003
     2) Essongue, Oswald ESSO16019809
*/
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <limits>
#include "date.h"
#include "epicerie.h"
#include "pointst.h"

using namespace std;

ArbreMap<string,Epicerie> listeEpicerie;

/**
 * Insère l'épicerie dans l'arbre 'listeEpicerie'
 * 
 * @param nomEpicerie le nom de l'épicerie
 * @param position la position de l'épicerie
 */
void insererEpicerieDansArbre(string nomEpicerie, PointST position){
    Epicerie epicerie;
    epicerie.placer(nomEpicerie,position);
    listeEpicerie[nomEpicerie] = epicerie;
}

/**
 * Approvisionne l'épicerie dans l'arbre d'épiceries
 * 
 * @param nomEpicerie le nom de l'épicerie
 * @param nomProduit le nom du produit
 * @param quantite la quantité du produit
 * @param date la date d'expiration du produit
 */
void approvisionnerEpicerie(string nomEpicerie, string nomProduit, int quantite, Date date){

    listeEpicerie[nomEpicerie].approvisionner(nomProduit,quantite,date);

}



int tp2(istream& entree){
    Date maintenant;
    while(entree){
        string typecommande;
        entree >> typecommande;
        if(!entree) break; // détection fin ==> sortie
        
        if(typecommande=="RECOMMANDER"){
            PointST p;
            int nbMaxEpiceries=0;
            double maxdistance=0;
            Commande c;
            char deuxpoints=0;
            entree >> p >> nbMaxEpiceries >> maxdistance >> deuxpoints >> c;
            assert(deuxpoints==':');
            c.recommander(listeEpicerie,maintenant,maxdistance,p,nbMaxEpiceries);
        }else if(typecommande=="RAMASSER"){
            Commande c;
            entree >> c;
            string nomepicerie;
            entree >> nomepicerie;
            int ordre = 1;
            while(entree && nomepicerie!=";"){
                c.insererEpicerie(ordre, nomepicerie);
                ordre++;
                entree >> nomepicerie;
            }
            c.ramasser(listeEpicerie,maintenant);
            cout << c;
        }else if(typecommande=="APPROV"){
            string nomepicerie;
            char deuxpoints=0;
            entree >> nomepicerie >> deuxpoints;
            assert(deuxpoints==':');
            string nomproduit;
            entree >> nomproduit;
            while(entree && nomproduit!=";"){
                int quantite;
                Date dateexpiration;
                entree >> quantite >> dateexpiration;
                approvisionnerEpicerie(nomepicerie,nomproduit,quantite,dateexpiration);
                entree >> nomproduit;
            }
            cout << "OK";
        }else if(typecommande=="PLACER"){
            PointST position;
            string nom;
            char pointvirgule=0;
            entree >> nom >> position >> pointvirgule;
            assert(pointvirgule==';');
            insererEpicerieDansArbre(nom, position);
            cout << "OK";
        }else if(typecommande=="INVENTAIRE"){
            string nomepicerie;
            char pointvirgule=0;
            entree >> nomepicerie>> pointvirgule;
            assert(pointvirgule==';');
            if(listeEpicerie.contient(nomepicerie)){
                listeEpicerie[nomepicerie].afficherEpicerie(maintenant);
            }else{
               cout << "?"; 
            }
        }else if(typecommande=="DATE"){
            char pointvirgule=0;
            entree >> maintenant >> pointvirgule;
            assert(pointvirgule==';');
            cout << "OK";
        }else{
            cout << "Commande '" << typecommande << "' invalide!" << endl;
            return 2;
        }
        cout << endl;
        entree >> ws; // force la lecture d'un espace blanc.
    }
    return 0;
}
// syntaxe d'appel : ./tp2 [nomfichier.txt]
int main(int argc, const char** argv){
    // Gestion de l'entrée :
    //  - lecture depuis un fichier si un argument est spécifié;
    //  - sinon, lecture depuis std::cin.
    if(argc>1){
         std::ifstream entree_fichier(argv[1]);
         if(entree_fichier.fail()){
             std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
             return 1;
         }
         return tp2(entree_fichier);
    }else
         return tp2(std::cin);        

    return 0;
}

