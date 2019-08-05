#include <iostream>
#include<string>
#include<stack>
using std::cout;
using std::endl;
using std::stack;
using std::string;
class Solution
{   
    public:
        bool isValid(string s)
        {
            stack<char> result;
            for(auto it=s.begin();it!=s.end();++it)
            {
                if(*it=='('||*it=='['||*it=='{')
                {
                    result.push(*it);
                }

                else if(*it==')'&&result.top()=='(')
                {
                    result.pop();
                }
                else if(*it==']'&&result.top()=='[')
                {
                    result.pop();
                }
                else if(*it=='}'&&result.top()=='{')
                {
                    result.pop();
                }
            }
            if(result.empty()){cout<<"valid success"<<endl;return true;}
            else {cout<<"valid false"<<endl;return false;}
        }
};

int main()
{
    Solution v;
    v.isValid("([)dasd][dasd]sda");
    
    return 0;
}

