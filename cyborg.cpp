#include <iostream>
#include <fstream>
#include <string>
using namespace std;
  
bool isKeyword(string);
bool isOperator(string);
bool isInteger(string);

int main(int argc, char** argv)
{
  string text;
  string lex = "";
  ifstream file("program.cy");
  while (getline (file, text)) {
    for(int i = 0; i <= text.length() - 1; i++){
      if(text[i] != ' ' && text[i] != '.' && text[i] != '\n' && text[i] != 0){
        lex+=text[i];
      }else{
        if(isKeyword(lex))
          cout << "\"" << lex << "\"" << " is a keyword" << "\n";
        else if(isInteger(lex))
          cout << "\"" << lex << "\"" << " is a integer" << "\n";
        else if(isOperator(lex))
          cout << "\"" << lex << "\"" << " is a operator" << "\n";
        else
          cout << "\"" << lex << "\"" << " is a not identified" << "\n";

        lex = "";
      }
      if(text[i] == '.'){
        cout << "\".\" is a seperator" << "\n";
      }
    }
  }
  file.close();

  return 0;
}

bool isKeyword(string lex){
  if(
  lex=="if" || 
  lex=="else" || 
  lex=="print" || 
  lex=="assign" || 
  lex=="times" || 
  lex=="variable"
  ){
    return true;
  }
  return false;
}
bool isOperator(string lex){
  if(
  lex[0]=='+' || 
  lex[0]=='-' || 
  lex[0]=='*' || 
  lex[0]=='/'
  ){
    return true;
  }
  return false;
}
bool isInteger(string lex){
  for (int i = 0; i < lex.length(); i++) {
    if(lex[i] <= '0' || lex[i] >= '9'){
      return false;
    }
  }
  return true;
}
