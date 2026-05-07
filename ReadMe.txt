
make            builds 
make run        buildZ and runs
make clean      removes object files 



1. Binomial vs binary heap — Binary heaps are slow to merge (O(n)); binomial heaps merge in O(log n), so the priority queue is faster on big graphs.
2. Path compression + union by size — Plain Quick-Union can become a long chain (find ~ O(n)). Union by size keeps trees short, path compression flattens them, so find/union becomes ~O(1).
3. Timing observations — Same MST cost in both. Tiny graphs: similar speeds. Big graphs: V2 ~14× faster (100k nodes → 0.2 s vs 2.8 s). V1 is O(m log m + m·n) worst case; V2 is ~O(m log m).