ALGORITHM
1. Start the program.
2. Read grid size N and validate it (3 to 6).
3. Read all risk scores into a 2D array and validate them (0 to 100).
4. Read and validate the warning threshold T (1 to 100).
5. Display the grid.
6. Calculate all row totals and find the highest row total.
7. Calculate all column totals and find the highest column total.
8. Find the highest risk score, its positions and count cells meeting the threshold.
9. Calculate both diagonal totals and check whether they are balanced.
10. Calculate the boundary total without counting corners twice.
11. Find all local hotspots by comparing interior cells with their four neighbours.
12. Display CRITICAL, WARNING or NORMAL based on the conditions and stop.
