# CyberTree
## About
`cybertree` is a programming language like natural language. 

## Syntax
### Grammar (Backus-Naur Form)
```grammar
<start>      ::= <exprlines>
<start>      ::= <start> <start>
<exprlines>  ::= <exprlines> <exprlines>
<exprlines>  ::= <exprline>
<exprline>   ::= <expr> .
<expr>       ::= <expr> integer times
<expr>       ::= <printexpr>
<printexpr>  ::= print <stringexpr>
<printexpr>  ::= print <mathexpr>
<printexpr>  ::= <printexpr> <string>
<string>     ::= <string> <string>
<string>     ::= id
<stringexpr> ::= " <string> "
<mathexpr>   ::= ( <math> )
<math>       ::= <math> + integer
<math>       ::= <math> - integer
<math>       ::= <math> * integer
<math>       ::= <math> / integer
<math>       ::= integer + integer
<math>       ::= integer - integer
<math>       ::= integer * integer
<math>       ::= integer / integer
```

### Print expr
```cybertree
print "print hello world" 3 times.
print (3 + 4 - 2).
```

## Technologies
- C++
- C

## License
[MIT](LICENSE)