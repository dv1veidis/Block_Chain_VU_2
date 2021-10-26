# Block_Chain_VU_2
Self made blockchain for VU block chain course

## V0.1

### Naudojimasis

Reikia susikurti aplanka pavadinimu blockChain
Tada paleisti 
 ``` powershell
 g++ main.cpp -o main
 ./main
 ```
 Ir pasirinkti kiekį naudotojų ir transakcijų
 ``` powershell
 How many users?
 1000
 How many transactions?
 10000
 ```
 
 ### Informacija apie esama kodą
 
   1. Naudojamas 2 nulių sunkumas, kadangi dėl hashavimo nepastovumo naudojant daugiau nei 2 sunkumą rezultatuoja į programos nutraukima kasant, bet kodėl įvyksta dar bandoma išsiaiškinti
   2. Kodo kasimas kol kas nėra matuojamas laiku
   3. Kol kas nėra realizuotas merkel tree hashavimas, yra tiesiog visų transakcijų hashų bendras hashas

 ### Bloko pavyzdys
 ``` powershell
 Block hash: 0001e2a3b64bc76b6fa98844a1e50b984448a0040a89365cb2a852c3ba786302
Prievious hash: 00013077e0435ade016849de5e73c2b8573a5319e3ec73f720b9c16351157d63
Timestamp: Thu Oct 14 22:15:59 2021
Difficulty: 3
Merkle Root: 821167b3122e3e790788b0b02439ef4fe3f0c586f8d205e0fe1dfc8011ef46c7
Version: 1
Nonce: 48015546
Height: 2
Transactions(100):
------------------------------------------------------------
Transaction id 31e5b732dd651207df947db6fefb5a2fe42d0a08bbcf73a3398db8624de9e4c8
Sender: user6
Receiver: user1
Amount: 65497
Transaction id db05f62dcf27c5b331c84a77d2387bdfeeb027dd8ae4f55227abba84742d9f26
Sender: user1
Receiver: user7
Amount: 26157
 ```
 ### Vartotojo pavyzdys
 ``` powershell
user1
1ebd96d16b98ba9e488a7c267c98695b7ff2fbfcf974fe28fc5f167ab9bd5617
71271
user2
b4da19963f37e017d0ed6663c8bf175c91cc2afffbccab18fb29772e7c4b7b8f
42606
 ```
 
 ## version 0.1.1
 
  1. Įgyvendintas merkle tree hashavimas
  2. Įgyvendintas transakcijų baseino pervedimų sumos ir hasho verifikavimas
  3. Hashavimo funkcijos patobulinimas
 
