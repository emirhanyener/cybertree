#include <iostream>
#include <fstream>
#include <string>
//#include "lexeme_token_list/linkedlist.cpp"
#include "linkedlist.cpp"
#include "grammar.cpp"
using namespace std;
  
bool isKeyword(string);
bool isOperator(string);
bool isSymbol(string);
bool isInteger(string);

//linkedlist * lexeme_token_list = new linkedlist();
linkedlist<grammar *> * grammars = new linkedlist<grammar *>();

int main(int argc, char** argv)
{
  grammars->push(new grammar("<start>", "<exprlines>"));
  grammars->push(new grammar("<exprlines>", "<exprlines> <exprlines>"));
  grammars->push(new grammar("<exprlines>", "<exprline>"));
  grammars->push(new grammar("<exprline>", "<expr> ."));
  grammars->push(new grammar("<expr>", "<printexpr>"));
  grammars->push(new grammar("<printexpr>", "print <stringexpr>"));
  grammars->push(new grammar("<printexpr>", "print <math>"));
  grammars->push(new grammar("<stringexpr>", "\" <string> \""));
  grammars->push(new grammar("<string>", "<string> <string>"));
  grammars->push(new grammar("<string>", "id"));
  grammars->push(new grammar("<math>", "integer + integer"));
  grammars->push(new grammar("<math>", "integer - integer"));
  grammars->push(new grammar("<math>", "integer * integer"));
  grammars->push(new grammar("<math>", "integer / integer"));
  grammars->push(new grammar("<printexpr>", "<printexpr> <string>"));
  if(string(argv[1]) == "grammar"){
    grammars->firstNode();
    while(grammars->nextNode()){
        cout << "[" << grammars->next->data->nonTerminal << "::=" << grammars->next->data->terminal << "]" << endl;
    }
    return 0;
  }
        

  //Lexical Analysis Start
  string all_text = "";
  string lexical_text = "";
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
  
  cout << endl << "[Lexical Analysis Started]";
  while (getline (file, text)) {
    all_text += text;
    for(int i = 0; i <= text.length() - 1; i++){
      if(text[i] == ' ' || text[i] == '.' || text[i] == '\n' || text[i] == 0 || text[i] == '\"' || text[i] == '\''){
        if(lex != ""){
          if(isKeyword(lex)){
            //lexeme_token_list->push(lex, "keyword");
            lexical_text += lex + " ";
          }
          else if(isInteger(lex)){
            //lexeme_token_list->push(lex, "integer");
            lexical_text += "integer ";
          }
          else if(isOperator(lex)){
            //lexeme_token_list->push(lex, "operator");
            lexical_text += lex + " ";
          }
          else if(isSymbol(lex)){
            //lexeme_token_list->push(lex, "symbol");
            lexical_text += lex + " ";
          }
          else{
            //lexeme_token_list->push(lex, "id");
            lexical_text += "id ";
          }
        }
        
        if(text[i] == '.'){
          //lexeme_token_list->push(".", ".");
          lexical_text += ". ";
        }
        if(text[i] == '\"'){
          //lexeme_token_list->push("\"", "\"");
          lexical_text += "\" ";
        }
        if(text[i] == '\''){
          //lexeme_token_list->push("\'", "\'");
          lexical_text += "\' ";
        }
        lex = "";
      } else {
        lex += text[i];
      }
    }
  }
  file.close();
  //lexeme_token_list->print();
  cout << endl;
  cout << lexical_text << endl;
  cout << "[Lexical Analysis Completed]" << endl;
  all_text = lexical_text;

  //Lexical Analysis End
  ////////////////////////////////////////////////////////////////////////////
  //Syntax Analysis Start
  
  cout << endl << "[Syntax Analysis Started]";
  //shift reduce
  int right = 0;
  int left = 0;
  
  while (right < all_text.length())
  {
    cout << endl << "[stack=$" << all_text.substr(0, right) << "]";
    bool control = true;
    for (int left = 0; left < right; left++)
    {
      while(grammars->nextNode()){
        if(grammars->next->data->terminal == all_text.substr(left, right - left)){
          cout << endl <<  "*reduce = " << grammars->next->data->nonTerminal << "<--" << grammars->next->data->terminal << endl;
          cout << "*new text = " << all_text.substr(0, left) + grammars->next->data->nonTerminal + all_text.substr(right, all_text.length() - right) << endl;
          all_text = all_text.substr(0, left) + grammars->next->data->nonTerminal + all_text.substr(right, all_text.length() - right);
          control = false;
          break;
        }
      }
      grammars->firstNode();
      if(!control){
        break;
      }
    }
    if(control){
      right++;
    } else {
      right = 0;
      control = true;
    }
  }

  if(all_text == "<start> ")
    cout << endl << "[s][Syntax Analysis Completed]" << endl;
  else
    cout << endl << "[f][Syntax Error]" << endl;

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
bool isSymbol(string lex){
  if(
  lex[0]=='\"' || 
  lex[0]=='\'' || 
  lex[0]=='(' || 
  lex[0]==')' ||
  lex[0]==',' || 
  lex[0]=='[' || 
  lex[0]==']' || 
  lex[0]=='{' || 
  lex[0]=='}' || 
  lex[0]=='$' || 
  lex[0]=='%' || 
  lex[0]=='!' || 
  lex[0]=='?' || 
  lex[0]=='<' || 
  lex[0]=='>'
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