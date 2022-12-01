#include <iostream>
#include <fstream>
#include <string>
#include "lexeme_token_list/linkedlist.cpp"
using namespace std;
  
bool isKeyword(string);
bool isOperator(string);
bool isInteger(string);

linkedlist * lexeme_token_list = new linkedlist();

int main(int argc, char** argv)
{
  string sentence = "";
  string text;
  string lex = "";
  string filename = argv[1] + string(".cy");
  ifstream fileexist(filename);
  if (fileexist) {
    fileexist.close();
  } else {
    cout << "\"" << argv[1] << "\" file doesn't exist";
    return 0;
  }
  
  ifstream file(filename);
  while (getline (file, text)) {
    for(int i = 0; i <= text.length() - 1; i++){
      if(text[i] != ' ' && text[i] != '.' && text[i] != '\n' && text[i] != 0){
        lex+=text[i];
      }else{
        if(isKeyword(lex)){
          lexeme_token_list->push(lex, "Keyword");
        }
        else if(isInteger(lex)){
          lexeme_token_list->push(lex, "Integer");
        }
        else if(isOperator(lex)){
          lexeme_token_list->push(lex, "Operator");
        }
        else{
          lexeme_token_list->push(lex, "Id");
        }

        lex = "";
      }
      if(text[i] == '.'){
        lexeme_token_list->push(lex, "Seperator");
      }
    }
  }
  file.close();
  lexeme_token_list->print();

  string cppfilename = argv[1] + string(".cpp");
  ofstream MyFile(cppfilename);
  MyFile << "#include <iostream>\nusing namespace std;\nint main(){\nreturn 0;\n}";

  MyFile.close();

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