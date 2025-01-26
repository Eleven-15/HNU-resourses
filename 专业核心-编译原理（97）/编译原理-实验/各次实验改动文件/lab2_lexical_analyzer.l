%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>

#include "syntax_tree.h"
#include "syntax_analyzer.h"

int files_count;
int lines;
int pos_start;
int pos_end;

void pass_node(char *text){
     yylval.node = new_syntax_tree_node(text);
}
%}

%%
 /* 运算 */
\+   {pos_start = pos_end; pos_end++; pass_node(yytext); return ADD;}
\-   {pos_start = pos_end; pos_end++; pass_node(yytext); return SUB;}
\*   {pos_start = pos_end; pos_end++; pass_node(yytext); return MUL;}
\/   {pos_start = pos_end; pos_end++; pass_node(yytext); return DIV;}
\<   {pos_start = pos_end; pos_end++; pass_node(yytext); return LT;}
"<=" {pos_start = pos_end; pos_end+=2; pass_node(yytext); return LTE;}
\>   {pos_start = pos_end; pos_end++; pass_node(yytext); return GT;}
">=" {pos_start = pos_end; pos_end+=2; pass_node(yytext); return GTE;}
"==" {pos_start = pos_end; pos_end+=2; pass_node(yytext); return EQ;}
"!=" {pos_start = pos_end; pos_end+=2; pass_node(yytext); return NEQ;}
\=   {pos_start = pos_end; pos_end++; pass_node(yytext); return ASSIN;}

 /* 符号 */
\;   {pos_start = pos_end; pos_end++; pass_node(yytext); return SEMICOLON;}
\,   {pos_start = pos_end; pos_end++; pass_node(yytext); return COMMA;}
\(  {pos_start = pos_end; pos_end++; pass_node(yytext); return LPARENTHESE;}
\)  {pos_start = pos_end; pos_end++; pass_node(yytext); return RPARENTHESE;}
\[  {pos_start = pos_end; pos_end++; pass_node(yytext); return LBRACKET;}
\]  {pos_start = pos_end; pos_end++; pass_node(yytext); return RBRACKET;}
\{  {pos_start = pos_end; pos_end++; pass_node(yytext); return LBRACE;}
\}  {pos_start = pos_end; pos_end++; pass_node(yytext); return RBRACE;}

 /* 关键字 */
else {pos_start = pos_end; pos_end+=4; pass_node(yytext); return ELSE;}
if   {pos_start = pos_end; pos_end+=2; pass_node(yytext); return IF;}
int  {pos_start = pos_end; pos_end+=3; pass_node(yytext); return INT;}
float {pos_start = pos_end; pos_end+=5; pass_node(yytext); return FLOAT;}
return {pos_start = pos_end; pos_end+=6; pass_node(yytext); return RETURN;}
void   {pos_start = pos_end; pos_end+=4; pass_node(yytext); return VOID;}
while  {pos_start = pos_end; pos_end+=5; pass_node(yytext); return WHILE;}

 /* ID & NUM */
[a-zA-Z]+ {pos_start = pos_end; pos_end+=yyleng; pass_node(yytext); return IDENTIFIER;}
[0-9]+    {pos_start = pos_end; pos_end+=yyleng; pass_node(yytext); return INTEGER;}
[0-9]+\.|[0-9]*\.[0-9]+ {pos_start = pos_end; pos_end+=yyleng; pass_node(yytext); return FLOATPOINT;}
"[]" {pos_start = pos_end; pos_end+=2; pass_node(yytext); return ARRAY;}
[a-zA-Z]  {pos_start = pos_end; pos_end++; pass_node(yytext); return LETTER;}

 /* others */
\n  {lines++; pos_end=1;}
\/\*[^*]*\*+([^/*][^*]*\*+)*\/  {
                for (int i=0;i<yyleng;i++){
                    if (yytext[i]=='\n'){   /*换行操作*/
                        lines++;
                        pos_end=1;
                    }
                    else pos_end++;
                }}
" " {pos_start = pos_end; pos_end+=yyleng;}
\t  {pos_start = pos_end; pos_end+=yyleng;}
 /* \r  {return BLANK;} */
. {}
