#include<iostream>
#include "arithmetic_worksheet.h"
#include "jason_worksheet.h"
using namespace std;


int main(int argc, char *argv[])
{
	unsigned noq = 20;
	if (argc > 1) {
		noq = atoi(argv[1]);
	}

	//basic_work_sheet wks(noq);
	cout << "Populating a work sheet with " << noq << " questions.." << endl;
	string filename = "worksheet-1.txt";
	if (argc > 2) {
		filename = argv[2];
	}
	cout << "The name of o/p file is " << filename << endl;
	cout << "Generating work sheet.." << endl;
	
	//auto wks = new arithmetic_worksheet(noq);
	auto wks = new jason_worksheet(noq);
	
	wks->populate_ques("percent_question.json");
	wks->generate_question(filename);
	cout << "Worksheet generated!! Here is the content of work sheet.." << endl;
	//wks->generate_answers(filename.append(".key.txt"));
	wks->print();

}
