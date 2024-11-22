# Bankers-Algorithm

Implementation of Banker's Algorithm for deadlock avoidance.

Given process tables in data.txt, conducts classic Banker's Algorithm in searching for a safe sequence of the system. System is safe if each process can successfully fulfill their needed resources through the program iterations. If there exists a process that cannot be satisfied, the system is deemed 'unsafe' and no sequence is possible.

Run using:
g++ bankers-algorithm.cpp -o bank-algo
./bank-algo data.txt
