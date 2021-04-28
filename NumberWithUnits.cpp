#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <cstdlib>
#include "NumberWithUnits.hpp" 
#include <vector>
constexpr double EPS=0.00001;
char Realchar;
using namespace std;
namespace ariel{
unordered_map<string,unordered_map<string,double>>NumberWithUnits::umap;
vector<string>NumberWithUnits::rcl;
char b;

NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& s){
    (this->number)-=(this->convert(s));
    return *this;
         
}

NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& s){
    (this->number)+=(this->convert(s));
    return *this;
          
    
}

NumberWithUnits NumberWithUnits::operator--(int dummy_flag_for_postfix_increment){
    NumberWithUnits  same  =*this;
    this->number-=1;
    return same;                
}

NumberWithUnits& NumberWithUnits::operator--(){
    this->number-=1;
    return *this;
}

NumberWithUnits NumberWithUnits::operator++(int dummy_flag_for_postfix_increment){
    NumberWithUnits same=*this;
    this->number+=1;
    return same;                
}

NumberWithUnits& NumberWithUnits::operator++(){
    this->number+=1;
    return *this;
}

bool NumberWithUnits::operator>(const NumberWithUnits& s)const{

    return this->number-this->convert(s)>EPS;}

bool NumberWithUnits::operator>=(const NumberWithUnits& s)  const {return (this->compare(s)>=0);}

bool NumberWithUnits::operator==(const NumberWithUnits& s)const{return (abs(this->compare(s)))<=EPS;}

bool NumberWithUnits::operator!=(const NumberWithUnits& s)const{return !(*this==s);}

bool NumberWithUnits::operator<(const NumberWithUnits& s)const{return!(*this>=s);}

bool NumberWithUnits::operator<=(const NumberWithUnits& s)const{return((this->compare(s))<=0);}

NumberWithUnits operator-(const NumberWithUnits& s1,const NumberWithUnits& other2){
return (NumberWithUnits(s1.number-s1.convert(other2),s1.word));
}

NumberWithUnits operator +(const NumberWithUnits& s1,const NumberWithUnits& other2){
return (NumberWithUnits(s1.number+s1.convert(other2),s1.word));
}

NumberWithUnits operator *(double num,const NumberWithUnits& word){return  NumberWithUnits(word.number*num,word.word);}

NumberWithUnits operator *(const NumberWithUnits& word,double num){return (num*word);}

ostream& operator<< (std::ostream& os, const NumberWithUnits & word){
    return (os<<word.number<<"["<<word.word<<"]");
}
static istream& checkChar(istream& input, char c) {
    input >> Realchar;
    if (!input) {return input;}
    if (Realchar!=c) {
        // failbit is for format error
        input.setstate(ios::failbit);
    }
    return input;
}

istream& operator>> (istream& input, NumberWithUnits& s) {
    double num = 0;
    string word;
    ios::pos_type start = input.tellg();
    if ((!(input >> num))||(!checkChar(input,'['))||(!(input >> word))) {
        auto error = input.rdstate(); // remember error state
        input.clear(); // clear error so seekg will work
        input.seekg(start); // rewind
        input.clear(error); // set b the error flag
    } else {
        if(word.at(word.length()-1)==']'){word=word.substr(0,word.length()-1);}
        else{checkChar(input,']');}
        if(NumberWithUnits::umap.find(word)==NumberWithUnits::umap.end()){throw out_of_range{"Units do not match"};}
        s.word = word;
        s.number = num;
    }

    return input;
}


}
