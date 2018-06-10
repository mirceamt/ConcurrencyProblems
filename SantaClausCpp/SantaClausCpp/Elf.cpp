#include "Elf.h"

int Elf::s_counterId = 0;

Elf::Elf()
{
    s_counterId++;
    m_id = s_counterId;
}
