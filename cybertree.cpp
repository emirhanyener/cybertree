#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "grammar_node_data.c"
#include "grammar_node.c"
#include "grammar_list.c"
#include "char_pointer_functions/append_charpointer.h"
#include "char_pointer_functions/sub_charpointer.h"
using namespace std;

bool isKeyword(char *);
bool isOperator(char *);
bool isSymbol(char *);
bool isInteger(char *);

grammar_list * grammar = NULL;

int main(int argc, char **argv)
{
  grammar = (struct grammar_list *) malloc (sizeof(struct grammar_list));
  grammar->first = NULL;
  grammar->next = NULL;
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

  printf("grammar success\n");
  if (string(argv[1]) == "grammar")
  {
    do
    {
      printf("[%s::=%s]\n", grammar->next->data->nonTerminal, grammar->next->data->terminal);
    } while (grammarListNextNode(grammar));
    return 0;
  }

  // Lexical Analysis Start
  bool is_string = false;
  char * lexical_text = "";
  char * lex = "";
  char * filename = "";
  filename = append(argv[1], ".leaf");

//////////////////////////////////////////////////////////////////////////////
  FILE* fptr;
  char ch;
	char * all_text = "";
  fptr = fopen("test.leaf", "r");
  if (NULL == fptr) {
      printf("file can't be opened \n");
      return 0;
  }
//////////////////////////////////////////////////////////////////////////////

  printf("file success\n");

  printf("\n[Lexical Analysis Started]");
  
  do {
      ch = fgetc(fptr);
      all_text = appendc(all_text, ch);
      if (ch == ' ' || ch == '.' || ch == '\n' || ch == 0 || ch == '\"' || ch == '\'' || ch == '(' || ch == ')')
      {
        if (lex != "")
        {
          if(is_string)
          {
            //lexical_text = lexical_text + "id ";
            lexical_text = append(lexical_text, "id ");
          }
          else if (isKeyword(lex))
          {
            // lexeme_token_list->push(lex, "keyword");
            //lexical_text += lex + " ";
            lexical_text = append(append(lexical_text, lex), " ");
          }
          else if (isInteger(lex))
          {
            // lexeme_token_list->push(lex, "integer");
            //lexical_text += "integer ";
            lexical_text = append(lexical_text, "integer ");
          }
          else if (isOperator(lex))
          {
            // lexeme_token_list->push(lex, "operator");
            //lexical_text += lex + " ";
            lexical_text = append(append(lexical_text, lex), " ");
          }
          else if (isSymbol(lex))
          {
            // lexeme_token_list->push(lex, "symbol");
            //lexical_text += lex + " ";
            lexical_text = append(append(lexical_text, lex), " ");
          }
          else
          {
            // lexeme_token_list->push(lex, "id");
            //lexical_text += "id ";
            lexical_text = append(lexical_text, "id ");
          }
        }

        if (ch == '.')
        {
          // lexeme_token_list->push(".", ".");
          //lexical_text += ". ";
          lexical_text = append(lexical_text, ". ");
        }
        else if (ch == '\"')
        {
          // lexeme_token_list->push("\"", "\"");
          //lexical_text += "\" ";
          lexical_text = append(lexical_text, "\" ");
          is_string = !is_string;
        }
        else if (ch == '\'')
        {
          // lexeme_token_list->push("\'", "\'");
          //lexical_text += "\' ";
          lexical_text = append(lexical_text, "\' ");
        }
        else if (ch == '(')
        {
          // lexeme_token_list->push("\'", "\'");
          //lexical_text += "( ";
          lexical_text = append(lexical_text, "( ");
        }
        else if (ch == ')')
        {
          // lexeme_token_list->push("\'", "\'");
          //lexical_text += ") ";
          lexical_text = append(lexical_text, ") ");
        }
        lex = "";
      }
      else
      {
        //lex += text[i];
        lex = appendc(lex, ch);
      }
    
  } while (ch != EOF);

  fclose(fptr);
  // lexeme_token_list->print();
  printf("\n%s\n", lexical_text);
  printf("[Lexical Analysis Completed]\n");
  all_text = lexical_text;

  // Lexical Analysis End
  ////////////////////////////////////////////////////////////////////////////
  // Syntax Analysis Start

  printf("\n[Syntax Analysis Started]");
  // shift reduce
  int right = 0;
  int left = 0;

  while (right < strlen(all_text))
  {
    printf("\n[Stack=$%s]", substr(all_text, right));
    bool control = true;
    for (int left = 0; left < right; left++)
    {
      do
      {
        if (strcmp(grammar->next->data->terminal, substrs(all_text, left,  right - left)) == 0)
        {
          all_text = append(substr(all_text, left), append(grammar->next->data->nonTerminal, substrs(all_text, right, strlen(all_text) - right)));
          printf("\n*Reduce = %s <-- %s\n", grammar->next->data->nonTerminal, grammar->next->data->terminal);
          printf("*New Text = %s\n", all_text);
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
    printf("\n[s][Syntax Analysis Success]\n");
  else
    printf("\n[f][Syntax Error]\n");

  // Syntax Analysis End

  /*
    string cppfilename = argv[1] + string(".cpp");
    ofstream outputfile(cppfilename);
    outputfile << "#include <iostream>\nusing namespace std;\nint main(){\nreturn 0;\n}";
    outputfile.close();
  */
  return 0;
}

bool isKeyword(char * lex)
{
  if (
      !strcmp(lex, "if") ||
      !strcmp(lex, "else") ||
      !strcmp(lex, "print") ||
      !strcmp(lex, "assign") ||
      !strcmp(lex, "times") ||
      !strcmp(lex, "variable"))
  {
    return true;
  }
  return false;
}
bool isOperator(char * lex)
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
bool isSymbol(char * lex)
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
bool isInteger(char * lex)
{
  for (int i = 0; i < strlen(lex); i++)
  {
    if (lex[i] <= '0' || lex[i] >= '9')
    {
      return false;
    }
  }
  return true;
}