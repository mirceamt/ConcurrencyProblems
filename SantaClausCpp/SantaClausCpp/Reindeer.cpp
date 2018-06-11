#include "Reindeer.h"
#include "SantaClaus.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#define CHECK_IF_ITS_TIME_TO_DIE if (santa->GetRemainingIterations() <= 0) return ;

using namespace std;
using namespace std::chrono;


int Reindeer::s_counterId = 0;

Reindeer::Reindeer()
{
    s_counterId++;
    m_id = s_counterId;
}

void Reindeer::Run()
{
    while (true)
    {
        SantaClaus::GetInstance()->GetOutputStream() << "Reindeer " << GetId() << ": Going to holiday." << endl;
        this_thread::sleep_for(chrono::milliseconds(GetRandomHolidayTime()));

        SantaClaus* santa = SantaClaus::GetInstance();
        unique_lock<mutex> lock(santa->GetMutex());

        SantaClaus::GetInstance()->GetOutputStream() << "Reindeer " << GetId() << ": Back from holiday." << endl;

        santa->AddReindeer(this);

        if (santa->GetReindeersQueueSize() == 9)
            santa->GetSantaWakeUpCV().notify_one();

        CHECK_IF_ITS_TIME_TO_DIE
        santa->GetWaitingReindeersCV().wait(lock);
        CHECK_IF_ITS_TIME_TO_DIE
    }
}

int Reindeer::GetId()
{
    return m_id;
}

int Reindeer::GetRandomHolidayTime()
{
    return 500 + rand() % 201;
}
