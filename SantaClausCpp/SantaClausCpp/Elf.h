#pragma once

class Elf
{
public:
    Elf();
    void Run();
    int GetId();    
private:
    int GetRandomMakingToysTime();
    static int s_counterId;
    int m_id;
};