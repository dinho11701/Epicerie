/*  AUTEUR(S):
    1) Chagnon, Lysanne CHAL65550003
    2) Essongue, Oswald ESSO16019809
*/
#if !defined(_EPICERIE__H_)
#define _EPICERIE__H_

#include <string>
#include "arbremap.h"
#include "pointst.h"
#include "date.h"


using namespace std;


class Epicerie{
    public:

        /**
         * Crée une épicerie avec son nom et sa position
         * 
         * @param nomEpicerie le nom de l'épicerie
         * @param position la position de l'épicerie
         */
        void placer(string nomEpicerie, PointST position);

        /**
         * Réapprovisionne l'épicerie avec un type de produit
         * 
         * @param nomProduit le nom du produit
         * @param quantite la quantité de ce produit
         * @param date la date d'expiration du produit
         */
        void approvisionner(string nomProduit, int quantite, Date date);

        /**
         * Affiche l'inventaire de l'épicerie selon la date du jour
         * 
         * @param date la date du jour
         */
        void afficherEpicerie(Date date);
        
    private:
        
        std::string nom;
        PointST positiongeo;
        ArbreMap <std::string,ArbreMap<Date,int>> inventaire;
        
        friend class Commande;
        
};

class Commande{
    public:

        /**
         * Insère dans l'ordre les épiceries que la personne veut visiter
         * 
         * @param ordre l'ordre de l'épicerie
         * @param nomEpicerie le nom de l'épicerie
         */
        void insererEpicerie(int ordre, string nomEpicerie);

        /**
         * Ramasse les produits demandés du client selon l'ordre des épiceries et la date du jour
         * 
         * @param listeEpicerie un arbre contenant tous les épiceries placées
         * @param date la date du jour
         */
        void ramasser(ArbreMap<string,Epicerie>& listeEpicerie, Date date);

        /**
         * Recommande des épiceries pour une commande
         * 
         * @param listeEpicerie un arbre contenant tous les épiceries placées
         * @param date la date du jour
         * @param distance la distance maximum que le client peut parcourir
         * @param position la position du client
         * @param maxEpicerie le nombre maximum d'épicerie que le client veut aller
         */
        void recommander(ArbreMap<string,Epicerie>& listeEpicerie, Date date, double distance,
         PointST position, int maxEpicerie);

    private:

        friend istream& operator >>(istream& is, Commande& c);
        friend std::ostream& operator << (std::ostream&, const Commande& e);

        /**
         * Recommande une épicerie pour une commande
         * 
         * @param listeEpicerie un arbre contenant tous les épiceries placées
         * @param date la date du jour
         * @param distance la distance maximum que le client peut parcourir
         * @param position la position du client
         */
        void recommander1Epicerie(ArbreMap<string,Epicerie>& listeEpicerie, Date date, double distance, PointST position);


        /**
         * Recommande une ou deux épiceries pour une commande
         * 
         * @param listeEpicerie un arbre contenant tous les épiceries placées
         * @param date la date du jour
         * @param distance la distance maximum que le client peut parcourir
         * @param position la position du client
         * @param nbEpicerie le nombre maximum d'épicerie que le client veut aller
         */
        void recommander23Epicerie(ArbreMap<string,Epicerie>& listeEpicerie, Date date, double distance, PointST position, int nbEpicerie);
        /**
         * Remplie un arbre de produit avec les données de la liste de produits de la commande
         * 
         * @param listeProduit la copie de la liste de produits de la commande
         */
        void remplirCopieCommande(ArbreMap<string,int>& listeProduit);

        ArbreMap<std::string,int> produitsClients;
        ArbreMap<int, std::string> epicerieClients;
};



/**
 * Vérifie si la commande est vide (tous les produits sont à 0)
 * 
 * @param listeProduit la copie de la liste de produits de la commande
 */
bool verifVide(ArbreMap<string,int>& listeProduit);

/**
 * Remplie la copie d'une copie
 * 
 * @param listeProduit la copie de la liste de produits de la commande originale
 * @param listeProduit la 2e copie de la liste de produits de la commande
 */
void remplirCopieCopie(ArbreMap<string,int>& listeProduit, ArbreMap<string,int>& listeProduit2);


#endif
