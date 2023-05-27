# TP2 INF3105

## Auteurs
1) Chagnon, Lysanne CHAL65550003
2) Essongue, Oswald ESSO16019809

## Auto-évaluation
Les commandes DATE, PLACER, APPROV, INVENTAIRE et RAMASSER fonctionnent correctement.
La commande RECOMMANDER fonctionne avec 1 épicerie max avec les dates d'expiration et avec 2 et 3 épiceries max (si le max est plus grand que 3, le programme va quand même regarder pour juste 3 épiceries max).

## Temps d'exécution des tests
```
Test    	CPU	Mém.(k)	Validation
exemple1.txt	0.00	3904k	26 bon(s)	1 erreur(s)	/27	|	Échec
exemple2.txt	0.00	3596k	20 bon(s)	0 erreur(s)	/20	|	OK
exemple3.txt	0.00	3784k	19 bon(s)	0 erreur(s)	/19	|	OK
exemple4.txt	0.00	3500k	12 bon(s)	0 erreur(s)	/12	|	OK
exemple5.txt	0.00	4072k	15 bon(s)	0 erreur(s)	/15	|	OK
testC0.txt	0.00	4144k	33 bon(s)	0 erreur(s)	/33	|	OK
testC1.txt	0.00	4164k	303 bon(s)	0 erreur(s)	/303	|	OK
testC2.txt	0.00	4116k	359 bon(s)	0 erreur(s)	/359	|	OK
testC3.txt	0.02	4284k	364 bon(s)	0 erreur(s)	/364	|	OK
testC4.txt	5.31	9948k	3435 bon(s)	0 erreur(s)	/3435	|	OK
testC5.txt	58.88	16500k	30500 bon(s)	0 erreur(s)	/30500	|	OK
testC6.txt	52.09	41068k	3251 bon(s)	0 erreur(s)	/3251	|	OK
testD0.txt	0.00	4124k	402 bon(s)	0 erreur(s)	/402	|	OK
testD1.txt	0.01	4236k	3110 bon(s)	0 erreur(s)	/3110	|	OK
testD2.txt	0.93	8672k	6300 bon(s)	0 erreur(s)	/6300	|	OK
testD3.txt	103.59	41492k	30600 bon(s)	0 erreur(s)	/30600	|	OK
testE0.txt	0.00	4188k	402 bon(s)	0 erreur(s)	/402	|	OK
testE1.txt	0.13	4196k	3041 bon(s)	69 erreur(s)	/3110	|	Échec
testE2.txt	179.97	5092k	1198 bon(s)	54 erreur(s)	/6300	|	Échec
testE3.txt	179.93	8696k	2593 bon(s)	0 erreur(s)	/30600	|	OK_interrompu
testE4.txt	179.98	5088k	534 bon(s)	28 erreur(s)	/30600	|	Échec
testE5.txt	0.20	4204k	3029 bon(s)	81 erreur(s)	/3110	|	Échec
```

## Complexité temporelle

* e indique nombre d'épiceries visitées par le client
* n indique nombre d'épiceries placé (ou à placer);
* m indique nombre de types de produit différents (juste le nom du produit);
* k indique nombre d'items sur la liste de la commande;
* d indique la date d'expiration du produit;

### PLACER
```
condition PLACER -> O(8) -> O(1)
    insererEpicerieDansArbre -> O(1 + log(n)) -> O(log(n))
        placer -> O(2) -> O(1)
O(1 + log(n) + 1) -> O(log(n))
```

### APPROV
```
condition APPROV -> O(8) -> O(1)
    boucle while -> O(n + 5) -> O(n)
        * approvisionnerEpicerie
            approvisionner -> O(1 + log(m) + log(m)log(d) + log(m)log(d) + log(m)log(d)) -> O(log(m)log(d))
            [] -> O(log (n))
O(1 + n*(log(m)log(d) + log(n))) -> O(nlog(m)log(d) + nlog(n))
```

### RAMASSER
```
condition RAMASSER -> O(k + k + 1 + 1 + k(1 + 1 + log(k) + 1)) -> O(klog(k))
    boucle while -> O(e + 2) -> O(e)
        * insererEpicerie -> O(log(e))
    ramasser -> O(1 + e*(log(n) + k*(log(n)log(m) + 1 + 1 + log(n)log(m)log(d) + d*(3 + log(k) + log(n)log(m)log(d) + 2 + log(n)log(m)log(d))))) -> O(ekd)
O(klog(k) + elog(e) + ekd) -> O(ekd)
```

### RECOMMANDER

#### Nb d'épicerie max = 1
```
condition RECOMMANDER -> O(10 + klog(k)) -> O(klog(k))
    recommander -> O(2) -> O(1)
        recommander1Epicerie -> O(1 + 1 + n(1 + k + k(log(m) + log(k) + d(log(m) + 1 + 1 + log(k))) + k + 1 + 1) + 4) -> O(nk + nkdlog(m) + nkdlog(k))
            n * remplirCopieCommande -> O(n(klog(k))) -> O(knlog(k))
O(klog(k) + 1 + knlog(k) + nk + nkdlog(m) + nkdlog(k)) -> O(nk + nkdlog(m) + nkdlog(k))
```
#### Nb d'épicerie max = 2
```
condition RECOMMANDER -> O(10 + klog(k)) -> O(klog(k))
    recommander -> O(2) -> O(1)
    recommander23Epicerie -> O(recommander1Epicerie^2) -> O(n^2k^2 + n^2k^2d^2log(m)^2 + n^2k^2d^2log(k)^2)
        n * remplirCopieCommande -> O(n(klog(k))) -> O(knlog(k))
        n * remplirCopieCopie -> O(n(klog(k))) -> O(knlog(k))
O(klog(k) + 1 + k^2n^2log(k)^2 + n^2k^2 + n^2k^2d^2log(m)^2 + n^2k^2d^2log(k)^2) -> O(n^2k^2 + n^2k^2d^2log(m)^2 + n^2k^2d^2log(k)^2)
```
#### Nb d'épicerie max = 3
```
condition RECOMMANDER -> O(10 + klog(k)) -> O(klog(k))
    recommander -> O(2) -> O(1)
    recommander23Epicerie -> O(recommander1Epicerie^3) -> O(n^3k^3 + n^3k^3d^3log(m)^3 + n^3k^3d^3log(k)^3)
        n * remplirCopieCommande -> O(n(klog(k))) -> O(knlog(k))
        n * remplirCopieCopie -> O(n(klog(k))) -> O(knlog(k))
        n * remplirCopieCopie -> O(n(klog(k))) -> O(knlog(k))
O(klog(k) + 1 + k^3n^3log(k)^3 + n^3k^3 + n^3k^3d^3log(m)^3 + n^3k^3d^3log(k)^3) -> O(n^3k^3 + n^3k^3d^3log(m)^3 + n^3k^3d^3log(k)^3)
```

### Programme
La complexité de notre programme (./tp2) est de O(n^3k^3 + n^3k^3d^3log(m)^3 + n^3k^3d^3log(k)^3) parce que la commande RECOMMANDER (avec 3 épiceries maximale) est celle qui a la plus grande complexité dans tout le programme.