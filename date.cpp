/*  AUTEUR(S):
    1) Chagnon, Lysanne CHAL65550003
    2) Essongue, Oswald ESSO16019809
*/

#include "date.h"
#include <cstdio>
#include <iomanip>
#include <assert.h>

bool Date::operator <(const Date& d) const{
    if(annee < d.annee) return true;
    else if(annee == d.annee){
        if(mois < d.mois)   return true;
        else if(mois == d.mois){
            if(jour < d.jour)   return true;
        }
    }
    return false;
}

bool Date::operator >(const Date& date) const{
    if(annee > date.annee) return true;
    else if(annee == date.annee){
        if(mois > date.mois)    return true;
        else if(mois == date.mois){
            if(jour > date.jour)    return true;
        }
    }
    return false;
}

bool Date::operator ==(const Date& date) const{
    return annee == date.annee && mois == date.mois && jour == date.jour;
}

bool Date::operator !=(const Date& date) const{
    return annee != date.annee || mois != date.mois || jour != date.jour;
}

void Date::diminuerDate(){
    if(jour != 1){
        jour--;
    }else{
        if(mois != 1){
            mois--;
            jour = 31;
        }else{
            annee--;
            mois = 12;
            jour = 31;
        }
    }
}

void Date::genereGrandeDate(){
    jour = 31;
    mois = 12;
    annee = 9999;
}

std::ostream& operator << (std::ostream& os, const Date& d){
    int a = d.annee;
    int m = d.mois;
    int j = d.jour;
    char chaine[40];
    sprintf(chaine, "%04d-%02d-%02d", a, m, j);
    os << chaine;
    return os;
}

std::istream& operator >> (std::istream& is, Date& d){
    int a=0, m=0, j=0;
    char t1=0,t2=0;
    is >> a >> t1 >> m >> t2 >> j;
    assert(t1=='-');
    assert(t2=='-');
    d.annee = a;
    d.mois = m;
    d.jour = j;
    return is;
}

