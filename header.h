#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define YYSTYPE const char *
int yylex();
int yyparse();
void yyerror(const char *msg);

extern int error_count;
extern int decl_count;
extern FILE *infile;

typedef struct Param {
  const char *type;
  const char *name;
  struct Param *next;
} Param; 

extern Param *params;
extern Param *vars;
void addParam(const char *type, const char *name);
void clearParams();
void writeComment(const char *mtype, const char *mname);
void addVar(const char *type, const char *name);
void clearVars();


#endif
