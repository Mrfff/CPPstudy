#pragma once


namespace wd{
class Task
{
public:

    virtual
        void process()=0;
    virtual ~Task(){}
};



}//end of namespace
