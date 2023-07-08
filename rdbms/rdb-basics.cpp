// this file is the crux of this assignment and contains all the functions 

#include"rdb.h"
using namespace std;
#define pb push_back

// below are the functions of Record class
Record::Record(){
        attrptr.clear();
}

void Relation::setnrecs(){
nrecs++;
}

Record::Record(const Record & r){                // COPY CONSTRUCTOR
    for(auto u:r.attrptr){
        if((typeid(*u).name())==(typeid(integerAttribute).name())){
            integerAttribute* ptr=dynamic_cast<integerAttribute*>(u);
            Attr* a2=new integerAttribute(ptr->getval());
            attrptr.push_back(a2);
        }
        else if((typeid(*u).name())==(typeid(floatAttribute).name())){
            floatAttribute* ptr=dynamic_cast<floatAttribute*>(u);
            Attr* a2=new floatAttribute(ptr->getval());
            attrptr.push_back(a2);
        } 
        else if ((typeid(*u).name())==(typeid(stringAttribute).name())){
            stringAttribute* ptr=dynamic_cast<stringAttribute*>(u);
            Attr* a2=new stringAttribute(ptr->getval());
            attrptr.push_back(a2);
        }
    }

}
bool Record::operator==(const Record& right){
    int i=0;
    for(auto u:this->attrptr){
        if(*u!=*right.attrptr[i]) return false;
        i++;
    }
    return true;
}
vector<Attr*>& Record::getrecord(){
    return attrptr;
}


// below are the functions of relation class
int Relation::getnattr(){ return nattr;}
int Relation::getnrecs(){ return nrecs;}

Relation::Relation(vector<string> v,vector<int> v2):nattr((int)v.size()),nrecs(0) { 

    int i;
    for(i=0;i<(int)v.size();i++)
    {
        attrnames.pb(v[i]);
           attrinds.pb(v2[i]);  //mapping schema 0=int,1=float,2=string     /*******************check this line************/
    }
}

void Relation::addrecord( Record* r){
    if(r->attrptr.size()!=nattr) { cout<<"the record types don't match"<<endl;return;}
    recs.push_back(r);nrecs++;
}

 list <Record *>& Relation::getrecs(){
    return recs;
 }
 vector<string>& Relation:: getattrname(){
    return attrnames;
 }
vector<int>& Relation:: getattrinds(){
        return attrinds;
}




/************************************FUNCTIONS******************************/
Relation* Union(Relation * R1,Relation * R2){ // returns the union of two tables

    int flag=0;
    vector<string> v1;
    vector<int> v2;
    list<Record *> l1,l2;
    v2=R1->getattrinds();
    v1=R1->getattrname();
    l1=R1->getrecs();
    l2=R2->getrecs();
    Relation* unirel =new Relation(v1,v2);
    list<Record*>& l3 = unirel->getrecs();
    // l3=unirel->getrecs();
    for(auto u:l1)
    {
        flag=0;
        for(auto v:l2)
        {
            if(*u==*v) { flag=1;break; } 
        }
        if(!flag) {
            Record* r=new Record(*u);
            l3.push_back(r);
    }
}

    for(auto v:l2)
        {
            Record* r=new Record(*v);
             l3.push_back(r);
        }
    return unirel;

}

Relation* Difference(Relation * R1,Relation * R2){// return the difference of two tables



    int flag=0;
       vector<string> v1;
    vector<int> v2;
    list<Record *> l1,l2;
    v1=R1->getattrname();
    v2=R1->getattrinds();
    l1=R1->getrecs();
    l2=R2->getrecs();
    Relation* diffrel =new Relation(v1,v2);
    // l3=diffrel->getrecs();
    list<Record*>& l3 = diffrel->getrecs();

    for(auto u:l1)
    {
        flag=0;
        for(auto v:l2)
        {
            if(*u==*v) { flag=1;break; } 
        }
        if(!flag) {
            Record* r=new Record(*u);
            l3.push_back(r);
    }
}
    return diffrel;

}

Relation* Cartesianproduct(Relation*R1,Relation*R2){ // this returns the cartesian product of two tables

    int i=0;
    vector<string> v1,v3;
    vector<int> v2,v4;
    list<Record *> l1,l2;
    v1=R1->getattrname();
    v3=R2->getattrname();
    v2=R1->getattrinds();
    v4=R2->getattrinds();
    l1=R1->getrecs();
    l2=R2->getrecs();

    vector<string> vs(v1);
    vector<int> vi(v2); 
  
    for (i=0;i<v3.size();i++)
    {
            vs.push_back(v3[i]);
            vi.push_back(v4[i]);
    }
    Relation* cartrel =new Relation(vs,vi);
                // list<Record *>l3;
                // l3=cartrel->getrecs();
    list<Record*>& l3 = cartrel->getrecs();

    for ( auto u:l1)
    {
        for (auto v: l2)
        {
            Record* r=new Record(*u);

                vector<Attr*> vatr;
                vector<Attr*>& vatr2=r->getrecord();
                vatr=v->getrecord();
                 for(auto z:vatr)
                 {
                        if((typeid(*z).name())==(typeid(integerAttribute).name())){
                            integerAttribute* ptr=dynamic_cast<integerAttribute*>(z);
                            Attr* a2=new integerAttribute(ptr->getval());
                            vatr2.push_back(a2);
                        }
                        else if((typeid(*z).name())==(typeid(floatAttribute).name())){
                            floatAttribute* ptr=dynamic_cast<floatAttribute*>(z);
                            Attr* a2=new floatAttribute(ptr->getval());
                            vatr2.push_back(a2);
                        } 
                        else if ((typeid(*z).name())==(typeid(stringAttribute).name())){
                            stringAttribute* ptr=dynamic_cast<stringAttribute*>(z);
                            Attr* a2=new stringAttribute(ptr->getval());
                            vatr2.push_back(a2);
                        }
                }
 
                l3.push_back(r);

        }
        
    }
      return cartrel;
}



Relation* Projection(Relation*R1,list<string> projectattrs)
{// this gives the projection of a table basically it makes a new table whose colums are the subset of the input table
      vector<string> v1;
    vector<int> v2;
    list<Record *> l1;
    v1=R1->getattrname();
    v2=R1->getattrinds();
    l1=R1->getrecs();

    vector<string> vs,vs2;

    for(auto u:projectattrs)  vs.pb(u); 
    
    int i;map<int,int> m;
    
    vector<int> vattrin;
    
    for(i=0;i<v1.size();i++)
    {
        for(auto z:vs)
        {
            
            if(v1[i]==z) {vattrin.pb(v2[i]);vs2.push_back(z);m[i]=1;break;}
        }

    }
    Relation* projrel= new Relation(vs2,vattrin);
    list<Record*>& l3 = projrel->getrecs();


        for(auto u:l1)
    {

        Record* r=new Record;
                vector<Attr*> vatr;
                vatr=u->getrecord();
                vector<Attr*>& vatr2=r->getrecord();
             for(i=0;i<vatr.size();i++)
            {
                 if(m[i]){
                        Attr* x=vatr[i];
                          if((typeid(*x).name())==(typeid(integerAttribute).name())){
                            integerAttribute* ptr=dynamic_cast<integerAttribute*>(x);
                            Attr* a2=new integerAttribute(ptr->getval());
                            vatr2.push_back(a2);
                        }
                        else if((typeid(*x).name())==(typeid(floatAttribute).name())){
                            floatAttribute* ptr=dynamic_cast<floatAttribute*>(x);
                            Attr* a2=new floatAttribute(ptr->getval());
                            vatr2.push_back(a2);
                        } 
                        else if ((typeid(*x).name())==(typeid(stringAttribute).name())){
                            stringAttribute* ptr=dynamic_cast<stringAttribute*>(x);
                            Attr* a2=new stringAttribute(ptr->getval());
                            vatr2.push_back(a2);
                        }
                      }
        }
        // r->printRecord();
        l3.push_back(r);
    }
    return projrel;

}
// typedef struct DNFformula { 
//     list <list <tuple <string, char, Attr *> > > ops; 
// }DNFformula ;
Relation * Union (Relation * R1, DNFformula * f){ // this function is the implementation of dnf select

    vector<string>v1;
    vector<int> v2;
    v1=R1->getattrname();
    v2=R1->getattrinds();
    list<Record*>l1;
    l1=R1->getrecs();
    
    Relation* selrel=new Relation(v1,v2);
    list<Record*>& l3 = selrel->getrecs();


    int flag=0,i=0;
    
    for(auto u:l1)
    {
        vector<Attr*> vatr;
        vatr=u->getrecord();
        for(auto v:f->ops)
        {
            flag=1;

            for(auto z:v)
           {

                i=0;
                auto it=vatr.begin();
                while( v1[i]!=(get<0>(z)))  
                {
                    i++;
                    it++;
                }
                    if(get<1>(z)=='=')
                    {
                        if(!(**it==*(get<2>(z))))
                        {flag=0;break;}
                    }

                else if(get<1>(z)=='>')
                    {
                        if(!(**it>*(get<2>(z))))
                        {flag=0;break;}
                    }

                else if(get<1>(z)=='<')
                    {
                        if(!(**it<*(get<2>(z))))
                        {flag=0;break;}
                    }
            }

            if(flag==1) {l3.push_back(u);break;}
             
       }

    }
return selrel;

}

Relation* Difference(Relation*R1,string s1,string s2)
{ // this is rename function
vector<string>& v = R1->getattrname();
   auto it= find(v.begin(),v.end(),s1);
   *it=s2;
   return R1;
}

void Relation::printRelation()
{
    //auxilliary function to print a relation(table)
    for(auto col:attrnames){
        cout<<setw(width)<<left<<col;
    }
    cout<<endl;
    for(auto it = recs.begin(); it!=recs.end(); it++){
        (*it)->printRecord();
        cout<<endl;
    }

}

void Record::printRecord()
{
    //auxilliary function to print a record
    for(auto x:attrptr){
        cout<<setw(width)<<left;
        x->print();
    }
  
}

void Relation::addRecord_interactive()
{
    //function to add a record to an existing table
    string attr_types[]={"integer","floating-point","string"};
    Record* r=new Record;
    int int_temp;
    double float_temp;
    string string_temp;
    for(int i=0; i<nattr; i++){
        cout<<"Enter the value for the column '"<<attrnames[i]<<"' (of "<<attr_types[attrinds[i]]<<" data type): ";
        if(attrinds[i]==0){
            cin>>int_temp;
            Attr* a2=new integerAttribute(int_temp);
             r->attrptr.push_back(a2);

        }
        else if(attrinds[i]==1){
            cin>>float_temp;
            Attr* a2=new floatAttribute(float_temp);
            r->attrptr.push_back(a2);

        }
        else if(attrinds[i]==2){
            cin>>string_temp;
            Attr* a2=new stringAttribute(string_temp);
             r->attrptr.push_back(a2);  
        }
    }
    nrecs++;
    recs.push_back(r);
}

// Relation * naturaljoin(Relation * R1, Relation * R2, list<string> joinattr)
// {
//     Relation * temp1 = NULL;
//     Relation * temp2 = R2;  
//     int x=0;
//     for(auto u:joinattr)
//     {
//         temp1 = temp2;
//         temp2 = Difference(temp1, u, to_string(x++));
//         if(temp1!=R2) delete temp1;
//     }

//     Relation * cartrel = Cartesianproduct(R1, temp2);  
//     Attr *attr1, *attr2;   
//     DNFformula f;
//     x=0;   temp1=NULL;
//     Relation *P = cartrel;   
//     for(auto u:joinattr)
//     {   
    
//         f.ops.clear();

//         int i=0;
//         int pos1;  
//         for(auto v:R1->attrnames)
//         {
//             if(u==v) pos1 = i;
//             i++;
//         }

//         int pos2;
//         i=0;
//         for(auto v:R2->attrnames)
//         {
//             if(u==v) pos2 = i;
//             i++;
//         }


//         for(auto z:R1->recs)
//         {
//             attr1 = z->attrptr[pos1];

//             for(auto q:R2->recs)
//             {
//                 attr2 = q->attrptr[pos2];
            
//                 if(*attr1 == *attr2)
//                 {
//                     tuple<string,char,Attr*> t1 = make_tuple(u,'=',attr1);
//                     tuple<string,char,Attr*> t2 = make_tuple(to_string(x),'=',attr2);
//                     list<tuple<string,char,Attr*>> l = {t1, t2};
//                     f.ops.push_back(l);
//                     break;
//                 }
//             }
//         }

//         x++;
//         temp1 = P;
//         P = Union(temp1, &f);
//         if(temp1!=cartrel) delete temp1;
//     }

//     bool unique;


//     list<string> final_attr;


//     for(auto u:R1->attrnames)
//     {
//         unique=true;
//         for(auto v:joinattr)
//         {
//             if(u == v)
//             {
//                 unique=false;
//                 break;
//             }
//         }
//         if(unique) final_attr.push_back(u);
//     }

//     for(auto u:joinattr)
//     {
//         final_attr.push_back(u);
//     }

//     for(auto u:R2->attrnames)
//     {
//         unique=true;
//         for(auto v:joinattr)
//         {
//             if(u == v)
//             {
//                 unique = false;
//                 break;
//             }
//         }
//         if(unique) final_attr.push_back(u);
//     }

//     Relation * natjoirel = Projection(P, final_attr);

//     return natjoirel;
// } 