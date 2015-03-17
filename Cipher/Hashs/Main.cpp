#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef std::pair<std::string, int> list_t;
typedef std::vector<list_t> list_t_hash;

int gener_idx(std::string &word_, int &amount)
{
	int degree = 1;
	int code = 53;
	int code_hash;
	int code_name = 0;
	size_t idx;
	for (int i = 0; i < word_.size(); ++i)
	{
		code_hash = word_[i] * degree;
		code_name += code_hash;
		degree *= code;
	}
	idx = code_name % amount;
	return idx;
}

class HashTable

{
public:
	HashTable()		
	{
		hash_table.resize(size_hash);
	};
	void add_objs(std::string &word, int &ages)
	{
		idx = gener_idx(word, size_hash); //forming id
		for (int i = 0; i < hash_table[idx].size(); ++i)
			if (hash_table[idx][i].first == word)
			{
				hash_table[idx][i].second = ages;
				find_name = true;
			}
		if (find_name == false)
		{
			name_age = std::make_pair(word, ages); //forming name-age 
			hash_table[idx].push_back(name_age);
			added_el++;
		}
		find_name = false;


	}
	void input_hash()
	{
		for (int id = 0; id < hash_table.size(); ++id)
			for (int i = 0; i < hash_table[id].size(); ++i)
			{
				std::cout << hash_table[id][i].first << " - " << hash_table[id][i].second;
				std::cout << "\n";
			}		
	}
	double kof()
	{
		kof_ = (double)added_el / size_hash;
		return kof_;
	}
	void rehash()
	{
		resize_hash = size_hash * increase;
		new_hash.resize(resize_hash);
		for (int i = 0; i < hash_table.size(); ++i)
			new_hash[i] = hash_table[i];
		hash_table.clear();
		size_hash = resize_hash;
		hash_table.resize(size_hash);
		for (int i = 0; i < hash_table.size(); ++i)
			hash_table[i] = new_hash[i];		
		new_hash.clear();
	}
	void find_name_hash(std::string &name_f)
	{
		conv_name = false;
		find_size = size_hash;
		if (find_size != first_size)
		{
			do
			{
				idx = gener_idx(name_f, find_size);
				for (int i = 0; i < hash_table[idx].size(); ++i)
					if (hash_table[idx][i].first == name_f)
					{
						std::cout << hash_table[idx][i].first << " - " << hash_table[idx][i].second << std::endl;
						conv_name = true;
					}
				find_size = find_size / increase;
			} 
			while (find_size != first_size);
		}
		else
		{
			idx = gener_idx(name_f, find_size);
			for (int i = 0; i < hash_table[idx].size(); ++i)
				if (hash_table[idx][i].first == name_f)
				{
					std::cout << hash_table[idx][i].first << " - " << hash_table[idx][i].second << std::endl;
					conv_name = true;
				}
		}
		if (conv_name == false)
			std::cout << "Not found!" << std::endl;	
	}
private:
	int first_size = 10;
	int find_size;
	int size_hash = 10;
	int increase = 2;
	int resize_hash;
	bool find_name;
	double kof_;
	int added_el = 0;
	bool conv_name = false;
	size_t idx;
	list_t name_age;
	std::vector<std::vector <list_t>> hash_table;
	std::vector<std::vector <list_t>> new_hash;
};

int main()
{
	HashTable hash_table;
	std::fstream in("input.txt");
	std::string name_f;
	std::string word;
	int size_hash = 10;
	int ages;	
	while (in >> word >> ages)
	{
		//if (hash_table.kof() >= 1)
			//hash_table.rehash();
		hash_table.add_objs(word, ages);
	}
	hash_table.input_hash();
	while (true)
	{
		std::cout << "Enter name: " << std::endl;
		std::cin >> name_f;
		hash_table.find_name_hash(name_f);
	}
	return 0;
}