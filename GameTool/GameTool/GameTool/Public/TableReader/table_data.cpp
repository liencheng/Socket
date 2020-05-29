#include "table_data.h"

#define TYPE_ROW_ID (2)   //类型配置在第2行
#define TYPE_COMMENT_ID (3)	//注释行
#define TYPE_INT32_S ("INT32")
#define TYPE_INT_S ("INT")
#define TYPE_INT64_S ("INT64") 
#define TYPE_UINT64_S ("UINT64") 
#define TYPE_FLOAT_S ("FLOAT") 
#define TYPE_STRING_S ("STRING") 


void table_data::readtype(std::string line)
{
	std::vector<std::string> typeList;
	boost::split(typeList, line, "\t");
	if (typeList.size() > 0)
	{
		for (int32 idx = 0; idx < typeList.size(); ++idx)
		{
			std::string nTypeName = typeList[idx];
			if (nTypeName == TYPE_INT32_S)
			{
				m_data_type_vec.push_back((int32)(cell_type::T_INT32));
			}
			else if (nTypeName == TYPE_INT_S)
			{
				m_data_type_vec.push_back((int32)(cell_type::T_INT32));
			}
			else if (nTypeName == TYPE_INT64_S)
			{
				m_data_type_vec.push_back((int32)(cell_type::T_INT64));
			}
			else if (nTypeName == TYPE_UINT64_S)
			{
				m_data_type_vec.push_back((int32)(cell_type::T_UINT64));
			}
			else if (nTypeName == TYPE_FLOAT_S)
			{
				m_data_type_vec.push_back((int32)(cell_type::T_FLOAT));
			}
			else if (nTypeName == TYPE_STRING_S)
			{
				m_data_type_vec.push_back((int32)(cell_type::T_STRING));
			}
		}
	}
}

void table_data::readdata(std::string line, int32 row)
{
	std::vector<std::string> dataList;
	boost::split(dataList, line, "\t");
	if (typeList.size() > 0)
	{
		m_table_data[row] = dataList;
	}
}

void table_data::readfile(std::string filepath)
{

	ifstream infile;
	infile.open(filepath.data());   //将文件流对象与文件连接起来 
	if (!infile.is_open())  //若失败,则输出错误消息,并终止程序运行 
	{
		MyLog::Log("open file failed, file:%s", filepath.data());
		return;
	}

	string strline;
	int32 nIdx = 0;
	while (getline(infile, strline))
	{
		nIdx++;
		if (nIdx == TYPE_ROW_ID)
		{
			readtype(strline);
			continue;
		}
		else if (nIdx > TYPE_COMMENT_ID)
		{
			readdata(strline, nIdx);
		}
	}
	infile.close();             //关闭文件输入流 
}

void table_data::read(int32 &val, int32 row_num, int32 filed_idx)
{
	auto itF = m_table_data.find(row_num);
	if (itF == m_table_data.end())
	{
		return;
	}
	if (filed_idx < 0)
	{
		return;
	}
	if (itF->second.size() <= filed_idx)
	{
		return;
	}
	std::string filedval = itF->second[filed_idx];
	val = stoi(filedval);
}

void table_data::read(int64 &val, int32 row_num, int32 filed_idx)
{
	auto itF = m_table_data.find(row_num);
	if (itF == m_table_data.end())
	{
		return;
	}
	if (filed_idx < 0)
	{
		return;
	}
	if (itF->second.size() <= filed_idx)
	{
		return;
	}
	std::string filedval = itF->second[filed_idx];
	val = stoll(filedval);
}

void table_data::read(float &val, int32 row_num, int32 filed_idx)
{
	auto itF = m_table_data.find(row_num);
	if (itF == m_table_data.end())
	{
		return;
	}
	if (filed_idx < 0)
	{
		return;
	}
	if (itF->second.size() <= filed_idx)
	{
		return;
	}
	std::string filedval = itF->second[filed_idx];
	val = stof(filedval);
}

void table_data::read(string &val, int32 row_num, int32 filed_idx)
{
	auto itF = m_table_data.find(row_num);
	if (itF == m_table_data.end())
	{
		return;
	}
	if (filed_idx < 0)
	{
		return;
	}
	if (itF->second.size() <= filed_idx)
	{
		return;
	}
	std::string filedval = itF->second[filed_idx];
	val = filedval;
}