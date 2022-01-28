Questions:
1.) The first video of selection sort (the gypsy folk dance one) contains the error. The mistake they make is that as they are going through the array making comparisons with the current value, when they find a smaller value they move the current value they are comparing to the spot where the new smallest value is. This is incorrect because in selection sort swapping only occurs once you have checked every value in the array for the new smallest value. Only then does the smallest value move to the end of the sorted portion in the beginning of the array.

2.) see attached pictures

3.) see insertionSort.cpp

4.) see quick.cxx

5.) see officeHoursMain.cpp, teacher.h, teacher.cpp, student.h, and student.cpp

How to run:
g++ insertionSort.cpp
./a.exe

g++ quick.cxx
./a.exe

g++ officeHoursMain.cpp teacher.cpp student.cpp
./a.exe

Note about office hours simulation:
- After each time the simulateOH function is called, the function stores a record of all of the data contained in the map and then sorts it according to the parameters passed in. The first asks for the filename to save the map's data to.The second parameter asks for the user to enter either "questionTopic" to sort the file with regards to the topics the students asked about in office hours, or "studentName" to sort the file by the students' names. The third parameter asks for the desired sorting order. The user can either enter "ascending" or "descending" depending on the sorting order they prefer.

There is also a function in the main file called loadMapFromFile that can be used to load the map from the file saved with the map's data.