#pragma once

#include<iostream>
#include<fstream>
#include<map>
#include<random>
#include<cassert>
#include<sstream>
#include "worksheet_interface.h"

using namespace std;
class expression_question:public question_interface
{
private:
	unsigned oper_count;

public:
	enum class operation{
		add,
		subtract 
	};


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
	expression_question():oper_count(0) {}
	int answer()
	{
		return 0;
	}
	
	//Implementation of question interface functions
	void create() {


		std::random_device rd;
		std::mt19937 gen(rd());
		if (oper_count == 0) {
			std::uniform_int_distribution<> dis_sign(1, 3);
			oper_count = dis_sign(gen);
		}
						
		
		std::uniform_int_distribution<> dis_sign(0, 1);
		std::uniform_int_distribution<> dis_operation(0, 1);
		std::uniform_int_distribution<> lhs_gen(1, 30);
		for (auto i = 0; i < oper_count; i++) {
			int operand = lhs_gen(gen);
			if (dis_sign(gen)) { operand = operand * -1; }
			m_expression_vec.push_back(operand);
			m_expression_vec.push_back(dis_operation(gen));
		}
		m_expression_vec.push_back(lhs_gen(gen));
				
	}
	void print_question(ostream& os) {
		os << *this;
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

