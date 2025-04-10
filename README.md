# password_policies

În noua aplicație web pe care ați dezvoltat-o este necesară introducerea unor elemente suplimentare de securitate. Pentru asta veți dezvolta o bibliotecă de Password Policies. Aceste politici de parolă sunt configurate de fiecare client care folosește biblioteca voastră și apoi fiecare parola setată de utilizatori este verificată contra acestor reguli. Ele sunt:

Length - restricția poate specifica lungimea minimă sau lungimea minimă și maximă a unei parole.
Class - restricția spune câte clase diferite de caractere trebuie să aibă minim parola; clasele sunt: literă mică, literă mare, cifră și alte caractere
Must Include - parola trebuie obligatoriu să includă cel puțin un caracter din clasa specificată.
Must Not Include - parola trebuie obligatoriu să NU includă niciun caracter din clasa respectivă.
Repetition - restricția impune de câte ori se poate repeta consecutiv același caracter în parolă
Consecutive - restricția impune un număr maxim de caractere consecutive (ex: abc sau 123)

## Cerințe pentru punctaj maxim
Să se creeze o clasă cu numele Policy cu următoarele specificații:
- clasa trebuie să conțină 1 atribut protected numit isChecked de tip boolean.
- clasa trebuie să conțină 1 metodă publică pur virtuală numită check. Aceasta nu trebuie să întoarcă nimic, iar ca parametru trebuie să primească un std::string (parola pe care trebuie să o verificați), ca referință constantă.
- clasa trebuie să conțină o metodă publică fără niciun parametru numită getCheck, care trebuie să întoarcă atributul isChecked. Metoda trebuie să fie declarată const qualified.

## Să se creeze o clasă cu numele LengthPolicy cu următoarele specificații:
- clasa trebuie să fie moștenită din clasa Policy.
- clasa trebuie să conțină 2 atribute private numite minLength și maxLength, acestea fiind numere întregi fără semn pe 16 biți.
- clasa trebuie să conțină un constructor public cu 1 parametru, care să inițializeze minimul cu valoarea dată și maximul cu valoarea 255.
- clasa trebuie să conțină un constructor public cu 2 parametri, care să inițializeze minimul și maximul cu valorile date.
- clasele trebuie să implementeze metoda check din clasa de bază. Aceasta trebuie să verifice ceea ce este specificat în cerință.

## Să se creeze o clasă cu numele ClassPolicy cu următoarele specificații:
- clasa trebuie să fie moștenită din clasa Policy.
- clasa trebuie să conțină 1 atribut privat numit minClassCount, acesta fiind un număr întreg fără semn pe 16 biți.
- clasa trebuie să conțină un constructor public cu 1 parametru, care să inițializeze atributul cu valoarea specificată.
- clasele trebuie să implementeze metoda check din clasa de bază. Aceasta trebuie să verifice ceea ce este specificat în cerință.

## Să se creeze clasele numite IncludePolicy și NotIncludePolicy cu următoarele specificații:
- clasele trebuie să fie moștenite din clasa Policy.
- clasele trebuie să conțină 1 atribut privat numit characterType, acesta fiind de tip char.
- clasele trebuie să conțină un constructor public cu 1 parametru, care să inițializeze atributul cu valoarea specificată.
- clasele trebuie să implementeze metoda check din clasa de bază. Aceasta trebuie să verifice ceea ce este specificat în cerință.
Sfat: Folositi biblioteca ctype.h.

## Să se creeze o clasele numite RepetitionPolicy și ConsecutivePolicy și  cu următoarele specificații:
- clasele trebuie să fie moștenite din clasa Policy.
- clasele trebuie să conțină 1 atribut privat numit maxCount, acesta fiind de tip număr întreg fără semn pe 16 biți.
- clasele trebuie să conțină un constructor public cu 1 parametru, care să inițializeze atributul cu valoarea specificată.
- clasele trebuie să implementeze metoda check din clasa de bază. Aceasta trebuie să verifice ceea ce este specificat în cerință.

## Să se scrie o funcție numită checkPassword, care să primească 2 parametri, primul de tip std::string, reprezentând parola pe care vreți să o verificați, iar al doilea un std::vector de obiecte de tip Policy*, reprezentând politicile citite de la tastatură. Funcția trebuie să returneze un std::string care să fie "OK" sau "NOK", în funcție de parolă.

## Cerință
Dându-se un set de politici de parolă sigură și apoi o listă de parole, să se afișeze pentru fiecare din ele OK sau NOK, în funcție de respectarea sau nu a tuturor acestor politici.

## Date de intrare
Pe prima linie se află un număr întreg pozitiv n, necunoscut de mare, reprezentând numărul de reguli care trebuie respectate. Pe următoarele n linii se află definiția unei reguli, în următoarele formate posibile:

length <min_length> - parola trebuie să aibă min_length caractere (inclusiv); 0 < min_length
length <min_length> <max_length> - parola trebuie să aibă între min_length și max_length caractere (inclusiv); 0 < min_length <= max_length
class <min_class_count> - parola trebuie să aibă minim min_class_count tipuri de caractere diferite (literă mică, literă mare, cifră și alte caractere); 0 < min_class_count < 5
include <class> - parola trebuie obligatoriu să includă cel puțin un caracter din clasa specificată; class poate fi a, A, 0 sau $, caractere ce denotă clasa dorită
ninclude <class> - parola trebuie obligatoriu să nu includă niciun caracter din clasa specificată; class urmează aceleași reguli de mai sus
repetition <max_count> - același caracter se poate repeta pe poziții consecutive de maxim max_count ori; 0 < max_count
consecutive <max_count> - parola poate avea max_count caractere consecutive în secvență; 0 < max_count
Pe următoarele linii, până la EOF, se află câte o parolă pe linie, ce vor fi verificate cu regulile specificate.

## Date de ieșire
Pentru fiecare parolă verificată, se va afișa OK dacă parola respectă TOATE regulile specificate, sau NOK dacă există măcar o regulă care nu este respectată.



## Exemple
Intrare	Ieșire	Explicații
4
length 6
include 0
include A
repetition 2
PimpMyPassword
HoldMyB33r
OnceUponAtimeinKansas
1234
NOK
OK
NOK
NOK
Există patru restricții: parola trebuie să aibă minim 6 caractere, să conțină cel puțin o cifră și o literă mare și lungimea maximă de caractere repetate să fie 2.

PimpMyPassword - NOK (nu conține cel puțin o cifră)
HoldMyB33r - OK
OnceUponAtimeinKansas - NOK (nu conține cel puțin o cifră)
1234 - NOK (mai scurtă de 6 și nu conține nicio literă mare)
3
length 6 12
class 3
consecutive 3
PimpMyPassword
HoldMyB33r
OnceUponAtimeinKansas
1234

NOK
OK
NOK
NOK
Există trei restricții: parola trebuie să aibă minim 6 și maxim 12 caractere, să conțină cel puțin trei tipuri de caractere diferite și lungimea maximă de caractere consecutive să fie 3.

PimpMyPassword - NOK (are mai mult de 12 caractere, conține doar două tipuri de caractere)
HoldMyB33r - OK
OnceUponAtimeinKansas - NOK (are mai mult de 12 caractere, conține doar două tipuri de caractere)
1234 - NOK (mai scurtă de 6 caractere, conține doar un tip de caractere și are 4 caractere consecutive în secvență)
