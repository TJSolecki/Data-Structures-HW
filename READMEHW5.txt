How to run :
First, cd to the directory in which the program files are stored and then type

	g++ officeHoursMain.cpp teacher.cpp student.cpp

into your console and press enter. Then you will run ./a.exe on windows or ./a.out on mac to run the program.

Information about the program :
Every minute there is a 1/8 chance that a student will come to office hours with a question. I am using this number as In my experience around 7 or 8 people usually come to office hours when the class is around 40 people and 60 * 1/8 = 7.5

Each student's question can range from 1 - 10 minutes

Each student's question can range in priority from 1 (being the lowest) to 3 (being the highest)

Each student's question is about 1 of 10 topics which are:
	1. B-Trees
	2. BSTs
	3. Red-Black Trees
	4. MAPs
	5. Heaps
	6. Queues
	7. Quick Sort
	8. Trees
	9. Insertion Sort
	10. Stacks

One iteration of the for loop in the simulateOH function represents the passing of one minute except the first iteration which no time has passed since the office hours started but a student can still arrive. This is done as students can show up the moment office hours have started even though no time has passed.

The program also creates individualized reports for all 40 students. These reports include the students name, the amount of times they attended office hours, and the topic they asked about each time they came. The files are titled "StudentX report.txt".
