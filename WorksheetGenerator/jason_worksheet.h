#pragma once

#include<iostream>
#include<fstream>
#include<map>
#include<random>
#include<cassert>
#include<sstream>
#include <vector> // vector
#include <regex>
#include "worksheet_interface.h"
#include "basic_question.h"
#include "expression_question.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

class jason_worksheet : public wks_intf {
public:
	jason_worksheet(unsigned noq) :wks_intf(noq) {

	}
	bool populate_ques();
	bool populate_ques(string input_filename);

	bool generate_question(string filename);
	bool generate_answers(string filename);
	void print();
private:
	std::vector<string> m_questions;
	std::vector<string> m_selected_questions;

};

bool jason_worksheet::populate_ques(string input_filename)
{
    ifstream infile; 
    infile.open(input_filename); 
    if(!infile.is_open()) {
		cout << "ERROR:Could not open file " << input_filename << " for reading" <<endl;
        return false;
    }

    json jq;
    infile >> jq;
    json jquestions = jq["questions"];
    for (auto &question : jquestions) {
        // cout << question << endl;
        string current_ques = question["description"];
        json elems = question["elem"];
        for (auto &i : elems) {
            // cout << i << endl;
            auto q = current_ques;
            for (auto &x : i.items()) {
                regex re(x.key());
                if (x.value().is_number()) {
                    string value = to_string(x.value());
                    // cout << "replacing:" << x.key() << " with " << value << endl;
                    q = regex_replace(q, re, value);
                }
            }
            m_questions.push_back(q);
			cout  << q << endl;
        }
    }

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis_selection(0, 5);
	std::uniform_int_distribution<> total_selection(0, m_questions.size()-1);
	cout << "Numberquestions = " << m_questions.size() << endl;
	unsigned number_of_banks = m_questions.size() / 6;
	if(number_of_banks==0) return false;
	// unsigned questions_per_bank = ceil(m_noq * 1.0 / number_of_banks);
	unsigned questions_per_bank = m_noq * 1.0 / number_of_banks;
	for(unsigned i=0; i<number_of_banks; i++) {
		    for(unsigned j=0; j< questions_per_bank; j++) {
		    unsigned selection = i*6 + dis_selection(gen);
		    cout << " Selection :" << selection << endl;
		    m_selected_questions.push_back(m_questions[selection]);
		 }
	 }
	if(m_selected_questions.size() < m_noq) {
		for(unsigned j=m_selected_questions.size(); j< m_noq; j++) {
		    unsigned selection =  total_selection(gen);
		    cout << " Selection :" << selection << endl;
		    m_selected_questions.push_back(m_questions[selection]);
		 }
	}

	return true;
}

bool jason_worksheet::populate_ques()
{
    return(populate_ques("percent_question.json"));
}


bool jason_worksheet::generate_question(string filename)
{
	ofstream ofs;
	ofs.open(filename.c_str());
	if (!ofs.is_open()) cout << "Error: COuld not open file " << filename << "for writing!!" << endl;

	ofs << "**************************************************************" << endl;
	ofs << "*******************\t" << filename << "\t**********************" << endl;
	ofs << "**************************************************************\n" << endl;
	auto counter = 1;
	for (auto q:m_selected_questions) {
	 	ofs << "  " << counter++ << ")\t";
		ofs << q << endl << endl;
	}
	// 	itr->second->print_question(ofs);
	// }
	ofs << "\n************************************************************" << endl;
	ofs << "***************** END: Work Sheet ***************************" << endl;
	ofs << "*************************************************************" << endl;

	return true;
}

bool jason_worksheet::generate_answers(string filename)
{
	ofstream ofs;
	ofs.open(filename.c_str());
	if (!ofs.is_open()) cout << "Error: Could not open file " << filename << "for writing!!" << endl;

	ofs << "**************************************************************************" << endl;
	ofs << "********************\t" << filename << "\t*********************" << endl;
	ofs << "**************************************************************************\n" << endl;
	// for (auto itr = m_questions.begin(); itr != m_questions.end(); itr++) {
	// 	ofs << "  " << itr->first + 1 << ")\t";
	// 	itr->second->print_answer(ofs);
	// }
	ofs << "\n*****************************************************************************" << endl;
	ofs << "*************************** END: Work Sheet **********************************" << endl;
	ofs << "******************************************************************************" << endl;

	return true;
}



void jason_worksheet::print()
{
	// for (const auto & ques : m_questions) {
	// 	cout << ques.first + 1 << ")\t"; 
	// 	ques.second->print_question(cout);
	// }
    auto counter = 1;
	for (auto q:m_selected_questions) {
	 	cout << "  " << counter++ << ")\t";
		cout << q << endl;
	}
}

