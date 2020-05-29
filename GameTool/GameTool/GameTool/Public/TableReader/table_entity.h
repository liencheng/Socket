#pragma once;

template <typename _tableclass>
class table_entity
{
public:
	table_entity(){}
	~table_entity();
private:
	_tableclass m_tableentity;
};