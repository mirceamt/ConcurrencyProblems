#pragma once

class Elf
{
public:
    Elf();
private:
    static int s_counterId;
    int m_id;
};