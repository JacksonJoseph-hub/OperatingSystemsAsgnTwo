# OperatingSystemsAsgnTwo

Second Assignment for Operating Systems (Spring 2022) - Banker's Algorithm is used to determine whether a processes request for an available resource leaves the system in a safe state.  The System is safe if the processes can be arranged into a sequence that allows them to complete with the available resources and the resources held by the processes.
This file (BankersAlgorithm.cpp) determines whether the provided system, given the allocation, max and available information contained in "test.txt" has a safe sequence.

In this case it does and that sequence is: p1, p3, p4, p0, p2
