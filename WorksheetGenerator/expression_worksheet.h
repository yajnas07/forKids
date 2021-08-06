#ifndef EXPRESSION_WORKSHEET_
#define EXPRESSION_WORKSHEET_

#include<iostream>
#include<fstream>
#include<map>
#include<random>
#include<cassert>
#include<sstream>
#include "worksheet_interface.h"

using namespace std;
class expression_question
{
public:
	enum class operation{
		add,
		subtract 
	} oper;


	static std::string operation_str(operation op) {
		switch (op)
		{
		case expression_question::operation::add:
			return " + ";
		case expression_question::operation::subtract:
			return " - ";
			break;
		default:
			return " invalid ";
		}
	}

	expression_question(unsigned oper_count)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis_sign(0, 1);
		std::uniform_int_distribution<> dis_operation(0, 1);
		std::uniform_int_distribution<> lhs_gen(1, 30);
		for(auto i=0 ; i<oper_count ; i++) {
			int operand = lhs_gen(gen);
			if(dis_sign(gen)) { operand = operand * -1; }
			m_expression_vec.push_back(operand);
			m_expression_vec.push_back(dis_operation(gen));
		}
		m_expression_vec.push_back(lhs_gen(gen));
	}
	int answer()
	{
		return 0;
	}
	
	void print_question(ostream& os) {
		cout << *this;
	}
	void print_answer(ostream& os) {
	}

	friend ostream& operator << (ostream & os, const expression_question& q); 
	std::vector<int> m_expression_vec;

};

ostream& operator << (ostream & os, const expression_question& q)
{
	for(int i=0; i<q.m_expression_vec.size(); i++) {
		if(i & 0x1) {
		os << expression_question::operation_str((expression_question::operation)(q.m_expression_vec[i])) << " ";
		} else {
		os << str_with_sign(q.m_expression_vec[i]) << " ";
		}
	}
	os << " = _______" << endl;
	return os;
}
class expression_worksheet: public wks_intf {
public:
	expression_worksheet(unsigned noq):wks_intf(noq) {

	}
	bool populate_ques(bool gen_negatives = 0);
	bool generate_question(string filename);
	bool generate_answers(string filename);
	void print();
private:
std::map<int, expression_question> m_questions;

};

bool expression_worksheet::generate_question(string filename)
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

bool expression_worksheet::generate_answers(string filename)
{
	//Not implemented
	return false;
}

bool expression_worksheet::populate_ques(bool gen_negatives)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis_sign(1, 3);
	for (unsigned i = 0; i < m_noq; i++) {
		m_questions.insert(std::make_pair(i, expression_question(dis_sign(gen))));
	}
	return true;
}



void expression_worksheet::print()
{
	for (auto itr = m_questions.begin(); itr != m_questions.end(); itr++) {
		cout <<itr->first + 1 << ")\t" << itr->second;
	}

}

#endif

