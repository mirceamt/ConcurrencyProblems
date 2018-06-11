#include <iostream>
#include <thread>
#include "SantaClaus.h"
#include "Reindeer.h"
#include "Elf.h"

using namespace std;

int main()
{
    thread santaThread;
    thread reindeerThreads[9];
    thread elfTreads[10];

    SantaClaus *santa = SantaClaus::GetInstance();
    santa->Init(20);
    Reindeer *reindeers = new Reindeer[9];
    Elf *elves = new Elf[10];

    santaThread = thread(&SantaClaus::Run, santa);
    for (int i = 0; i < 9; ++i)
    {
        reindeerThreads[i] = thread(&Reindeer::Run, reindeers[i]);
    }
    for (int i = 0; i < 10; ++i)
    {
        elfTreads[i] = thread(&Elf::Run, elves[i]);
    }

    santaThread.join();
    for (int i = 0; i < 9; ++i)
    {
        reindeerThreads[i].join();
    }
    for (int i = 0; i < 10; ++i)
    {
        elfTreads[i].join();
    }
    delete santa;
    delete[] elves;
    delete[] reindeers;

    cout << "\n\ndone";
    return 0;
}