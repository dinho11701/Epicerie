/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2017 | Lab8 + TP2
    http://ericbeaudry.uqam.ca/INF3105/lab8/
    http://ericbeaudry.uqam.ca/INF3105/tp2/

    AUTEUR(S):
     1) Chagnon, Lysanne CHAL65550003
     2) Essongue, Oswald ESSO16019809
*/
#if !defined(__ARBREMAP_H__)
#define __ARBREMAP_H__
#include "arbreavl.h"

template <class K, class V>
class ArbreMap {

  public:
    bool contient(const K&) const;

    void enlever(const K&);
    void vider();
    bool vide() const;

    const V& operator[] (const K&) const;
    V& operator[] (const K&);

    

  private:
    // À compléter : voir la Section 8.11 (Arbres associatifs (Mapping Trees)) des notes de cours.

    class Entree{
        public:
            Entree(const K& c):cle(c),valeur(){}
            K cle;
            V valeur;
            bool operator < (const Entree& e) const {
                return cle < e.cle;
            }
            bool operator > (const Entree& e) const {
                return cle > e.cle;
            }
            bool operator == (const Entree& e) const {
                return cle == e.cle;
            }
            bool operator != (const Entree& e) const {
                return cle != e.cle;
            }
    };

    ArbreAVL<Entree> entrees;
    
    public:
    class Iterateur {
      public:
        Iterateur(const ArbreMap& a) : iter(a.entrees.debut()) {}
        Iterateur(typename ArbreAVL<Entree>::Iterateur i) : iter(i) {}
        operator bool() const;
        bool operator!() const;
        
        Iterateur& operator++();
        Iterateur operator++(int);

        const K& cle() const;
        const V& valeur() const; // ?? constant ou non ??

      private:
        typename ArbreAVL<Entree>::Iterateur iter;
    };
    // ...

    Iterateur debut() const;
    Iterateur fin() const;
    Iterateur rechercher(const K& cle) const;
    Iterateur rechercherEgalOuSuivant(const K& cle) const;
    Iterateur rechercherEgalOuPrecedent(const K& cle) const;
};

template <class K, class V>
void ArbreMap<K,V>::vider(){
    entrees.vider();
}

template <class K, class V>
bool ArbreMap<K,V>::vide() const{
    return entrees.vide();
}

template <class K, class V>
void ArbreMap<K,V>::enlever(const K& c)
{
    // À compléter
}

template <class K, class V>
bool ArbreMap<K,V>::contient(const K& c) const
{
    return entrees.contient(Entree(c));
}

template <class K, class V>
const V& ArbreMap<K,V>::operator[] (const K& c)  const
{
    return entrees[entrees.rechercher(c)].valeur;
}

template <class K, class V>
V& ArbreMap<K,V>::operator[] (const K& c) 
{
    typename ArbreAVL<Entree>::Iterateur iter=entrees.rechercher(Entree(c));
    if(!iter){
        entrees.inserer(Entree(c));
        iter = entrees.rechercher(c);
    }
    return entrees[iter].valeur;
}


//------------------------ITERATEUR--------------------------------------

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::debut() const{
    return Iterateur(entrees.debut());
    // typename ArbreAVL<Entree>::Iterateur iter = entrees.debut();
    // return Iterateur(iter);
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::fin() const{
    return Iterateur(entrees.fin());
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::rechercher(const K &c) const{
    return Iterateur(entrees.rechercher(Entree(c)));
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::rechercherEgalOuPrecedent(const K &c) const{
    return Iterateur(entrees.rechercherEgalOuPrecedent(Entree(c)));
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::rechercherEgalOuSuivant(const K &c) const{
    return Iterateur(entrees.rechercherEgalOuSuivant(Entree(c)));
}

template <class K, class V>
ArbreMap<K,V>::Iterateur::operator bool() const{
    return iter.operator bool();
}

template <class K, class V>
bool ArbreMap<K,V>::Iterateur::operator!() const{
    //pas sure
    return !iter.operator bool();
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur &ArbreMap<K,V>::Iterateur::operator++(){
    ++iter;
    return *this;
}

template<class K, class V> 
typename ArbreMap<K, V>::Iterateur ArbreMap<K, V>::Iterateur::operator++(int){
    Iterateur copie(*this);
    operator++();
    // retourne l'ancienne valeur
    return copie;
}

template<class K, class V>
const K &ArbreMap<K, V>::Iterateur::cle() const{
    return (*iter).cle;
}

template<class K, class V> 
const V &ArbreMap<K, V>::Iterateur::valeur() const{
    return (*iter).valeur;
}


#endif