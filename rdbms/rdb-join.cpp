// this code calculates the natural join of two tables 
// for details on natural join refer https://en.wikipedia.org/wiki/Relational_algebra

#include "rdb.h"
Relation * naturaljoin(Relation * R1, Relation * R2, list<string> joinattr)
{

    vector<string> v1;
    v1=R1->getattrname();
    vector<string> v3;
    vector<int> v2,v4;
    v2=R1->getattrinds();
    v4=R2->getattrinds();

    v3=R2->getattrname();
    list<Record*> l1;
    l1=R1->getrecs();
    list<Record*> l2;
    l2=R2->getrecs();

    Relation * temp1 = NULL;
    Relation * temp2 = new Relation(v3, v4);  
    for(auto rec2:l2){
        temp2->addrecord(new Record(*rec2));
    }
    int x=0;

    for(auto u:joinattr)
    {
    
        temp2 = Difference(temp2, u, to_string(x++));
        
    }
    Relation * cartrel = Cartesianproduct(R1, temp2);  
    Attr *attr1, *attr2;   
    DNFformula f;
    x=0;   temp1=NULL;
    Relation *P = cartrel;   
    for(auto u:joinattr)
    {   
    
        f.ops.clear();

        int i=0;
        int pos1;  
        for(auto v:v1)
        {
            if(u==v) pos1 = i;
            i++;
        }

        int pos2;
        i=0;
        for(auto v:v3)
        {
            if(u==v) pos2 = i;
            i++;
        }


        for(auto z:l1)
        {
             vector<Attr*>vatr1;
            vatr1=z->getrecord();
            attr1 = vatr1[pos1];

            for(auto q:l2)
            {
                 vector<Attr*>vatr2;
                vatr2=q->getrecord(); 
                attr2 = vatr2[pos2];
            
                if(*attr1 == *attr2)
                {
                    tuple<string,char,Attr*> t1 = make_tuple(u,'=',attr1);
                    tuple<string,char,Attr*> t2 = make_tuple(to_string(x),'=',attr2);
                    list<tuple<string,char,Attr*>> l = {t1, t2};
                    f.ops.push_back(l);
                    break;
                }
            }
        }

        x++;
        temp1 = P;
        P = Union(temp1, &f);
        if(temp1!=cartrel) delete temp1;
    }

    bool unique;


    list<string> final_attr;


    for(auto u:v1)
    {
        unique=true;
        for(auto v:joinattr)
        {
            if(u == v)
            {
                unique=false;
                break;
            }
        }
        if(unique) final_attr.push_back(u);
    }

    for(auto u:joinattr)
    {
        final_attr.push_back(u);
    }

    for(auto u:v3)
    {
        unique=true;
        for(auto v:joinattr)
        {
            if(u == v)
            {
                unique = false;
                break;
            }
        }
        if(unique) final_attr.push_back(u);
    }

    Relation * natjoirel = Projection(P, final_attr);

    return natjoirel;
} 