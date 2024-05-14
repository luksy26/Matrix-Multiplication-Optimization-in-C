dtrmm - double triangular matrix multiplication
daxpy - double alpha X plus Y
dgemm - double general matrix multiplication


RUNTIMES (jobs 459021 459020 and 459022 on fep):

Run=./tema3_blas: N=100: Time=0.001065
Run=./tema3_blas: N=200: Time=0.004689
Run=./tema3_blas: N=400: Time=0.026733
Run=./tema3_blas: N=500: Time=0.051534
Run=./tema3_blas: N=600: Time=0.081149
Run=./tema3_blas: N=800: Time=0.179827
Run=./tema3_blas: N=1000: Time=0.357315
Run=./tema3_blas: N=1200: Time=0.605521
Run=./tema3_blas: N=1400: Time=0.939647
Run=./tema3_blas: N=1600: Time=1.403887



Run=./tema3_neopt: N=100: Time=0.008818
Run=./tema3_neopt: N=200: Time=0.072697
Run=./tema3_neopt: N=400: Time=0.599500
Run=./tema3_neopt: N=500: Time=1.221508
Run=./tema3_neopt: N=600: Time=2.037308
Run=./tema3_neopt: N=800: Time=4.952152
Run=./tema3_neopt: N=1000: Time=9.235767
Run=./tema3_neopt: N=1200: Time=18.232872
Run=./tema3_neopt: N=1400: Time=26.907232
Run=./tema3_neopt: N=1600: Time=45.050560


Run=./tema3_opt_m: N=100: Time=0.003906
Run=./tema3_opt_m: N=200: Time=0.030376
Run=./tema3_opt_m: N=400: Time=0.234758
Run=./tema3_opt_m: N=500: Time=0.458715
Run=./tema3_opt_m: N=600: Time=0.781578
Run=./tema3_opt_m: N=800: Time=1.887403
Run=./tema3_opt_m: N=1000: Time=3.747496
Run=./tema3_opt_m: N=1200: Time=6.301920
Run=./tema3_opt_m: N=1400: Time=10.181114
Run=./tema3_opt_m: N=1600: Time=15.395063
Run=./tema3_opt_m: Bonus=2p

Nume:
Grupă:

# Tema <NR> TODO
#### Este recomandat să folosiți diacritice. Se poate opta și pentru realizarea în limba engleză. 

Organizare
-
1. Explicație pentru soluția aleasă:

***Obligatoriu:*** 


* De făcut referință la abordarea generală menționată în paragraful de mai sus. Aici se pot băga bucăți de cod/funcții - etc.
* Consideri că tema este utilă?
* Consideri implementarea naivă, eficientă, se putea mai bine?

***Opțional:***


* De menționat cazuri speciale, nespecificate în enunț și cum au fost tratate.


Implementare
-

* De specificat dacă întregul enunț al temei e implementat
* Dacă există funcționalități extra, pe lângă cele din enunț - descriere succintă + motivarea lor
* De specificat funcționalitățile lipsă din enunț (dacă există) și menționat dacă testele reflectă sau nu acest lucru
* Dificultăți întâmpinate
* Lucruri interesante descoperite pe parcurs


Resurse utilizate
-

* Resurse utilizate - toate resursele publice de pe internet/cărți/code snippets, chiar dacă sunt laboratoare de ASC

Git
-
1. Link către repo-ul de git

Ce să **NU**
-
* Detalii de implementare despre fiecare funcție/fișier în parte
* Fraze lungi care să ocolească subiectul în cauză
* Răspunsuri și idei neargumentate
* Comentarii (din cod) și *TODO*-uri

Acest model de README a fost adaptat după [exemplul de README de la SO](https://github.com/systems-cs-pub-ro/so/blob/master/assignments/README.example.md).