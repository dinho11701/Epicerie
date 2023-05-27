/*  AUTEUR(S):
    1) Chagnon, Lysanne CHAL65550003
    2) Essongue, Oswald ESSO16019809
*/
#include <iostream>
#include "epicerie.h"
#include <cmath>

using namespace std;

istream& operator >>(istream& is, Commande& c){
    c.produitsClients.vider();
    c.epicerieClients.vider();
    string nomproduit;
    is >> nomproduit;
    while(is && nomproduit!=";"){
	    int quantite;
        is >> quantite;
        c.produitsClients[nomproduit] = quantite;
        is >> nomproduit;
        
    }
    return is;
}

void Commande::insererEpicerie(int ordre, string nomEpicerie){
    epicerieClients[ordre] = nomEpicerie;
}

void Epicerie::placer(string nomEpicerie, PointST position){
    positiongeo = position;
    nom = nomEpicerie;
}


void Epicerie::approvisionner(string nomProduit, int quantite, Date date){


    int quantiteTotal = quantite;

    if(inventaire.contient(nomProduit)){

        if(inventaire[nomProduit].contient(date)){
            quantiteTotal += inventaire[nomProduit][date];
        }

    }

    inventaire[nomProduit][date] = quantiteTotal;


}


void Commande::ramasser(ArbreMap<string,Epicerie>& listeEpicerie, Date date){

    int quantiteNouvelle;

    for(ArbreMap<int, string>::Iterateur iter = epicerieClients.debut();iter;++iter){
        //le nom produit est ds l'inventaire épicerie
        if(listeEpicerie.contient(iter.valeur())){

            for(ArbreMap<string, int>::Iterateur iter1 = produitsClients.debut();iter1;++iter1){
                //si l'épicerie contient ce produit et le prod est diff de 0
                if(listeEpicerie[iter.valeur()].inventaire.contient(iter1.cle()) && iter1.valeur() != 0){
                    Date dateTest;
                    dateTest.genereGrandeDate();
                    ArbreMap<Date,int>::Iterateur iter2 = listeEpicerie[iter.valeur()].inventaire[iter1.cle()].rechercherEgalOuPrecedent(dateTest);
                    while(iter2 && iter2.cle() > date && iter1.valeur() != 0){
                        if(iter1.valeur() != 0 && iter2.valeur() != 0){
                            
                            //le nombre de produits demandés par le client est plus grand que le nombre de produits ds l'inventaire
                            if(iter1.valeur() > iter2.valeur()){
                                quantiteNouvelle = iter1.valeur() - iter2.valeur();
                                produitsClients[iter1.cle()] = quantiteNouvelle;

                                listeEpicerie[iter.valeur()].inventaire[iter1.cle()][iter2.cle()] = 0;

                            }else{
                                quantiteNouvelle = iter2.valeur() - iter1.valeur();
                                listeEpicerie[iter.valeur()].inventaire[iter1.cle()][iter2.cle()] = quantiteNouvelle;

                                produitsClients[iter1.cle()] = 0;

                            }
                        }
                        dateTest = iter2.cle();
                        dateTest.diminuerDate();
                        iter2 = listeEpicerie[iter.valeur()].inventaire[iter1.cle()].rechercherEgalOuPrecedent(dateTest);
                    }

                }


            }

        }


    }

}

void Commande::recommander(ArbreMap<string,Epicerie>& listeEpicerie, Date date, double distance,
 PointST position, int maxEpicerie){
    if(maxEpicerie == 1){
        recommander1Epicerie(listeEpicerie,date,distance,position);
    }else{
        recommander23Epicerie(listeEpicerie,date,distance,position,maxEpicerie);
    }
}

void Commande::recommander1Epicerie(ArbreMap<string,Epicerie>& listeEpicerie, Date date, double distance,
 PointST position){
    ArbreMap<string,int> copie;
    string epicerieChoisie = "";

    for(ArbreMap<string,Epicerie>::Iterateur iter = listeEpicerie.debut(); iter; ++iter){
        double distanceTest = position.distance(iter.valeur().positiongeo) * 2;
        remplirCopieCommande(copie);

        for(ArbreMap<string,int>::Iterateur iter1 = copie.debut(); iter1; ++iter1){
            if(iter.valeur().inventaire.contient(iter1.cle()) && copie[iter1.cle()] != 0){
                for(ArbreMap<Date,int>::Iterateur iter2 = iter.valeur().inventaire[iter1.cle()].debut(); iter2; ++iter2){
                    if(date < iter2.cle() && iter1.valeur() != 0 && iter2.valeur() != 0){
                        if(iter1.valeur() > iter2.valeur()){
                            copie[iter1.cle()] = iter1.valeur() - iter2.valeur();
                        }else{
                            copie[iter1.cle()] = 0;
                        }
                    }
                }
            }
        }
        if(verifVide(copie) && distanceTest < distance){
            distance = distanceTest;
            epicerieChoisie = iter.cle();
        }
    }

    if(epicerieChoisie != ""){
        cout << round(distance)
            << "m "
            << epicerieChoisie;
    }else{
        cout << "IMPOSSIBLE";
    }
}

void Commande::recommander23Epicerie(ArbreMap<string,Epicerie>& listeEpicerie, Date date, double distance, PointST position, int nbEpicerie){
    ArbreMap<string,int> copie;
    ArbreMap<string,int> copie2;
    ArbreMap<string,int> copie3;
    ArbreAVL<string> epiceriesChoisies;
    for(ArbreMap<string,Epicerie>::Iterateur iter = listeEpicerie.debut(); iter; ++iter){
        double distanceTest = position.distance(iter.valeur().positiongeo);
        remplirCopieCommande(copie);
        for(ArbreMap<string,int>::Iterateur iter1 = copie.debut(); iter1; ++iter1){
            if(iter.valeur().inventaire.contient(iter1.cle()) && copie[iter1.cle()] != 0){
                for(ArbreMap<Date,int>::Iterateur iter2 = iter.valeur().inventaire[iter1.cle()].debut(); iter2; ++iter2){
                    if(date < iter2.cle() && iter1.valeur() != 0 && iter2.valeur() != 0){
                        if(iter1.valeur() > iter2.valeur()){
                            copie[iter1.cle()] = iter1.valeur() - iter2.valeur();
                        }else{
                            copie[iter1.cle()] = 0;
                        }
                    }
                }
            }
        }
        if(verifVide(copie) && distanceTest*2 < distance){
            epiceriesChoisies.vider();
            distance = distanceTest*2;
            epiceriesChoisies.inserer(iter.cle());
        }else if(!verifVide(copie)){
            for(ArbreMap<string,Epicerie>::Iterateur iter10 = listeEpicerie.debut(); iter10; ++iter10){
                remplirCopieCopie(copie,copie2);
                if(iter.valeur().positiongeo.distance(iter10.valeur().positiongeo) != 0){
                    double distanceTest2 = distanceTest + iter.valeur().positiongeo.distance(iter10.valeur().positiongeo);
                    for(ArbreMap<string,int>::Iterateur iter11 = copie2.debut(); iter11; ++iter11){
                        if(iter10.valeur().inventaire.contient(iter11.cle()) && copie2[iter11.cle()] != 0){
                            for(ArbreMap<Date,int>::Iterateur iter21 = iter10.valeur().inventaire[iter11.cle()].debut(); iter21; ++iter21){
                                if(date < iter21.cle() && iter11.valeur() != 0 && iter21.valeur() != 0){
                                    if(iter11.valeur() > iter21.valeur()){
                                        copie2[iter11.cle()] = iter11.valeur() - iter21.valeur();
                                    }else{
                                        copie2[iter11.cle()] = 0;
                                    }
                                }
                            }
                        }
                    }
                    double distanceRentre = distanceTest2 + iter10.valeur().positiongeo.distance(position);
                    if(verifVide(copie2) && distanceRentre < distance){
                        epiceriesChoisies.vider();
                        distance = distanceRentre;
                        epiceriesChoisies.inserer(iter.cle());
                        epiceriesChoisies.inserer(iter10.cle());
                    }else if(!verifVide(copie2) && nbEpicerie > 2){
                        for(ArbreMap<string,Epicerie>::Iterateur iter20 = listeEpicerie.debut(); iter20; ++iter20){
                            remplirCopieCopie(copie2,copie3);
                            if(iter10.valeur().positiongeo.distance(iter20.valeur().positiongeo) != 0){
                                double distanceTest3 = distanceTest2 + iter10.valeur().positiongeo.distance(iter20.valeur().positiongeo);
                                for(ArbreMap<string,int>::Iterateur iter12 = copie3.debut(); iter12; ++iter12){
                                    if(iter20.valeur().inventaire.contient(iter12.cle()) && copie3[iter12.cle()] != 0){
                                        for(ArbreMap<Date,int>::Iterateur iter22 = iter20.valeur().inventaire[iter12.cle()].debut(); iter22; ++iter22){
                                            if(date < iter22.cle() && iter12.valeur() != 0 && iter22.valeur() != 0){
                                                if(iter12.valeur() > iter22.valeur()){
                                                    copie3[iter12.cle()] = iter12.valeur() - iter22.valeur();
                                                }else{
                                                    copie3[iter12.cle()] = 0;
                                                }
                                            }
                                        }
                                    }
                                }
                                distanceRentre = distanceTest3 + iter20.valeur().positiongeo.distance(position);
                                if(verifVide(copie3) && distanceRentre < distance){
                                    epiceriesChoisies.vider();
                                    distance = distanceRentre;
                                    epiceriesChoisies.inserer(iter.cle());
                                    epiceriesChoisies.inserer(iter10.cle());
                                    epiceriesChoisies.inserer(iter20.cle());
                                }
                            }
                        }
                    }
                }
            }
                
        }
    }
    if(!epiceriesChoisies.vide()){
        cout << round(distance)
            << "m ";
        for(ArbreAVL<string>::Iterateur iterFinal = epiceriesChoisies.debut(); iterFinal; ++iterFinal){
            cout << *iterFinal
                << " ";
        }
    }else{
        cout << "IMPOSSIBLE";
    }
}


void Commande::remplirCopieCommande(ArbreMap<string,int>& listeProduit){
    listeProduit.vider();
    for(ArbreMap<string,int>::Iterateur iter = produitsClients.debut(); iter; ++iter){
        listeProduit[iter.cle()] = iter.valeur();
    }
}

bool verifVide(ArbreMap<string,int>& listeProduit){
    for(ArbreMap<string,int>::Iterateur iter = listeProduit.debut(); iter; ++iter){
        if(iter.valeur() != 0)    return false;
    }
    return true;
}

void remplirCopieCopie(ArbreMap<string,int>& listeProduit, ArbreMap<string,int>& listeProduit2){
    listeProduit2.vider();
    for(ArbreMap<string,int>::Iterateur iter = listeProduit.debut(); iter; ++iter){
        listeProduit2[iter.cle()] = iter.valeur();
    }
}

void Epicerie::afficherEpicerie(Date date){
    for(ArbreMap<string,ArbreMap<Date,int>>::Iterateur iter = inventaire.debut(); iter; ++iter){
        int nbProduit = 0;
        for(ArbreMap<Date,int>::Iterateur iter1 = iter.valeur().debut(); iter1; ++iter1){
            if(iter1.cle() > date){
               nbProduit += iter1.valeur(); 
            }
        }
        if(nbProduit != 0){
            cout << iter.cle()
                << " "
                << nbProduit
                << " ";
        }
    }

    cout << ";";
}

std::ostream& operator << (std::ostream& os, const Commande& c){
    int reste = 0;
    for(ArbreMap<std::string,int>::Iterateur iter = c.produitsClients.debut(); iter; ++iter){
        reste += iter.valeur();
    }
    if(reste == 0){
        os << "COMPLET ";
    }else{
        os << "MANQUE ";
        for(ArbreMap<std::string,int>::Iterateur iter1 = c.produitsClients.debut(); iter1; ++iter1){
            if(iter1.valeur() != 0){
                os << iter1.cle()
                    << " "
                    << iter1.valeur()
                    << " ";
            }
        }
        os << ";";
    }
    return os;
}


