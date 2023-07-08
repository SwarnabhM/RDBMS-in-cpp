//implementation of the User interface for the assignment
#include "rdb.h"
Relation *create_relation()
{
    vector<string> attrname;
    vector<int> attrind;

    cout<<"Now, enter the schema for this new relation/table :-"<<endl;
    char counter='y';
    string attr_name;
    int attr_ind;
    while(counter=='y' || counter=='Y'){
        cout<<"Enter the name of the column: ";
        cin>>attr_name;
        cout<<"Choose among the following :"<<endl;
        cout<<"0. Integer data type"<<endl;
        cout<<"1. Floating-point data type"<<endl;
        cout<<"2. String data type"<<endl;
        cout<<"Enter the data type of this column: ";
        cin>>attr_ind;
        if(attr_ind==0 || attr_ind==1 || attr_ind==2){
            attrname.push_back(attr_name);
            attrind.push_back(attr_ind);
        }
        else{
            cout<<"Please enter a valid input."<<endl;
        }

        cout<<"Would you like to enter more columns for this relation/table? (y/n) : ";
        cin>>counter;
    }

    Relation *new_relation = new Relation(attrname, attrind);

    return new_relation;
}

void list_tables(const vector<pair<Relation *, string>>& relations){
    int item=1;
    for(auto rel:relations){
        cout<<item++<<". "<<rel.second<<endl;
        rel.first->printRelation();
        cout<<endl;
    }
}

void relational_algebra(vector<pair<Relation *,string>>& relations){
    cout<<"Available realational algebra operations:-"<<endl;
    cout<<"1. Union"<<endl;
    cout<<"2. Difference"<<endl;
    cout<<"3. Cartesian product"<<endl;
    cout<<"4. Projection"<<endl;
    cout<<"5. Selection"<<endl;
    cout<<"6. Rename an attribute in a relation"<<endl;
    cout<<"7. Natural join"<<endl;
    int op;
    cout<<"Choose one of the above operation: ";
    cin>>op;

    switch(op){
        case 1:{
            cout<<"The current existing tables in the database are:-"<<endl;
            list_tables(relations);
            int rel1,rel2;
            cout<<"Enter two table numbers from the above, whose union is to be taken: ";
            cin>>rel1>>rel2;
            string un_rel;
            cout<<"Enter a name for this new table: ";
            cin>>un_rel;
            Relation *union_rel = Union(relations[rel1-1].first,relations[rel2-1].first);
            if(union_rel==NULL){
                cout<<"The operation couldn't be performed."<<endl;
                break;
            }
            cout<<"The union of the two tables is:-"<<endl;
            union_rel->printRelation();
            relations.push_back(make_pair(union_rel,un_rel));
            break;
        }
        case 2:{
            cout<<"The current existing tables in the database are:-"<<endl;
            list_tables(relations);
            int rel1,rel2;
            cout<<"Enter two table numbers from the above, whose difference is to be taken: ";
            cin>>rel1>>rel2;
            string dif_rel;
            cout<<"Enter a name for this new table: ";
            cin>>dif_rel;
            Relation *difrel = Difference(relations[rel1-1].first,relations[rel2-1].first);
            if(difrel==NULL){
                cout<<"The operation couldn't be performed."<<endl;
                break;
            }
            cout<<"The difference of the two tables is:-"<<endl;
            difrel->printRelation();
            relations.push_back(make_pair(difrel,dif_rel));
            break;
        }
        case 3:{
            cout<<"The current existing tables in the database are:-"<<endl;
            list_tables(relations);
            int rel1,rel2;
            cout<<"Enter two table numbers from the above, whose cartesian product is to be taken: ";
            cin>>rel1>>rel2;
            string cp_rel;
            cout<<"Enter a name for this new table: ";
            cin>>cp_rel;
            Relation *cproduct_rel = Cartesianproduct(relations[rel1-1].first,relations[rel2-1].first);
            if(cproduct_rel==NULL){
                cout<<"The operation couldn't be performed."<<endl;
                break;
            }
            cout<<"The cartesian product of the two tables is:-"<<endl;
            cproduct_rel->printRelation();
            relations.push_back(make_pair(cproduct_rel,cp_rel));
            break;
        }
        case 4:
        {
            cout<<"The current existing tables in the database are:-"<<endl;
            list_tables(relations);
            int rel;
            cout<<"Enter the table no. whose projection is to be taken: ";
            cin>>rel;
            list<string> l;
            cout<<"The attributes in the selected table are:-"<<endl;
            int x=1;
            vector<string> tempstrv1;
            tempstrv1=relations[rel-1].first->getattrname();
            for(auto str:tempstrv1){
                cout<<x++<<". "<<str<<endl;
            }
            cout<<"Now enter the no. of attributes to be included in the projection: ";
            int attrn; 
            cin>>attrn;
            cout<<"Now enter "<<attrn<<" integers corresponding to the attributes' no. displayed above, to be included in the projection :-"<<endl;

            for(int i=0; i<attrn; i++){
                cin>>x;
                l.push_back(tempstrv1[x-1]);
            }
            
            string proj_rel;
            cout<<"Enter a name for this new table: ";
            cin>>proj_rel;
            Relation *proj = Projection(relations[rel-1].first, l);
            if(proj==NULL){
                cout<<"The operation couldn't be performed."<<endl;
                break;
            }
            cout<<"The required projection table is :-"<<endl;
            proj->printRelation();
            relations.push_back(make_pair(proj,proj_rel));
            break;
        }
        case 5:{
            cout<<"The current existing tables in the database are:-"<<endl;
            list_tables(relations);
            int rel;
            cout<<"Enter the table no. from which selection is to be performed: ";
            cin>>rel;
            cout<<"The attributes in this table are:-"<<endl;
            int x=1;
            vector<string> tempstrv1;
            tempstrv1=relations[rel-1].first->getattrname();
            vector<int> tempintv1;
            tempintv1=relations[rel-1].first->getattrinds();
 
            for(auto str: tempstrv1){
                cout<<x++<<". "<<str<<endl;
            }

            DNFformula conds;
            int disj;
            cout<<"Now, for the selection operation, enter the number of disjunctions: ";
            cin>>disj;
            for(int i=0; i<disj; i++){
                list<tuple<string,char,Attr*>> l;
                int conj;
                cout<<"Enter the number of conjunctions in disjunction "<<i+1<<": ";
                cin>>conj;
                for(int j=0; j<conj; j++){
                    int ind; char c;
                    cout<<"For the conjunction "<<j+1<<", enter the comparison in the form of <attribute_no.(int) comparator(char) value(to be compared to)>: ";
                    cin>>ind>>c;

                    if(tempintv1[ind-1]==0){
                        int val; 
                        cin>>val;
                        // vector<s> tempstrv;
            
                        l.push_back(make_tuple(tempstrv1[ind-1],c,new integerAttribute(val)));
                    }
                    else if(tempintv1[ind-1]==1){
                        double val; cin>>val;
                        l.push_back(make_tuple(tempstrv1[ind-1],c,new floatAttribute(val)));
                    }
                    else if(tempintv1[ind-1]==2){
                        string val; cin>>val;
                        l.push_back(make_tuple(tempstrv1[ind-1],c,new stringAttribute(val)));
                    }
                }
                conds.ops.push_back(l);
            }

            string selection;
            cout<<"Enter a name for this new table: ";
            cin>>selection;
            Relation *sel = Union(relations[rel-1].first, &conds);
            if(sel==NULL){
                cout<<"The operation couldn't be performed."<<endl;
                break;
            }
            cout<<"The required selection table is :-"<<endl;
            sel->printRelation();
            relations.push_back(make_pair(sel,selection));
            break;
        }
        case 6:{
            cout<<"The current existing tables in the database are:-"<<endl;
            list_tables(relations);
            int rel;
            cout<<"Enter the table no. whose attribute name is to be changed: ";
            cin>>rel;

            cout<<"The attributes in this table are:-"<<endl;
            int x=1;


            vector<string> tempstrv1;
            tempstrv1=relations[rel-1].first->getattrname();
            for(auto str:tempstrv1){
                cout<<x++<<". "<<str<<endl;
            }
            int ind;
            cout<<"Enter the attribute no., whose name is to be changed: ";
            cin>>ind;
            string new_name;
            cout<<"Enter the corresponding new attribute name: ";
            cin>>new_name;

            string renamed;
            cout<<"Enter a name for this new table: ";
            cin>>renamed;
            Relation *renamed_rel = Difference(relations[rel-1].first, tempstrv1[ind-1], new_name);
            if(renamed_rel==NULL){
                cout<<"The operation couldn't be performed."<<endl;
                break;
            }
            cout<<"The required table with renamed attribute:-"<<endl;
            renamed_rel->printRelation();
            relations.push_back(make_pair(renamed_rel, renamed));
            break;
        }
        case 7:{
            cout<<"The current existing tables in the database are:-"<<endl;
            list_tables(relations);
            int rel1,rel2;
            cout<<"Enter two tables no.s from above, whose natural join is to be taken: ";
            cin>>rel1>>rel2;

            list<string> cattr;
            vector<string> tempstrv1,tempstrv2;
            tempstrv1=relations[rel1-1].first->getattrname();
            tempstrv2=relations[rel2-1].first->getattrname();
            for(auto str1:tempstrv1)
            {
                for(auto str2:tempstrv2)
                {
                    if(str1 == str2){
                        cattr.push_back(str1);
                        break;
                    }
                }
            }

            string nj;
            cout<<"Enter a name for the new table: ";
            cin>>nj;
            Relation *natural_join = naturaljoin(relations[rel1-1].first, relations[rel2-1].first, cattr);
            if(natural_join==NULL){
                cout<<"The operation couldn't be performed."<<endl;
                break;
            }
            cout<<"The required natural join of the two table is:-"<<endl;
            natural_join->printRelation();
            relations.push_back(make_pair(natural_join,nj));

            break;
        }
        default:
            cout<<"Please enter a valid input."<<endl;
            break;
    }
}


int main(){

    cout<<"***RELATIONAL DATABASE MANAGEMENT SYSTEM***"<<endl;

    vector<pair<Relation *,string>> all_rels;


    char counter='y';
    int option;
    while(counter=='y' || counter=='Y'){
        cout<<"**************************"<<endl;
        cout<<"1. Create a new table"<<endl;
        cout<<"2. Delete an existing table"<<endl;
        cout<<"3. Add a record to an existing table"<<endl;
        cout<<"4. Print a table"<<endl;
        cout<<"5. Create a new table from the existing tables using relational algebra operations"<<endl;

        cout<<"Enter your choice: ";
        cin>>option;

        switch(option){
            case 1:{
                string rel_name;
                cout<<"Enter the name of this new table: ";
                cin>>rel_name;
                all_rels.push_back(make_pair(create_relation(),rel_name));
                cout<<"The new table has been created in the database."<<endl;
                break;
            }
            case 2:{
                cout<<"The current existing tables in the database are:-"<<endl;
                list_tables(all_rels);
                int del;
                cout<<"Enter the table no. to be deleted: ";
                cin>>del;
                if(del>all_rels.size()){
                    cout<<"Please enter a valid table number."<<endl;
                    break;
                }
                delete all_rels[del-1].first;
                all_rels.erase(all_rels.begin()+del-1);
                cout<<"The table has been deleted from the database."<<endl;
                break;
            }
            case 3:{
                cout<<"The current existing tables in the database are:-"<<endl;
                list_tables(all_rels);
                int add_rec;
                cout<<"Enter the table no. to which a record is to be added: ";
                cin>>add_rec;
                if(add_rec>all_rels.size()){
                    cout<<"Please enter a valid table number."<<endl;
                    break;
                }
                all_rels[add_rec-1].first->addRecord_interactive();
                cout<<"The record has been added to the table."<<endl;
                break;
            }
            case 4:{
                cout<<"The current existing table names in the database are:-"<<endl;
                int x=1;
                for(auto rel:all_rels){
                    cout<<x++<<". "<<rel.second<<endl;
                }
                int print_rec;
                cout<<"Enter the table no. to be printed: ";
                cin>>print_rec;
                if(print_rec>all_rels.size()){
                    cout<<"Please enter a valid table number."<<endl;
                    break;
                }
                all_rels[print_rec-1].first->printRelation();
                break;
            }
            case 5:{
                relational_algebra(all_rels);
                break;
            }
            default:
                cout<<"Please enter a valid input."<<endl;
                break;
        }

        cout<<"Would you like to counterinue? (y/n) : ";
        cin>>counter;

    }
    return 0;
}