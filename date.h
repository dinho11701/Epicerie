/*  AUTEUR(S):
    1) Chagnon, Lysanne CHAL65550003
    2) Essongue, Oswald ESSO16019809
*/

#if !defined(__DATE_H__)
#define __DATE_H__

#include <iostream>

class Date{
  public:

    bool operator <(const Date& date) const;
    bool operator >(const Date& date) const;
    bool operator ==(const Date& date) const;
    bool operator !=(const Date& date) const;

    /**
     * Diminue la date par 1 journée
     */
    void diminuerDate();

    /**
     * Change la date par une date très loin dans le futur
     */
    void genereGrandeDate();

  private:
    int annee = 2000;
    int mois = 1;
    int jour = 1;
    
  friend std::ostream& operator << (std::ostream&, const Date& date);
  friend std::istream& operator >> (std::istream&, Date& date);
};

#endif
