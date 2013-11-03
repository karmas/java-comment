%{
#include "header.h"
%}


%token tok_variable
%token tok_static
%token tok_public
%token tok_private

%%

decl_list : method_decl_list

method_decl_list : method_decl
		 | method_decl method_decl_list

method_decl : method_decl_prefix var_name '(' param_list ')' '{'
    	{
	  //printf("decl: %d [ %s %s ]\n", ++decl_count, $1, $2);
	  writeComment($1, $2);
    	}
    	| error
	{
	  // parser calls yyerror to print error message
	}

method_decl_prefix : modifier type
		   {
		     $$ = $2;
		   }
		   | modifier tok_static type
		   {
		     $$ = $3;
		   }

modifier : tok_public | tok_private ;

type : tok_variable
     | tok_variable '[' ']'
     {
     }

param_list : param ;
	   | param ',' param_list ;
	   | ;

param : type var_name
      {
        addParam($1, $2);
      }

var_name : tok_variable ;

%%


int stringType(const char *s)
{
  // save string name
  yylval = strdup(s);
  if (!strcmp(s, "static")) return tok_static;
  if (!strcmp(s, "public")) return tok_public;
  if (!strcmp(s, "private")) return tok_private;
  return tok_variable;
}

int yylex()
{
  int c = 0;

  // skip blanks
  while ( (c=fgetc(infile)) && isspace(c) );
  ungetc(c, infile);

  // try to get a word
  const int buf_len = 100;
  char buf[buf_len];
  memset(buf, 0, buf_len);
  int buf_index = 0;
  while ( (c=fgetc(infile)) && isalnum(c) ) {
    buf[buf_index++] = c;
  }

  if (buf_index)
  {
    ungetc(c, infile);
    return stringType(buf);
  }

  // return single character if not word
  return c;
}
