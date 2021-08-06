#ifndef WORKSHEET_INTF_H
#define WORKSHEET_INTF_H
#include<iostream>
#include<map>
#include<sstream>


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
	virtual bool populate_ques(bool gen_negatives = 0) = 0;
	virtual bool generate_question(std::string filename = "") = 0;
	virtual bool generate_answers(std::string filename) = 0;
	virtual void print() = 0;
	virtual ~wks_intf() {}
protected:
	unsigned m_noq = 0;
};
#endif