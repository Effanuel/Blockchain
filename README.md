# Blockchain
Bitcoin blockchain implementacija naudojant C++
## Reikalavimai
---
Sukurkite "centralizuotą" blokų grandinę (blockchain'ą) ir susimuliuokite blokų grandinės veikimą kuo natūralesnėmis sąlygomis. Norint tai pasiekti, preliminari veiksmų seka (nebūtinai eilės tvarka, tokia kokia čia nurodyta) galėtų būti tokia:

1. Sugeneruoti ~1000 tinklo vartotojų (aka user'ių), kurie turėtų bent tris atributus: vardą, viešąjį hash raktą (public_key) ir tam tikros valiutos atsitiktinį balansą, pvz. nuo 1000 iki 1000000 vienetų.
2. Sugeneruoti tam tikrą skaičių, pvz., transkacijų pol'ą sudarytą iš 10000 atsitiktinių transakcijų (jų struktūrą kol kas yra neformalizuota) tarp visų vartotojų, kurių metu jie vienas kitam atlikinėtų pinigų pervedimus.
3. Iš šių transakcijų atsitiktinai pasirinkti 100-ą (tarsime, kad blokas talpins apie 100 transakcijų) ir jas priskirti naujam sugeneruotam blokui (kurį kitame žingsnyje dar reikės "iškąsti"), kurio struktūra nurodyta paveiksle aukščiau.
4. Realizuoti naujų blokų kasimo (angl. mining) Proof-of-Work (PoW) procesą, kurio tikslas yra surasti naujam blokui hash'ą, tenkinantį Difficulty Targer reikalavimą, t.y., hash'o pradžioje esančių nulių skaičių.
5. Suradus tokį naujo bloko hash'ą, bloką pridėti prie grandinės. Kartoti 3-5 žingsnius tol, kol yra laisvų transakcijų.
---

 ### Blockchain block'as susidaro iš:
 * Timestamp;
 * Version;
 * Merkel Root Hash;
 * Nonce;
 * Difficulty target;
 * Transactions body;
 
 ### Mining algorithm:
 * Simple incrementation of nonce by 1 each time;
 
 
 ### Hash to mine:
 * Merkel_Root_Hash + nonce


---

## Prerequisites
1. GNU C++ Compiler

## Installation
1. [Atsisiūskite naujausią versiją.]()
2. Extract failus.
3. Per command-line:
```
cd HashGenerator
make run
```
4. Executable yra **./Blockchain/bin/project.exe**
```
cd bin
./project
```
---





