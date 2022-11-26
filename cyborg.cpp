#include <iostream>
#include <fstream>
#include <string>
using namespace std;
  
bool isKeyword(string);

int main(int argc, char** argv)
{
  string text;
  string lex = "";
  ifstream file("program.cy");
  while (getline (file, text)) {
    for(int i = 0; i <= text.length(); i++){
      if(text[i] != ' ' && text[i] != '.'){
        lex+=text[i];
      }else{
        if(isKeyword(lex))
          cout << lex << " is a keyword" << "\n";
        else
          cout << lex << " is not a keyword" << "\n";

        lex = "";
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