# Recursive-Descent-Parser-w-C++-


  The program is for the following EBNF grammar for a very simple programming language:

       program  ::=  S {statemt}
       statemt  ::=  assnmt | ifstmt | do | inout | progcall
       assnmt   ::=  ident ~ exprsn ;
       ifstmt   ::=  I comprsn @ {statemt} [% {statemt}] &
       do       ::=  D {statemt} U comprsn E
       inout    ::=  iosym ident {, ident } ;
       iosym    ::=  R | O
       progcall ::=  C program G
       comprsn  ::=  ( oprnd opratr oprnd )
       exprsn   ::=  factor {+ factor}
       factor   ::=  oprnd {* oprnd}
       oprnd    ::=  integer | ident | bool | ( exprsn )
       opratr   ::=  < | = | > | ! | ^ 
       ident    ::=  letter {char}
       char     ::=  letter | digit
       integer  ::=  digit {digit}
       letter   ::=  W | X | Y | Z
       digit    ::=  0 | 1
       bool     ::=  T | F

   The tokens are: S I D U E R O C G W X Y Z 0 1 T F ; ~ @ % & , ( ) + * < = > ! ^
   Nonterminals are shown as lowercase words.
   The following characters are NOT tokens (they are EBNF metasymbols):   | { } [ ]
   Note that parentheses are TOKENS, not EBNF metasymbols in this particular grammar.
   
   ---------------------------------------------------------------------------------------------
   Please note that you should run the program with -std=c++11 argunemt for the g++ in linux machine.
   The program requires C++11 features to run.
