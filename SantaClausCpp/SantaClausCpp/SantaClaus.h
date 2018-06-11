#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

class Reindeer;
class Elf;

class SantaClaus 
{
public:
    static SantaClaus* GetInstance();
    void Init(int iterations);
    void Run();
    void AddReindeer(Reindeer* r);
    int GetReindeersQueueSize();
    void AddElf(Elf* e);
    int GetElfQueueSize();
    std::mutex& GetMutex();
    std::condition_variable& GetSantaWakeUpCV();
    std::condition_variable& GetWaitingReindeersCV();
    std::condition_variable& GetWaitingElvesCV();
    std::condition_variable& GetElvesAtSantaCV();

    int& GetWaitingElvesNumber();
    bool& GetElvesRequestedHelp();
    int& GetAvailableElvesPositions();
    int& GetServedElvesNumber();

    int GetRemainingIterations();

private:
    std::unique_lock<std::mutex> GoToSleep(std::unique_lock<std::mutex> lock);

    int GetRandomHarnessTime();
    int GetRandomUnharnessTime();
    int GetRandomConsultingTime();

    int m_waitingElvesNumber;  // ne spune cati elfi asteapta sa intre la santa
    bool m_elvesRequestedHelp; // true daca s-a dus macar cineva catre santa sa ceara ajutor
    int m_availableElvesPositions; // ne spune cati elfi mai pot merge la santa sa ceara ajutor in grupul curent
    int m_servedElvesNumber;


    std::mutex m_mutex;
    std::condition_variable m_santaWakeUp;
    std::condition_variable m_waitingReindeers;
    std::condition_variable m_waitingElves;
    std::condition_variable m_elvesAtSanta;
    std::queue<Elf*> m_elves;
    std::queue<Reindeer*> m_reindeers;

    int m_iterations;

    SantaClaus();
    static SantaClaus *m_instance;
};