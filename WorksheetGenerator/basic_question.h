#pragma once

#include<iostream>
#include<fstream>
#include<map>
#include<random>
#include<cassert>
#include<sstream>
#include "worksheet_interface.h"


class basic_question : public question_interface
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

	basic_question():lhs(0),rhs(0),oper(operation::add) {}

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

	//Implementation of question interface functions
	void create() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis_sign(0, 1);
		std::uniform_int_distribution<> dis(1, 20);
		std::uniform_int_distribution<> lhs_gen(20, 200);
		std::uniform_int_distribution<> rhs_gen(2, 50);
		
		
		basic_question::operation op = (basic_question::operation)(dis(gen) & 3);
		int ls = 0;
		int rs = 0;
		if (op == operation::divide) {
			std::uniform_int_distribution<> div_gen(2, 20);
			std::uniform_int_distribution<> quo_gen(5, 500);
			rs = div_gen(gen);
			ls = rs * quo_gen(gen);
		}
		else {
			ls = lhs_gen(gen);
			rs = rhs_gen(gen);
			if (dis_sign(gen))ls = ls * -1;
			if (dis_sign(gen))rs = rs * -1;
		}

		this->lhs = ls;
		this->rhs = rs;
		this->oper = op;
				
	}

	void print_question(ostream& os) {
		os << *this;
	}
	void print_answer(ostream& os) {
		os << lhs << "\t" << basic_question::operation_str(oper) << "\t" << rhs << "\t = \t" << this->answer() <<  endl;
	}

	friend ostream& operator << (ostream & os, const basic_question& q); 
	int lhs;
	int rhs;

};


ostream& operator << (ostream & os, const basic_question& q)
{
	os << str_with_sign(q.lhs) << "\t" << basic_question::operation_str(q.oper) << "\t" << str_with_sign(q.rhs) << "\t = \t _________" <<  endl;
	return os;
}
