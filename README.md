Nume: Lăzăroiu Lucas
Grupă: 341C5

# Tema 3

Organizare
-
Tema presupune calculul unei operatii cu matrice in 3 moduri diferite. Primul mod este cel clasic, fara nicio imbunatatire. Celelalte doua moduri presupun doua tipuri de optimizari: unul folosind o biblioteca externa specializata pentru operatii de algebra liniara, iar celalalt profitand de anumite proprietati ale parcurgerii matricelor/a modului cum sunt ținute datele in memorie.

* Este important de mentionat ca matricele sunt liniarizate. De exemplu, la o matrice patratica A de dimensiune N, pentru a accesa A[i][j] facem astfel: A[i * N + j] (sau *(A + i * N + j)).
* Pentru operatiile cu matrice transpuse nu este nevoie de lucrul "direct" cu transpusa (ce ar necesita alocari, copieri si eliberari aditionale de memorie). De exemplu, daca avem nevoie de At[i][j], putem pur si simplu sa accesam A[j][i] (sau *(A + j * N + i) in cazul nostru cu matrice liniarizate).
* Pentru varianta "clasica", in solver_neopt.c se fac parcurgeri normale cu bucle i-j-k la inmultirea matricelor. Codul este usor de inteles, nimic special de mentionat aici.
* Pentru varianta ce foloseste o biblioteca externa (cblas.h), in solver_blas.c buclele au fost inlocuite cu apeluri de functii specifice nevoilor noastre:
    * cblas_dtrmm (double triangular matrix multiplication), pentru inmultiri ce profitau ca matricea A este superior triunghiulara.
    * cblas_daxpy (double alphaX plus Y), pentru adunare de matrice (in mod specific vectori, deoarece matricele noastre sunt liniarizate).
    * cblas_dgemm (double general matrix multiplication), pentru inmultiri obisnuite de matrice.
    * mentionez primul argument pentru dgemm si dtrmm, care indica modul in care matricele sunt liniarizate in memorie (pe linii sau pe coloane). In cazul nostru folosim 'CblasRowMajor', pentru ca avem liniarizare pe "randuri".
* Pentru varianta optimizata, in solver_opt.c se folosesc urmatoarele tehnici:
    * se schimba ordinea parcurgerii buclelor astfel incat calculul din bucla cea mai interioara sa foloseasca o constanta si doua variabile secventiale (i.e. la urmatoarea iteratie a buclei acestea trebuie doar incrementate pentru ca valorile de care avem nevoie sunt adiacente intr-o zona de memorie contigua).
    * se foloseste cuvantul cheie "register" pentru variabilele ce sunt accesate foarte mult, sugerand compilatorului sa le țină in registrii procesorului pentru un acces mai rapid.

* Consider tema destul de utila deoarece solidifica cunostintele fundamentale legate de stocarea datelor in memorie si diferenta de performanta intre programele care tin sau nu cont de acest lucru. A fost interesant si lucrul cu biblioteca specializata si documentarea/setup-ul acesteia pentru rezolvarea problemei. Desi complexitatea este O(N^3) pentru toate implementarile, factorul constant ascuns de notatia Big O nu trebuie ignorat.
* Cred ca implementarea mea este foarte buna pentru toate cele trei solvere. Am respectat constrangerile si am tinut cont de cerintele date. Codul este lizibil, contine comentarii pertinente si are un flow usor de inteles. As fi putut imbunatati implementarea din solver_opt.c daca foloseam Blocked-Matrix-Multiplication pentru utilizarea mai eficienta a cache-ului.


Implementare
-

* Tema a fost implementata in totalitate: cele 3 solvere obtin rezultate corecte si timpul de executie pentru N=1200 la solver_opt.c este sub 10s pe partitia haswell.
* Nu exista memory leaks si au fost rulate executabilele folosind valgrind cu tool-urile memcheck si cachegrind. Output-urile se afla in folderele memory, respectiv cache.
* Fisierele din folderul cache contin diferite valori ce se refera la numarul de referinte/miss-uri la instructiuni si date (read sau write). Un miss inseamna ca resursa respectiva nu a fost gasita in cache si este nevoie sa fie accesata memoria principala. 
* Se poate vedea si numarul de instructiuni de tip branch executate (conditional: e.g. if, sau indirect: e.g. apeluri de functii), dar si numarul de predictii incorecte (facute de CPU) ale branch-ului.
* Se observa ca singura diferenta semnificativa intre 'blas' si celelalte doua variante se afla la numarul brut de referinte si branch-uri. Miss si Mispred rate-urile sunt peste tot sub 1%. Singura mentiune este ca 'blas' pare sa faca mai multe write-uri. In orice caz, acesta are performanta cea mai buna.
* Comparand 'neopt' cu 'opt_m', putem spune ca sunt aproape identice (neopt are un mispred rate mai mare cu 0.1%), mai putin la (din nou) numarul brut de I refs si D refs:
    * Pentru I_refs, in 'opt_m' se retin constante sau valori partiale din bucle si astfel nu se fac atat de multe inmultiri/adunari pentru a afla zona de memorie de unde dorim sa accesam/modificam date.
    * Pentru D_refs, in 'opt_m' se folosesc variabile 'register', fapt ceea ce face sa nu avem nevoie nici macar de cache pentru accesul la date atunci procesorul/compilatorul ne permite asta.

* A fost facuta si o analiza comparativa a timpilor de rulare pentru diverse valori ale lui N (pe coada haswell de pe gridul institutional):

    * Job-ul 459021:

        * Run=./tema3_blas: N=100: Time=0.001065
        * Run=./tema3_blas: N=200: Time=0.004689
        * Run=./tema3_blas: N=400: Time=0.026733
        * Run=./tema3_blas: N=500: Time=0.051534
        * Run=./tema3_blas: N=600: Time=0.081149
        * Run=./tema3_blas: N=800: Time=0.179827
        * Run=./tema3_blas: N=1000: Time=0.357315
        * Run=./tema3_blas: N=1200: Time=0.605521
        * Run=./tema3_blas: N=1400: Time=0.939647
        * Run=./tema3_blas: N=1600: Time=1.403887

    * Job-ul 459020:

        * Run=./tema3_neopt: N=100: Time=0.008818
        * Run=./tema3_neopt: N=200: Time=0.072697
        * Run=./tema3_neopt: N=400: Time=0.599500
        * Run=./tema3_neopt: N=500: Time=1.221508
        * Run=./tema3_neopt: N=600: Time=2.037308
        * Run=./tema3_neopt: N=800: Time=4.952152
        * Run=./tema3_neopt: N=1000: Time=9.235767
        * Run=./tema3_neopt: N=1200: Time=18.232872
        * Run=./tema3_neopt: N=1400: Time=26.907232
        * Run=./tema3_neopt: N=1600: Time=45.050560

    * Job-ul 459022:

        * Run=./tema3_opt_m: N=100: Time=0.003906
        * Run=./tema3_opt_m: N=200: Time=0.030376
        * Run=./tema3_opt_m: N=400: Time=0.234758
        * Run=./tema3_opt_m: N=500: Time=0.458715
        * Run=./tema3_opt_m: N=600: Time=0.781578
        * Run=./tema3_opt_m: N=800: Time=1.887403
        * Run=./tema3_opt_m: N=1000: Time=3.747496
        * Run=./tema3_opt_m: N=1200: Time=6.301920
        * Run=./tema3_opt_m: N=1400: Time=10.181114
        * Run=./tema3_opt_m: N=1600: Time=15.395063
        * Run=./tema3_opt_m: Bonus=2p

* Graficele se afla in fisierul Analiza_comparativa.png, de la care putem trage urmatoarele concluzii:
    * Varianta 'blas' este pe departe cea mai rapida, cu un speed-up de ~30x fata de 'neopt'.
    * Varianta 'opt_m' nu este nici pe departe comparabila cu 'blas' pentru valori > 800 ale lui N, dar are un speed-up semnificativ fata de 'neopt', aproximativ 3x.
    * toate graficele au o crestere cubica a timpului de rulare, dar se poate observa foarte clar diferenta dintre factorii constanti pentru cele trei abordari (intuitiv, ar fi 30, 10, 1 pentru 'neopt', 'opt_m', respectiv 'blas').

* Dificultăți întâmpinate
    * La un moment dat primeam BUS Error cand dadeam submit la job-uri pe haswell (doar un job din trei era afectat).
    * A existat o perioada cand partitia haswell avea o performanta cu 50% mai mica (e.g. timp de 18s vs 12s).
    * Cele doua probleme mentionate mai sus se intamplau in acelasi timp.
    * Site-ul netlib.org/blas/ (al carui link este in enuntul temei), nu este de prea mare ajutor ("Not Found ; The requested URL was not found on this server." cand incercam sa ma documentez despre functiile oferite de BLAS). 

Resurse utilizate
-

* Laboratorul 9 pentru tehnici de optimizare a inmultirii matricelor.
* https://web.archive.org/web/20221204071232/https://www.netlib.org/blas/ : site functional pentru documentatie BLAS.
* https://matrixcalc.org/ro/ : pentru testare corectitudine implementari.
* https://github.com/vtjnash/atlas-3.10.0/tree/master/interfaces/blas/C/src : pentru documentatie implementare specifica in C a bibliotecii.
* https://www.baeldung.com/linux/solve-shared-object-error : testare pe local BLAS
