How to run :
First, cd to the directory in which the program files are stored and then type

	g++ officeHoursMain.cpp teacher.cpp

into your console and press enter. Then you will run ./a.exe on windows or ./a.out on mac to run the the program.

Information about the program :
Every minute there is a 1/8 chance that a student will come to office hours with a question. I am using this number as In my experience around 7 or 8 people usually come to office hours when the class is aroud 40 people and 60 * 1/8 = 7.5

Each student's question can range from 1 - 10 minutes

One iteration of the for loop in the simulateOH function represents the passing of one minute except the first iteration which no time has passed since the office hours started but a student can still arive. This is done as students can show up the moment office hours have started even though no time has passed.

