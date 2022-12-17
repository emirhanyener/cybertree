#include <iostream>
#include <fstream>
#include <string>
// #include "lexeme_token_list/linkedlist.cpp"
#include "grammar_node_data.c"
#include "grammar_node.c"
#include "grammar_list.c"
using namespace std;

bool isKeyword(string);
bool isOperator(string);
bool isSymbol(string);
bool isInteger(string);

// linkedlist * lexeme_token_list = new linkedlist();
grammar_list * grammar = NULL;

int main(int argc, char **argv)
{
  grammar = (struct grammar_list *) malloc (sizeof(struct grammar_list));
  cout << "open success" << endl;
  //grammar
  grammarListPush(grammar, createGrammarNodeData((char *)"<start>", (char *)"<exprlines>"));
  grammarListPush(grammar, createGrammarNodeData((char *)"<start>", (char *)"<start> <start>"));
  grammarListPush(grammar, createGrammarNodeData((char *)"<exprlines>", (char *)"<exprlines> <exprlines>"));
  grammarListPush(grammar, createGrammarNodeData((char *)"<exprlines>", (char *)"<exprline>"));
  grammarListPush(grammar, createGrammarNodeData((char *)"<exprline>", (char *)"<expr> ."));
  grammarListPush(grammar, createGrammarNodeData((char *)"<expr>", (char *)"<expr> integer times"));
  grammarListPush(grammar, createGrammarNodeData((char *)"<expr>", (char *)"<printexpr>"));
  grammarListPush(grammar, createGrammarNodeData((char *)"<printexpr>", (char *)"print <stringexpr>"));
  grammarListPush(grammar, createGrammarNodeData((char *)"<printexpr>", (char *)"print <mathexpr>"));
  grammarListPush(grammar, createGrammarNodeData((char *)"<printexpr>", (char *)"<printexpr> <string>"));
  grammarListPush(grammar, createGrammarNodeData((char *)"<string>", (char *)"<string> <string>"));
  grammarListPush(grammar, createGrammarNodeData((char *)"<string>", (char *)"id"));
  grammarListPush(grammar, createGrammarNodeData((char *)"<stringexpr>", (char *)"\" <string> \""));

  grammarListPush(grammar, createGrammarNodeData((char *)"<mathexpr>", (char *)"( <math> )"));

  grammarListPush(grammar, createGrammarNodeData((char *)"<math>", (char *)"<math> + integer"));
  grammarListPush(grammar, createGrammarNodeData((char *)"<math>", (char *)"<math> - integer"));
  grammarListPush(grammar, createGrammarNodeData((char *)"<math>", (char *)"<math> * integer"));
  grammarListPush(grammar, createGrammarNodeData((char *)"<math>", (char *)"<math> / integer"));
  grammarListPush(grammar, createGrammarNodeData((char *)"<math>", (char *)"integer + integer"));
  grammarListPush(grammar, createGrammarNodeData((char *)"<math>", (char *)"integer - integer"));
  grammarListPush(grammar, createGrammarNodeData((char *)"<math>", (char *)"integer * integer"));
  grammarListPush(grammar, createGrammarNodeData((char *)"<math>", (char *)"integer / integer"));

  cout << "grammar success" << endl;
  if (string(argv[1]) == "grammar")
  {
    do
    {
      cout << "[" << grammar->next->data->nonTerminal << "::=" << grammar->next->data->terminal << "]" << endl;
    } while (grammarListNextNode(grammar));
    return 0;
  }

  // Lexical Analysis Start
  bool is_string = false;
  string all_text = "";
  string lexical_text = "";
  string text;
  string lex = "";
  string filename = argv[1] + string(".leaf");
  ifstream fileexist(filename);
  if (fileexist)
  {
    fileexist.close();
  }
  else
  {
    cout << "\"" << argv[1] << "\" file doesn't exist";
    return 0;
  }

  ifstream file(filename);
  cout << "file success" << endl;

  cout << endl
       << "[Lexical Analysis Started]";
  while (getline(file, text))
  {
    all_text += text;
    for (int i = 0; i <= text.length() - 1; i++)
    {
      if (text[i] == ' ' || text[i] == '.' || text[i] == '\n' || text[i] == 0 || text[i] == '\"' || text[i] == '\'' || text[i] == '(' || text[i] == ')')
      {
        if (lex != "")
        {
          if(is_string)
          {
            lexical_text += "id ";
          }
          else if (isKeyword(lex))
          {
            // lexeme_token_list->push(lex, "keyword");
            lexical_text += lex + " ";
          }
          else if (isInteger(lex))
          {
            // lexeme_token_list->push(lex, "integer");
            lexical_text += "integer ";
          }
          else if (isOperator(lex))
          {
            // lexeme_token_list->push(lex, "operator");
            lexical_text += lex + " ";
          }
          else if (isSymbol(lex))
          {
            // lexeme_token_list->push(lex, "symbol");
            lexical_text += lex + " ";
          }
          else
          {
            // lexeme_token_list->push(lex, "id");
            lexical_text += "id ";
          }
        }

        if (text[i] == '.')
        {
          // lexeme_token_list->push(".", ".");
          lexical_text += ". ";
        }
        else if (text[i] == '\"')
        {
          // lexeme_token_list->push("\"", "\"");
          lexical_text += "\" ";
          is_string = !is_string;
        }
        else if (text[i] == '\'')
        {
          // lexeme_token_list->push("\'", "\'");
          lexical_text += "\' ";
        }
        else if (text[i] == '(')
        {
          // lexeme_token_list->push("\'", "\'");
          lexical_text += "( ";
        }
        else if (text[i] == ')')
        {
          // lexeme_token_list->push("\'", "\'");
          lexical_text += ") ";
        }
        lex = "";
      }
      else
      {
        lex += text[i];
      }
    }
  }
  file.close();
  // lexeme_token_list->print();
  cout << endl;
  cout << lexical_text << endl;
  cout << "[Lexical Analysis Completed]" << endl;
  all_text = lexical_text;

  // Lexical Analysis End
  ////////////////////////////////////////////////////////////////////////////
  // Syntax Analysis Start

  cout << endl
       << "[Syntax Analysis Started]";
  // shift reduce
  int right = 0;
  int left = 0;

  while (right < all_text.length())
  {
    cout << endl
         << "[Stack=$" << all_text.substr(0, right) << "]";
    bool control = true;
    for (int left = 0; left < right; left++)
    {
      do
      {
        if (grammar->next->data->terminal == all_text.substr(left, right - left))
        {
          cout << endl
               << "*Reduce = " << grammar->next->data->nonTerminal << " <-- " << grammar->next->data->terminal << endl;
          cout << "*New Text = " << all_text.substr(0, left) + grammar->next->data->nonTerminal + all_text.substr(right, all_text.length() - right) << endl;
          all_text = all_text.substr(0, left) + grammar->next->data->nonTerminal + all_text.substr(right, all_text.length() - right);
          control = false;
          break;
        }
      } while (grammarListNextNode(grammar));
      grammarListFirstNode(grammar);
      if (!control)
      {
        break;
      }
    }
    if (control)
    {
      right++;
    }
    else
    {
      right = 0;
      control = true;
    }
  }

  if (all_text == "<start> ")
    cout << endl
         << "[s][Syntax Analysis Success]" << endl;
  else
    cout << endl
         << "[f][Syntax Error]" << endl;

  // Syntax Analysis End

  /*
    string cppfilename = argv[1] + string(".cpp");
    ofstream outputfile(cppfilename);
    outputfile << "#include <iostream>\nusing namespace std;\nint main(){\nreturn 0;\n}";
    outputfile.close();
  */
  return 0;
}

bool isKeyword(string lex)
{
  if (
      lex == "if" ||
      lex == "else" ||
      lex == "print" ||
      lex == "assign" ||
      lex == "times" ||
      lex == "variable")
  {
    return true;
  }
  return false;
}
bool isOperator(string lex)
{
  if (
      lex[0] == '+' ||
      lex[0] == '-' ||
      lex[0] == '*' ||
      lex[0] == '/')
  {
    return true;
  }
  return false;
}
bool isSymbol(string lex)
{
  if (
      lex[0] == '\"' ||
      lex[0] == '\'' ||
      lex[0] == '(' ||
      lex[0] == ')' ||
      lex[0] == ',' ||
      lex[0] == '[' ||
      lex[0] == ']' ||
      lex[0] == '{' ||
      lex[0] == '}' ||
      lex[0] == '$' ||
      lex[0] == '%' ||
      lex[0] == '!' ||
      lex[0] == '?' ||
      lex[0] == '<' ||
      lex[0] == '>')
  {
    return true;
  }
  return false;
}
bool isInteger(string lex)
{
  for (int i = 0; i < lex.length(); i++)
  {
    if (lex[i] <= '0' || lex[i] >= '9')
    {
      return false;
    }
  }
  return true;
}