#include "TableReader.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "boost/algorithm/string.hpp"
using namespace std;

#define TYPE_ROW_ID (2)   //���������ڵ�2��
#define TYPE_INT32_S ("INT32")
#define TYPE_INT_S ("INT")
#define TYPE_INT64_S ("INT64") 
#define TYPE_UINT64_S ("UINT64") 
#define TYPE_FLOAT_S ("FLOAT") 
#define TYPE_STRING_S ("STRING") 



void TableData::ReaderHeader()
{
	m_HeaderType.clear();
	ifstream infile;
	infile.open(m_FilePath.data());   //���ļ����������ļ��������� 
	if (!infile.is_open())  //��ʧ��,�����������Ϣ,����ֹ�������� 
	{
		MyLog::Log("open file failed, file:%s", m_FilePath.data());
		return;
	}

	string strline;
	int32 nIdx = 0;
	while (getline(infile, strline))
	{
		nIdx++;
		if (nIdx == TYPE_ROW_ID)
		{

			std::vector<std::string> typeList;
			boost::split(typeList, strline, "\t");
			if (typeList.size() > 0)
			{
				for (int32 idx = 0; idx < typeList.size(); ++idx)
				{
					std::string nTypeName = typeList[idx];
					if (nTypeName == TYPE_INT32_S)
					{
						m_HeaderType.push_back((int32)(DATA_TYPE::T_INT32));
					}
					else if (nTypeName == TYPE_INT_S)
					{
						m_HeaderType.push_back((int32)(DATA_TYPE::T_INT32));
					}
					else if (nTypeName == TYPE_INT64_S)
					{
						m_HeaderType.push_back((int32)(DATA_TYPE::T_INT64));
					}
					else if (nTypeName == TYPE_UINT64_S)
					{
						m_HeaderType.push_back((int32)(DATA_TYPE::T_UINT64));
					}
					else if (nTypeName == TYPE_FLOAT_S)
					{
						m_HeaderType.push_back((int32)(DATA_TYPE::T_FLOAT));
					}
					else if (nTypeName == TYPE_STRING_S)
					{
						m_HeaderType.push_back((int32)(DATA_TYPE::T_STRING));
					}
				}
			}
			break;
		}
	}
	infile.close();             //�ر��ļ������� 
}