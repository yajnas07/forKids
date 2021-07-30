#include<iostream>
#include<fstream>
#include<map>
#include<random>
#include<cassert>

using namespace std;

class question
{
public:
	enum class operation{
		add,
		subtract,
		multiply,
		divide
	} oper;

	static string operation_str(operation op) {
		switch (op)
		{
		case question::operation::add:
			return " + ";
		case question::operation::subtract:
			return " - ";
			break;
		case question::operation::multiply:
			return " x ";
		case question::operation::divide:
			return " / ";
		default:
			return " invalid ";
		}
	}
	//question()
	//	:lhs(0), rhs(0), oper(operation::add)
	//{}

	question(int l, int r, question::operation op) 
		:lhs(l), rhs(r), oper(op)
	{
		if (op == operation::subtract && (lhs < rhs)) {
			std::swap<int>(lhs,rhs);
		}
		if (op == operation::divide ) {
			if(lhs < rhs) std::swap<int>(lhs,rhs);
			rhs = rhs % 10 + 1;
			if (lhs % rhs) {
				lhs = ((lhs*10) / rhs) * rhs;
				if (!lhs) lhs++;
			}
			assert(rhs != 0 && "RHS cannot be 0 for Divide operation");
		}
	}
	int answer()
	{
		switch (oper)
		{
		case operation::add: return lhs + rhs;
		case operation::subtract: return lhs - rhs;
		case operation::multiply: return lhs * rhs;
		case operation::divide: return lhs / rhs;

		default:
			break;
		}
		return 0;
	}
	void print_question(ostream& os) {
		os << lhs << "\t" << question::operation_str(oper) << "\t" << rhs << "\t = \t _________" <<  endl << endl;
	}
	void print_answer(ostream& os) {
		os << lhs << "\t" << question::operation_str(oper) << "\t" << rhs << "\t = \t" << this->answer() <<  endl << endl;
	}

	friend ostream& operator << (ostream & os, const question& q); 
	int lhs;
	int rhs;

};

ostream& operator << (ostream & os, const question& q)
{
	os << q.lhs << "\t" << question::operation_str(q.oper) << "\t" << q.rhs << "\t = \t _________" <<  endl << endl;
	return os;
}

class work_sheet {
public:
	work_sheet(unsigned noq):m_noq(noq) {

	}
	bool populate_ques();
	bool generate_question(string filename = "");
	bool generate_answers(string filename);
	void print();

private:
	unsigned m_noq = 0;
	std::map<int, question> m_questions;
};


int main(int argc, char *argv[])
{
	unsigned noq = 0;
	if (argc > 1) {
		noq = atoi(argv[1]);
	}
	else {
		cout << "How many questions do you want?" << endl;
		cin >> noq;
	}

	work_sheet wks(noq);
	cout << "Populating a work sheet with " << noq << " questions.." << endl;
	wks.populate_ques();
	string filename = "worksheet-1.txt";
	if (argc > 2) {
		filename = argv[2];
	}
	cout << "The name of o/p file is " << filename << endl;
	cout << "Generating work sheet.." << endl;
	wks.generate_question(filename);
	cout << "Worksheet generated!! Here is the content of work sheet.." << endl;
	wks.generate_answers(filename.append(".key.txt"));
	wks.print();

	



}

bool work_sheet::generate_question(string filename)
{
	ofstream ofs;
	ofs.open(filename.c_str());
	if (!ofs.is_open()) cout << "Error: COuld not open file " << filename << "for writing!!" << endl;

	ofs << "**************************************************************" << endl;
	ofs << "******************* Work Sheet *******************************" << endl;
	ofs << "**************************************************************\n" << endl;
	for (auto itr = m_questions.begin(); itr != m_questions.end(); itr++) {
		ofs << "  " << itr->first + 1 << ")\t" << itr->second;
	}
	ofs << "\n************************************************************" << endl;
	ofs << "***************** END: Work Sheet ***************************" << endl;
	ofs << "*************************************************************" << endl;

	return true;
}

bool work_sheet::generate_answers(string filename)
{
	ofstream ofs;
	ofs.open(filename.c_str());
	if (!ofs.is_open()) cout << "Error: COuld not open file " << filename << "for writing!!" << endl;

	ofs << "*****************************************************************************" << endl;
	ofs << "*************************** Work Sheet **************************************" << endl;
	ofs << "*****************************************************************************\n" << endl;
	for (auto itr = m_questions.begin(); itr != m_questions.end(); itr++) {
		ofs << "  " << itr->first + 1 << ")\t";
		itr->second.print_answer(ofs);
	}
	ofs << "\n*****************************************************************************" << endl;
	ofs << "*************************** END: Work Sheet **********************************" << endl;
	ofs << "******************************************************************************" << endl;

	return true;
}

bool work_sheet::populate_ques()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 20);


	for (unsigned i = 0; i < m_noq; i++)
	{
		int lhs = dis(gen);
		int rhs = dis(gen);
		question::operation op = (question::operation)(dis(gen) & 3);

		m_questions.insert(std::make_pair(i, question(lhs,rhs,op)));
		
	}
	return true;
}



void work_sheet::print()
{
	for (auto itr = m_questions.begin(); itr != m_questions.end(); itr++) {
		cout <<itr->first + 1 << ")\t" << itr->second;
	}

}




