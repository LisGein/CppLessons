#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef std::pair<std::string, int> list_t;
typedef std::vector<list_t> list_hash;

int gener_idx(std::string &word_, int &amount)
{
	int code = 53;
	unsigned __int64 degree = 1;
	unsigned __int64 code_hash = 0;
	unsigned __int64 code_name = 0;
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
		hash_table_.resize(size_hash_);
	};
	void add_objs(std::string &word, int &ages)
	{
		double coefficient = (double)added_obj_ / size_hash_;
		if (coefficient < 1)
		{
			size_t idx;
			bool find_name = false;
			idx = gener_idx(word, size_hash_); //forming id
			for (int i = 0; i < hash_table_[idx].size(); ++i)
				if (hash_table_[idx][i].first == word)
				{
					hash_table_[idx][i].second = ages;
					find_name = true;
				}
			if (find_name == false)
			{
				name_age_ = std::make_pair(word, ages); //forming name-age 
				hash_table_[idx].push_back(name_age_);
				added_obj_++;
			}
			find_name = false;
		}
		else		
			rehash();
		
	}
	void input_hash()
	{
		for (int id = 0; id < hash_table_.size(); ++id)
			for (int i = 0; i < hash_table_[id].size(); ++i)
				std::cout << hash_table_[id][i].first << " - " << hash_table_[id][i].second << "\n";	
	}

	void rehash()
	{
		size_t idx;
		int increase = 2;
		int resize_hash = size_hash_ * increase;
		std::vector<list_hash> new_hash(resize_hash);
		for (int id = 0; id < hash_table_.size(); ++id)
			if (hash_table_[id].size() != 0)
				for (int i = 0; i < hash_table_[id].size(); ++i)
				{
					idx = gener_idx(hash_table_[id][i].first, resize_hash);
					name_age_ = std::make_pair(hash_table_[id][i].first, hash_table_[id][i].second); //forming name-age 
					new_hash[idx].push_back(name_age_);
				}		
		hash_table_.clear();
		size_hash_ = resize_hash;
		hash_table_.resize(size_hash_);
		hash_table_ = new_hash;
		new_hash.clear();
	}
	void find_hash(std::string &name_f)
	{
		size_t idx;
		bool conv_name = false;
		idx = gener_idx(name_f, size_hash_);
		for (int i = 0; i < hash_table_[idx].size(); ++i)
			if (hash_table_[idx][i].first == name_f)
			{
				std::cout << hash_table_[idx][i].first << " - " << hash_table_[idx][i].second << std::endl;
				conv_name = true;
			}
		if (conv_name == false)
			std::cout << "Not found!" << std::endl;	
	}
private:
	int size_hash_ = 10;
	int added_obj_ = 0;
	list_t name_age_;
	std::vector<list_hash> hash_table_;
};

int main()
{
	HashTable hashTable;
	std::fstream in("input.txt");
	std::string word;
	std::string name_find;
	std::string cmd;
	int ages;
	while (in >> word >> ages)
		hashTable.add_objs(word, ages);
	while (true)
	{
		std::cout << "Enter cmd: " << std::endl;
		std::cin >> cmd;
		if (cmd == "output")
			hashTable.input_hash();
		if (cmd == "find")
		{
			std::cout << "Enter name: " << std::endl;
			std::cin >> name_find;
			hashTable.find_hash(name_find);
		}
	}
	return 0;
}