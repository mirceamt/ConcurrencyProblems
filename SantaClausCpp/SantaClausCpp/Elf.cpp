#include "Elf.h"
#include "SantaClaus.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <queue>
#include <mutex>
#include <string>
#include <cstdio>
#include <condition_variable>
#define CHECK_IF_ITS_TIME_TO_DIE if (santa->GetRemainingIterations() <= 0) return;

using namespace std;
using namespace std::chrono;

int Elf::s_counterId = 0;

Elf::Elf()
{
    s_counterId++;
    m_id = s_counterId;
}

void Elf::Run()
{
    while (true)
    {
        SantaClaus* santa = SantaClaus::GetInstance();

        CHECK_IF_ITS_TIME_TO_DIE

        string s;
        s = "Elf " + to_string(m_id) + ": Making toys.";

        SantaClaus::GetInstance()->GetOutputStream() << s << endl;
        this_thread::sleep_for(chrono::milliseconds(GetRandomMakingToysTime()));

        unique_lock<mutex> lock(santa->GetMutex());


        santa->GetWaitingElvesNumber()++;

        s = "Elf " + to_string(m_id) + ": Can't make toys. Needs help.";
        SantaClaus::GetInstance()->GetOutputStream() << s << endl;

        if (santa->GetWaitingElvesNumber() < 3 || santa->GetElvesRequestedHelp() == true)
        { 
            while (santa->GetAvailableElvesPositions() == 0)
            {
                s = "Elf " + to_string(m_id) + ": waits to go to santa.";
                SantaClaus::GetInstance()->GetOutputStream() << s << endl;
                CHECK_IF_ITS_TIME_TO_DIE
                santa->GetWaitingElvesCV().wait(lock);
                this_thread::yield();
                CHECK_IF_ITS_TIME_TO_DIE
            }
        }
        else
        {
            santa->GetAvailableElvesPositions() += 3;
            santa->GetElvesRequestedHelp() = true;
            // aici intra al treilea elf si ii mai si pe cei doi sa mearga cu ei la santa.
            santa->GetWaitingElvesCV().notify_one();
            santa->GetWaitingElvesCV().notify_one();
        }

        // aici un elf ii cere ajutor lui santa. dar nu ajunge la santa decat cand 3 ii vor cere ajutor
        s = "Elf " + to_string(m_id) + ": I request help from santa.";
        SantaClaus::GetInstance()->GetOutputStream() << s << endl;
        santa->GetWaitingElvesNumber()--;
        santa->GetAvailableElvesPositions()--;

        santa->AddElf(this);

        if (santa->GetAvailableElvesPositions() == 0)
            santa->GetSantaWakeUpCV().notify_one();

        CHECK_IF_ITS_TIME_TO_DIE
        santa->GetElvesAtSantaCV().wait(lock);
        CHECK_IF_ITS_TIME_TO_DIE

        santa->GetServedElvesNumber()++;

        if (santa->GetServedElvesNumber() == 3)
        {
            santa->GetServedElvesNumber() = 0;
            santa->GetElvesRequestedHelp() = false;
            santa->GetWaitingElvesCV().notify_all();
        }
    }
}

int Elf::GetRandomMakingToysTime()
{
    return 100 + rand() % 101;
}

int Elf::GetId()
{
    return m_id;
}
