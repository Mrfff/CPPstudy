#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<ostream>
#include<map>
#include<set>
#include<sstream>
#include<algorithm>
#include <utility>
#include<memory>
#include <stdexcept>
using std::runtime_error;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::map;
using std::multimap;
using std::pair;
using std::set;
class QueryResult;
class TextQuery
{
public:
    using line_no =vector<string>::size_type;
    TextQuery (ifstream&);//输入文件名
    QueryResult query(const string &)const;
private:
    std::shared_ptr<vector<string>> file;
    map<string , std::shared_ptr<set<line_no>>> wm;
};
class QueryResult
{
friend std::ostream & print(std::ostream &,const QueryResult&);
public:
    typedef  vector<string>::size_type line_no;
    typedef set<line_no>::const_iterator line_it;
    QueryResult(string s,std::shared_ptr <set<line_no>> p,std::shared_ptr<vector<string>> f)
        :sought(s)
        ,lines(p)
        ,file(f){}
    line_it begin(){return lines->begin();}
    line_it end(){return lines->end();}
    std::shared_ptr<vector<string>> get_file(){ return file; }
private:
    string sought;
    std::shared_ptr<set<line_no>> lines;
    std::shared_ptr<vector<string>> file;
};
std::ostream&print(std::ostream&,const QueryResult&);
class Query_base//通用基类
{
friend class Query;
protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base()=default;
private:
    virtual QueryResult eval(const TextQuery&) const =0;
    virtual string rep()const =0;
};
class Query//实现的接口
{
    friend Query operator ~(const Query&);
    friend Query operator |(const Query&,const Query&);
    friend Query operator &(const Query&,const Query&);
public:
    Query(const string&);
    //接口函数，调用基类Query_base
    QueryResult eval(const TextQuery&t)const{ return _q->eval(t);}
    string rep()const{return _q->rep();}
private:
    Query(std::shared_ptr<Query_base> query)
    :_q(query){};
    std::shared_ptr<Query_base> _q;//将基类的成员给_q
};
#if 1
std::ostream& operator<<(std::ostream &os,const Query &query)
{
    return os<<query.rep();
}
#endif
//以下是Query的派生类

//查找给定的单词s
class WordQuery
    :public Query_base 
{
friend class Query;//使用接口函数
private:
    WordQuery(const string &s)
    :_queryWord(s){}
    QueryResult eval(const TextQuery &t)const{return t.query(_queryWord);}
    string rep()const{return _queryWord;}
    string _queryWord;//查找的单词；

};
inline Query::Query(const string &s):_q(new WordQuery(s)){}
class NotQuery
:public Query_base
{   
    friend Query operator~(const Query &);    
    NotQuery(const Query &q):query(q){}
    string rep()const {return "~("+query.rep()+")";}
    QueryResult eval(const TextQuery&)const;
    Query query;
};
inline Query operator~(const Query &p)
{
    return std::shared_ptr<Query_base>(new NotQuery(p));
}

class BinaryQuery:public Query_base
{
protected:
    BinaryQuery(const Query &l,const Query &r,string s)
    :lhs(l)
    ,rhs(r)
    ,opSym(s){}

    string rep()const 
    {
        return "("+lhs.rep()+" "
            +opSym+" "+rhs.rep()+")";
    }
Query lhs,rhs;
string opSym;
};//没有定义eval故还是抽象类

class AndQuery:public BinaryQuery
{
    friend Query operator&(const Query&,const Query&);
private:
    AndQuery(const Query&left,const Query&right)
        :BinaryQuery(left,right,"&"){}
    QueryResult eval(const TextQuery&)const;

};
inline Query operator&(const Query&lhs,const Query&rhs)
{
    return std::shared_ptr<Query_base> (new AndQuery(lhs,rhs));
}

class OrQuery:public BinaryQuery
{
    friend Query operator |(const Query&,const Query&);
private:
    OrQuery(const Query&left,const Query&right):BinaryQuery(left,right,"|"){}
    QueryResult eval(const TextQuery &)const;
};
inline Query operator|(const Query&lhs,const Query&rhs)
{
    return std::shared_ptr<Query_base> (new OrQuery(lhs,rhs));
}

//ifstream& open_file(ifstream&,const string&);
TextQuery get_file(int,char**);
std::ostream &print(std::ostream&,const QueryResult&);

//一下是各个类的实现
TextQuery get_file(int argc,char**argv)
{
    ifstream infile;
    if(argc==2)
        infile.open(argv[1]);
    if(!infile)
    {
        throw runtime_error("No input file~");
    }
    return TextQuery(infile);
}

TextQuery::TextQuery(ifstream &is)
    :file(new vector<string>)
{
    string text;
    while(getline(is,text))
    {
        file->push_back(text);
        int n=file->size()-1;//获取行号
        std::istringstream line(text);
        string word;
        while(line>>word)
        {
            auto &lines=wm[word];
            if(!lines)//第一次遇到这个单词
            {
                lines.reset(new set<line_no>);
                lines->insert(n);
            }
        }
    }
}
//TextQuery的实现
  
QueryResult TextQuery::query(const string &sought)const
{
    static std::shared_ptr<set<line_no> > nodata(new set<line_no>);//未找到就返回一个空set；
    auto loc=wm.find(sought);
    if(loc==wm.end())
    
    {
        return QueryResult(sought,nodata,file);
    }
    else return QueryResult(sought,loc->second,file);
}
//TextQuery::query的实现

std::ostream &print(std::ostream&os,const QueryResult &qr)
{
    os<<qr.sought<<"occurs"<<qr.lines->size()<<" "
        <<"time"<<endl;
    for(auto num=qr.lines->begin();num!=qr.lines->end();++num)
    {
        os<<"\t(line"<<*num+1<<")"<<*(qr.file->begin()+*num)<<endl;
    }
    return os;
}

QueryResult OrQuery::eval(const TextQuery&text)const
{
    auto right=rhs.eval(text);
    auto left=lhs.eval(text);
    auto ret_line=std::make_shared<set<line_no>> (left.begin(),left.end());
    ret_line->insert(right.begin(),right.end());
    return QueryResult(rep(),ret_line,left.get_file());
}

QueryResult AndQuery::eval(const TextQuery&text)const
{
    auto left=lhs.eval(text);
    auto right=rhs.eval(text);
    auto ret_line=std::make_shared<set<line_no>>();
    set_intersection(left.begin(),left.end()
                     ,right.begin(),right.end()
                     ,inserter(*ret_line,ret_line->begin()));
    return QueryResult(rep(),ret_line,left.get_file());
}

QueryResult NotQuery::eval(const TextQuery&text)const
{
    auto result=query.eval(text);
    auto ret_line=std::make_shared<set<line_no>>();
    auto it=result.begin();
    auto sz=result.get_file()->size();
    for(size_t i=0;i!=sz;i++)
    {
        if(it==result.end()||*it==i)
        {
            ret_line->insert(i);
        }else if (it!=result.end())
        {
            ++it;
        }
    }
    return QueryResult(rep(),ret_line,result.get_file());
}

int main(int argc,char**argv)
{
    TextQuery file=get_file(argc,argv);
    Query q=Query("fiery")&Query("bird")|Query("wind");
    cout << "\nExecuting Query for: " << q << endl;
    const QueryResult results = q.eval(file); 
    print(cout, results);
    return 0;
}
