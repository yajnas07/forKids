#ifndef BASIC_WORKSHEET_
#define BASIC_WORKSHEET_

#include<iostream>
#include<fstream>
#include<map>
#include<random>
#include<cassert>
#include<sstream>
#include "worksheet_interface.h"

using namespace std;
class basic_question
{
public:
	enum class operation{
		add,
		subtract, 
		multiply,
		divide
	} oper;


	static std::string operation_str(operation op) {
		switch (op)
		{
		case basic_question::operation::add:
			return " + ";
		case basic_question::operation::subtract:
			return " - ";
			break;
		case basic_question::operation::multiply:
			return " x ";
		case basic_question::operation::divide:
			return " / ";
		default:
			return " invalid ";
		}
	}

	basic_question(int l, int r, basic_question::operation op) 
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
		os << lhs << "\t" << basic_question::operation_str(oper) << "\t" << rhs << "\t = \t _________" <<  endl << endl;
	}
	void print_answer(ostream& os) {
		os << lhs << "\t" << basic_question::operation_str(oper) << "\t" << rhs << "\t = \t" << this->answer() <<  endl << endl;
	}

	friend ostream& operator << (ostream & os, const basic_question& q); 
	int lhs;
	int rhs;

};
string with_sign(int value)
{
	stringstream ss;
	if(value >= 0) {
		ss << value;
	} else {
		ss << "(" << value << ")";
	}	
	return ss.str();

}
ostream& operator << (ostream & os, const basic_question& q)
{
	os << with_sign(q.lhs) << "\t" << basic_question::operation_str(q.oper) << "\t" << with_sign(q.rhs) << "\t = \t _________" <<  endl << endl;
	return os;
}
class basic_work_sheet: public wks_intf {
public:
	basic_work_sheet(unsigned noq):wks_intf(noq) {

	}
	bool populate_ques(bool gen_negatives = 0);
	bool generate_question(string filename);
	bool generate_answers(string filename);
	void print();
private:
std::map<int, basic_question> m_questions;

};

bool basic_work_sheet::generate_question(string filename)
{
	ofstream ofs;
	ofs.open(filename.c_str());
	if (!ofs.is_open()) cout << "Error: COuld not open file " << filename << "for writing!!" << endl;

	ofs << "**************************************************************" << endl;
	ofs << "*******************\t"<< filename << "\t**********************" << endl;
	ofs << "**************************************************************\n" << endl;
	for (auto itr = m_questions.begin(); itr != m_questions.end(); itr++) {
		ofs << "  " << itr->first + 1 << ")\t" << itr->second;
	}
	ofs << "\n************************************************************" << endl;
	ofs << "***************** END: Work Sheet ***************************" << endl;
	ofs << "*************************************************************" << endl;

	return true;
}

bool basic_work_sheet::generate_answers(string filename)
{
	ofstream ofs;
	ofs.open(filename.c_str());
	if (!ofs.is_open()) cout << "Error: COuld not open file " << filename << "for writing!!" << endl;

	ofs << "**************************************************************************" << endl;
	ofs << "********************\t"<< filename << "\t*********************" << endl;
	ofs << "**************************************************************************\n" << endl;
	for (auto itr = m_questions.begin(); itr != m_questions.end(); itr++) {
		ofs << "  " << itr->first + 1 << ")\t";
		itr->second.print_answer(ofs);
	}
	ofs << "\n*****************************************************************************" << endl;
	ofs << "*************************** END: Work Sheet **********************************" << endl;
	ofs << "******************************************************************************" << endl;

	return true;
}

bool basic_work_sheet::populate_ques(bool gen_negatives)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis_sign(0, 1);
	std::uniform_int_distribution<> dis(1, 20);
	std::uniform_int_distribution<> lhs_gen(20, 200);
	std::uniform_int_distribution<> rhs_gen(2, 50);


	for (unsigned i = 0; i < m_noq; i++)
	{
		int lhs = lhs_gen(gen);
		int rhs = rhs_gen(gen);
		basic_question::operation op = (basic_question::operation)(dis(gen) & 3);
		if(gen_negatives &&  (op != basic_question::operation::divide)) {
			if(dis_sign(gen))lhs = lhs * -1;
			if(dis_sign(gen))rhs = rhs * -1;
		}
		m_questions.insert(std::make_pair(i, basic_question(lhs,rhs,op)));
		
	}
	return true;
}



void basic_work_sheet::print()
{
	for (auto itr = m_questions.begin(); itr != m_questions.end(); itr++) {
		cout <<itr->first + 1 << ")\t" << itr->second;
	}

}

#endif
