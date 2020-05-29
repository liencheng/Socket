#pragma once;
#include <string>
#include "table_data.h"
#include <map>

template <typename _table_line>
class table_logic
{
	using tableconfig = std::map<int32, _table_line>;
public:
	table_logic(){};
	~table_logic(){};

	void load(string filepath)
	{
		table_data tablefile(filepath);
		int32 nline_count = tablefile.get_line_count();
		for (int32 idx = 0; idx < nline_count; ++idx)
		{
			_table_line line;
			line.load(tablefile, idx);
			m_tablecfg[line.GetId()] = line;
		}
	}

private:
	tableconfig m_tablecfg;
};