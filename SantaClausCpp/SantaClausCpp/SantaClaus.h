#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

class Reindeer;
class Elf;

class SantaClaus 
{
public:
    static SantaClaus* GetInstance();
    void Run();
private:
    std::queue<Reindeer*> m_reindeers;
    std::queue<Elf*> m_elves;
    std::mutex m_santaMtx;
    std::condition_variable m_santaCV;
    SantaClaus();
    static SantaClaus *m_instance;
};