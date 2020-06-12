
#parame once
class (Test)
{
Test(){};
~Test(){};
void Clean()
{
DataId = 0;
Guid = 0;
StrVal = error_val;
DataMap = error_val;
DataVec = error_val;

}

void CopyFrom(const Test& rFrom)
{
DataId = rFrom.GetDataId();
Guid = rFrom.GetGuid();
StrVal = rFrom.GetStrVal();
DataMap = rFrom.GetDataMap();
DataVec = rFrom.GetDataVec();
}

Test & operate=(const Test &rFrom)
{
if(this != &rFrom)
{
this->CopyFrom(rFrom);
}
return *this;
}

bool operate==(const Test &rFrom)
{
bool bEqual = true;
bEqual  = (bEqual
 && (DataId == rFrom.GetDataId())
 && (Guid == rFrom.GetGuid())
 && (StrVal == rFrom.GetStrVal())
 && (DataMap == rFrom.GetDataMap())
 && (DataVec == rFrom.GetDataVec())
);
return bEqual;
}

bool operate!=(const Test &rFrom)
{
bool bEqual =(*this == rFrom);
return !bEqual;
}

int GetDataId() const {return DataId;}
int64 GetGuid() const {return Guid;}
error_type GetStrVal() const {return StrVal;}
error_type GetDataMap() const {return DataMap;}
error_type GetDataVec() const {return DataVec;}

void SetDataId(int val){DataId = val;}
void SetGuid(int64 val){Guid = val;}
void SetStrVal(error_type val){StrVal = val;}
void SetDataMap(error_type val){DataMap = val;}
void SetDataVec(error_type val){DataVec = val;}


private:
int DataId;
int64 Guid;
error_type StrVal;
error_type DataMap;
error_type DataVec;
};




