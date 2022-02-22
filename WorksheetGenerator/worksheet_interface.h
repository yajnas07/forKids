#pragma once

#include<iostream>
#include<map>
#include<sstream>

using namespace std;

class question_interface {
	public:
	virtual void create() = 0;
	virtual void print_question(ostream& os) = 0; 
	virtual void print_answer(ostream& os) = 0;
	
};


static std::string str_with_sign(int value)
{
	std::stringstream ss;
	if(value >= 0) {
		ss << value;
	} else {
		ss << "(" << value << ")";
	}	
	return ss.str();
}

class wks_intf {
public:
	wks_intf(unsigned mno):m_noq(mno){}
	virtual bool populate_ques() = 0;
	virtual bool populate_ques(string input_filename) {return false;};
	virtual bool generate_question(std::string filename = "") = 0;
	virtual bool generate_answers(std::string filename) = 0;
	virtual void print() = 0;
	virtual ~wks_intf() {}
protected:
	unsigned m_noq = 0;
};
