#include "header.h"

// globals
FILE *infile = NULL;
FILE *outfile = NULL;
int error_count = 0;
int decl_count = 0;
Param *params = NULL;
Param *vars = NULL;

int main(int argc, const char *argv[])
{
  if (argc < 2) {
    puts("PROG JAVA_FILE [OUT_FILE]");
    return 1;
  }

  if ( !(infile = fopen(argv[1], "r")) ) {
    puts("Unable to open java file");
    return 1;
  }

  if (argc == 3) {
    if ( !(outfile = fopen(argv[2], "w")) ) {
      puts("Unable to open out file");
      return 1;
    }
  }

  if (!outfile) outfile = stdout;

  yyparse();

  if (outfile != stdout) fclose(outfile);
  return 0;
}

void yyerror(const char *msg)
{
  //fprintf(stderr, "%s : %d [ not a declaration ]\n", msg, ++error_count);
}

void addParam(const char *type, const char *name)
{
  Param *param = (Param *)malloc(sizeof(Param));
  if (!param) {
    fprintf(stderr, "Unable to allocate memory for a parameter");
    exit(1);
  }

  param->type = type;
  param->name = name;
  param->next = NULL;

  if (!params) params = param;
  else {
    Param *p = params;
    while (p->next) p = p->next;
    p->next = param;
  }
  //printf("adding: %s, %s\n", type, name);
}

void clearParams()
{
  Param *param = params;
  Param *save = NULL;
  while (param) {
    save = param;
    param = param->next;
    //printf("freeing : %s\n", save->name);
    free((void *)save->name);
    free((void *)save->type);
    free(save);
  }
  params = NULL;
}

void writeComment(const char *mtype, const char *mname)
{
  ++decl_count;
  fprintf(outfile, "Javadoc Comment for: %s \n", mname);
  fprintf(outfile, "/**\n");
  fprintf(outfile, " * DESCRIPTION\n");
  /*
  if (params || strcmp(mtype, "void"))
    fprintf(outfile, " *\n");
    */

  Param *param = params;
  while (param) {
    fprintf(outfile, " * @param %s DESCRIPTION\n", param->name);
    param = param->next;
  }

  if (strcmp(mtype, "void")) {
    fprintf(outfile, " * @return DESCRIPTION\n");
  }

  Param *var = vars;
  while (var) {
    fprintf(outfile, " * @throws %s DESCRIPTION\n", var->name);
    var = var->next;
  }

  fprintf(outfile, " */\n\n");

  clearParams();
  clearVars();
  free((void *)mtype);
  free((void *)mname);
}

void addVar(const char *type, const char *name)
{
  Param *var = (Param *)malloc(sizeof(Param));
  if (!var) {
    fprintf(stderr, "Unable to allocate memory for a variable");
    exit(1);
  }

  var->type = type;
  var->name = name;
  var->next = vars;
  vars = var;
}

void clearVars()
{
  Param *var = vars;
  Param *save = NULL;
  while (var) {
    save = var;
    var = var->next;
    //printf("freeing : %s\n", save->name);
    free((void *)save->name);
    free((void *)save->type);
    free(save);
  }
  vars = NULL;
}
