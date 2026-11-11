# Questions - TME 3 : Threads

Instructions : copiez vos réponses dans ce fichier (sous la question correspondante). A la fin de la séance, commitez vos réponses.

## Question 1.

```
cd build-release && ./TME3 ../WarAndPeace.txt freqstd && ./TME3 ../WarAndPeace.txt freqstdf && ./TME3 ../WarAndPeace.txt freq && check.sh *.freq
```

Traces pour les 3 modes, invocation de `check.sh` sans erreur :

Résultats obtenus :

```text
Preparing to parse ../WarAndPeace.txt (mode=freqstd N=4), containing 3235342 bytes
Total runtime (wall clock) : 282 ms

Preparing to parse ../WarAndPeace.txt (mode=freqstdf N=4), containing 3235342 bytes
Total runtime (wall clock) : 295 ms

Preparing to parse ../WarAndPeace.txt (mode=freq N=4), containing 3235342 bytes
Total runtime (wall clock) : 286 ms

../check.sh *.freq
All files are identical
```

Les trois modes produisent donc les mêmes résultats (`freqstd.freq`,
`freqstdf.freq` et `freq.freq`). La commande `check.sh` ne signale aucune
différence.

## Question 2.

start vaut XX

end vaut YY

Code des lambdas :
```
for(int i = 0; i < num_threads; ++i){
            travailleurs.emplace_back([&, i]() {
                pr::processRange(
                    filename, 
                    parts[i], 
                    parts[i + 1], 
                    [&](const std::string &word){
                        total_words++;
                        //um[word]++;
                    }
                );
            });
        }
```
je dois commenter ```um[word]``` car sinon ça cause une segmentation fault
et total_words subit une data race donc le resultat est faux
Accès identifiés :

## Question 3.

Continuez de compléter ce fichier avec vos traces et réponses.

```
mt_naive
Preparing to parse ../WarAndPeace.txt (mode=mt_naive N=4), containing 3235342 bytes
Total runtime (wall clock) : 99 ms




mt_atomic
Preparing to parse ../WarAndPeace.txt (mode=mt_atomic N=4), containing 3235342 bytes
Total runtime (wall clock) : 101 ms


mt_mutex
Preparing to parse ../WarAndPeace.txt (mode=mt_mutex N=4), containing 3235342 bytes
Total runtime (wall clock) : 246 ms

mt_hashes
Preparing to parse ../WarAndPeace.txt (mode=mt_hashes N=4), containing 3235342 bytes
Total runtime (wall clock) : 162 ms
plus rapide car pas de synchronisation
```

un mutex utilise un atomic donc ça sert à rien

