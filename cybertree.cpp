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
  //Lexical Analysis Start
  string sentence = "";
  string text;
  string lex = "";
  string filename = argv[1] + string(".leaf");
  ifstream fileexist(filename);
  if (fileexist) {
    fileexist.close();
  } else {
    cout << "\"" << argv[1] << "\" file doesn't exist";
    return 0;
  }
  
  ifstream file(filename);
  
  cout << endl << "----------Lexical Analysis Started----------";
  while (getline (file, text)) {
    for(int i = 0; i <= text.length() - 1; i++){
      if(text[i] != ' ' && text[i] != '.' && text[i] != '\n' && text[i] != 0){
        lex+=text[i];
      }else{
        if(isKeyword(lex)){
          lexeme_token_list->push(lex, "keyword");
        }
        else if(isInteger(lex)){
          lexeme_token_list->push(lex, "int");
        }
        else if(isOperator(lex)){
          lexeme_token_list->push(lex, "operator");
        }
        else{
          lexeme_token_list->push(lex, "id");
        }

        lex = "";
      }
      if(text[i] == '.'){
        lexeme_token_list->push(".", "seperator");
      }
    }
  }
  file.close();
  lexeme_token_list->print();
  cout << endl << "----------Lexical Analysis Completed----------" << endl;
  //Lexical Analysis End
  ////////////////////////////////////////////////////////////////////////////
  //Syntax Analysis Start

  //Syntax Analysis End

  /*
    string cppfilename = argv[1] + string(".cpp");
    ofstream outputfile(cppfilename);
    outputfile << "#include <iostream>\nusing namespace std;\nint main(){\nreturn 0;\n}";
    outputfile.close();
  */
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