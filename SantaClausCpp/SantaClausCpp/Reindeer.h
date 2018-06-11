#pragma once

class Reindeer
{
public:
    Reindeer();
    void Run();
    int GetId();
private:
    int GetRandomHolidayTime();
    static int s_counterId;
    int m_id;
};