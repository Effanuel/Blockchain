# Blockchain
Bitcoin blockchain implementacija naudojant C++
## Reikalavimai
---
Sukurkite "centralizuotą" blokų grandinę (blockchain'ą) ir susimuliuokite blokų grandinės veikimą kuo natūralesnėmis sąlygomis. Norint tai pasiekti, preliminari veiksmų seka (nebūtinai eilės tvarka, tokia kokia čia nurodyta) galėtų būti tokia:

1. Sugeneruoti ~1000 tinklo vartotojų (aka user'ių), kurie turėtų bent tris atributus: **vardą**, **viešąjį hash raktą (public_key)** ir tam tikros valiutos atsitiktinį **balansą**, pvz. nuo 1000 iki 1000000 vienetų.
2. Sugeneruoti tam tikrą skaičių, pvz., **transkacijų pol'ą sudarytą iš 10000 atsitiktinių transakcijų** (jų struktūrą kol kas yra neformalizuota) tarp visų vartotojų, kurių metu jie vienas kitam atlikinėtų pinigų pervedimus.
3. Iš šių transakcijų atsitiktinai pasirinkti 100-ą (tarsime, kad blokas talpins apie 100 transakcijų) ir jas **priskirti naujam sugeneruotam blokui** (kurį kitame žingsnyje dar reikės "iškąsti"), kurio struktūra nurodyta paveiksle aukščiau.
4. Realizuoti naujų blokų **kasimo (angl. mining) Proof-of-Work (PoW) procesą,** kurio tikslas yra surasti naujam blokui hash'ą, tenkinantį **Difficulty Target** reikalavimą, t.y., hash'o pradžioje esančių nulių skaičių.
5. Suradus tokį naujo bloko hash'ą, **bloką pridėti prie grandinės**. Kartoti 3-5 žingsnius tol, kol yra laisvų transakcijų.
---

 ### Blockchain block'as susidaro iš:
 * Timestamp; *(time the block got added to the main blockchain)*
 * Merkel Root Hash; *(Hash of all strings of transactions in the body)*
 * Nonce; *(iterable number variable for mining the block)*
 * Difficulty target; *(number of zeroes needed at the start of mined hash)*
 * Version; *(version of a blockchain)*
 * Block hash; *(mined hash of merkle root hash and nonce)*
 * Confirmed transactions body; *(chosen and mined transactions. Default is 100)*
 
 ### Mining algorithm:
 * Simple incrementation of nonce by 1 each time;
 
---

## Prerequisites
1. GNU C++ Compiler

## Installation
1. [Atsisiūskite naujausią versiją.](https://github.com/Effanuel/Blockchain/releases/tag/v0.3)
2. Extract failus.
3. Per command-line:
```
cd Blockchain
g++ -std=c++14 -O3 Blockchain.cpp -o project
```
4. Executable yra **./project.exe**
---


[v0.1](https://github.com/Effanuel/Blockchain/archive/v0.1.zip) Features:
* Random transactions are created;
* Miners choose top 100 of those transactions and create their own block out of them;
* Miners use ```merkle_root_hash``` and incrementable ```nonce``` to find suitable hash that suffices blockchain's ```difficulty target```;
* Mined transactions with the block are added to the main blockchain
* Confirmed/mined transactions' amounts are sent;

---

[v0.2](https://github.com/Effanuel/Blockchain/archive/v0.2.zip) Features:
* **Validation of balances and hashes** before adding to the unconfirmed transaction pool;
* **Artificial miner concurrency function**:
  * 5 different miners mine, each having limited number of tries to find the hash;
  * If hash out of that iteration is not found by all of the miners, number of tries is increased;
  * Repeat, until the correct hash is found;
* **Random transaction taking** from the pool;
* Reward to the miners; *(default: 100 + fees)*

---

[v0.3](https://github.com/Effanuel/Blockchain/archive/v0.3.zip) Features:
* Update merkle root tree for **transactions**;







