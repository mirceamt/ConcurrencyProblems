#include "Reindeer.h"

int Reindeer::s_counterId = 0;

Reindeer::Reindeer()
{
    s_counterId++;
    m_id = s_counterId;
}