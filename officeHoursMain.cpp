#include <iostream>
#include "student.h"
#include "teacher.h"
#include <ctime>
#include <cstdlib>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

void simulateOH(double& totalStudentQTime, double& totalTimeSpentWaiting, int& totalStudentsHelped, double& totalTimeAfterOH, multimap<string, string>& StudentTopics); // simulates 1 office hour session
int newStudentNumber(vector<int> used)
{
  int newNumber;
  do
  {
  newNumber = rand() % 40 + 1;
}while(find(used.begin(), used.end(), newNumber) != used.end());
return newNumber;
}
void generateReport(int studentNumber, multimap<string, string> StudentTopics);
void loadMapFromFile(ifstream& in, multimap<string, string>& StudentTopics);

int main()
{
  srand(time(0)); // makes it so that the random function returns different values each time the program is run
  int totalStudentsHelped = 0;
  double totalTimeSpentWaiting = 0, totalStudentQTime = 0, totalTimeAfterOH = 0;
  multimap<string, string> StudentTopics; // keeps track of the topics each student has asked about
  for(int i = 0; i < 100; i++) // simulates 100 office hours
  {
    simulateOH(totalStudentQTime, totalTimeSpentWaiting, totalStudentsHelped, totalTimeAfterOH, StudentTopics);
  }
  for(int i = 1; i < 41; i++) // creates all of the 40 students reports
  {
    generateReport(i, StudentTopics);
  }
  // **SEARCHING FUNCTIONS**
  vector<string> topics;
  findTopicsOfStudent("StudentReports.txt", "Student38", topics);
  cout << "Student38 asked about:\n";
  for(string i : topics)
  {
    cout << i << endl;
  }
  vector<string> students;
  findStudentsOfTopic("StudentReports.txt", "MAPS", students);
  cout << "The following students asked about MAPS:\n";
  for(string i : students)
  {
    cout << i << endl;
  }
  cout << "RESULTS\n";
  cout << "The average time a student spent waiting during the office hour visit was " << totalTimeSpentWaiting / totalStudentsHelped << " min" << endl;
  cout << "The average time a student spent with the professor during an office hour visit was " << totalStudentQTime / totalStudentsHelped << " min" << endl;
  cout << "The amount of time the Professor spent at the office hour beyond the 1 hour he intended to was " << totalTimeAfterOH / 100.0 << " min";
  return 0;
}

void simulateOH(double& totalStudentQTime, double& totalTimeSpentWaiting, int& totalStudentsHelped, double& totalTimeAfterOH, multimap<string, string>& StudentTopics)
{
  ofstream out;
  int totalTimeInOH = 0; // used to keep track of the minutes passed in the office hour
  priority_queue<student> students;
  teacher professor;
  vector<int> used;
  int newNumber;
  string studentName;
  for(; totalTimeInOH < 61; totalTimeInOH++) // each iteration represents one minute passing
  {
    if((rand() % 8 + 1) == 8) students.emplace(student(totalTimeInOH)); // 1 in 8 chance that a student will arrive each minute
    if(totalTimeInOH > 0) professor.minutePass();
    if(!professor.isHelpingStudent() && !students.empty()) // if the teacher is free and there are students waiting, then help a new student
    {
      newNumber = newStudentNumber(used);
      used.push_back(newNumber);
      studentName = "Student" + to_string(newNumber);
      StudentTopics.insert(pair<string, string>(studentName, students.top().getTopic()));
      totalTimeSpentWaiting += totalTimeInOH - students.top().getArriveTime();
      totalStudentQTime += students.top().getQTime();
      totalStudentsHelped++;
      professor.helpNewStudent(students.top().getArriveTime());
      students.pop();
    }
    if(totalTimeInOH == 60 && professor.isHelpingStudent()) // if the last minute has passed and the professor is in the middle of helping someone
    {
      totalTimeInOH += professor.getTimeLeftWithStudent(); // adds the amount of time left with the student to the amount of time passed
      professor.leaveStudent();
    }
  }
  while(!students.empty()) // if there are still students waiting, then simulate the time required to answer all their questions
  {
    newNumber = newStudentNumber(used);
    used.push_back(newNumber);
    studentName = "Student" + to_string(newNumber);
    StudentTopics.insert(pair<string, string>(studentName, students.top().getTopic()));
    totalStudentsHelped++;
    totalTimeSpentWaiting += totalTimeInOH - students.top().getArriveTime();
    totalStudentQTime += students.top().getQTime();
    totalTimeInOH += students.top().getQTime();
    students.pop();
  }
  totalTimeAfterOH += totalTimeInOH - 60;
  professor.storeMapAsFile(out, StudentTopics);
  professor.sortFile("StudentReports.txt", "questionTopic", "ascending");
}

void generateReport(int studentNumber, multimap<string, string> StudentTopics)
{
  string studentName = "Student" + to_string(studentNumber);
  string fileName1 = studentName + " report.txt";
  ofstream output(fileName1);
  output << "Report for Student" << studentNumber << endl;
  if(StudentTopics.find(studentName) == StudentTopics.end())
  {
    output << "You attended 0 office hours.";
    output.close();
  }
  else
  {
    int numAttended = 0;
    output << "You asked about the following topics in office hours each time you came:\n";
    auto currIt = StudentTopics.find(studentName);
    while(currIt != StudentTopics.end() && currIt->first == studentName)
    {
      output << '\t' << ++numAttended << ".) " << currIt->second << endl;
      currIt++;
    }
    output << "You came to office hours " << numAttended << " time(s)" << endl;
    output.close();
  }
}

void loadMapFromFile(ifstream& in, multimap<string, string>& StudentTopics)
{
  string temp, temp1, dummy;
  while(!in.eof())
  {
    in >> temp;
    getline(in, temp1);
    StudentTopics.insert(make_pair(temp, temp1));
  }
}
