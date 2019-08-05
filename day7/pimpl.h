#pragma once

class Sumdata
{
    class SumdataImpl;
public:
    Sumdata(int x,int y) ;
    ~Sumdata() ;
    void printSumdata()const;
private:
SumdataImpl *_pimpl;

};

