#ifndef STUDENT_H
#define STUDENT_H

#include <ctime>
#include <cstdlib>
#include <string>

class student
{
public:
  std::string topics[10] = {"B-Trees", "MAPS", "Heaps", "BSTs", "Trees", "Red-Black Trees", "Insertion Sort", "Quick Sort", "Stacks", "Queues"};
  student() : arriveTime(0), qTime(rand() % 10 + 1), priority(rand() % 3 + 1), topic(topics[rand() % 10]){} // qTime is a random number between 1 and 10 and priority is a random number between 1 and 3
  student(unsigned int arriveT) : arriveTime(arriveT), qTime(rand() % 10 + 1), priority(rand() % 3 + 1), topic(topics[rand() % 10]) {} // qTime is a random number between 1 and 10 and priority is a random number between 1 and 3
  void setQTime(unsigned int time) { qTime = time; }
  unsigned int getQTime() const { return qTime; }
  unsigned int getArriveTime() const { return arriveTime; }
  unsigned int getPriority() const { return priority; }
  std::string getTopic() const { return topic; }
private:
  unsigned int qTime; // the amount of time in minutes that their question will take
  unsigned int arriveTime; // the amount of time in minutes that have passed since the office hours started when the student arrives
  unsigned int priority; // determines the urgency of a question. 3 being the highest and 1 being the lowest.
  std::string topic;
};

bool operator >(const student& studentA, const student& studentB);
bool operator <(const student& studentA, const student& studentB);
bool operator >=(const student& studentA, const student& studentB);
bool operator <=(const student& studentA, const student& studentB);
bool operator ==(const student& studentA, const student& studentB);

#endif
