#ifndef TEACHER_H
#define TEACHER_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

class teacher
{
public:
  teacher() : helpingStudent(false), timeLeftWithStudent(0) {}
  void minutePass();
  void leaveStudent() { timeLeftWithStudent = 0; helpingStudent = false;}
  void helpNewStudent(unsigned int qTime) { timeLeftWithStudent = qTime; helpingStudent = true;}
  void storeMapAsFile(std::ofstream& out, const std::multimap<std::string, std::string>& StudentTopics);
  void sortFile(std::string fileName, std::string column, std::string sortingDirection);
  bool isHelpingStudent() const { return helpingStudent; }
  unsigned int getTimeLeftWithStudent() const { return timeLeftWithStudent; }
private:
  bool helpingStudent;
  unsigned int timeLeftWithStudent; // amount of time remaining in order to answer the studnent's question
};

// this function takes in a filename which it then searchs for the topics the student who was specified in studentName asked, and then stores them in the topics vector
void findTopicsOfStudent(std::string fileName, std::string studentName, std::vector<std::string>& topics);
void findStudentsOfTopic(std::string fileName, std::string topic, std::vector<std::string>& students);

#endif
