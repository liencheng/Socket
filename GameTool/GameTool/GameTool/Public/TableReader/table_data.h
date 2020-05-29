#pragma once;
#include "../../stdafx.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class cell_type
{
public:
	enum 
	{
		T_INT32,
		T_INT64,
		T_UINT64,
		T_FLOAT,
		T_STRING,
	};
};

using cell_data = std::string;

class table_data
{
public:
	table_data(std::string filepath){ readfile(filepath); };
	~table_data(){};
	void read(int32 &val, int32 row_num, int32 filed_idx);
	void read(int64 &val, int32 row_num, int32 filed_idx);
	void read(float &val, int32 row_num, int32 filed_idx);
	void read(string &val, int32 row_num, int32 filed_idx);
private:
	void readfile(std::string filepath);
	void readtype(std::string line);
	void readdata(std::string line, int32 row);
	int32 get_line_count() const{ return m_table_data.size(); }

private:

	std::vector<int32> m_data_type_vec;
	std::map<int32, std::vector<cell_data>> m_table_data;
		
};