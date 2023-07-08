//this the header file and it contains all the required inbuilt libraries and the class definitions along with the function definitions

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <tuple>
#include <iomanip>
#include <map>
#include <algorithm>
using namespace std;
#define width 17

class Attr{
    public:
    virtual bool operator== (const Attr & right) = 0;
    virtual bool operator!= (const Attr & right) = 0;
    virtual bool operator< (const Attr & right) = 0;
    virtual bool operator<= (const Attr & right) = 0;
    virtual bool operator> (const Attr & right) = 0;
    virtual bool operator>= (const Attr & right) = 0;
    virtual void print()=0;
};
class Record{
    vector<Attr*> attrptr;    // public change to private if possible
    public: 

    Record();

    Record(const Record & r);
    bool operator==(const Record& right);
    void printRecord();
    vector<Attr*>& getrecord();
    friend class Relation;
};

class Relation{
    int nattr, nrecs; // number of attributes and records    //    public
    vector <string> attrnames; // schema
    vector <int> attrinds; // mapping schema to indices
    list <Record *> recs; // list of records
    int getnattr();
    int getnrecs();
    void setnrecs();
    public: 
    list <Record *>& getrecs();
    vector<string>& getattrname();
    vector<int>& getattrinds();

    Relation(vector<string> v,vector<int>v2);

    void addrecord( Record* r);
    void printRelation();
    void addRecord_interactive();
};

class integerAttribute:public Attr{
    int val;
    public:
    integerAttribute(int v=0):val(v){}
    bool operator==(const Attr& right);
    bool operator!=(const Attr& right);
    bool operator<(const Attr& right);
    bool operator<=(const Attr& right);
    bool operator>(const Attr& right);
    bool operator>=(const Attr& right);
    void print();
    int getval();
};

class floatAttribute:public Attr{
    float val;
    public:
    floatAttribute(float v=0.0):val(v){}
    bool operator==(const Attr& right);
    bool operator!=(const Attr& right);
    bool operator<(const Attr& right);
    bool operator<=(const Attr& right);
    bool operator>(const Attr& right);
    bool operator>=(const Attr& right);
    void print();
    float getval();
};

class stringAttribute:public Attr{
    string val;
    public:
    stringAttribute(string v=""):val(v){}
    bool operator==(const Attr& right);
    bool operator!=(const Attr& right);
    bool operator<(const Attr& right);
    bool operator<=(const Attr& right);
    bool operator>(const Attr& right);
    bool operator>=(const Attr& right);
    void print();
    string getval();
};

typedef struct DNFformula { 
    list <list <tuple <string, char, Attr *> > > ops; 
}DNFformula ;
Relation* Union(Relation * R1,Relation * R2);
Relation* Difference(Relation * R1,Relation * R2);
Relation* Cartesianproduct(Relation*R1,Relation*R2);
Relation* Projection(Relation*R1,list<string> projectattrs);
Relation * Union (Relation * R1, DNFformula * f);
Relation* Difference(Relation*R1,string s1,string s2);
Relation * naturaljoin(Relation * R1, Relation * R2, list<string> joinattr);