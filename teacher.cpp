#include "teacher.h"
#include <vector>

  void teacher::minutePass()
  {
    if(timeLeftWithStudent > 0) // if the student isn't done with their question
    {
      timeLeftWithStudent--;
      helpingStudent = true;
    }
    else // if the student's question is done or the teacher is not helping a student
    {
      helpingStudent = false;
    }
  }

  void swapVals(std::string& a, std::string& b)
  {
    std::string temp = b;
    b = a;
    a = temp;
  }

  void insertionSortNamesAscending(std::vector<std::string>& arr)
  {
    for(int i = 1; i < arr.size() - 1; i++)
    {
      int j = i;
      while(j > 0 && std::stoi(arr[j-1].substr(7,2)) > std::stoi(arr[j].substr(7,2)))
      {
        swapVals(arr[j], arr[j-1]);
        j--;
      }
    }
  }

  void insertionSortNamesDescending(std::vector<std::string>& arr)
  {
    for(int i = 1; i < arr.size()-1; i++)
    {
      int j = i;
      while(j > 0 && std::stoi(arr[j-1].substr(7,2)) < std::stoi(arr[j].substr(7,2)))
      {
        swapVals(arr[j], arr[j-1]);
        j--;
      }
    }
  }

  void insertionSortTopicsAscending(std::vector<std::string>& arr)
  {
    for(int i = 1; i < arr.size() - 1; i++)
    {
      int j = i;
      while(j > 0 && arr[j-1].substr(arr[j-1].find_first_not_of('\t', 9),4) > arr[j].substr(arr[j].find_first_not_of('\t', 9),4))
      {
        swapVals(arr[j], arr[j-1]);
        j--;
      }
    }
  }

  void insertionSortTopicsDescending(std::vector<std::string>& arr)
  {
    for(int i = 1; i < arr.size()-1; i++)
    {
      int j = i;
      while(j > 0 && arr[j-1].substr(arr[j-1].find_first_not_of('\t', 9),4) < arr[j].substr(arr[j].find_first_not_of('\t', 9),4))
      {
        swapVals(arr[j], arr[j-1]);
        j--;
      }
    }
  }

  void teacher::storeMapAsFile(std::ofstream& out, const std::multimap<std::string, std::string>& StudentTopics)
  {
    out.open("StudentReports.txt");
    for(auto it : StudentTopics)
    {
      out << it.first << "\t" << it.second << std::endl;
    }
    out.close();
  }

  void teacher::sortFile(std::string fileName, std::string column, std::string sortingDirection)
  {
    if(column == "studentName")
    {
      std::ifstream in;
      in.open(fileName);
      std::vector<std::string> arr;
      std::string temp;
      while(!in.eof())
      {
        std::getline(in, temp);
        arr.push_back(temp);
      }
      in.close();
      if(sortingDirection != "descending") insertionSortNamesAscending(arr);
      else insertionSortNamesDescending(arr);
      std::ofstream out;
      out.open(fileName);
      for(int i = 0; i < arr.size(); i++)
      {
        out << arr[i] << std::endl;
      }
      out.close();
    }
    else if(column == "questionTopic")
    {
      std::ifstream in;
      in.open(fileName);
      std::vector<std::string> arr;
      std::string temp;
      while(!in.eof())
      {
        std::getline(in, temp);
        arr.push_back(temp);
      }
      in.close();
      if(sortingDirection != "descending")
      {
        insertionSortNamesAscending(arr);
        insertionSortTopicsAscending(arr);
      }
      else
      {
        insertionSortNamesDescending(arr);
        insertionSortTopicsDescending(arr);
      }
      std::ofstream out;
      out.open(fileName);
      for(int i = 0; i < arr.size(); i++)
      {
        out << arr[i] << std::endl;
      }
      out.close();
  }
}

// **SORTING FUNCTIONS**
void findTopicsOfStudent(std::string fileName, std::string studentName, std::vector<std::string>& topics)
{
  std::ifstream in;
  in.open(fileName);
  std::string temp;
  while(!in.eof())
  {
    getline(in, temp);
    if(temp.substr(0, studentName.length()) == studentName)
    {
      topics.push_back(temp.substr(studentName.length() + 1, temp.length() - studentName.length() + 1));
    }
  }
}

void findStudentsOfTopic(std::string fileName, std::string topic, std::vector<std::string>& students)
{
  std::ifstream in;
  in.open(fileName);
  std::string temp;
  while(!in.eof())
  {
    getline(in, temp);
    if(temp.length() <= 1) return;
    if(temp.substr(temp.find_first_not_of('\t', 9), 4) == topic.substr(0,4))
    {
      students.push_back(temp.substr(0, temp.find_first_not_of('\t', 9) - 1));
    }
  }
}
