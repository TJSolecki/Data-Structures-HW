#include "student.h"

bool operator >(const student& studentA, const student& studentB)
{
  return studentA.getPriority() > studentB.getPriority();
}

bool operator <(const student& studentA, const student& studentB)
{
  return studentA.getPriority() < studentB.getPriority();
}
bool operator >=(const student& studentA, const student& studentB)
{
  return studentA.getPriority() >= studentB.getPriority();
}
bool operator <=(const student& studentA, const student& studentB)
{
  return studentA.getPriority() <= studentB.getPriority();
}
bool operator ==(const student& studentA, const student& studentB)
{
  return studentA.getPriority() == studentB.getPriority();
}
