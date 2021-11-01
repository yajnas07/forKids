#include<iostream>
#include"basic_worksheet.h"
#include"expression_worksheet.h"
using namespace std;


int main(int argc, char *argv[])
{
	unsigned noq = 0;
	if (argc > 1) {
		noq = atoi(argv[1]);
	} else {
		cout << "How many questions do you want?" << endl;
		cin >> noq;
	}

	//basic_work_sheet wks(noq);
	cout << "Populating a work sheet with " << noq << " questions.." << endl;
	string filename = "worksheet-1.txt";
	if (argc > 2) {
		filename = argv[2];
	}
	cout << "The name of o/p file is " << filename << endl;
	cout << "Generating work sheet.." << endl;

	bool gen_negatives = false;
	if (argc > 3) {
		if(string(argv[3]) == "-gen_neg") gen_negatives = true;
	}
	
	wks_intf * wks = NULL;
	if (argc > 4) {
		if(string(argv[4]) == "-basic") {
			wks = new basic_work_sheet(noq);
		} else if(string(argv[4]) == "-expr") {
			wks = new expression_worksheet(noq);
		} else {
			cout << "Invalid option argv[4]. Allowed values '-basic' & '-expr' " << endl;
		}
	}
	
	if(!wks) {
		wks = new basic_work_sheet(noq);
	}
	
	wks->populate_ques(gen_negatives);
	wks->generate_question(filename);
	cout << "Worksheet generated!! Here is the content of work sheet.." << endl;
	//wks->generate_answers(filename.append(".key.txt"));
	wks->print();

}
