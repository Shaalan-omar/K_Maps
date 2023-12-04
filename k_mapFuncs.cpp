#include "k_mapFuncs.h"
namespace ANSWER {
	const int rows = 2, col = 4;

	int num_minterms = 0;
	int decimalmin_array[7];
	minterm Kmap[rows * col];
	string simplfied_exp = "";
	vector<minterm> vec_1, vec_2, vec_3, vec_4, vec_5, included_arr;

	vector<mintermstr> obtained_imp;
	void input()
	{
		cout << "Enter number of minterms : ";
		cin >> num_minterms;
		while (num_minterms < 1 || num_minterms>8)
		{
			cout << "This number is not applicable. Please try again : ";
			cin >> num_minterms;
			cout << endl;
		}
		cout << endl;
		int temp;

		for (int i = 0; i < num_minterms; i++)
		{
			cout << "Enter the " << i + 1 << " minterm : ";
			cin >> temp;
			while (temp < 0 || temp > 7)
			{
				cout << "This minterm is not valid. Please try again : ";
				cin >> temp;
			}
			decimalmin_array[i] = temp;
		}
	}

	void initialize_k_map()
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < col; j++)
			{
				int index = i * col + j;
				Kmap[index].state = 0; //intializing the state of the kmap array to zeroes
			}

		//giving the array cells its position in the kmap
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < col; j++)
			{
				int index = i * col + j;
				Kmap[index].dec_value = index;
			}

		Kmap[2].dec_value = 3;
		Kmap[3].dec_value = 2;
		Kmap[6].dec_value = 7;
		Kmap[7].dec_value = 6;

		for (int i = 0; i < num_minterms; i++)
		{
			switch (decimalmin_array[i])
			{
			case 3:
				Kmap[2].state = 1;
				break;
			case 2:
				Kmap[3].state = 1;
				break;
			case 6:
				Kmap[7].state = 1;
				break;
			case 7:
				Kmap[6].state = 1;
				break;
			default:
				Kmap[decimalmin_array[i]].state = 1;

				break;
			}
		}
		std::bitset<3> set;
		for (int i = 0; i < 8; i++)
		{
			set = Kmap[i].dec_value;
			Kmap[i].binary_value = set.to_string();
		}

		print_map();
	}

	void print_map() //printing the obtained k map
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < col; j++)
			{
				int index = i * col + j;
				cout << Kmap[index].state << "  ";
			}
			cout << endl;
		}
	}

	void implicants() //storing the implicants in each vector 
	{
		if (num_minterms == 8)
			simplfied_exp = "1";
		else if (num_minterms == 0)
			simplfied_exp = "0";
		else
		{
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < col; j++)
				{
					int implicantNum = 0;
					int index = i * col + j;
					if (Kmap[index].state == 1)
					{
						vec_1.push_back(Kmap[index]);
						int index1 = i * col + ((j + 1) % col);
						int index2 = ((i + 1) % rows) * col + j;
						int index3 = ((i + 1) % rows) * col + ((j + 1) % col);
						if (Kmap[index1].state == 1)
						{
							vec_2.push_back(Kmap[index]);
							vec_2.push_back(Kmap[index1]);
						}
						if (Kmap[index2].state == 1)
						{
							vec_3.push_back(Kmap[index]);
							vec_3.push_back(Kmap[index2]);
						}
						if (Kmap[index1].state == 1 && Kmap[index2].state == 1 && Kmap[index3].state == 1)
						{
							vec_4.push_back(Kmap[index]);
							vec_4.push_back(Kmap[index1]);
							vec_4.push_back(Kmap[index2]);
							vec_4.push_back(Kmap[index3]);
						}
						int index4 = i * col + ((j + 2) % col);
						int index5 = i * col + ((j + 3) % col);
						if (Kmap[index1].state == 1 && Kmap[index4].state == 1 && Kmap[index5].state == 1)
						{
							vec_5.push_back(Kmap[index]);
							vec_5.push_back(Kmap[index1]);
							vec_5.push_back(Kmap[index4]);
							vec_5.push_back(Kmap[index5]);
						}
						included_arr = find_maxsize_vector();

						for (int m = 0; m < included_arr.size(); m++)
						{
							int& dcMinTerm = included_arr[m].dec_value;
							switch (dcMinTerm)
							{
							case 3:
								Kmap[3].inclusion_times += 1;
								break;
							case 2:
								Kmap[2].inclusion_times += 1;
								break;
							case 6:
								Kmap[7].inclusion_times += 1;
								break;
							case 7:
								Kmap[6].inclusion_times += 1;
								break;
							default:
								Kmap[dcMinTerm].inclusion_times += 1;
								break;
							}
						}

						obtained_imp.push_back(mintermstr());
						for (int k = 0; k < included_arr.size(); k++)
						{
							obtained_imp.back().minterms.push_back(included_arr[k]);
						}
						obtained_imp.back().size = included_arr.size();
						implicantNum++;
					}
					vec_1.clear();
					vec_2.clear();
					vec_3.clear();
					vec_4.clear();
					vec_5.clear();
				}
			}
		}
	}

	vector<minterm>& find_maxsize_vector()
	{
		int vector_sizes[5];
		vector_sizes[0] = vec_1.size();
		vector_sizes[1] = vec_2.size();
		vector_sizes[2] = vec_3.size();
		vector_sizes[3] = vec_4.size();
		vector_sizes[4] = vec_5.size();
		vector<minterm>* vs[] = { &vec_1, &vec_2, &vec_3, &vec_4, &vec_5 };
		int max = -1;
		int vector_number;
		for (int i = 0; i < 5; i++)
		{
			if (vector_sizes[i] > max)
			{
				max = vector_sizes[i];
				vector_number = i;
			}
		}
		return *vs[vector_number];
	}

	void sort_imp()
	{
		sort(obtained_imp.begin(), obtained_imp.end());
	}

	void inclusion()
	{
		for (int i = 0; i < obtained_imp.size(); i++)
		{
			for (int j = 0; j < obtained_imp[i].minterms.size(); j++)
			{
				int& dcMinTerm = obtained_imp[i].minterms[j].dec_value;
				int& included = obtained_imp[i].minterms[j].inclusion_times;
				switch (dcMinTerm)
				{
				case 3:
					included = Kmap[2].inclusion_times;
					break;
				case 2:
					included = Kmap[3].inclusion_times;
					break;
				case 6:
					included = Kmap[7].inclusion_times;
					break;
				case 7:
					included = Kmap[6].inclusion_times;
					break;
				default:
					included = Kmap[dcMinTerm].inclusion_times;
					break;
				}

			}
		}
	}

	void duplicates() //removing duplicates from the obtained implicants 
	{
		int numberOfMinterms = 0;
		for (int i = 0; i < obtained_imp.size(); i++)
			for (int k = 1; k < obtained_imp.size() - 1; k++)
				for (int j = 0; j < obtained_imp[i].minterms.size(); j++)
				{
					numberOfMinterms = 0;
					for (int N = 0; N < obtained_imp[k].minterms.size(); N++)
						if (obtained_imp[i].minterms[j].binary_value == obtained_imp[k].minterms[N].binary_value)
							numberOfMinterms++;

					if (numberOfMinterms == obtained_imp[i].minterms.size() && obtained_imp[i].size == obtained_imp[k].size)
					{
						decrease_imp_num(i);
						obtained_imp.erase(obtained_imp.begin() + i);
					}
				}
	}

	void decrease_imp_num(int indexOfImplicant) //decreasing the number of obtained implicants in case of dublication
	{
		const int& implicantsSize = obtained_imp.size();
		auto& specialImplicantMinTerms = obtained_imp[indexOfImplicant].minterms;
		for (int k = 0; k < implicantsSize; k++)
		{
			const int& mintermsSize = obtained_imp[k].minterms.size();
			for (int L = 0; L < mintermsSize; L++)
				for (int S = 0; S < specialImplicantMinTerms.size(); S++)
					if (obtained_imp[k].minterms[L].binary_value == specialImplicantMinTerms[S].binary_value)
						obtained_imp[k].minterms[L].inclusion_times--;
		}
	}

	void prime_implicants()
	{
		int count = 0;

		for (int i = 0; i < obtained_imp.size(); i++)
		{
			count = 0;
			for (int j = 0; j < obtained_imp[i].minterms.size(); j++)
				if (obtained_imp[i].minterms[j].inclusion_times > 1)
					count++;

			if (count == obtained_imp[i].size)
			{
				decrease_imp_num(i);
				obtained_imp.erase(obtained_imp.begin() + i);
				i = i - 1;
			}
		}
	}

	string final_experession()
	{
		string* mintermsInPrimeImplicant;
		simplfied_exp  = "";
		int NumOfMinterms;
		for (int i = 0; i < obtained_imp.size(); i++)
		{
			NumOfMinterms = obtained_imp[i].minterms.size();
			mintermsInPrimeImplicant = new string[obtained_imp[i].minterms.size()];
			for (int j = 0; j < obtained_imp[i].minterms.size(); j++)
				mintermsInPrimeImplicant[j] = obtained_imp[i].minterms[j].binary_value;

			int count = 0;

			for (int j = 0; j < 3; j++)
			{
				int m = 0;
				for (int k = 1; k < NumOfMinterms; k++) {
					auto& p1 = mintermsInPrimeImplicant[m][j];
					auto& p2 = mintermsInPrimeImplicant[k][j];
					if (p1 == p2)
						count++;
				}

				if (count == NumOfMinterms - 1)
				{
					simplfied_exp += char(j + 65);
					if (mintermsInPrimeImplicant[0][j] == '0')
						simplfied_exp += "`";
					
						
				}
				count = 0;
			}
			delete[] mintermsInPrimeImplicant;
			simplfied_exp += " + ";
		}
		simplfied_exp = simplfied_exp.erase(simplfied_exp.size() - 2); // to remove the extra + in the end
		return simplfied_exp;
	}

	bool mintermstr::operator<(const mintermstr& m2)
	{
		return size < m2.size;
	}

	string find_answer()
	{
		implicants();
		sort_imp();
		inclusion();
		duplicates();
		prime_implicants();
		return final_experession();
	}
}