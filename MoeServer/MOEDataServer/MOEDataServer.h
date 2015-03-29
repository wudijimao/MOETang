#ifndef MOE_DATA_SERVER_H
#define MOE_DATA_SERVER_H

#include <iostream>
#include <icrsint.h>
#include <windows.h>
#include <string>
using namespace std;
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")

static class GetReturn
{
public:
	//使用时必须传入初始化好的str
	static char* c_str(char *str,_variant_t in)
	{
		strncpy(str,(_bstr_t)in,128);
		return str;
	}
};
enum MyType
{
	mystring,
	myint,
	myData
};
class MOEDataServer
{
	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
public:
	_RecordsetPtr m_pRecord;
	MOEDataServer()
	{
		CoInitialize(NULL);
		m_pConnection.CreateInstance("ADODB.Connection"/*_uuidof(Connection)*/);
		bstr_t strConnect="Driver={Microsoft Access Driver (*.mdb)}; DSN=MOEDataBase; DBQ=D:\\DataBase\\MOEDateBase.mdb; Uid=; Pwd=;";
		m_pCommand.CreateInstance(_uuidof(Command));
		try
		{

			//m_pConnection->Properties("Prompt") = adPromptAlways;
			m_pConnection->Open(strConnect,"","",adModeUnknown);
		}
		catch (_com_error e)
		{
			cout<<"数据库初始化错误"<<endl;
			system("pause");
			return;
		}
		m_pCommand->ActiveConnection=m_pConnection;
		cout<<"连接成功！"<<endl;
		m_pRecord.CreateInstance(_uuidof(Recordset));
	}
	bool doSql(const char *str)
	{
		string a = "INSERT   INTO   login   VALUES   ('1','25',12)";
		try
		{
			m_pRecord = m_pConnection-> Execute((_bstr_t)str,NULL,adCmdText);
		}
		catch (_com_error* e)
		{
			cout<<e->Error();
			system("pause");
		}
		
		/*m_pCommand->CommandText=_bstr_t(str);
		try
		{
			m_pRecord->Open((IDispatch*)m_pCommand,vtMissing,adOpenStatic,adLockOptimistic,adCmdUnspecified);
		}
		catch(_com_error e)
		{
			cout<<"无法打开表"<<endl;
			return false;
		}*/
		return true;
	}
	bool myselect(string tablename,string where)//myselect("login","username = haha");
	{
		string str ="select * from " + tablename + " where "+ where;
		return doSql(str.c_str());
	}
	bool myselect(string tablename)//myselect("login","username = haha");
	{
		string str ="select * from " + tablename;
		return doSql(str.c_str());
	}
	bool myinsert(string tablename,string linenames,string neirong)//myinsert("login","haha,123");
	{
		string str ="insert into " + tablename + "("+ linenames +") values ("+ neirong + ")";
		return doSql(str.c_str());
	}
	bool myupdate(string tablename,string where,string neirong)//myupdate("login","username = haha","password = 123");
	{
		string str ="update " + tablename + " SET "+ neirong + " where " + where;
		return doSql(str.c_str());
	}
	bool mydelete(string tablename,string where)//mydelete("login","username = haha");
	{
		string str ="delete from " + tablename + " where "+ where;
		return doSql(str.c_str());
	}
	void showAll(MyType type[],int num)//输出所有查询结果
	{
		int i;
		while (!isEnd())
		{
			for(i=0;i<num;++i)
			{
				switch(type[i])
				{
					case MyType::mystring:
						cout<<getLineString(i);
						break;
					case MyType::myint:
						cout<<getLineInt(i);
						break;
				}
				cout<<"\t";
			}
			cout<<endl;
			NextRecord();
		}
		system("pause");
	}
	void NextRecord()
	{
		m_pRecord->MoveNext();
	}
	bool isEnd()
	{
		return m_pRecord->adoEOF;
	}
	string getLineString(string line)
	{
		char str[128];
		return string(GetReturn::c_str(str,m_pRecord->Fields->Item[_variant_t(line.c_str())]->Value));
	}
	string getLineString(int line)
	{
		char str[128];
		return string(GetReturn::c_str(str,m_pRecord->Fields->Item[_variant_t((long)(line+1))]->Value));
	}
	int getLineInt(string line)
	{
		return (int)m_pRecord->Fields->Item[_variant_t(line.c_str())]->Value;
	}
	int getLineInt(int line)
	{
		return (int)m_pRecord->Fields->Item[_variant_t((long)(line+1))]->Value;
	}
	~MOEDataServer()
	{
		m_pRecord->Close();
		m_pConnection->Close();
		m_pRecord.Release();
		m_pConnection.Release();
		CoUninitialize();
	}
};
#endif