#include "SantaClaus.h"
#include "Reindeer.h"
#include "Elf.h"
#include <mutex>
#include <condition_variable>
#include <memory>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

SantaClaus* SantaClaus::m_instance = nullptr;

SantaClaus::SantaClaus()
{
    m_waitingElvesNumber = 0;
    m_elvesRequestedHelp = false;
    m_availableElvesPositions = 0;
    m_servedElvesNumber = 0;
}

SantaClaus* SantaClaus::GetInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new SantaClaus();
    }
    return m_instance;
}

void SantaClaus::Init(int iterations)
{
    m_iterations = iterations;
}

void SantaClaus::Run()
{
    unique_lock<mutex> lock(m_mutex);

    while (true)
    {
        lock = this->GoToSleep(std::move(lock));

        if (m_reindeers.size() == 9)
        {
            cout << "Santa Claus: Welcome reindeers!" << endl;

            queue<Reindeer*> aux = m_reindeers;
            while (!m_reindeers.empty())
            {
                Reindeer* r = m_reindeers.front();
                m_reindeers.pop();

                cout << "Santa Claus: Harness reindeer " << r->GetId() << endl;
                this_thread::sleep_for(chrono::milliseconds(GetRandomHarnessTime()));
            }
            cout << "Santa Claus: Delivering gifts... " << endl;
            this_thread::sleep_for(chrono::milliseconds(50));

            while (!aux.empty())
            {
                Reindeer* r = aux.front();
                aux.pop();

                cout << "Santa Claus: Unharness reindeer " << r->GetId() << endl;
                this_thread::sleep_for(chrono::milliseconds(GetRandomUnharnessTime()));
            }

            m_waitingReindeers.notify_all();
            m_iterations--;
            if (m_iterations <= 0)
            {
                m_waitingReindeers.notify_all();
                m_waitingElves.notify_all();
                m_elvesAtSanta.notify_all();
                return;
            }
        }
        


        if (m_elves.size() == 3)
        {
            cout << "Santa Claus: Welcome elves!" << endl;

            while (!m_elves.empty())
            {
                Elf* e = m_elves.front();
                m_elves.pop();
                cout << "Santa Claus: Consulting elf " << e->GetId() << endl;
                this_thread::sleep_for(chrono::milliseconds(GetRandomConsultingTime()));
            }

            m_elvesAtSanta.notify_all();
            m_iterations--;
            if (m_iterations <= 0)
            {
                m_waitingReindeers.notify_all();
                m_waitingElves.notify_all();
                m_elvesAtSanta.notify_all();
                return;
            }
        }
    }
}

void SantaClaus::AddReindeer(Reindeer * r)
{
    m_reindeers.push(r);
}

int SantaClaus::GetReindeersQueueSize()
{
    return m_reindeers.size();
}

void SantaClaus::AddElf(Elf * e)
{
    m_elves.push(e);
}

int SantaClaus::GetElfQueueSize()
{
    return m_elves.size();
}

std::mutex & SantaClaus::GetMutex()
{
    return m_mutex;
}

std::condition_variable & SantaClaus::GetSantaWakeUpCV()
{
    return m_santaWakeUp;
}

std::condition_variable & SantaClaus::GetWaitingReindeersCV()
{
    return m_waitingReindeers;
}

std::condition_variable & SantaClaus::GetWaitingElvesCV()
{
    return m_waitingElves;
}

std::condition_variable & SantaClaus::GetElvesAtSantaCV()
{
    return m_elvesAtSanta;
}

int & SantaClaus::GetWaitingElvesNumber()
{
    return m_waitingElvesNumber;
}

bool & SantaClaus::GetElvesRequestedHelp()
{
    return m_elvesRequestedHelp;
}

int & SantaClaus::GetAvailableElvesPositions()
{
    return m_availableElvesPositions;
}

int & SantaClaus::GetServedElvesNumber()
{
    return m_servedElvesNumber;
}

int SantaClaus::GetRemainingIterations()
{
    return m_iterations;
}

unique_lock<mutex> SantaClaus::GoToSleep(unique_lock<mutex> lock)
{
    cout << "Santa Claus: Going to sleep." << endl;
    m_santaWakeUp.wait(lock);
    return move(lock);
}

int SantaClaus::GetRandomHarnessTime()
{
    return 10 + rand() % 11;
}

int SantaClaus::GetRandomUnharnessTime()
{
    return 10 + rand() % 11;
}

int SantaClaus::GetRandomConsultingTime()
{
    return 10 + rand() % 11;
}
