#include<iostream>
#include "arithmetic_worksheet.h"
#include "jason_worksheet.h"
using namespace std;

enum class worksheet_type { 
	arithmetic,
	percentage,
	algebric_expression,
	linear_equation
};

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
	worksheet_type type = worksheet_type::arithmetic;
	string input_file = "";
	if (argc > 3) {
		string stype = argv[3];
		if (stype == "arithmetic") {
			type = worksheet_type:: arithmetic;
		} else if(stype == "percentage") { 
			input_file = "percent_question.json";
			type = worksheet_type::percentage;
		} else if(stype == "algebric_expression") {
			input_file = "algebric_expression.json";
			type = worksheet_type::algebric_expression;

		} else if(stype == "linear_equation") {
			input_file = "linear_equation.json";
			type = worksheet_type::linear_equation;

		} else {
			cout << "Invalid argument for expression type\n";
			cout << "Valid vaules for type are: arithmetic, percentage, algebric_expression, linear_equation";
			return -1;
		}

	}

	cout << "The name of o/p file is " << filename << endl;
	cout << "Generating work sheet.." << endl;
	
	wks_intf * wks = nullptr;
	if(type == worksheet_type::arithmetic) {
	    wks = new arithmetic_worksheet(noq);
		wks->populate_ques();
	} else {
	    wks = new jason_worksheet(noq);
		wks->populate_ques(input_file);
	}
	
	wks->generate_question(filename);
	cout << "Worksheet generated!! Here is the content of work sheet.." << endl;
	//wks->generate_answers(filename.append(".key.txt"));
	wks->print();

}
