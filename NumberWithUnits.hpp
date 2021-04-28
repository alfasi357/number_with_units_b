#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <unordered_map>
#include <vector>
namespace ariel{
    class NumberWithUnits{
        public:
            static std::vector<std::string>rcl;
            static std::unordered_map<std::string,std::unordered_map<std::string,double>>umap;
            double number;
            std::string word;
            NumberWithUnits(double num,std::string str){
            if(umap.find(str)==umap.end()){   throw std::out_of_range{"units doesn't match"};;}
            number=num;word=str;
            }

            static void read_units(std::ifstream& file){
                double n1;
                double n2;
                char els;
                std::string word1;
                std::string word2;             
                while(file>>n1>>word1>>els>>n2>>word2){
                    umap[word1][word2]=n2;
                    umap[word2][word1]=(1/n2);
                    umap[word1][word1]=1;
                    umap[word2][word2]=1;
                    if(!(count(rcl.begin(),rcl.end(),word1))){
                        rcl.push_back(word1);
                    }
                    if(!(count(rcl.begin(),rcl.end(),word2))){
                        rcl.push_back(word2);
                    }
                }
                for (auto k = rcl.begin(); k != rcl.end(); ++k){
                    for (auto i = rcl.begin(); i != rcl.end(); ++i){
                        for (auto j = rcl.begin(); j != rcl.end(); ++j){
                            if(umap[*i].find(*j)==umap[*i].end()){
                                if(umap[*i].find(*k)!=umap[*i].end()&&umap[*k].find(*j)!=umap[*k].end()){
                                    umap[*i][*j]=umap[*i][*k]*umap[*k][*j];
                                }
                            }
                        }
                    }
                }
            }

            double convert(const NumberWithUnits& s)const{
                if(umap[s.word].find(this->word)==umap[s.word].end()){throw std::out_of_range{"units doesn't match"};}
                return (umap[s.word][this->word]*s.number);
            }                
            
            double compare(const NumberWithUnits& s)const{
                if(umap[s.word].find(this->word)==umap[s.word].end()){throw std::out_of_range{"units doesn't match"};}
                double answer=(double)((this->number)-(umap[s.word][this->word]*s.number));
                return answer;
             }
            
            NumberWithUnits& operator-=(const NumberWithUnits& s);
            
            NumberWithUnits& operator+=(const NumberWithUnits& s);
                          
            NumberWithUnits operator--(int dummy_flag_for_postfix_increment);
            
            NumberWithUnits& operator--();
            
            NumberWithUnits& operator++();
            
            NumberWithUnits operator++(int dummy_flag_for_postfix_increment);            
            
            NumberWithUnits operator-(){return NumberWithUnits(-(this->number),this->word);}//implementation
           
            NumberWithUnits operator+(){return NumberWithUnits((this->number),this->word);} //implementation
            
            bool operator>(const NumberWithUnits& s)const;

            bool operator>= (const NumberWithUnits& s)const;

            bool operator<(const NumberWithUnits& s)const;

            bool operator<=(const NumberWithUnits& s)const;

            bool operator==(const NumberWithUnits& s)const;

            bool  operator!=(const NumberWithUnits& s)const;

            friend NumberWithUnits operator -(const NumberWithUnits& s1,const NumberWithUnits& s2);
            
            friend NumberWithUnits operator +(const NumberWithUnits& s1,const NumberWithUnits& s2);            

            friend NumberWithUnits operator *(const NumberWithUnits& word,double num);
           
            friend NumberWithUnits operator *(double num,const NumberWithUnits& word);
    
            friend std::ostream& operator<< (std::ostream& os, const NumberWithUnits & word);
            
            friend std::istream& operator>> (std::istream& input, NumberWithUnits& s);

    };
}