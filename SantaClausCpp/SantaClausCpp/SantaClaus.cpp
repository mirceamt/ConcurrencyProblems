#include "SantaClaus.h"
#include "Reindeer.h"
#include <mutex>
#include <condition_variable>

using namespace std;

SantaClaus* SantaClaus::m_instance = nullptr;

SantaClaus::SantaClaus()
{
    //
}

SantaClaus* SantaClaus::GetInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new SantaClaus();
    }
    return m_instance;
}

void SantaClaus::Run()
{
    unique_lock<mutex> lock(m_santaMtx);
    m_santaCV.wait(lock);

}