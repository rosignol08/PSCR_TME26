## Question 0

```text
Image resizer starting with input folder 'input_images', output folder 'output_reference', mode 'resize', nthreads 4, nbread 1, nbresize 1, nbwrite 1, queue_size 10
Thread 129983135668544 (main): 7805 ms CPU
Total runtime (wall clock): 8380 ms
Memory usage: Resident: 59.8 MB, Peak: 142 MB
Peak RSS (bytes): 149336064
Total CPU time across all threads: 7805 ms
WARNING: CPU random generator seem to be failing, disabling hardware random number generation
WARNING: RDRND generated: 0xffffffff 0xffffffff 0xffffffff 0xffffffff
Image resizer starting with input folder 'input_images', output folder 'output_images', mode 'pipe', nthreads 4, nbread 1, nbresize 1, nbwrite 1, queue_size 10
Thread 138465924507328 (treatImage): 7730 ms CPU
Thread 138465970030912 (main): 8 ms CPU
Total runtime (wall clock): 8162 ms
Memory usage: Resident: 60 MB, Peak: 142 MB
Peak RSS (bytes): 149377024
Total CPU time across all threads: 7738 ms
OK : 41 fichiers dans chaque dossier.
```

## Question 1

```text
Image resizer starting with input folder 'input_images', output folder 'output_images', mode 'pipe', nthreads 4, nbread 1, nbresize 1, nbwrite 1, queue_size 1
Thread 127959535867584 (treatImage): 7864 ms CPU
Thread 127959572027712 (main): 12 ms CPU
Total runtime (wall clock): 8420 ms
Memory usage: Resident: 59.9 MB, Peak: 142 MB
Peak RSS (bytes): 149192704
Total CPU time across all threads: 7876 ms
```
## Question 2

si on inverse l'etape 2 et 3 :
```text
Image resizer starting with input folder 'input_images', output folder 'output_images', mode 'pipe', nthreads 4, nbread 1, nbresize 1, nbwrite 1, queue_size 1 
```
et rien ne se passe 

si on inverse l'etape 3 et 4 :
```text
Image resizer starting with input folder 'input_images', output folder 'output_images', mode 'pipe', nthreads 4, nbread 1, nbresize 1, nbwrite 1, queue_size 1
Thread 139131763074752 (treatImage): 0 ms CPU
```
si on inverse l'etape 4 et 5 :
```text
Image resizer starting with input folder 'input_images', output folder 'output_images', mode 'pipe', nthreads 4, nbread 1, nbresize 1, nbwrite 1, queue_size 1
```
et rien ne se passe nonplus

## Question 3

```text
avec 4 threads c'est plus rapide Thread 130618960389824 (treatImage): 1414 ms CPU
Thread 130618968782528 (treatImage): 1392 ms CPU
Thread 130618977175232 (treatImage): 1482 ms CPU
Thread 130618985567936 (treatImage): 1497 ms CPU
Thread 130619025725760 (main): 6 ms CPU
Total runtime (wall clock): 1798 ms
Memory usage: Resident: 168 MB, Peak: 437 MB
Peak RSS (bytes): 457793536
Total CPU time across all threads: 5791 ms
vs 
avec 1 thread : 
Thread 135505009223360 (treatImage): 5111 ms CPU
Thread 135505048119616 (main): 7 ms CPU
Total runtime (wall clock): 5445 ms
Memory usage: Resident: 59.9 MB, Peak: 144 MB
Peak RSS (bytes): 150990848
Total CPU time across all threads: 5118 ms
```

## Question 5

```text
en mode pipeline ça donne Image resizer starting with input folder 'input_images', output folder 'output_images', mode 'mt_pipeline', nthreads 1, nbread 1, nbresize 1, nbwrite 1, queue_size 4
Thread 127631761647296 (reader): 4477 ms CPU
Thread 127631753254592 (resizer): 138 ms CPU
Thread 127631744861888 (saver): 756 ms CPU
Thread 127631813077312 (main): 6 ms CPU
Total runtime (wall clock): 4516 ms
Memory usage: Resident: 91 MB, Peak: 183 MB
Peak RSS (bytes): 191410176
Total CPU time across all threads: 5377 ms
```

## Question 6

```text
Image resizer starting with input folder 'input_images', output folder 'output_images', mode 'mt_pipeline', nthreads 1, nbread 1, nbresize 1, nbwrite 1, queue_size 1
Thread 130586744727232 (reader): 6638 ms CPU
Thread 130586736334528 (resizer): 218 ms CPU
Thread 130586727941824 (saver): 985 ms CPU
Thread 130586784115008 (main): 9 ms CPU
Total runtime (wall clock): 6684 ms
Memory usage: Resident: 91.2 MB, Peak: 181 MB
Peak RSS (bytes): 190140416
Total CPU time across all threads: 7850 ms

et 

Image resizer starting with input folder 'input_images', output folder 'output_images', mode 'mt_pipeline', nthreads 1, nbread 4, nbresize 4, nbwrite 4, queue_size 4
Thread 133806776981184 (reader): 1587 ms CPU
Thread 133806768588480 (reader): 1477 ms CPU
Thread 133806760195776 (reader): 1991 ms CPU
Thread 133806751803072 (reader): 1945 ms CPU
Thread 133806735017664 (resizer): 42 ms CPU
Thread 133806718232256 (resizer): 55 ms CPU
Thread 133806743410368 (resizer): 36 ms CPU
Thread 133806726624960 (resizer): 53 ms CPU
Thread 133806693054144 (saver): 202 ms CPU
Thread 133806684661440 (saver): 223 ms CPU
Thread 133806709839552 (saver): 180 ms CPU
Thread 133806701446848 (saver): 320 ms CPU
Thread 133806833531200 (main): 9 ms CPU
Total runtime (wall clock): 2651 ms
Memory usage: Resident: 250 MB, Peak: 415 MB
Peak RSS (bytes): 435154944
Total CPU time across all threads: 8120 ms
```

## Question 7

```text
config           elapsed_ms       cpu_ms   peak_rss_bytes    files   exit check
reference              8575         7768        144928768       41      0 REFERENCE
Traces, arguments et tableau : results/20261125-142249-reference-P0XNUI


config           elapsed_ms       cpu_ms   peak_rss_bytes    files   exit check
1                      8204         7678        151883776       41      0 OK
2                      4421         7968        238596096       41      0 OK
4                      2557         8080        412524544       41      0 OK
8                      2593         8135        614871040       41      0 OK
Traces, arguments et tableau : results/20261125-142317-pipe_mt-YzO9t4


config           elapsed_ms       cpu_ms   peak_rss_bytes    files   exit check
1/1/1                  6833         7859        190676992       41      0 OK
2/1/1                  3996         8044        287240192       41      0 OK
1/2/1                  6782         7877        213692416       41      0 OK
1/1/2                  6753         7908        191328256       41      0 OK
Traces, arguments et tableau : results/20261125-142339-pipeline-DHFAyd
```
le mode 1/1/1 semble le meilleur car on est equilibré et le mode 1/1/2 semble aussi un bon candidat car il va unpeu plus lentement que 1/2/1 mais consomme moin de ressources 
sachant que ma machine a 4 coeur aller au delas de 4 ralentirais les calculs.
## Question 8

```text
...
```

## Question 9

```text
...
```
