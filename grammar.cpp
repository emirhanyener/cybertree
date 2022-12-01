#include <iostream>
#include <fstream>
#include <string>

class grammar{
    public:
    string grammars[13];

    grammar(){
        grammars[0] = "<start>:=<exprlines>";

        grammars[1] = "<exprlines>:=<exprline><exprlines>";
        grammars[2] = "<exprlines>:=";

        grammars[3] = "<exprline>:=<expr>.";

        grammars[4] = "<expr>:=<printexpr>";

        grammars[5] = "<printexpr>:=print <string>";
        grammars[6] = "<printexpr>:=print <math>";

        grammars[7] = "<string>:=<string> string";
        grammars[8] = "<string>:=string";

        grammars[9] = "<math>:=id+id";
        grammars[10] = "<math>:=id-id";
        grammars[11] = "<math>:=id*id";
        grammars[12] = "<math>:=id/id";
    }
}