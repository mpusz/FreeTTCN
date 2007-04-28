%{
#include "tools.h"
#include "grammar.tab.h"

extern YYLTYPE *yylloc;
extern YYSTYPE *yylval;
extern TTCN3::CFile *file;

long int cmntLen = 0;

/* an action that is done for each matched token */
#define YY_USER_ACTION                                  \
        {                                               \
          yylloc->first_line = yylloc->last_line;       \
          yylloc->first_column = yylloc->last_column;   \
                                                        \
          if (YYSTATE == CMNT)                          \
            yylloc->last_column = yyleng - cmntLen;     \
          else                                          \
            yylloc->last_column += yyleng;              \
        }

%}

/* %option noyymore */
/* %option yyclass="TTCN3FlexLexer" */

%option nounput

WS              [ \t\r]*
L		[a-zA-Z]
B               [0-1]
NZD             [1-9]
D		[0-9]
H               [0-9a-fA-F]

C               [\x20-\x7e]
UC              {C}
EAN             [\32-\126\161-\172\174-\255]

NUMBER          ({NZD}{D}*)|0
FLOAT_DOT       {NUMBER}"."{D}+
FLOAT_E         {NUMBER}("."{D}+)?E-?{NUMBER}
FLOAT           {FLOAT_DOT}|{FLOAT_E}

B_STRING        '{B}*'B
H_STRING        '{H}*'H
O_STRING        '({H}{H})*'O
C_STRING        \"{C}*\"
UC_STRING       \"{UC}*\"
TEXT            \"{EAN}*\"

B_STRING_MATCH  '[{B}*?]*'B
H_STRING_MATCH  '[{H}*?]*'H
O_STRING_MATCH  '[({H}{H})*?]*'O

ID		{L}({L}|{D}|_)*


/* exclusive start conditions - %x */
%x CMNT

%%
{WS}                    { /* ignore white spaces */ }
\n                      { ++yylloc->last_line; yylloc->last_column=1; }

"//".*                  { printf("%s\n", yytext); }
"/*"                    { BEGIN(CMNT); cmntLen=0; yymore(); }

":="                    { return '='; }
";"                     { return ';'; }
","                     { return ','; }
"{"                     { return '{'; }
"}"                     { return '}'; }
"("                     { return '('; }
")"                     { return ')'; }
"["                     { return '['; }
"]"                     { return ']'; }
"+"                     { return '+'; }
"-"                     { return '-'; }
"*"                     { return '*'; }
"/"                     { return '/'; }
"."                     { return '.'; }
"?"                     { return '?'; }
":"                     { return ':'; }
"&"                     { return '&'; }
".."                    { return T_RANGE; }
"->"                    { return T_REDIRECT; }

"<"                     { return T_LESS; }
">"                     { return T_GREATER; }
"<="                    { return T_NOT_GREATER; }
">="                    { return T_NOT_LESS; }

"=="                    { return T_EQUAL; }
"!="                    { return T_NOT_EQUAL; }

"<<"                    { return T_SHIFT_LEFT; }
">>"                    { return T_SHIFT_RIGHT; }
"<@"                    { return T_ROTATE_LEFT; }
"@>"                    { return T_ROTATE_RIGHT; }

action                  { return T_ACTION; }
activate                { return T_ACTIVATE; }
address                 { return T_ADDRESS; }
alive                   { return T_ALIVE; }
all                     { return T_ALL; }
alt                     { return T_ALT; }
altstep                 { return T_ALTSTEP; }
and                     { return T_AND; }
and4b                   { return T_AND4B; }
any                     { return T_ANY; }
anytype                 { return T_ANYTYPE; }

bitstring               { return T_BITSTRING; }
boolean                 { return T_BOOLEAN; }

case                    { return T_CASE; }
call                    { return T_CALL; }
catch                   { return T_CATCH; }
char                    { return T_CHAR; }
charstring              { return T_CHARSTRING; }
check                   { return T_CHECK; }
clear                   { return T_CLEAR; }
complement              { return T_COMPLEMENT; }
component               { return T_COMPONENT; }
connect                 { return T_CONNECT; }
const                   { return T_CONST; }
control                 { return T_CONTROL; }
create                  { return T_CREATE; }

deactivate              { return T_DEACTIVATE; }
default                 { return T_DEFAULT; }
disconnect              { return T_DISCONNECT; }
display                 { return T_DISPLAY; }
do                      { return T_DO; }
done                    { return T_DONE; }

else                    { return T_ELSE; }
encode                  { return T_ENCODE; }
enumerated              { return T_ENUMERATED; }
error                   { return T_ERROR; }
except                  { return T_EXCEPT; }
exception               { return T_EXCEPTION; }
execute                 { return T_EXECUTE; }
extends                 { return T_EXTENDS; }
extension               { return T_EXTENSION; }
external                { return T_EXTERNAL; }

fail                    { return T_FAIL; }
false                   { return T_FALSE; }
float                   { return T_FLOAT; }
for                     { return T_FOR; }
from                    { return T_FROM; }
function                { return T_FUNCTION; }

getverdict              { return T_GETVERDICT; }
getcall                 { return T_GETCALL; }
getreply                { return T_GETREPLY; }
goto                    { return T_GOTO; }
group                   { return T_GROUP; }

hexstring               { return T_HEXSTRING; }

if                      { return T_IF; }
ifpresent               { return T_IFPRESENT; }
import                  { return T_IMPORT; }
in                      { return T_IN; }
inconc                  { return T_INCONC; }
infinity                { return T_INFINITY; }
inout                   { return T_INOUT; }
integer                 { return T_INTEGER; }
interleave              { return T_INTERLEAVE; }

kill                    { return T_KILL; }
killed                  { return T_KILLED; }

label                   { return T_LABEL; }
language                { return T_LANGUAGE; }
length                  { return T_LENGTH; }
log                     { return T_LOG; }

map                     { return T_MAP; }
match                   { return T_MATCH; }
message                 { return T_MESSAGE; }
mixed                   { return T_MIXED; }
mod                     { return T_MOD; }
modifies                { return T_MODIFIES; }
module                  { return T_MODULE; }
modulepar               { return T_MODULEPAR; }
mtc                     { return T_MTC; }

noblock                 { return T_NOBLOCK; }
none                    { return T_NONE; }
not                     { return T_NOT; }
not4b                   { return T_NOT4B; }
nowait                  { return T_NOWAIT; }
null                    { return T_NULL; }

octetstring             { return T_OCTETSTRING; }
of                      { return T_OF; }
omit                    { return T_OMIT; }
on                      { return T_ON; }
optional                { return T_OPTIONAL; }
or                      { return T_OR; }
or4b                    { return T_OR4B; }
out                     { return T_OUT; }
override                { return T_OVERRIDE; }

param                   { return T_PARAM; }
pass                    { return T_PASS; }
pattern                 { return T_PATTERN; }
permutation             { return T_PERMUTATION; }
port                    { return T_PORT; }
procedure               { return T_PROCEDURE; }

raise                   { return T_RAISE; }
read                    { return T_READ; }
receive                 { return T_RECEIVE; }
record                  { return T_RECORD; }
recursive               { return T_RECURSIVE; }
rem                     { return T_REM; }
repeat                  { return T_REPEAT; }
reply                   { return T_REPLY; }
return                  { return T_RETURN; }
running                 { return T_RUNNING; }
runs                    { return T_RUNS; }

select                  { return T_SELECT; }
self                    { return T_SELF; }
send                    { return T_SEND; }
sender                  { return T_SENDER; }
set                     { return T_SET; }
setverdict              { return T_SETVERDICT; }
signature               { return T_SIGNATURE; }
start                   { return T_START; }
stop                    { return T_STOP; }
subset                  { return T_SUBSET; }
superset                { return T_SUPERSET; }
system                  { return T_SYSTEM; }

template                { return T_TEMPLATE; }
testcase                { return T_TESTCASE; }
timeout                 { return T_TIMEOUT; }
timer                   { return T_TIMER; }
to                      { return T_TO; }
trigger                 { return T_TRIGGER; }
true                    { return T_TRUE; }
type                    { return T_TYPE; }

union                   { return T_UNION; }
universal               { return T_UNIVERSAL; }
unmap                   { return T_UNMAP; }

value                   { return T_VALUE; }
valueof                 { return T_VALUEOF; }
var                     { return T_VAR; }
variant                 { return T_VARIANT; }
verdicttype             { return T_VERDICTTYPE; }

while                   { return T_WHILE; }
with                    { return T_WITH; }

xor                     { return T_XOR; }
xor4b                   { return T_XOR4B; }


int2char                { return T_INT2CHAR; }
int2unichar             { return T_INT2UNICHAR; }
int2bit                 { return T_INT2BIT; }
int2hex                 { return T_INT2HEX; }
int2oct                 { return T_INT2OCT; }
int2str                 { return T_INT2STR; }
int2float               { return T_INT2FLOAT; }
float2int               { return T_FLOAT2INT; }
char2int                { return T_CHAR2INT; }
char2oct                { return T_CHAR2OCT; }
unichar2int             { return T_UNICHAR2INT; }
bit2int                 { return T_BIT2INT; }
bit2hex                 { return T_BIT2HEX; }
bit2oct                 { return T_BIT2OCT; }
bit2str                 { return T_BIT2STR; }
hex2int                 { return T_HEX2INT; }
hex2bit                 { return T_HEX2BIT; }
hex2oct                 { return T_HEX2OCT; }
hext2str                { return T_HEX2STR; }
oct2int                 { return T_OCT2INT; }
oct2bit                 { return T_OCT2BIT; }
oct2hex                 { return T_OCT2HEX; }
oct2str                 { return T_OCT2STR; }
oct2char                { return T_OCT2CHAR; }
str2int                 { return T_STR2INT; }
str2oct                 { return T_STR2OCT; }
str2float               { return T_STR2FLOAT; }

lengthof                { return T_LENGTHOF; }
sizeof                  { return T_SIZEOF; }
sizeoftype              { return T_SIZEOFTYPE; }

ispresent               { return T_ISPRESENT; }
ischosen                { return T_ISCHOSEN; }

regexp                  { return T_REGEXP; }
substr                  { return T_SUBSTR; }
replace                 { return T_REPLACE; }

rnd                     { return T_RND; }

{FLOAT}                 { yylval->floatValue = atof(yytext); return T_FLOAT_VAL; }
{NUMBER}                { yylval->intValue = atoi(yytext); return T_INT_VAL; }

{B_STRING}              { return T_B_STRING; }
{H_STRING}              { return T_H_STRING; }
{O_STRING}              { return T_O_STRING; }
{C_STRING}              { return T_C_STRING; }
{UC_STRING}             { return T_UC_STRING; }
{TEXT}                  { return T_TEXT; }

{B_STRING_MATCH}        { return T_B_STRING_MATCH; }
{H_STRING_MATCH}        { return T_H_STRING_MATCH; }
{O_STRING_MATCH}        { return T_O_STRING_MATCH; }

{ID}                    { // check if that ID is already defined
/*                           TTCN3::Identifier *id = TTCN3::Identifier::list.Get(yytext); */
/*                           if (id) { */
/*                             yylval->id = id; */
/*                             id->Location(*yylloc); */

/*                             if (id->Type() == T_ID) { */
/*                               // ID was not assigned to any type for now */
/*                               // and it has the same name as current */
/*                               // it must be a redefinition */
/*                               return T_REDEFINED_ID; */
/*                             } */
/*                             else { */
/*                               // it is a reference to already created type */
/*                               return id->Type(); */
/*                             } */
/*                           } */
/*                           else { */
/*                             // it is a new ID */
                            strcpy(yylval->text, yytext);
                            return T_ID;
/*                           } */
                        }

"_"({L}|{D}|_)+         { strcpy(yylval->text, yytext); return T_U_ID; }
{D}({L}|{D}|_)+         { strcpy(yylval->text, yytext); return T_D_ID; }

.                       { strcpy(yylval->text, yytext); return T_UNKNOWN; }

<CMNT>"/*"              { yymore(); yyerror(yylloc, *file, "'/*' within comment", true); }
<CMNT>[^/*\n]*          |
<CMNT>"*"+[^/\n]*       |
<CMNT>"/"+[^*\n]*       { yymore(); }
<CMNT>[^/*\n]*\n        |
<CMNT>"*"+[^/\n]*\n     |
<CMNT>"/"+[^*\n]*\n     { ++yylloc->last_line; yylloc->last_column=1; cmntLen=yyleng; yymore(); }
<CMNT>"*/"              { BEGIN(INITIAL); printf("%s", yytext); cmntLen=0; }
<CMNT><<EOF>>           { BEGIN(INITIAL); yylloc->first_column = ++yylloc->last_column; ++yylloc->last_column;
                          yyerror(yylloc, *file, "EOF in a comment"); cmntLen=0; yyterminate(); }

%%

/*
  Function returns 1 when the end of file is reached
*/
int yywrap(void)
{
  return 1;
}
