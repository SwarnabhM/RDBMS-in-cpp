// this code uses the property of inheritance of clases
#include"rdb.h"
using namespace std;



// below are the same functions for different datatypes that is integer float and string
    bool integerAttribute::operator==(const Attr & right) {return val==static_cast<const integerAttribute&>(right).val;}
    bool integerAttribute::operator!=(const Attr & right) {return val!=static_cast<const integerAttribute&>(right).val;}
    bool integerAttribute::operator>=(const Attr & right) {return val>=static_cast<const integerAttribute&>(right).val;} 
    bool integerAttribute::operator<=(const Attr & right) {return val<=static_cast<const integerAttribute&>(right).val;}
    bool integerAttribute::operator>(const Attr & right) {return val>static_cast<const integerAttribute&>(right).val;}
    bool integerAttribute::operator<(const Attr & right) {return val<static_cast<const integerAttribute&>(right).val;}
    void integerAttribute::print(){cout<<val;}
    int integerAttribute::getval(){return val;}




    bool floatAttribute::operator==(const Attr & right) {return val==static_cast<const floatAttribute&>(right).val;}
    bool floatAttribute::operator!=(const Attr & right) {return val!=static_cast<const floatAttribute&>(right).val;}
    bool floatAttribute::operator>=(const Attr & right) {return val>=static_cast<const floatAttribute&>(right).val;} 
    bool floatAttribute::operator<=(const Attr & right) {return val<=static_cast<const floatAttribute&>(right).val;}
    bool floatAttribute::operator>(const Attr & right) {return val>static_cast<const floatAttribute&>(right).val;}
    bool floatAttribute::operator<(const Attr & right) {return val<static_cast<const floatAttribute&>(right).val;}
      void floatAttribute::print(){cout<<val;}
      float floatAttribute::getval(){return val;}
      





    bool stringAttribute::operator==(const Attr & right) {return val==static_cast<const stringAttribute&>(right).val;}
    bool stringAttribute::operator!=(const Attr & right) {return val!=static_cast<const stringAttribute&>(right).val;}
    bool stringAttribute::operator>=(const Attr & right) {return val>=static_cast<const stringAttribute&>(right).val;} 
    bool stringAttribute::operator<=(const Attr & right) {return val<=static_cast<const stringAttribute&>(right).val;}
    bool stringAttribute::operator>(const Attr & right) {return val>static_cast<const stringAttribute&>(right).val;}
    bool stringAttribute::operator<(const Attr & right) {return val<static_cast<const stringAttribute&>(right).val;}
      void stringAttribute::print(){cout<<val;}
      string stringAttribute::getval(){return val;}