#pragma once

#include<iostream>
#include<fstream>
#include<map>
#include<random>
#include<cassert>
#include<sstream>
#include "worksheet_interface.h"
#include "basic_question.h"
#include "expression_question.h"

class arithmetic_worksheet : public wks_intf {
public:
	arithmetic_worksheet(unsigned noq) :wks_intf(noq) {

	}
	bool populate_ques();
	bool generate_question(string filename);
	bool generate_answers(string filename);
	void print();
private:
	std::map<int, question_interface*> m_questions;

};

bool arithmetic_worksheet::generate_question(string filename)
{
	ofstream ofs;
	ofs.open(filename.c_str());
	if (!ofs.is_open()) cout << "Error: COuld not open file " << filename << "for writing!!" << endl;

	ofs << "**************************************************************" << endl;
	ofs << "*******************\t" << filename << "\t**********************" << endl;
	ofs << "**************************************************************\n" << endl;
	for (auto itr = m_questions.begin(); itr != m_questions.end(); itr++) {
		ofs << "  " << itr->first + 1 << ")\t";
		itr->second->print_question(ofs);
	}
	ofs << "\n************************************************************" << endl;
	ofs << "***************** END: Work Sheet ***************************" << endl;
	ofs << "*************************************************************" << endl;

	return true;
}

bool arithmetic_worksheet::generate_answers(string filename)
{
	ofstream ofs;
	ofs.open(filename.c_str());
	if (!ofs.is_open()) cout << "Error: Could not open file " << filename << "for writing!!" << endl;

	ofs << "**************************************************************************" << endl;
	ofs << "********************\t" << filename << "\t*********************" << endl;
	ofs << "**************************************************************************\n" << endl;
	for (auto itr = m_questions.begin(); itr != m_questions.end(); itr++) {
		ofs << "  " << itr->first + 1 << ")\t";
		itr->second->print_answer(ofs);
	}
	ofs << "\n*****************************************************************************" << endl;
	ofs << "*************************** END: Work Sheet **********************************" << endl;
	ofs << "******************************************************************************" << endl;

	return true;
}

bool arithmetic_worksheet::populate_ques()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis_gen(0, 1);
	for (unsigned i = 0; i < m_noq; i++) {
		if (dis_gen(gen)) {
			question_interface * new_ques = new basic_question();
			m_questions.insert(std::make_pair(i, new_ques));
		}
		else {
			question_interface * new_ques = new expression_question();
			m_questions.insert(std::make_pair(i, new_ques));
		}
		
	}
	for (auto & ques : m_questions) {
		ques.second->create();
	}
	return true;
}



void arithmetic_worksheet::print()
{
	for (const auto & ques : m_questions) {
		cout << ques.first + 1 << ")\t"; 
		ques.second->print_question(cout);
	}

}

