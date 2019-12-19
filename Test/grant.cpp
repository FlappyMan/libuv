#include "UProtocol.h"

enum
{
    SQL_BUFF_SIZE = 4096
};
void TestMysql()
{
    string sError;
    string sHost = "127.0.0.1";
    uint16_t uiPort = 3306;
    string sUser = "grant";
    string sPwd = "123456";
    string sDB = "grant_test";

    // 创建mysql 对象，并连接数据库
    UBMysql mysql(SQL_BUFF_SIZE);
    bool bConnected = mysql.Connect(sHost, uiPort, sUser, sPwd, sDB);
    if (bConnected == false)
    {
        mysql.Error(sError);
        cout << "connect to database failed:" << mysql.Error() << ":" << sError << endl;
        return;
    }
    cout << "connect to database:" << sHost << ":" << uiPort << endl;

    // 执行一条sql语句，删除已经存在的表
    string sql = "DROP TABLE A;";
    int iRet = mysql.Exec(sql);
    cout << sql << endl;
    if (iRet < 0)
    {
        mysql.Error(sError);
        cout << "exec sql failed:" << mysql.Error() << ":" << sError << endl;
    }

    // 创建一张新表A
    sql = "create table A(id int not null default 0);";
    cout << sql << endl;
    iRet = mysql.Exec(sql);
    if (iRet < 0)
    {
        mysql.Error(sError);
        cout << "exec sql failed:" << mysql.Error() << ":" << sError << endl;
    }

    // 向表A中插入100条数据
    int iSqlLen = 0;
    char sSql[256];
    for (int i = 0; i < 100; i++)
    {
        iSqlLen = snprintf(sSql, 256, "insert into A(id) values(%u)", i);
        cout << sSql << endl;
        mysql.Exec(sSql, iSqlLen);
    }

    // 从表A中查询全部数据，并打印
    sql = "select id from A";
    cout << sql << endl;
    bool bHasValue = mysql.Select(sql);
    if (bHasValue == false)
    {
        cout << sql << " has no record" << endl;
    }

    uint32_t uiResult = 0;
    while (mysql.NextRow())
    {
        mysql.Value(0, uiResult);
        cout << uiResult << endl;
    }

    // 断开连接
    mysql.Disconnect();
}

void TestJson()
{
    string str = "";

    Json::Value root;
    root["key"] = Json::Value("value");
    UBJsonPack(str, root, true);
    cout << "json:" << str << endl;

    root.clear();
    UBJsonUnpack(root, str);

    cout << root["key"] << endl;
}

void TestJson2()
{
    string str = "{}";

    Json::Value root;
    UBJsonPack(str, root, true);

    Json::Value &v = root["key"];
    if (root["key"].isNull())
    {
        cout << "json has no key" << endl;
        return;
    }

    if (root["key"]["key2"].isNull())
    {
        cout << "json has no key.key2" << endl;
        return;
    }

    int x = root["key"]["key2"].asUInt();

    cout << "All Ok:" << x << endl;
    return;
}

void TestUBBuffer()
{
    string a = "aaaaaaaaaa";
    string b = "bbbbbbbbbb";
    string c = "cccccccccc";

    UBBuffer buffer(2048);
    buffer.AppendData(a);

    string str(buffer.Data(), buffer.DataLength());
    cout << "a only:\t" << str << endl;

    buffer.AppendData(b);
    str.assign(buffer.Data(), buffer.DataLength());
    cout << "a & b:\t" << str << endl;

    buffer.RemoveData(a.length());
    str.assign(buffer.Data(), buffer.DataLength());
    cout << "b only:\t" << str << endl;

    buffer.AppendData(c);
    str.assign(buffer.Data(), buffer.DataLength());
    cout << "b & c:\t" << str << endl;

    buffer.RemoveData(b.length());
    str.assign(buffer.Data(), buffer.DataLength());
    cout << "c only:\t" << str << endl;

    buffer.RemoveData(c.length());
    str.assign(buffer.Data(), buffer.DataLength());
    cout << "nothing left:\t" << str << endl;

    UBBuffer buffer2(2048);
    buffer2.AppendData(a);
    buffer2.AppendData(b);
    buffer2.AppendData(c);
    buffer2.Swap(&buffer);
    str.assign(buffer.Data(), buffer.DataLength());
    cout << "after swap(a & b & c):" << str << endl;

    buffer.Clear();
    str.assign(buffer.Data(), buffer.DataLength());
    cout << "after clear():" << str << endl;
}

class A
{
public:
    A(){};
    virtual ~A() { cout << "~A()" << endl; };

public:
    int a1 = 1;
    int a2 = 2;
};

class B
{
public:
    B(){};
    virtual ~B() { cout << "~B()" << endl; };

public:
    int b1 = 3;
    int b2 = 4;
};

class C : public A, public B
{
public:
    C(){};
    ~C() { cout << "~C()" << endl; };

public:
    int c1 = 5;
    int c2 = 6;
};

void TestInherit()
{
    {C c;
        A *a = &c;
        cout << a->a1 << endl;
    }
    {
        C *c = new C;
        A *a = c;
        cout << "begin delete a" << endl;
        delete a;
        cout << "end delete a" << endl;
    }
}

int main()
{
    //	TestMysql();
    //	TestJson();
    //	TestJson2();
    //	TestUBBuffer();
    //  TestInherit();


    return 0;
}
