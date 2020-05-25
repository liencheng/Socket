#pragma once
#include <map>
#include <vector>
#include <string>
#include "../../stdafx.h"


class DATA_TYPE
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

struct Cell
{
	union Val
	{
		int32 m_int32;
		int64 m_int64;
		uint64 m_uint64;
		float m_float;
		std::string m_string;
	};
	Val m_val;
};

typedef int32 DATATYPE;

class TableData
{
public:
	TableData(std::string filePath):m_FilePath(filePath) {};
	~TableData() {};
	void ReaderHeader();
	void ReaderComment();
	void ReaderData();
private:
	std::string m_FilePath;
	std::map<int32, std::vector<Cell>> m_Data;
	std::vector<DATATYPE> m_HeaderType;
};
