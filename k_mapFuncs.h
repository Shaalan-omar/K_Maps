#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;
namespace ANSWER {
	struct minterm
	{
		int state;
		int dec_value;
		int inclusion_times = 0;
		string binary_value;
	};

	struct mintermstr
	{
		vector<minterm> minterms;
		int size;
		bool operator<(const mintermstr& m2);
	};


	void initialize_k_map();
	void input();
	void implicants();
	void sort_imp();
	void decrease_imp_num(int i);
	void print_map();
	void duplicates();
	vector<minterm>& find_maxsize_vector();
	void prime_implicants();
	string final_experession();

	void inclusion();
	string find_answer();
}