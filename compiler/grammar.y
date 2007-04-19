%{
#include <cstdio>
#include <cstring>
#include "identifier.h"
#include "file.h"
#include "module.h"
#include "importdef.h"
#include "tools.h"
  
%}

%union 
{
  bool                          flag;
  long int                      intValue;
  float                         floatValue;
  TTCN3Type_t                   type;
  TTCN3::CIdentifier            *id;
  TTCN3::CCommaList             *commaList;
  TTCN3::CSemicolonList         *semicolonList;
  TTCN3::CImportDef             *importDef;
  TTCN3::CImportSpec            *importSpec;
  TTCN3::CImportSpecElement     *importSpecElement;
  char                          text[128];
}


/* specify grammar tokens */
%token 
        /* TTCN-3 special terminal symbols */
        '{' '}' '(' ')' '[' ']' ',' ';' '=' '+' '-' '*' '/' ':' '&'

        /* TTCN-3 terminals which are reserved words */
        T_ACTION T_ACTIVATE T_ADDRESS T_ALIVE T_ALL T_ALT
        T_ALTSTEP T_AND T_AND4B T_ANY T_ANYTYPE
        
        T_BITSTRING T_BOOLEAN
        
        T_CASE T_CALL T_CATCH T_CHAR T_CHARSTRING T_CHECK
        T_CLEAR T_COMPLEMENT T_COMPONENT T_CONNECT T_CONST
        T_CONTROL T_CREATE
        
        T_DEACTIVATE T_DEFAULT T_DISCONNECT T_DISPLAY
        T_DO T_DONE

        T_ELSE T_ENCODE T_ENUMERATED T_ERROR T_EXCEPT
        T_EXCEPTION T_EXECUTE T_EXTENDS T_EXTENSION
        T_EXTERNAL
        
        T_FAIL T_FALSE T_FLOAT T_FOR T_FROM T_FUNCTION
        
        T_GETVERDICT T_GETCALL T_GETREPLY T_GOTO T_GROUP
        
        T_HEXSTRING
        
        T_IF T_IFPRESENT T_IMPORT T_IN T_INCONC T_INFINITY
        T_INOUT T_INTEGER T_INTERLEAVE
        
        T_KILL T_KILLED
        
        T_LABEL T_LANGUAGE T_LENGTH T_LOG
        
        T_MAP T_MATCH T_MESSAGE T_MIXED T_MOD T_MODIFIES
        T_MODULE T_MODULEPAR T_MTC
        
        T_NOBLOCK T_NONE T_NOT T_NOT4B T_NOWAIT T_NULL
        
        T_OCTETSTRING T_OF T_OMIT T_ON T_OPTIONAL T_OR
        T_OR4B T_OUT T_OVERRIDE
        
        T_PARAM T_PASS T_PATTERN T_PORT T_PROCEDURE
        
        T_RAISE T_READ T_RECEIVE T_RECORD T_REM T_REPEAT
        T_REPLY T_RETURN T_RUNNING T_RUNS
        
        T_SELECT T_SELF T_SEND T_SENDER T_SET T_SETVERDICT
        T_SIGNATURE T_START T_STOP T_SUBSET T_SUPERSET
        T_SYSTEM
        
        T_TEMPLATE T_TESTCASE T_TIMEOUT T_TIMER T_TO
        T_TRIGGER T_TRUE T_TYPE
        
        T_UNION T_UNIVERSAL T_UNMAP
        
        T_VALUE T_VALUEOF T_VAR T_VARIANT T_VERDICTTYPE
        
        T_WHILE T_WITH
        
        T_XOR T_XOR4B


        /* TTCN-3 predefined function identifiers */
        T_INT2CHAR      T_INT2UNICHAR   T_INT2BIT
        T_INT2HEX       T_INT2OCT       T_INT2STR
        T_INT2FLOAT     T_FLOAT2INT     T_CHAR2INT
        T_CHAR2OCT      T_UNICHAR2INT   T_BIT2INT
        T_BIT2HEX       T_BIT2OCT       T_BIT2STR
        T_HEX2INT       T_HEX2BIT       T_HEX2OCT
        T_HEX2STR       T_OCT2INT       T_OCT2BIT
        T_OCT2HEX       T_OCT2STR       T_OCT2CHAR
        T_STR2INT       T_STR2OCT       T_STR2FLOAT
        
        T_LENGTHOF      T_SIZEOF        T_SIZEOFTYPE
        T_ISPRESENT     T_ISCHOSEN
        T_REGEXP        T_SUBSTR        T_REPLACE
        T_RND
        
        /* ??? */
        T_PERMUTATION   T_RECURSIVE

        /* other */
        T_RANGE         T_REDIRECT

        T_LESS          T_GREATER       T_NOT_GREATER
        T_NOT_LESS      T_EQUAL         T_NOT_EQUAL
        
        T_SHIFT_LEFT    T_SHIFT_RIGHT   T_ROTATE_LEFT
        T_ROTATE_RIGHT

        T_B_STRING      T_H_STRING      T_O_STRING
        T_C_STRING      T_UC_STRING     T_TEXT
        T_B_STRING_MATCH T_H_STRING_MATCH T_O_STRING_MATCH
        

%token <id>
        T_MODULE_ID                     T_MOD_PAR_ID
        T_STRUCT_TYPE_ID                T_STRUCT_FIELD_ID
        T_TIMER_ID                      T_TIMER_PAR_ID
        T_ENUM_ID       T_ENUM_TYPE_ID
        T_PORT_ID       T_PORT_TYPE_ID  T_PORT_PAR_ID
        T_TEMPL_ID                      T_TEMPL_PAR_ID
        T_FUNC_ID       T_EXT_FUNC_ID
        T_CONST_ID      T_EXT_CONST_ID
        T_SUB_TYPE_ID
        T_COMP_TYPE_ID
        T_SIG_ID
        T_TC_ID
        T_ALTSTEP_ID
        T_GROUP_ID
        T_VAR_ID
        T_VALUE_PAR_ID
        T_LABEL_ID
        
        T_REDEFINED_ID

%token <floatValue> T_FLOAT_VAL
%token <intValue>   T_INT_VAL
%token <text>       T_ID        T_U_ID          T_D_ID          T_UNKNOWN


%type <id> identifier
%type <id> ttcn3_module_id module_id global_module_id module_identifier
           const_list single_const_def const_identifier struct_field_identifier
%type <id> definition_ref
%type <id> struct_type_identifier enum_type_identifier port_type_identifier
           component_type_identifier sub_type_identifier template_identifier
           altstep_identifier testcase_identifier function_identifier
           signature_identifier var_identifier timer_identifier port_identifier
           module_par_identifier group_identifier full_group_identifier
%type <id> enumerated_value

%type <semicolonList> opt_except_def except_spec my_except_spec

%type <type> predefined_type type my_type

%type <importDef> import_from_spec
%type <importSpec> my_import_spec all_with_excepts
%type <importSpecElement> except_element

%type <flag> opt_recursive_keyword


%destructor { delete $$; } identifier
%destructor { delete $$; } ttcn3_module_id module_id global_module_id module_identifier
           const_list single_const_def const_identifier struct_field_identifier
%destructor { delete $$; } definition_ref
%destructor { delete $$; } struct_type_identifier enum_type_identifier port_type_identifier
           component_type_identifier sub_type_identifier template_identifier
           altstep_identifier testcase_identifier function_identifier
           signature_identifier var_identifier timer_identifier port_identifier
           module_par_identifier group_identifier full_group_identifier


/* create a header file for grammar */
%defines

%glr-parser
/* %expect 1 */
/* %expect-rr 1 */

/* provide more specific descriptions instead of just 'syntax error'
%error-verbose

/* enable location tracking */
%locations

/* create a reentrant parser */
%pure-parser
%parse-param { TTCN3::CFile &file };
%lex-param { TTCN3::CFile &file }

/* set initial action for yyparse() function */
%initial-action
{
/*   @$.first_line = @$.last_line = 1; */
/*   @$.first_column = @$.last_column = 1; */

/*   @$.begin.filename = @$.end.filename = filename; */
}


%%

ttcn3_file
        : /* empty */
        | ttcn3_module;


/* ******************* T T C N - 3    M O D U L E ************************ */

/* 1 */
ttcn3_module
        : ttcn3_module_keyword ttcn3_module_id
                { file.Module(*new TTCN3::CModule(file, @1, *$2)); }
          '{' opt_module_definitions_part opt_module_control_part '}'
          opt_with_statement opt_semicolon
        ;

/* 2 */
ttcn3_module_keyword
        : T_MODULE
        ;

/* 3 */
ttcn3_module_id
        : identifier
                { $1->Type(T_MODULE_ID); }
        ;

/* 4 */
/* 
  STATIC SEMANTICS - opt_language_spec may only be ommited if the referenced
                     module contains TTCN-3 notation
*/
module_id
        : global_module_id opt_language_spec
        ;

/* 5 */
global_module_id
        : module_identifier
        | identifier
                { $1->Type(T_MODULE_ID); }
        ;

/* 6 */
module_identifier
        : T_MODULE_ID
        ;

/* 7 */
opt_language_spec
        : /* empty */
        | language_keyword free_text
        ;

/* 8 */
language_keyword
        : T_LANGUAGE
        ;



/* ********** M O D U L E    D E F I N I T I O N S    P A R T ************ */

/* ----------------------------- G E N E R A L --------------------------- */

/* 9 */
opt_module_definitions_part
        : /* empty */
        | module_definitions_list opt_semicolon
        ;

/* 10 */
module_definitions_list
        : module_definition
        | module_definitions_list opt_semicolon module_definition
        ;

/* 11 */
module_definition
        : module_definition_group1 opt_with_statement
        | error opt_with_statement
                { yyerrok; }
        ;

module_definition_group1
        : type_def
        | const_def
        | template_def
        | module_par_def
        | function_def
        | signature_def
        | testcase_def
        | altstep_def
        | import_def
        | group_def
        | ext_function_def
        | ext_const_def
        ;


/* ---------------- T Y P E D E F   D E F I N I T I O N S ---------------- */

/* 12 */
type_def
        : type_def_keyword type_def_body
        ;

/* 13 */
type_def_body
        : structured_type_def
        | sub_type_def
        ;

/* 14 */
type_def_keyword
        : T_TYPE
        ;

/* 15 */
structured_type_def
        : record_def
        | union_def
        | set_def
        | record_of_def
        | set_of_def
        | enum_def
        | port_def
        | component_def
        ;

/* 16 */
record_def
        : record_keyword struct_def_body
        ;

/* 17 */
record_keyword
        : T_RECORD
        ;

/* 18 */
struct_def_body
        : my_struct_type '{' my_opt_struct_def_item '}'
        ;

/* 19 */
struct_type_identifier
        : T_STRUCT_TYPE_ID
        ;

/* 20 */
opt_struct_def_formal_par_list
        : /* empty */
        | '(' my_opt_struct_def_formal_par_list ')'
        | '(' error ')'
                { yyerrok; }
        ;

/* 21 */
/* 
  STATIC SEMANTICS - formal_value_par shall resolve to an in parameter
*/
struct_def_formal_par
        : formal_value_par
        ;

/* 22 */
struct_field_def
        : my_type identifier
          opt_array_def opt_sub_type_spec opt_optional_keyword          %dprec 2
                { $2->Type(T_STRUCT_FIELD_ID); printf("%s %s\n", TTCN3TypeToString($1), $2->Name().c_str()); }
        | my_type field_reference
                {
/*                   yyclearin; */

/*                   const YYLTYPE &loc = $2->Location(); */
                  char buf[128];

/*                   sprintf(buf, "'%s' already defined", $2->Name().c_str()); */
                  sprintf(buf, "already defined");
                  yyerror(&@2, file, buf);
                  //                  yyerror(&loc, file, "First defined here");
                  YYERROR;
                }
          opt_array_def opt_sub_type_spec opt_optional_keyword          %dprec 1
        ;

/* 23 */
nested_type_def
        : nested_record_def
        | nested_union_def
        | nested_set_def
        | nested_record_of_def
        | nested_set_of_def
        | nested_enum_def
        ;

/* 24 */
nested_record_def
        : record_keyword '{' my_opt_struct_def_item '}'
        ;

/* 25 */
nested_union_def
        : union_keyword '{' my_union_def_item '}'
        ;

/* 26 */
nested_set_def
        : set_keyword '{' my_opt_struct_def_item '}'
        ;

/* 27 */
nested_record_of_def
        : record_keyword opt_string_length of_keyword my_type
        ;
        
/* 28 */
nested_set_of_def
        : set_keyword opt_string_length of_keyword my_type
        ;

/* 29 */
nested_enum_def
        : enum_keyword '{' enumeration_list '}'
        ;
        
/* 30 */
struct_field_identifier
        : T_STRUCT_FIELD_ID
        ;

/* 31 */
opt_optional_keyword
        : /* empty */
        | T_OPTIONAL
        ;
        
/* 32 */
union_def
        : union_keyword union_def_body
        ;

/* 33 */
union_keyword
        : T_UNION
        ;

/* 34 */
union_def_body
        : my_struct_type '{' my_union_def_item '}'
        ;

/* 35 */
union_field_def
        : my_type identifier
          opt_array_def opt_sub_type_spec
                {$2->Type(T_STRUCT_FIELD_ID); }
        ;
        
/* 36 */
set_def
        : set_keyword struct_def_body
        ;

/* 37 */
set_keyword
        : T_SET
        ;

/* 38 */
record_of_def
        : record_keyword opt_string_length
          of_keyword struct_of_def_body
        ;

/* 39 */
of_keyword
        : T_OF
        ;

/* 40 */
struct_of_def_body
        : my_type my_struct_type2 opt_sub_type_spec
        ;

/* 41 */
set_of_def
        : set_keyword opt_string_length
          of_keyword struct_of_def_body
        ;

/* 42 */
enum_def
        : enum_keyword my_enum_type '{' enumeration_list '}'
        ;
        
/* 43 */
enum_keyword
        : T_ENUMERATED
        ;

/* 44 */
enum_type_identifier
        : T_ENUM_TYPE_ID
        ;

/* 45 */
enumeration_list
        : enumeration
        | enumeration_list ',' enumeration
        ;

/* 46 */
enumeration
        : identifier my_opt_enum_initializer
                { $1->Type(T_ENUM_ID); }
        ;

/* 47 */
enumeration_identifier
        : T_ENUM_ID
        ;

/* 48 */
sub_type_def
        : type my_sub_type_type opt_array_def opt_sub_type_spec
        ;

/* 49 */
sub_type_identifier
        : T_SUB_TYPE_ID
        ;

/* 50 */
/* 
  STATIC SEMANTICS - allowed_values shall be of the same type
                     as the field being subtyped
*/
opt_sub_type_spec
        : /* empty */
        | allowed_values opt_string_length
        | string_length
        ;

/* 51 */
allowed_values
        : '(' my_allowed_value ')'
        | '(' error ')'
                { yyerrok; }
        ;

/* 52 */
/* 
  STATIC SEMANTICS - range_def production shall only be used
                     with integer, charstring, universal
                     charstring or float based types
*/
/* 
  STATIC SEMANTICS - when subtyping charstring or universal
                     charstring range and values shall not
                     be mixed in the same sub_type_spec
*/
value_or_range
        : range_def
        | constant_expression
        ;

/* 53 */
range_def
        : lower_bound T_RANGE upper_bound
        ;

/* 54 */
/* 
  STATIC SEMANTICS - string_length shall only be used with
                     String types or to limit set of and
                     record of. single_const_expression and
                     my_opt_upper_bound shall evaluate to
                     non-negative integer value (in case
                     of my_opt_upper_bound including
                     infinity)
*/
string_length
        : length_keyword '(' single_const_expression
          my_opt_upper_bound ')'
        | length_keyword '(' error ')'
                { yyerrok; }
        ;

opt_string_length
        : /* empty */
        | string_length
        ;

/* 55 */
length_keyword
        : T_LENGTH
        ;

/* 56 */
port_type
        : my_opt_module_prefix port_type_identifier
        ;

/* 57 */
port_def
        : port_keyword port_def_body
        ;

/* 58 */
port_def_body
        : identifier port_def_attribs
                { $1->Type(T_PORT_TYPE_ID); }
        ;

/* 59 */
port_keyword
        : T_PORT
        ;

/* 60 */
port_type_identifier
        : T_PORT_TYPE_ID
        ;

/* 61 */
port_def_attribs
        : message_attribs
        | procedure_attribs
        | mixed_attribs
        ;

/* 62 */
message_attribs
        : message_keyword '{' my_message_list opt_semicolon '}'
        | message_keyword '{' error opt_semicolon '}'
                { yyerrok; }
        ;

/* 63 */
message_list
        : direction all_or_type_list
        ;

/* 64 */
direction
        : in_par_keyword
        | out_par_keyword
        | inout_par_keyword
        ;

/* 65 */
message_keyword
        : T_MESSAGE
        ;

/* 66 */
/* 
  NOTE: The use of all_keyword in port definitions is deprecated
*/
all_or_type_list
        : all_keyword
        | type_list
        ;

/* 67 */
all_keyword
        : T_ALL
        ;

/* 68 */
type_list
        : type
        | type_list ',' type
        ;

/* 69 */
procedure_attribs
        : procedure_keyword '{' my_procedure_list opt_semicolon '}'
        ;

/* 70 */
procedure_keyword
        : T_PROCEDURE
        ;

/* 71 */
procedure_list
        : direction all_or_signature_list
        ;

/* 72 */
all_or_signature_list
        : all_keyword
        | signature_list
        ;

/* 73 */
signature_list
        : signature
        | signature_list ',' signature
        ;

/* 74 */
mixed_attribs
        : mixed_keyword '{' my_mixed_list opt_semicolon '}'
        ;

/* 75 */
mixed_keyword
        : T_MIXED
        ;

/* 76 */
mixed_list
        : direction proc_or_type_list
        ;

/* 77 */
proc_or_type_list
        : all_keyword
        | my_proc_or_type_list
        ;

/* 78 */
proc_or_type
        : signature
        | type
        ;

/* 79 */
component_def
        : component_keyword identifier
          my_opt_extends_component '{' opt_component_def_list '}'
                { $2->Type(T_COMP_TYPE_ID); }
        | component_keyword identifier
          my_opt_extends_component '{' error '}'
                { yyerrok; }
        ;

/* 80 */
component_keyword
        : T_COMPONENT
        ;

/* 81 */
extends_keyword
        : T_EXTENDS
        ;

/* 82 */
component_type
        : my_opt_module_prefix component_type_identifier
        ;

/* 83 */
component_type_identifier
        : T_COMP_TYPE_ID
        ;

/* 84 */
opt_component_def_list
        : /* empty */
        | my_opt_component_def_list opt_semicolon
        ;

/* 85 */
component_element_def
        : port_instance
        | var_instance
        | timer_instance
        | const_def
        ;

/* 86 */
port_instance
        : port_keyword port_type my_port_element_list
        ;

/* 87 */
port_element
        : identifier opt_array_def
                { $1->Type(T_PORT_ID); }
        | error opt_array_def
                { yyerrok; }
        ;

/* 88 */
port_identifier
        : T_PORT_ID
        ;



/* --------------- C O N S T A N T   D E F I N I T I O N S --------------- */

/* 89 */
/* 
  STATIC SEMANTICS - type shall follow the rules given in clause 9 of
                     ES 201 873-1
*/
const_def
        : const_keyword type const_list
                { printf("CONST %s %s\n", TTCN3TypeToString((TTCN3Type_t)$2), $3->Name().c_str()); }
        ;

/* 90 */
const_list
        : single_const_def
        | const_list ',' single_const_def
        ;

/* 91 */
/* 
  STATIC SEMANTICS - The value of the constant_expression shall be of the
                     same type as the stated type for the constants
*/
single_const_def
        : identifier opt_array_def '=' constant_expression
                { $1->Type(T_CONST_ID); }
        ;

/* 92 */
const_keyword
        : T_CONST
        ;

/* 93 */
const_identifier
        : T_CONST_ID
        ;


/* --------------- T E M P L A T E   D E F I N I T I O N S --------------- */

/* 94 */
template_def
        : template_keyword base_template my_opt_derived_def '=' template_body
        ;

/* 95 */
base_template
        : proc_or_type identifier my_opt_template_formal_par_list
                { $2->Type(T_TEMPL_ID); }
        | error identifier my_opt_template_formal_par_list
                { yyerrok; }
        | proc_or_type error my_opt_template_formal_par_list
                { yyerrok; }
        ;

/* 96 */
opt_template_keyword
        : /* empty */
        | template_keyword
        ;

template_keyword
        : T_TEMPLATE
        ;

/* 97 */
template_identifier
        : T_TEMPL_ID
        ;

/* 98 */
derived_def
        : modifies_keyword template_ref
        ;

/* 99 */
modifies_keyword
        : T_MODIFIES
        ;

/* 100 */
template_formal_par_list
        : template_formal_par
        | template_formal_par_list ',' template_formal_par
        ;

/* 101 */
/* 
  STATIC SEMANTICS - formal_value_par shall resolve to an in parameter
*/
template_formal_par
        : formal_value_par | formal_template_par
        ;

/* 102 */
/* 
  STATIC SEMANTICS - Within template_body the array_value_or_attrib
                     can be used for array, record, record of and
                     set of types
*/
template_body
        : my_template_spec
        | opt_extra_matching_attributes
        ;

/* 103 */
simple_spec
        : single_value_or_attrib
        ;

/* 104 */
field_spec_list
        : '{' my_opt_field_spec_list '}'
        ;

/* 105 */
field_spec
        : field_reference '=' template_body
        | error '=' template_body
                { yyerrok; }
        | field_reference '=' error
                { yyerrok; }
        | error '=' error
                { yyerrok; }
        ;

/* 106 */
/* 
  STATIC SEMANTICS - Within field_reference array_or_bit_ref can be
                     used for record of and set of templates/template
                     fields in modified templates only
*/
field_reference
        : struct_field_ref
        | array_or_bit_ref
        | par_ref
        ;

/* 107 */
/* 
  STATIC SEMANTICS - predefined_type and type_reference shall be used
                     for anytype value notation only. predefined_type
                     shall not be any_type_keyword
*/
struct_field_ref
        : struct_field_identifier
        | predefined_type
        | type_reference
        ;

/* 108 */
/* 
  STATIC SEMANTICS - signature_par_identifier shall be a formal parameter
                     identifier from the associated signature definition
*/
par_ref
        : signature_par_identifier
        ;

/* 109 */
signature_par_identifier
        : value_par_identifier
        ;

/* 110 */
/* 
  STATIC SEMANTICS - array_ref shall e opionally used for array types and
                     ASN.1 SET OF and SEQUENCE OF and TTCN-3 record of
                     and set of. The same notation can be used for a bit
                     reference inside an ASN.1 or TTCN-3 bitstring type
*/
array_or_bit_ref
        : '[' field_or_bit_number ']'
        ;

/* 111 */
/* 
  STATIC SEMANTICS - single_expression will resolve to a value of integer
                     type
*/
field_or_bit_number
        : single_expression
        ;

/* 112 */
/* 
  STATIC SEMANTICS - variable_identifier (accesed via single_expression)
                     may only be used in in-line template definitions
                     to reference varaibles in the current scope
*/
single_value_or_attrib
        : matching_symbol
        | single_expression
        | template_ref_with_par_list
        ;

/* 113 */
array_value_or_attrib
        : '{' array_element_spec_list '}'
        ;

/* 114 */
array_element_spec_list
        : array_element_spec
        | array_element_spec_list ',' array_element_spec
        ;

/* 115 */
array_element_spec
        : not_used_symbol
        | permutation_match
        | template_body
        ;

/* 116 */
not_used_symbol
        : '-'
        ;

/* 117 */
matching_symbol
        : complement
        | any_value
        | any_or_omit
        | value_or_attrib_list
        | range
        | bitstring_match
        | hexstring_match
        | octetstring_match
        | charstring_match
        | subset_match
        | superset_match
        | '(' error ')'
                { yyerrok; }
        ;

/* 118 */
opt_extra_matching_attributes
        : /* empty */
        | length_match
        | if_present_match
        | length_match if_present_match
        ;

/* 119 */
bitstring_match
        : T_B_STRING_MATCH
        | T_B_STRING
        ;

/* 121 */
hexstring_match
        : T_H_STRING_MATCH
        | T_H_STRING
        ;

/* 123 */
octetstring_match
        : T_O_STRING_MATCH
        | T_O_STRING
        ;

/* 125 */
charstring_match
        : pattern_keyword c_string
        ;

/* 126 */
pattern_keyword
        : T_PATTERN
        ;

/* 127 */
complement
        : complement_keyword value_list
        ;

/* 128 */
complement_keyword
        : T_COMPLEMENT
        ;

/* 129 */
value_list
        : '(' my_constant_expression_list ')'
        | '(' error ')'
                { yyerrok; }
        ;

/* 130 */
/* 
  STATIC SEMANTICS - Subset matching shall only be used with the set of type
*/
subset_match
        : subset_keyword value_list
        ;
        
/* 131 */
subset_keyword
        : T_SUBSET
        ;

/* 132 */
/* 
  STATIC SEMANTICS - Superset matching shall only be used with the set of type
*/
superset_match
        : superset_keyword value_list
        ;

/* 133 */
superset_keyword
        : T_SUPERSET
        ;

/* 134 */
permutation_match
        : permutation_keyword permutation_list
        ;

/* 135 */
permutation_keyword
        : T_PERMUTATION
        ;

/* 136 */
/* 
  STATIC SEMANTICS - Restrictions on the content of template_body are given
                     in clause B.1.3.3
*/
permutation_list
        : '(' my_template_body_list ')'
        | '(' error ')'
                { yyerrok; }
        ;

/* 137 */
any_value
        : '?'
        ;

/* 138 */
any_or_omit
        : '*'
        ;

/* 139 */
value_or_attrib_list
        : '(' my_template_body_list2 ')'
        ;

/* 140 */
length_match
        : string_length
        ;

/* 141 */
if_present_match
        : if_present_keyword
        ;

/* 142 */
if_present_keyword
        : T_IFPRESENT
        ;

/* 143 */
range
        : '(' lower_bound T_RANGE upper_bound ')'
        ;

/* 144 */
lower_bound
        : single_const_expression
        | '-' infinity_keyword
        ;

/* 145 */
/* 
  STATIC SEMANTICS - lower_bound and upper_bound shall evaluate to types
                     integer, charstring, universal charstring or float.
                     In case lower_bound or upper_bound evaluates to
                     types charstring or universal charstring, only
                     single_const_expression may be present and the
                     string length shall be 1
*/
upper_bound
        : single_const_expression
        | infinity_keyword
        ;

/* 146 */
infinity_keyword
        : T_INFINITY
        ;

/* 147 */
template_instance
        : in_line_template
        ;

/* 148 */
template_ref_with_par_list
        : my_opt_module_prefix template_identifier opt_template_actual_par_list
        | template_par_identifier
        ;

/* 149 */
template_ref
        : my_opt_module_prefix template_identifier      %dprec 2
        | template_par_identifier               %dprec 2
        | identifier                            %dprec 1
                { 
/*                   yyclearin; */
                  char buf[128];
                  sprintf(buf, "'%s' template not defined", $1->Name().c_str());
                  yyerror(&@1, file, buf);
                  YYERROR;
                }
        ;

/* 150 */
/* 
  STATIC SEMANTICS - The type field may only be omitted when the type is
                     implicitly unambiguous
*/
in_line_template
        : my_opt_type_prefix my_opt_derived_ref_with_par_list template_body
        ;

/* 151 */
derived_ref_with_par_list
        : modifies_keyword template_ref_with_par_list
        ;

/* 152 */
opt_template_actual_par_list
        : /* empty */
        | '(' my_template_actual_par_list ')'
        | '(' error ')'
                { yyerrok; }
        ;

/* 153 */
/* 
  STATIC SEMANTICS - When the corresponding formal parameter is not of template
                     type the template_instance production shall resolve to one
                     or more single_expression
*/
template_actual_par
        : template_instance
        ;

/* 154 */
template_ops
        : match_op
        | value_of_op
        ;

/* 155 */
/* 
  STATIC SEMANTICS - The type of the value returned by the expression must be
                     the same as the template type and each field of the template
                     shall resolve to a single value
*/
match_op
        : match_keyword '(' expression ',' template_instance ')'
        | '(' error ')'
                { yyerrok; }
        ;

/* 156 */
match_keyword
        : T_MATCH
        ;

/* 157 */
value_of_op
        : value_of_keyword '(' template_instance ')'
        | value_of_keyword '(' error ')'
                { yyerrok; }
        ;

/* 158 */
value_of_keyword
        : T_VALUEOF
        ;


/* --------------- F U N C T I O N   D E F I N I T I O N S --------------- */

/* 159 */
function_def
        : function_keyword identifier '(' opt_function_formal_par_list ')'
          opt_runs_on_spec opt_return_type statement_block
                { $2->Type(T_FUNC_ID); }
        | function_keyword identifier '(' error ')'
          opt_runs_on_spec opt_return_type statement_block
                { yyerrok; }
        ;

/* 160 */
function_keyword
        : T_FUNCTION
        ;

/* 161 */
function_identifier
        : T_FUNC_ID
        ;

/* 162 */
opt_function_formal_par_list
        : /* empty */
        | function_formal_par_list
        ;

function_formal_par_list
        : function_formal_par
        | function_formal_par_list ',' function_formal_par
        ;

/* 163 */
function_formal_par
        : formal_value_par
        | formal_timer_par
        | formal_template_par
        | formal_port_par
        ;

/* 164 */
/* 
  STATIC SEMANTICS - The use of the template keyword shall conform to
                     restriction in clause 16.1.0 of ES 201 873-1
*/
opt_return_type
        : /* empty */
        | return_type
        ;

return_type
        : return_keyword opt_template_keyword type
        ;

/* 165 */
return_keyword
        : T_RETURN
        ;

/* 166 */
opt_runs_on_spec
        : /* empty */
        | runs_on_spec
        ;

runs_on_spec
        : runs_keyword on_keyword component_type
        ;

/* 167 */
runs_keyword
        : T_RUNS
        ;

/* 168 */
on_keyword
        : T_ON
        ;

/* 169 */
mtc_keyword
        : T_MTC
        ;

/* 170 */
opt_statement_block
        : /* empty */
        | statement_block
        ;
        
statement_block
        : '{' opt_function_statement_or_def_list '}'
        ;
        
/* 171 */
opt_function_statement_or_def_list
        : /* empty */
        | my_opt_function_statement_or_def_list opt_semicolon
        ;

/* 172 */
function_statement_or_def
        : function_local_def
        | function_local_inst
        | function_statement
        ;

/* 173 */
function_local_inst
        : var_instance
        | timer_instance
        ;

/* 174 */
function_local_def
        : const_def
        | template_def
        ;

/* 175 */
function_statement
        : configuration_statements
        | timer_statements
        | communication_statements
        | basic_statements
        | behaviour_statements
        | verdict_statements
        | sut_statements
        ;

/* 176 */
function_instance
        : function_ref '(' opt_function_actual_par_list ')'
        | function_ref '(' error ')'
                { yyerrok; }
        ;

/* 177 */
function_ref
        : my_opt_module_prefix my_function_identifier
        | pre_def_function_identifier
        ;

/* 178 */
/* 
  STATIC SEMANTICS - The identifier will be one of the pre-defined TTCN-3
                     Function Identifiers from Annex C of ES 201 873-1
*/
pre_def_function_identifier
        : T_INT2CHAR
        | T_INT2UNICHAR
        | T_INT2BIT
        | T_INT2HEX
        | T_INT2OCT
        | T_INT2STR
        | T_INT2FLOAT
        | T_FLOAT2INT
        | T_CHAR2INT
        | T_CHAR2OCT
        | T_UNICHAR2INT
        | T_BIT2INT
        | T_BIT2HEX
        | T_BIT2OCT
        | T_BIT2STR
        | T_HEX2INT
        | T_HEX2BIT
        | T_HEX2OCT
        | T_HEX2STR
        | T_OCT2INT
        | T_OCT2BIT
        | T_OCT2HEX
        | T_OCT2STR
        | T_OCT2CHAR
        | T_STR2INT
        | T_STR2OCT
        | T_STR2FLOAT
        | T_LENGTHOF
        | T_SIZEOF
        | T_SIZEOFTYPE
        | T_ISPRESENT
        | T_ISCHOSEN
        | T_REGEXP
        | T_SUBSTR
        | T_REPLACE
        | T_RND
        ;

/* 179 */
opt_function_actual_par_list
        : /* empty */
        | function_actual_par_list
        ;

function_actual_par_list
        : function_actual_par
        | function_actual_par_list ',' function_actual_par
        ;

/* 180 */
/* 
  STATIC SEMANTICS - When the corresponding formal parameter is not of
                     template type the template_instance production shall
                     resolve to one or more single_expression i.e. equivalent
                     to the expression production
*/
function_actual_par
        : timer_ref
        | template_instance
        | port
        | component_ref
        ;



/* -------------- S I G N A T U R E   D E F I N I T I O N S -------------- */

/* 181 */
signature_def
        : signature_keyword identifier 
          '(' opt_signature_formal_par_list ')'
          my_opt_signature_type opt_exception_spec
                { $2->Type(T_SIG_ID); }
        | signature_keyword identifier '(' error ')'
          my_opt_signature_type opt_exception_spec
                { yyerrok; }
        ;

/* 182 */
signature_keyword
        : T_SIGNATURE
        ;

/* 183 */
signature_identifier
        : T_SIG_ID
        ;

/* 184 */
opt_signature_formal_par_list
        : /* empty */
        | signature_formal_par_list
        ;

signature_formal_par_list
        : signature_formal_par
        | signature_formal_par_list ',' signature_formal_par
        ;

/* 185 */
signature_formal_par
        : formal_value_par
        ;

/* 186 */
opt_exception_spec
        : /* empty */
        | exception_keyword '(' exception_type_list ')'
        | exception_keyword '(' error ')'
                { yyerrok; }
        ;

/* 187 */
exception_keyword
        : T_EXCEPTION
        ;

/* 188 */
exception_type_list
        : type
        | exception_type_list ',' type
        ;

/* 189 */
no_block_keyword
        : T_NOBLOCK
        ;

/* 190 */
signature
        : my_opt_module_prefix signature_identifier
        ;



/* --------------- T E S T C A S E   D E F I N I T I O N S --------------- */

/* 191 */
testcase_def
        : testcase_keyword identifier
          '(' opt_testcase_formal_par_list ')'
          config_spec statement_block
                { $2->Type(T_TC_ID); }
        | testcase_keyword identifier '(' error ')'
          config_spec statement_block
                { yyerrok; }
        ;

/* 192 */
testcase_keyword
        : T_TESTCASE
        ;

/* 193 */
testcase_identifier
        : T_TC_ID
        ;

/* 194 */
opt_testcase_formal_par_list
        : /* empty */
        | testcase_formal_par_list
        ;

testcase_formal_par_list
        : testcase_formal_par
        | testcase_formal_par_list ',' testcase_formal_par
        ;

/* 195 */
testcase_formal_par
        : formal_value_par
        | formal_template_par
        ;

/* 196 */
config_spec
        : runs_on_spec opt_system_spec
        ;

/* 197 */
opt_system_spec
        : /* empty */
        | system_keyword component_type
        ;

/* 198 */
system_keyword
        : T_SYSTEM
        ;

/* 199 */
testcase_instance
        : execute_keyword '(' testcase_ref '(' opt_testcase_actual_par_list ')'
          my_opt_testcase_timer_value ')'
        | execute_keyword '(' testcase_ref '(' error ')'
          my_opt_testcase_timer_value ')'
                { yyerrok; }
        | execute_keyword '(' error ')'
                { yyerrok; }
        ;

/* 200 */
execute_keyword
        : T_EXECUTE
        ;

/* 201 */
testcase_ref
        : my_opt_module_prefix testcase_identifier
        ;

/* 202 */
opt_testcase_actual_par_list
        : /* empty */
        | testcase_actual_par_list
        ;

testcase_actual_par_list
        : testcase_actual_par
        | testcase_actual_par_list ',' testcase_actual_par
        ;

/* 203 */
/* 
  STATIC SEMANTICS - When the corresponding formal parameter is not of
                     template type the template_instance production shall
                     resolve to one or more single_expression i.e. equivalent
                     to the expression production
*/
testcase_actual_par
        : template_instance
        ;



/* ---------------- A L T S T E P   D E F I N I T I O N S ---------------- */

/* 204 */
altstep_def
        : altstep_keyword identifier
          '(' opt_altstep_formal_par_list ')' opt_runs_on_spec
          '{' altstep_local_def_list ';' alt_guard_list '}'
                { $2->Type(T_ALTSTEP_ID); }
        | altstep_keyword identifier
          '(' opt_altstep_formal_par_list ')' opt_runs_on_spec
          '{' altstep_local_def_list opt_semicolon '}'
                { $2->Type(T_ALTSTEP_ID); }
        | altstep_keyword identifier
          '(' opt_altstep_formal_par_list ')' opt_runs_on_spec
          '{' opt_alt_guard_list '}'
                { $2->Type(T_ALTSTEP_ID); }
        | altstep_keyword identifier '(' error ')' '}'
                { yyerrok; }
        ;

/* 205 */
altstep_keyword
        : T_ALTSTEP
        ;

/* 206 */
altstep_identifier
        : T_ALTSTEP_ID
        ;

/* 207 */
/* 
  STATIC SEMANTICS - altsteps that are activated as defaults shall only have in
                     parameters, port parameters, or timer paramters
*/
/* 
  STATIC SEMANTICS - altstep that are only invoked as an alternative in an alt
                     statement or as stand-alone statement in a TTCN-3 behaviour
                     description may have in, out, and inout parameters
*/
opt_altstep_formal_par_list
        : /* empty */
        | function_formal_par_list
        ;

/* 208 */
altstep_local_def_list
        : my_altstep_local_def_list
        ;

/* 209 */
/* 
  STATIC SEMANTICS - altstep_local_def shall conform to restrictions in clause
                     16.2.2.1 of ES 201 873-1
*/
altstep_local_def
        : var_instance
        | timer_instance
        | const_def
        | template_def
        ;

/* 210 */
/* 
  STATIC SEMANTICS - all timer instances in function_actual_par_list shall be
                     declared as component local timers (see also production
                     component_element_def)
*/
altstep_instance
        : altstep_ref '(' opt_function_actual_par_list ')'
        | altstep_ref '(' error ')'
                { yyerrok; }
        ;

/* 211 */
altstep_ref
        : my_opt_module_prefix altstep_identifier
        ;


/* ----------------- I M P O R T   D E F I N I T I O N S ----------------- */

/* 212 */
import_def
        : import_keyword import_from_spec my_import_spec
                { $2->Spec(*$3); }
        ;

/* 213 */
import_keyword
        : T_IMPORT
        ;

/* 214 */
all_with_excepts
        : all_keyword opt_except_def
                { $$ = new TTCN3::CImportSpecAllWithExcepts(file, @$, $2); }
        ;

/* 215 */
opt_except_def
        : /* empty */
                { $$ = 0; }
        | except_keyword '{' except_spec '}'
                { if (!$3) $$ = new TTCN3::CSemicolonList(file, @1); else $$ = $3; }
        | except_keyword '{' error '}'
                { yyerrok; }
        ;

/* 216 */
except_keyword
        : T_EXCEPT
        ;

/* 217 */
/* 
  STATIC SEMANTICS - Any of the production (except_group_spec, except_type_def_spec
                     etc.) may be present only once in the except_spec production
*/
except_spec
        : /* empty */
                { $$ = 0 }
        | my_except_spec opt_semicolon
                { $$ = $1 }
        ;

/* 218 */
// TODO
except_element
        : except_group_spec
                { $$ = new TTCN3::CImportSpecElement(file, @1); }
        | except_type_def_spec
                { $$ = new TTCN3::CImportSpecElement(file, @1); }
        | except_template_spec
                { $$ = new TTCN3::CImportSpecElement(file, @1); }
        | except_const_spec
                { $$ = new TTCN3::CImportSpecElement(file, @1); }
        | except_testcase_spec
                { $$ = new TTCN3::CImportSpecElement(file, @1); }
        | except_altstep_spec
                { $$ = new TTCN3::CImportSpecElement(file, @1); }
        | except_function_spec
                { $$ = new TTCN3::CImportSpecElement(file, @1); }
        | except_signature_spec
                { $$ = new TTCN3::CImportSpecElement(file, @1); }
        | except_module_par_spec
                { $$ = new TTCN3::CImportSpecElement(file, @1); }
        | error
                { $$ = 0; yyclearin; yyerrok; }
        ;

/* 219 */
except_group_spec
        : group_keyword except_group_ref_list
        | group_keyword all_keyword
        ;

/* 220 */
except_type_def_spec
        : type_def_keyword type_ref_list
        | type_def_keyword all_keyword
        ;

/* 221 */
except_template_spec
        : template_keyword template_ref_list
        | template_keyword all_keyword
        ;

/* 222 */
except_const_spec
        : const_keyword const_ref_list
        | const_keyword all_keyword
        ;

/* 223 */
except_testcase_spec
        : testcase_keyword testcase_ref_list
        | testcase_keyword all_keyword
        ;

/* 224 */
except_altstep_spec
        : altstep_keyword altstep_ref_list
        | altstep_keyword all_keyword
        ;

/* 225 */
except_function_spec
        : function_keyword function_ref_list
        | function_keyword all_keyword
        ;

/* 226 */
except_signature_spec
        : signature_keyword signature_ref_list
        | signature_keyword all_keyword
        ;

/* 227 */
except_module_par_spec
        : module_par_keyword module_par_ref_list
        | module_par_keyword all_keyword
        ;

/* 228 */
import_spec
        : /* empty */
        | my_import_spec_list opt_semicolon
        ;

/* 229 */
import_element
        : import_group_spec
        | import_type_def_spec
        | import_template_spec
        | import_const_spec
        | import_testcase_spec
        | import_altstep_spec
        | import_function_spec
        | import_signature_spec
        | import_module_par_spec
        ;

/* 230 */
/* 
  NOTE: The use if recursive_keyword is deprecated
*/
import_from_spec
        : from_keyword module_id opt_recursive_keyword
                { $$ = new TTCN3::CImportDef(file, @$, *$2, file.Module(), $3); }
        ;

/* 231 */
opt_recursive_keyword
        : /* empty */
                { $$ = false; }
        | T_RECURSIVE
                { $$ = true; }
        ;

/* 232 */
import_group_spec
        : group_keyword group_ref_list_with_except
        | group_keyword all_groups_with_except
        ;

/* 233 */
group_ref_list
        : full_group_identifier
        | group_ref_list ',' full_group_identifier
        ;

/* 234 */
group_ref_list_with_except
        : full_group_identifier_with_except
        | group_ref_list_with_except ',' full_group_identifier_with_except
        ;

/* 235 */
all_groups_with_except
        : all_keyword my_opt_except_group_ref_list
        ;

/* 236 */
full_group_identifier
        : group_identifier
        | full_group_identifier '.' group_identifier
        ;

/* 237 */
full_group_identifier_with_except
        : full_group_identifier opt_except_def
        ;

/* 238 */
except_group_ref_list
        : except_full_group_identifier
        | except_group_ref_list ',' except_full_group_identifier
        ;

/* 239 */
except_full_group_identifier
        : full_group_identifier
        ;

/* 240 */
import_type_def_spec
        : type_def_keyword type_ref_list
        | type_def_keyword all_types_with_except
        ;

/* 241 */
type_ref_list
        : type_def_identifier
        | type_ref_list ',' type_def_identifier
        ;

/* 242 */
all_types_with_except
        : all_keyword my_opt_except_type_ref_list
        ;

/* 243 */
type_def_identifier
        : struct_type_identifier
        | enum_type_identifier
        | port_type_identifier
        | component_type_identifier
        | sub_type_identifier
        ;

/* 244 */
import_template_spec
        : template_keyword template_ref_list
        | template_keyword all_templs_with_except
        ;

/* 245 */
template_ref_list
        : template_identifier
        | template_ref_list ',' template_identifier
        ;

/* 246 */
all_templs_with_except
        : all_keyword my_opt_except_template_ref_list
        ;

/* 247 */
import_const_spec
        : const_keyword const_ref_list
        | const_keyword all_consts_with_except
        ;

/* 248 */
const_ref_list
        : const_identifier
        | const_ref_list ',' const_identifier
        ;

/* 249 */
all_consts_with_except
        : all_keyword my_opt_except_const_ref_list
        ;

/* 250 */
import_altstep_spec
        : altstep_keyword altstep_ref_list
        | altstep_keyword all_altsteps_with_except
        ;

/* 251 */
altstep_ref_list
        : altstep_identifier
        | altstep_ref_list ',' altstep_identifier
        ;

/* 252 */
all_altsteps_with_except
        : all_keyword my_opt_except_altstep_ref_list
        ;

/* 253 */
import_testcase_spec
        : testcase_keyword testcase_ref_list
        | testcase_keyword all_testcases_with_except
        ;

/* 254 */
testcase_ref_list
        : testcase_identifier
        | testcase_ref_list ',' testcase_identifier
        ;

/* 255 */
all_testcases_with_except
        : all_keyword my_opt_except_testcase_ref_list
        ;

/* 256 */
import_function_spec
        : function_keyword function_ref_list
        | function_keyword all_functions_with_except
        ;

/* 257 */
function_ref_list
        : function_identifier
        | function_ref_list ',' function_identifier
        ;

/* 258 */
all_functions_with_except
        : all_keyword my_opt_except_function_ref_list
        ;

/* 259 */
import_signature_spec
        : signature_keyword signature_ref_list
        | signature_keyword all_signatures_with_except
        ;

/* 260 */
signature_ref_list
        : signature_identifier
        | signature_ref_list ',' signature_identifier
        ;

/* 261 */
all_signatures_with_except
        : all_keyword my_opt_except_signature_ref_list
        ;

/* 262 */
import_module_par_spec
        : module_par_keyword module_par_ref_list
        | module_par_keyword all_module_par_with_except
        ;

/* 263 */
module_par_ref_list
        : module_par_identifier
        | module_par_ref_list ',' module_par_identifier
        ;

/* 264 */
all_module_par_with_except
        : all_keyword my_opt_except_module_par_ref_list
        ;



/* ------------------ G R O U P   D E F I N I T I O N S ------------------ */

/* 265 */
group_def
        : group_keyword identifier
/*                 { $2->Type(T_GROUP_ID); $$ = new TTCN3::CGroupDef(file, @$, *$2, file.Module()); } */
          '{' opt_module_definitions_part '}'
        ;

/* 266 */
group_keyword
        : T_GROUP
        ;

/* 267 */
group_identifier
        : T_GROUP_ID
        ;



/* ------ E X T E R N A L   F U N C T I O N   D E F I N I T I O N S ------ */

/* 268 */
ext_function_def
        : ext_keyword function_keyword identifier
          '(' opt_function_formal_par_list ')' opt_return_type
                { $3->Type(T_EXT_FUNC_ID); }
        | ext_keyword function_keyword identifier '(' error ')' opt_return_type
                { yyerrok; }
        ;

/* 269 */
ext_keyword
        : T_EXTERNAL
        ;

/* 270 */
ext_function_identifier
        : T_EXT_FUNC_ID
        ;



/* ------ E X T E R N A L   C O N S T A N T   D E F I N I T I O N S ------ */

/* 271 */
/* 
  STATIC SEMANTICS - Type shall follow the rules given in clause 9 of
                     ES 201 873-1
*/
ext_const_def
        : ext_keyword const_keyword type identifier
                { $4->Type(T_EXT_CONST_ID); }
        ;

/* 272 */
ext_const_identifier
        : T_EXT_CONST_ID
        ;



/* ------- M O D U L E   P A R A M E T E R   D E F I N I T I O N S ------- */

/* 273 */
module_par_def
        : module_par_keyword module_par
        | module_par_keyword '{' multityped_module_par_list '}'
        ;

/* 274 */
module_par_keyword
        : T_MODULEPAR
        ;

/* 275 */
multityped_module_par_list
        : module_par ';'
        | multityped_module_par_list module_par ';'
        ;

/* 276 */
/* 
  STATIC SEMANTICS - The value of the constant_expression shall be of
                     the same type as the stated type for the parameter
*/
module_par
        : module_par_type module_par_list
        ;

/* 277 */
/* 
  STATIC SEMANTICS - Type shall not be of component, default or anytype.
                     Type shall only resolve to address type if a definition
                     for the address type is defined within the module
*/
module_par_type
        : type
        ;

/* 278 */
module_par_list
        : identifier my_opt_assign_constant
                { $1->Type(T_MOD_PAR_ID); }
        | module_par_list ',' identifier my_opt_assign_constant
                { $3->Type(T_MOD_PAR_ID); }
        ;

/* 279 */
module_par_identifier
        : T_MOD_PAR_ID
        ;




/* *********************** C O N T R O L    P A R T ********************** */

/* --------------------------- G E N E R A L ----------------------------- */

/* 280 */
opt_module_control_part
        : /* empty */
        | module_control_part
        ;

module_control_part
        : control_keyword '{' module_control_body '}'
          opt_with_statement opt_semicolon
        ;

/* 281 */
control_keyword
        : T_CONTROL
        ;

/* 282 */
module_control_body
        : opt_control_statement_or_def_list
        ;

/* 283 */
opt_control_statement_or_def_list
        : /* empty */
        | my_opt_control_statement_or_def_list opt_semicolon
        ;

/* 284 */
control_statement_or_def
        : function_local_def
        | function_local_inst
        | control_statement
        ;

/* 285 */
/* 
  STATIC SEMANTICS - Restrictions on use of statements in the control part
                     are given in table 11
*/
control_statement
        : timer_statements
        | basic_statements
        | behaviour_statements
        | sut_statements
        | stop_keyword
        ;


/* ------------ V A R I A B L E   I N S T A N T I A T I O N -------------- */

/* 286 */
var_instance
        : var_keyword type var_list
        | var_keyword template_keyword type temp_var_list
        ;

/* 287 */
var_list
        : single_var_instance
        | var_list ',' single_var_instance
        ;

/* 288 */
single_var_instance
        : identifier opt_array_def my_opt_assign_init_value
                { $1->Type(T_VAR_ID); }
        | error opt_array_def my_opt_assign_init_value
                { yyerrok; }
        ;

/* 289 */
var_initial_value
        : expression
        ;

/* 290 */
var_keyword
        : T_VAR
        ;

/* 291 */
var_identifier
        : T_VAR_ID
        ;

/* 292 */
temp_var_list
        : single_temp_var_instance
        | temp_var_list ',' single_temp_var_instance
        ;

/* 293 */
single_temp_var_instance
        : var_identifier opt_array_def my_opt_assign_temp_init_value
        ;

/* 294 */
temp_var_initial_value
        : template_body
        ;

/* 295 */
variable_ref
        : var_identifier opt_extended_field_reference
        | value_par_identifier opt_extended_field_reference
        ;



/* --------------- T I M E R   I N S T A N T I A T I O N ----------------- */

/* 296 */
timer_instance
        : timer_keyword timer_list
        ;

/* 297 */
timer_list
        : single_timer_instance
        | timer_list ',' single_timer_instance
        ;

/* 298 */
single_timer_instance
        : identifier opt_array_def my_opt_assign_timer_value
                { $1->Type(T_TIMER_ID); }
        ;

/* 299 */
timer_keyword
        : T_TIMER
        ;

/* 300 */
timer_identifier
        : T_TIMER_ID
        ;

/* 301 */
/* 
  STATIC SEMANTICS - When expression resolves to single_expression it must
                     resolve to a value of type float. Expression shall only
                     resolves to compound_expression in the initialization
                     in default timer value assignment for timer arrays
*/
timer_value
        : expression
        ;

/* 302 */
timer_ref
        : timer_identifier my_opt_array_or_bit_ref_list
        | timer_par_identifier my_opt_array_or_bit_ref_list
        ;



/* ------------- C O M P O N E N T    O P E R A T I O N S ---------------- */

/* 303 */
configuration_statements
        : connect_statement
        | map_statement
        | disconnect_statement
        | unmap_statement
        | done_statement
        | killed_statement
        | start_tc_statement
        | stop_tc_statement
        | kill_tc_statement
        ;

/* 304 */
configuration_ops
        : create_op
        | self_op
        | system_op
        | mtc_op
        | running_op
        | alive_op
        ;

/* 305 */
/* 
  STATIC SEMANTICS - Restrictions on single_expression see in clause 22.1
*/
create_op
        : component_type '.' create_keyword my_opt_single_expression opt_alive_keyword
        ;

/* 306 */
system_op
        : system_keyword
        ;

/* 307 */
self_op
        : T_SELF
        ;

/* 308 */
mtc_op
        : mtc_keyword
        ;

/* 309 */
done_statement
        : component_id '.' done_keyword
        ;

/* 310 */
killed_statement
        : component_id '.' killed_keyword
        ;

/* 311 */
component_id
        : component_or_default_reference
        | my_any_or_all_keyword component_keyword
        ;

/* 312 */
done_keyword
        : T_DONE
        ;

/* 313 */
killed_keyword
        : T_KILLED
        ;

/* 314 */
running_op
        : component_id '.' running_keyword
        ;

/* 315 */
running_keyword
        : T_RUNNING
        ;

/* 316 */
alive_op
        : component_id '.' alive_keyword
        ;

/* 317 */
create_keyword
        : T_CREATE
        ;

/* 318 */
opt_alive_keyword
        : /* empty */
        | alive_keyword
        ;

alive_keyword
        : T_ALIVE
        ;

/* 319 */
connect_statement
        : connect_keyword single_connection_spec
        ;

/* 320 */
connect_keyword
        : T_CONNECT
        ;

/* 321 */
single_connection_spec
        : '(' port_ref ',' port_ref ')'
        ;

/* 322 */
port_ref
        : component_ref ':' port
        ;

/* 323 */
component_ref
        : component_or_default_reference
        | system_op
        | self_op
        | mtc_op
        ;

/* 324 */
disconnect_statement
        : disconnect_keyword opt_single_or_multi_connection_spec
        ;

/* 325 */
opt_single_or_multi_connection_spec
        : /* empty */
        | single_connection_spec
        | all_connections_spec
        | all_ports_spec
        | all_comps_all_ports_spec
        | '(' error ')'
                { yyerrok; }
        ;

/* 326 */
all_connections_spec
        : '(' port_ref ')'
        ;

/* 327 */
all_ports_spec
        : '(' component_ref ':' all_keyword port_keyword ')'
        ;

/* 328 */
all_comps_all_ports_spec
        : '(' all_keyword component_keyword ':' all_keyword port_keyword ')'
        ;

/* 329 */
disconnect_keyword
        : T_DISCONNECT
        ;

/* 330 */
map_statement
        : map_keyword single_connection_spec
        ;

/* 331 */
map_keyword
        : T_MAP
        ;

/* 332 */
unmap_statement
        : unmap_keyword opt_single_or_multi_connection_spec
        ;

/* 333 */
unmap_keyword
        : T_UNMAP
        ;

/* 334 */
/* 
  STATIC SEMANTICS - The function instance may only have in parameters
*/
/* 
  STATIC SEMANTICS - The function instance shall not havetimer parameters
*/
start_tc_statement
        : component_or_default_reference '.' start_keyword '(' function_instance ')'
        | component_or_default_reference '.' start_keyword '(' error ')'
                { yyerrok; }
        ;

/* 335 */
start_keyword
        : T_START
        ;

/* 336 */
stop_tc_statement
        : stop_keyword
        | component_or_default_reference '.' stop_keyword
        | mtc_op '.' stop_keyword
        | self_op '.' stop_keyword
        | all_keyword component_keyword '.' stop_keyword
        ;

/* 338 */
/*
  My correction
*/
kill_tc_statement
        : kill_keyword
        | component_or_default_reference '.' kill_keyword
        | mtc_op '.' kill_keyword
        | self_op '.' kill_keyword
        | all_keyword component_keyword '.' kill_keyword
        ;

/* 339 */
/* 
  STATIC SEMANTICS - The variable associated with variable_ref or the return
                     type associated with function_instance must be of component
                     type when used in configuration statements and shall be of
                     default type when used in the deactivate statement
*/
component_or_default_reference
        : variable_ref
        | function_instance
        ;

/* 340 */
kill_keyword
        : T_KILL
        ;


/* ------------------ P O R T    O P E R A T I O N S --------------------- */

/* 341 */
port
        : port_identifier my_opt_array_or_bit_ref_list
        | port_par_identifier my_opt_array_or_bit_ref_list
        ;

/* 342 */
communication_statements
        : send_statement
        | call_statement
        | reply_statement
        | raise_statement
        | receive_statement
        | trigger_statement
        | get_call_statement
        | get_reply_statement
        | catch_statement
        | check_statement
        | clear_statement
        | start_statement
        | stop_statement
        ;
        
/* 343 */
send_statement
        : port '.' port_send_op
        ;

/* 344 */
port_send_op
        : send_op_keyword '(' send_parameter ')' opt_to_clause
        | send_op_keyword '(' error ')' opt_to_clause
                { yyerrok; }
        ;

/* 345 */
send_op_keyword
        : T_SEND
        ;

/* 346 */
send_parameter
        : template_instance
        ;

/* 347 */
/* 
  STATIC SEMANTICS - address_ref should not contain matching mechanisms
*/
opt_to_clause
        : /* empty */
        | to_keyword address_ref
        | address_ref_list
        | all_keyword component_keyword
        ;

/* 348 */
address_ref_list
        : '(' my_address_ref_list ')'
        | '(' error ')'
                { yyerrok; }
        ;

/* 349 */
to_keyword
        : T_TO
        ;

/* 350 */
/* 
  STATIC SEMANTICS - template_instance must be of address or component type
*/
address_ref
        : template_instance
        ;

/* 351 */
call_statement
        : port '.' port_call_op opt_port_call_body
        ;

/* 352 */
port_call_op
        : call_op_keyword '(' call_parameters ')' opt_to_clause
        | call_op_keyword '(' error ')' opt_to_clause
                { yyerrok; }
        ;

/* 353 */
call_op_keyword
        : T_CALL
        ;

/* 354 */
/* 
  STATIC SEMANTICS - only out parameters may be omitted or specified with
                     a matching attribute
*/
call_parameters
        : template_instance my_opt_call_timer_value
        ;

/* 355 */
/* 
  STATIC SEMANTICS - Value must be of type float
*/
call_timer_value
        : timer_value
        | nowait_keyword
        ;

/* 356 */
nowait_keyword
        : T_NOWAIT
        ;

/* 357 */
opt_port_call_body
        : /* empty */
        | '{' call_body_statement_list opt_semicolon '}'
        ;

/* 358 */
call_body_statement_list
        : call_body_statement
        | call_body_statement_list ';' call_body_statement
        ;

/* 359 */
call_body_statement
        : call_body_guard statement_block
        ;

/* 360 */
call_body_guard
        : alt_guard_char call_body_ops
        ;

/* 361 */
call_body_ops
        : get_reply_statement
        | catch_statement
        ;

/* 362 */
reply_statement
        : port '.' port_reply_op
        ;

/* 363 */
port_reply_op
        : reply_keyword '(' template_instance opt_reply_value ')' opt_to_clause
        | reply_keyword '(' error ')' opt_to_clause
                { yyerrok; }
        ;

/* 364 */
reply_keyword
        : T_REPLY
        ;

/* 365 */
opt_reply_value
        : /* empty */
        | value_keyword expression
        ;

/* 366 */
raise_statement
        : port '.' port_raise_op
        ;

/* 367 */
port_raise_op
        : raise_keyword '(' signature ',' template_instance ')' opt_to_clause
        | raise_keyword '(' error ')' opt_to_clause
                { yyerrok; }
        ;

/* 368 */
raise_keyword
        : T_RAISE
        ;

/* 369 */
receive_statement
        : port_or_any '.' port_receive_op
        ;

/* 370 */
port_or_any
        : port
        | any_keyword port_keyword
        ;

/* 371 */
/* 
  STATIC SEMANTICS - the opt_port_redirect option may only be present if the
                     receive_parameter option is also present
*/
port_receive_op
        : receive_op_keyword my_opt_receive_parameter
          opt_from_clause opt_port_redirect
        ;

/* 372 */
receive_op_keyword
        : T_RECEIVE
        ;

/* 373 */
receive_parameter
        : template_instance
        ;

/* 374 */
opt_from_clause
        : /* empty */
        | from_clause
        ;

from_clause
        : from_keyword address_ref
        ;

/* 375 */
from_keyword
        : T_FROM
        ;

/* 376 */
opt_port_redirect
        : /* empty */
        | port_redirect_symbol value_spec opt_sender_spec
        | port_redirect_symbol sender_spec
        ;

/* 377 */
port_redirect_symbol
        : T_REDIRECT
        ;

/* 378 */
value_spec
        : value_keyword variable_ref
        ;

/* 379 */
value_keyword
        : T_VALUE
        ;

/* 380 */
/* 
  STATIC SEMANTICS - variable_ref must be of address or component type
*/
opt_sender_spec
        : /* empty */
        | sender_spec
        ;

sender_spec
        : sender_keyword variable_ref
        ;

/* 381 */
sender_keyword
        : T_SENDER
        ;

/* 382 */
trigger_statement
        : port_or_any '.' port_trigger_op
        ;

/* 383 */
/* 
  STATIC SEMANTICS - the opt_port_redirect option may only be present if the
                     receive_parameter option is also present
*/
port_trigger_op
        : trigger_op_keyword my_opt_receive_parameter
          opt_from_clause opt_port_redirect
        ;

/* 384 */
trigger_op_keyword
        : T_TRIGGER
        ;

/* 385 */
get_call_statement
        : port_or_any '.' port_get_call_op
        ;

/* 386 */
/* 
  STATIC SEMANTICS - the opt_port_redirect_with_param option may only be present
                     if the receive_parameter option is also present
*/
port_get_call_op
        : get_call_op_keyword my_opt_receive_parameter
          opt_from_clause opt_port_redirect_with_param
        ;

/* 387 */
get_call_op_keyword
        : T_GETCALL
        ;

/* 388 */
opt_port_redirect_with_param
        : /* empty */
        | port_redirect_symbol redirect_with_param_spec
        ;

/* 389 */
redirect_with_param_spec
        : param_spec opt_sender_spec
        | sender_spec
        ;

/* 390 */
opt_param_spec
        : /* empty */
        | param_spec
        ;

param_spec
        : param_keyword param_assignment_list
        ;

/* 391 */
param_keyword
        : T_PARAM
        ;

/* 392 */
param_assignment_list
        : '(' assignment_list ')'
        | '(' variable_list ')'
        | '(' error ')'
                { yyerrok; }
        ;

/* 393 */
assignment_list
        : variable_assignment
        | assignment_list ',' variable_assignment
        ;

/* 394 */
/* 
  STATIC SEMANTICS - the parameter_identifier must be from the corresponding
                     signature definition
*/
variable_assignment
        : variable_ref '=' parameter_identifier
        ;

/* 395 */
parameter_identifier
        : value_par_identifier
        ;

/* 396 */
variable_list
        : variable_entry
        | variable_list ',' variable_entry
        ;

/* 397 */
variable_entry
        : variable_ref
        | not_used_symbol
        ;

/* 398 */
get_reply_statement
        : port_or_any '.' port_get_reply_op
        ;

/* 399 */
/* 
  STATIC SEMANTICS - the opt_port_redirect_with_value_and_param may only be present
                     if the my_opt_receive_parameter_with_match option is also present
*/
port_get_reply_op
        : get_reply_op_keyword my_opt_receive_parameter_with_match
          opt_from_clause opt_port_redirect_with_value_and_param
        ;

/* 400 */
opt_port_redirect_with_value_and_param
        : /* empty */
        | port_redirect_symbol redirect_with_value_and_param_spec
        ;

/* 401 */
redirect_with_value_and_param_spec
        : value_spec opt_param_spec opt_sender_spec
        | redirect_with_param_spec
        ;

/* 402 */
get_reply_op_keyword
        : T_GETREPLY
        ;

/* 403 */
opt_value_match_spec
        : /* empty */
        | value_keyword template_instance
        ;

/* 404 */
check_statement
        : port_or_any '.' port_check_op
        ;

/* 405 */
port_check_op
        : check_op_keyword my_opt_check_parameter
        ;

/* 406 */
check_op_keyword
        : T_CHECK
        ;

/* 407 */
check_parameter
        : check_port_ops_present
        | from_clause_present
        | redirect_present
        ;

/* 408 */
from_clause_present
        : from_clause
        | from_clause port_redirect_symbol sender_spec
        ;

/* 409 */
redirect_present
        : port_redirect_symbol sender_spec
        ;

/* 410 */
check_port_ops_present
        : port_receive_op
        | port_get_call_op
        | port_get_reply_op
        | port_catch_op
        ;

/* 411 */
catch_statement
        : port_or_any '.' port_catch_op
        ;

/* 412 */
/* 
  STATIC SEMANTICS - the opt_port_redirect option may only be present if the
                     receive_parameter option is also present
*/
port_catch_op
        : catch_op_keyword my_opt_catch_op_parameter
          opt_from_clause opt_port_redirect
        ;

/* 413 */
catch_op_keyword
        : T_CATCH
        ;

/* 414 */
catch_op_parameter
        : signature ',' template_instance
        | timeout_keyword
        ;

/* 415 */
clear_statement
        : port '.' port_clear_op
        | all_keyword port_keyword '.' port_clear_op
        ;

/* 417 */
port_clear_op
        : clear_op_keyword
        ;

/* 418 */
clear_op_keyword
        : T_CLEAR
        ;

/* 419 */
start_statement
        : port '.' port_start_op
        | all_keyword port_keyword '.' port_start_op
        ;

/* 420 */
port_start_op
        : start_keyword
        ;

/* 421 */
stop_statement
        : port '.' port_stop_op
        | all_keyword port_keyword '.' port_stop_op
        ;

/* 422 */
port_stop_op
        : stop_keyword
        ;

/* 423 */
stop_keyword
        : T_STOP
        ;

/* 424 */
any_keyword
        : T_ANY
        ;



/* ----------------- T I M E R    O P E R A T I O N S -------------------- */

/* 425 */
timer_statements
        : timer_ref '.' start_keyword my_opt_timer_value
        | timer_ref '.' stop_keyword
        | all_keyword timer_keyword '.' stop_keyword
        | timer_ref '.' timeout_keyword
        | any_keyword timer_keyword '.' timeout_keyword
        ;

/* 426 */
timer_ops
        : read_timer_op
        | running_timer_op
        ;

/* 430 */
read_timer_op
        : timer_ref '.' read_keyword
        ;

/* 431 */
read_keyword
        : T_READ
        ;

/* 432 */
running_timer_op
        : timer_ref_or_any '.' running_keyword
        ;

/* 433 */
timeout_statement
        : timer_ref_or_any '.' timeout_keyword
        ;

/* 434 */
timer_ref_or_any
        : timer_ref
        | any_keyword timer_keyword
        ;

/* 435 */
timeout_keyword
        : T_TIMEOUT
        ;




/* ******************************* T Y P E ******************************* */

/* 436 */
type
        : predefined_type
        | referenced_type
                { $$ = TTCN3_NONE; }
        ;

/* 437 */
predefined_type
        : bitstring_keyword
                { $$ = TTCN3_BITSTING; }
        | boolean_keyword
                { $$ = TTCN3_BOOLEAN; }
        | charstring_keyword
                { $$ = TTCN3_CHARSTRING; }
        | universal_charstring_keyword
                { $$ = TTCN3_UNIVERSAL_CHARSTRING; }
        | integer_keyword
                { $$ = TTCN3_INTEGER; }
        | octetstring_keyword
                { $$ = TTCN3_OCTETSTRING; }
        | hexstring_keyword
                { $$ = TTCN3_HEXSTRING; }
        | verdict_type_keyword
                { $$ = TTCN3_VERDICT_TYPE; }
        | float_keyword
                { $$ = TTCN3_FLOAT; }
        | address_keyword
                { $$ = TTCN3_ADDRESS; }
        | default_keyword
                { $$ = TTCN3_DEFAULT; }
        | any_type_keyword
                { $$ = TTCN3_ANY_TYPE; }
        ;

/* 438 */
bitstring_keyword
        : T_BITSTRING
        ;

/* 439 */
boolean_keyword
        : T_BOOLEAN
        ;

/* 440 */
integer_keyword
        : T_INTEGER
        ;

/* 441 */
octetstring_keyword
        : T_OCTETSTRING
        ;

/* 442 */
hexstring_keyword
        : T_HEXSTRING
        ;

/* 443 */
verdict_type_keyword
        : T_VERDICTTYPE
        ;

/* 444 */
float_keyword
        : T_FLOAT
        ;

/* 445 */
address_keyword
        : T_ADDRESS
        ;

/* 446 */
default_keyword
        : T_DEFAULT
        ;

/* 447 */
any_type_keyword
        : T_ANYTYPE
        ;

/* 448 */
charstring_keyword
        : T_CHARSTRING
        ;

/* 449 */
universal_charstring_keyword
        : universal_keyword charstring_keyword
        ;

/* 450 */
universal_keyword
        : T_UNIVERSAL
        ;

/* 451 */
referenced_type
        : my_opt_module_prefix type_reference opt_extended_field_reference
        | my_opt_module_prefix error opt_extended_field_reference
                { yyerrok; }
        ;

/* 452 */
type_reference
        : struct_type_identifier opt_type_actual_par_list       %dprec 2
        | enum_type_identifier                  %dprec 2
        | sub_type_identifier                   %dprec 2
        | component_type_identifier             %dprec 2
        | identifier                            %dprec 1
                { 
/*                   yyclearin; */
                  char buf[128];
                  sprintf(buf, "'%s' type not defined", $1->Name().c_str());
                  yyerror(&@1, file, buf);
                  YYERROR;
                }
        ;

/* 453 */
opt_type_actual_par_list
        : /* empty */
        | '(' my_type_actual_par_list ')'
        | '(' error ')'
                { yyerrok; }
        ;

/* 454 */
type_actual_par
        : constant_expression
        ;

/* 455 */
opt_array_def
        : /* empty */
        | array_def
        ;

array_def
        : my_array_bounds
        | array_def my_array_bounds
        ;

/* 456 */
/* 
  STATIC SEMANTICS - array_bounds will resolve to a non negative value of
                     integer type
*/
array_bounds
        : single_const_expression
        ;


/* ****************************** V A L U E ****************************** */

/* 457 */
value
        : predefined_value
        | referenced_value
        ;

/* 458 */
predefined_value
        : bitstring_value
        | boolean_value
        | charstring_value
        | integer_value
        | octetstring_value
        | hexstring_value
        | verdict_type_value
        | enumerated_value
        | float_value
        | address_value
        | omit_value
        ;

/* 459 */
bitstring_value
        : b_string
        ;

/* 460 */
boolean_value
        : T_TRUE
        | T_FALSE
        ;

/* 461 */
integer_value
        : number
        ;

/* 462 */
octetstring_value
        : o_string
        ;

/* 463 */
hexstring_value
        : h_string
        ;

/* 464 */
verdict_type_value
        : T_PASS
        | T_FAIL
        | T_INCONC
        | T_NONE
        | T_ERROR
        ;

/* 465 */
enumerated_value
        : enumeration_identifier        %dprec 2
                { $$ = 0 }
        | identifier                    %dprec 1
                { 
/*                   yyclearin; */

                  char buf[128];
                  sprintf(buf, "'%s' not defined", $1->Name().c_str());
                  yyerror(&@1, file, buf);
                  YYERROR;
                }
        ;

/* 466 */
charstring_value
        : c_string
        | quadruple
        ;

/* 467 */
quadruple
        : char_keyword '(' group ',' plane ',' row ',' cell ')'
        | char_keyword '(' error ')'
                { yyerrok; }
        ;

/* 468 */
char_keyword
        : T_CHAR
        ;

/* 469 */
group
        : number
        ;

/* 470 */
plane
        : number
        ;

/* 471 */
row
        : number
        ;

/* 472 */
cell
        : number
        ;

/* 473 */
float_value
        : T_FLOAT_VAL
        ;

/* 477 */
referenced_value
        : value_reference opt_extended_field_reference
        ;

/* 478 */
value_reference
        : my_opt_module_prefix const_identifier
        | my_opt_module_prefix ext_const_identifier
        | my_opt_module_prefix module_par_identifier
        | value_par_identifier
        | var_identifier
        ;

/* 479 */
number
        : T_INT_VAL
        ;

/* 483 */
b_string
        : T_B_STRING
        ;

/* 485 */
h_string
        : T_H_STRING
        ;

/* 487 */
o_string
        : T_O_STRING
        ;

/* 489 */
c_string
        : T_C_STRING
        ;

/* 491 */
identifier
        : T_ID                          %dprec 2
                { $$ = new TTCN3::CIdentifier(file, @1, $1); }
        | T_REDEFINED_ID                %dprec 1
                { 
/*                   yyclearin; */

                  const YYLTYPE &loc = $1->Location();
                  char buf[128];

                  sprintf(buf, "'%s' redefined", $1->Name().c_str());
                  yyerror(&@1, file, buf);
                  yyerror(&loc, file, "First defined here");
                  YYERROR;
                }
        | T_U_ID                        %dprec 1
                {
/*                   yyclearin; */
                  char buf[128];
                  sprintf(buf, "'%s' - TTCN-3 identifiers can not start with '_' symbol", $1);
                  yyerror(&@1, file, buf);
                  YYERROR;
                }
        | T_D_ID                        %dprec 1
                {
/*                   yyclearin; */
                  char buf[128];
                  sprintf(buf, "'%s' - TTCN-3 identifiers can not start with a digit", $1);
                  yyerror(&@1, file, buf);
                  YYERROR;
                }
        | definition_ref                %dprec 1
                {
/*                   yyclearin; */

                  const YYLTYPE &loc = $1->Location();
                  char buf[128];

                  sprintf(buf, "'%s' already defined", $1->Name().c_str());
                  yyerror(&@1, file, buf);
                  yyerror(&loc, file, "First defined here");
                  YYERROR;
                }
        ;

/* 497 */
free_text
        : T_TEXT
        ;

/* 498 */
address_value
        : T_NULL
        ;

/* 499 */
omit_value
        : omit_keyword
        ;

/* 500 */
omit_keyword
        : T_OMIT
        ;



/* ******************** P A R A M E T R I Z A T I O N ******************** */

/* 501 */
in_par_keyword
        : T_IN
        ;

/* 502 */
out_par_keyword
        : T_OUT
        ;

/* 503 */
opt_inout_par_keyword
        : /* empty */
        | inout_par_keyword
        ;

inout_par_keyword
        : T_INOUT
        ;

/* 504 */
formal_value_par
        : my_opt_dir_spec type identifier
                { $3->Type(T_VALUE_PAR_ID); }
        ;

/* 505 */
value_par_identifier
        : T_VALUE_PAR_ID
        ;

/* 506 */
formal_port_par
        : opt_inout_par_keyword port_type_identifier identifier
                { $3->Type(T_PORT_PAR_ID); }
        ;

/* 507 */
port_par_identifier
        : T_PORT_PAR_ID
        ;

/* 508 */
formal_timer_par
        : opt_inout_par_keyword timer_keyword identifier
                { $3->Type(T_TIMER_PAR_ID); }
        ;

/* 509 */
timer_par_identifier
        : T_TIMER_PAR_ID
        ;

/* 510 */
formal_template_par
        : my_opt_dir_spec template_keyword type identifier
                { $4->Type(T_TEMPL_PAR_ID); }
        ;

/* 511 */
template_par_identifier
        : T_TEMPL_PAR_ID
        ;



/* ********************* W I T H   S T A T E M E N T ********************* */

/* 512 */
opt_with_statement
        : /* empty */
        | with_keyword with_attrib_list
        ;

/* 513 */
with_keyword
        : T_WITH
        ;

/* 514 */
with_attrib_list
        : '{' multi_with_attrib '}'
        ;

/* 515 */
multi_with_attrib
        : /* empty */
        | my_multi_with_attrib opt_semicolon
        ;

/* 516 */
single_with_attrib
        : attrib_keyword opt_override_keyword opt_attrib_qualifier attrib_spec
        ;

/* 517 */
attrib_keyword
        : encode_keyword
        | variant_keyword
        | display_keyword
        | extension_keyword
        ;

/* 518 */
encode_keyword
        : T_ENCODE
        ;

/* 519 */
variant_keyword
        : T_VARIANT
        ;

/* 520 */
display_keyword
        : T_DISPLAY
        ;

/* 521 */
extension_keyword
        : T_EXTENSION
        ;

/* 522 */
opt_override_keyword
        : /* empty */
        | T_OVERRIDE
        ;

/* 523 */
opt_attrib_qualifier
        : /* empty */
        | '(' def_or_field_ref_list ')'
        | '(' error ')'
                { yyerrok; }
        ;

/* 524 */
def_or_field_ref_list
        : def_or_field_ref
        | def_or_field_ref_list ',' def_or_field_ref
        ;

/* 525 */
/* 
  STATIC SEMANTICS - the def_or_field_ref must refer to a definition or field
                     which is within the module, group or definition to which
                     the with statement is associated
*/
def_or_field_ref
        : definition_ref
        | field_reference
        | all_ref
        ;

/* 526 */
definition_ref
        : struct_type_identifier
        | enum_type_identifier
        | port_type_identifier
        | component_type_identifier
        | sub_type_identifier
        | const_identifier
        | template_identifier
        | altstep_identifier
        | testcase_identifier
        | function_identifier
        | signature_identifier
        | var_identifier
        | timer_identifier
        | port_identifier
        | module_par_identifier
        | full_group_identifier
        ;

/* 527 */
all_ref
        : group_keyword all_keyword
        | group_keyword all_keyword except_keyword '{' group_ref_list '}'
        | type_def_keyword all_keyword
        | type_def_keyword all_keyword except_keyword '{' type_ref_list '}'
        | template_keyword all_keyword
        | template_keyword all_keyword except_keyword '{' template_ref_list '}'
        | const_keyword all_keyword
        | const_keyword all_keyword except_keyword '{' const_ref_list '}'
        | altstep_keyword all_keyword
        | altstep_keyword all_keyword except_keyword '{' altstep_ref_list '}'
        | testcase_keyword all_keyword
        | testcase_keyword all_keyword except_keyword '{' testcase_ref_list '}'
        | function_keyword all_keyword
        | function_keyword all_keyword except_keyword '{' function_ref_list '}'
        | signature_keyword all_keyword
        | signature_keyword all_keyword except_keyword '{' signature_ref_list '}'
        | module_par_keyword all_keyword
        | module_par_keyword all_keyword except_keyword '{' module_par_ref_list '}'
        ;

/* 528 */
attrib_spec
        : free_text
        ;



/* ************** B E H A V I O U R   S T A T E M E N T S **************** */

/* 529 */
/* 
  STATIC SEMANTICS - testcase_instance shall not be called from within an existing
                     executing testcase or function chain called from a testcase
                     i.e. testcases can only be instantiated from the control part
                     or from functions directly called from the control part
*/
/* 
  STATIC SEMANTICS - activate_op shall not be called from within the module control
                     part
*/
behaviour_statements
        : testcase_instance
        | function_instance
        | return_statement
        | alt_construct
        | interleaved_construct
        | label_statement
        | goto_statement
        | repeat_statement
        | deactivate_statement
        | altstep_instance
        | activate_op
        ;

/* 530 */
verdict_statements
        : set_local_verdict
        ;

/* 531 */
verdict_ops
        : get_local_verdict
        ;

/* 532 */
/*
  STATIC SEMANTICS - single_expression must resolve to a value of type verdict
*/
/*
  STATIC SEMANTICS - the set_local_verdict shall no be used to assign the value
                     error
*/
set_local_verdict
        : set_verdict_keyword '(' single_expression ')'
        | set_verdict_keyword '(' error ')'
                { yyerrok; }
        ;

/* 533 */
set_verdict_keyword
        : T_SETVERDICT
        ;

/* 534 */
get_local_verdict
        : T_GETVERDICT
        ;

/* 535 */
sut_statements
        : action_keyword '(' opt_action_text my_opt_string_action_text_list ')'
        | action_keyword '(' error ')'
                { yyerrok; }
        ;

/* 536 */
action_keyword
        : T_ACTION
        ;

/* 537 */
/*
  STATIC SEMANTICS - expression shall have the base type charstring or universal
                     charstring
*/
opt_action_text
        : /* empty */
        | action_text
        ;

action_text
        : free_text
        | expression
        ;

/* 538 */
return_statement
        : return_keyword opt_expression
        ;

/* 539 */
alt_construct
        : alt_keyword '{' opt_alt_guard_list '}'
        ;

/* 540 */
alt_keyword
        : T_ALT
        ;

/* 541 */
opt_alt_guard_list
        : /* empty */
        | alt_guard_list
        ;

alt_guard_list
        : my_alt_guard_list
        ;

/* 542 */
guard_statement
        : alt_guard_char altstep_instance opt_statement_block
        | alt_guard_char guard_op statement_block
        ;

/* 543 */
else_statement
        : '[' else_keyword ']' statement_block
        ;

/* 544 */
/*
  STATIC SEMANTICS - opt_boolean_expression shall conform to restrictions in
                     clause 20.1.2 of ES 201 873-1
*/
alt_guard_char
        : '[' opt_boolean_expression ']'
        ;

/* 545 */
/*
  STATIC SEMANTICS - guard_op used within the module control part shall only
                     contain the timeout_statement
*/
guard_op
        : timeout_statement
        | receive_statement
        | trigger_statement
        | get_call_statement
        | catch_statement
        | check_statement
        | get_reply_statement
        | done_statement
        | killed_statement
        ;

/* 546 */
interleaved_construct
        : interleaved_keyword '{' interleaved_guard_list opt_semicolon '}'
        ;

/* 547 */
interleaved_keyword
        : T_INTERLEAVE
        ;

/* 548 */
interleaved_guard_list
        : interleaved_guard_element
        | interleaved_guard_list ';' interleaved_guard_element
        ;

/* 549 */
interleaved_guard_element
        : interleaved_guard interleaved_action
        ;

/* 550 */
interleaved_guard
        : '[' ']' guard_op
        ;

/* 551 */
/*
  STATIC SEMANTICS - the statement_block may not contain loop statements,
                     goto, activate, deactivate, stop, return or calls
                     to functions
*/
interleaved_action
        : statement_block
        ;

/* 552 */
label_statement
        : label_keyword identifier
                { $2->Type(T_LABEL_ID); }
        ;

/* 553 */
label_keyword
        : T_LABEL
        ;

/* 554 */
label_identifier
        : T_LABEL_ID
        ;

/* 555 */
goto_statement
        : goto_keyword label_identifier
        ;

/* 556 */
goto_keyword
        : T_GOTO
        ;

/* 557 */
repeat_statement
        : T_REPEAT
        ;

/* 558 */
activate_op
        : activate_keyword '(' altstep_instance ')'
        | activate_keyword '(' error ')'
                { yyerrok; }
        ;

/* 559 */
activate_keyword
        : T_ACTIVATE
        ;
        
/* 560 */
deactivate_statement
        : deactivate_keyword
        | deactivate_keyword '(' component_or_default_reference ')'
        | deactivate_keyword '(' error ')'
                { yyerrok; }
        ;

/* 561 */
deactivate_keyword
        : T_DEACTIVATE
        ;
        


/* ****************** B A S I C   S T A T E M E N T S ******************** */

/* 562 */
basic_statements
        : assignment
        | log_statement
        | loop_construct
        | conditional_construct
        | select_case_construct
        ;

/* 563 */
/*
  STATIC SEMANTICS - expression shall not contain configuration, activate
                     operation or verdict operations within the module
                     control part
*/
opt_expression
        : /* empty */
        | expression
        ;

expression
        : single_expression
        | compound_expression
        ;

/* 564 */
/*
  STATIC SEMANTICS - Within compound_expression the array_expression can
                     be used for arrays, record, record of and set of types
*/
compound_expression
        : field_expression_list
        | array_expression
        ;

/* 565 */
field_expression_list
        : '{' my_field_expression_list '}'
        ;

/* 566 */
field_expression_spec
        : field_reference '=' not_used_or_expression
        ;

/* 567 */
array_expression
        : '{' opt_array_element_expression_list '}'
        ;

/* 568 */
opt_array_element_expression_list
        : /* empty */
        | my_opt_array_element_expression_list
        ;

/* 569 */
not_used_or_expression
        : expression
        | not_used_symbol
        ;

/* 570 */
constant_expression
        : single_const_expression
        | compound_const_expression
        ;

/* 571 */
/*
  STATIC SEMANTICS - single_const_expression shall not contain variables
                     or module parameters and shall resolve to a constant
                     value at compile time
*/
single_const_expression
        : single_expression
        ;

/* 572 */
/*
  STATIC SEMANTICS - opt_boolean_expression shall resolve to a value of type
                     boolean
*/
opt_boolean_expression
        : /* empty */
        | boolean_expression
        ;

boolean_expression
        : single_expression
        ;

/* 573 */
/*
  STATIC SEMANTICS - Within compound_const_expression the array_const_expression
                     can be used for arrays, record, record of and set of types
*/
compound_const_expression
        : field_const_expression_list
        | array_const_expression
        ;

/* 574 */
field_const_expression_list
        : '{' my_field_const_expression_list '}'
        ;

/* 575 */
field_const_expression_spec
        : field_reference '=' constant_expression
        ;

/* 576 */
array_const_expression
        : '{' opt_array_element_const_expression_list '}'
        ;

/* 577 */
opt_array_element_const_expression_list
        : /* empty */
        | my_opt_array_element_const_expression_list
        ;

/* 578 */
/*
  STATIC SEMANTICS - The expression on the right hand side of assignment shall
                     evaluate to an explicit value of a type compatible with
                     the type of the left hand side for value variables and
                     shall evaluate to an explicit value, template (literal
                     or a template instance) or a matching mechanism compatible
                     with the type of the left hand side for template variables
*/
assignment
        : variable_ref '=' expression
        | variable_ref '=' template_body
        ;

/* 579 */
/*
  STATIC SEMANTICS - If more than one xor_expression exists, then the xor_expressions
                     shall evaluate to specific values of compatible types
*/
single_expression
        : xor_expression
        | single_expression T_OR xor_expression
        ;

/* 580 */
/*
  STATIC SEMANTICS - If more than one and_expression exists, then the and_expressions
                     shall evaluate to specific values of compatible types
*/
xor_expression
        : and_expression
        | xor_expression T_XOR and_expression
        ;

/* 581 */
/*
  STATIC SEMANTICS - If more than one not_expression exists, then the not_expressions
                     shall evaluate to specific values of compatible types
*/
and_expression
        : not_expression
        | and_expression T_AND not_expression
        ;

/* 582 */
/*
  STATIC SEMANTICS - Operands of the not operator shall be of type boolean (TTCN
                     and ASN.1) or derivatives of type boolean
*/
not_expression
        : T_NOT equal_expression
        | equal_expression
        ;

/* 583 */
/*
  STATIC SEMANTICS - If more than one rel_expression exists, then the rel_expressions
                     shall evaluate to specific values of compatible types
*/
equal_expression
        : rel_expression
        | equal_expression equal_op rel_expression
        ;

/* 584 */
/*
  STATIC SEMANTICS - If more than one shift_expression exists, then the shift_expression
                     shall evaluate to specific values of compatible types
*/
rel_expression
        : shift_expression
        | rel_expression rel_op shift_expression
        ;

/* 585 */
/*
  STATIC SEMANTICS - Each result shall resolve to a specific value. If more
                     than one result exists the right hand operand shall be
                     of type integer or derivatives and if the shift op is
                     '<<' or '>>' then the left hand operand shall resolve
                     to either bitstring, hexstring or octetstring type or
                     derivatives of these types. If the shift op is '<@' or
                     '@>' then the left hand operand shall be of type
                     bitstring, hexstring, charstring or universal charstring
                     or derivatives of these types
*/
shift_expression
        : bit_or_expression
        | shift_expression shift_op bit_or_expression
        ;

/* 586 */
/*
  STATIC SEMANTICS - If more than one bit_xor_expression exists, then the 
                     bit_xor_expression shall evaluate to specific values of
                     compatible types
*/
bit_or_expression
        : bit_xor_expression
        | bit_or_expression T_OR4B bit_xor_expression
        ;

/* 587 */
/*
  STATIC SEMANTICS - If more than one bit_and_expression exists, then the 
                     bit_and_expression shall evaluate to specific values of
                     compatible types
*/
bit_xor_expression
        : bit_and_expression
        | bit_xor_expression T_XOR4B bit_and_expression
        ;

/* 588 */
/*
  STATIC SEMANTICS - If more than one bit_not_expression exists, then the 
                     bit_not_expression shall evaluate to specific values of
                     compatible types
*/
bit_and_expression
        : bit_not_expression
        | bit_and_expression T_AND4B bit_not_expression
        ;

/* 589 */
/*
  STATIC SEMANTICS - If the not4b operator exists, the operand shall be of
                     type bitstring, octetstring or hexstring or derivatives
                     of these types
*/
bit_not_expression
        : T_NOT4B add_expression
        | add_expression
        ;

/* 590 */
/*
  STATIC SEMANTICS - Each mul_expression shall resolve to a specific value.
                     If more than one mul_expression exists and tha add_op
                     resolves to string_op then the mul_expression shall
                     resolve to same type which shall be of bitstring,
                     hexstring, octetstring, charstring or universal
                     charstring or derivatives of these types. If more
                     than one mul_expression exists and the add_op does
                     not resolve string_op then the mul_expression shall
                     both resolve to type integer or float or derivatives
                     of these types.
*/
add_expression
        : mul_expression
        | add_expression add_op mul_expression
        ;

/* 591 */
/*
  STATIC SEMANTICS - Each unary_expression shall resolve to a specific value.
                     If more than one unary_expression exists then the
                     unary_expression shall resolve to type integer or float
                     or derivatives of these types.
*/
mul_expression
        : unary_expression
        | mul_expression multiply_op unary_expression
        ;

/* 592 */
/*
  STATIC SEMANTICS - primary shall resolve to a specific value of type integer
                     or float or derivatives of these types.
*/
unary_expression
        : unary_op primary
        | primary
        ;

/* 593 */
primary
        : op_call
        | value
        | '(' single_expression ')'
        | '(' error ')'
                { yyerrok; }
        ;

/* 594 */
/*
  STATIC SEMANTICS - the type_def_identifier shall be used only if the type
                     of the var_instance or referenced_value in which the
                     opt_extended_field_reference is used is anytype.
*/
opt_extended_field_reference
        : /* empty */
        | my_extended_field_reference_list
        ;

/* 595 */
op_call
        : configuration_ops
        | verdict_ops
        | timer_ops
        | testcase_instance
        | function_instance
        | template_ops
        | activate_op
        ;

/* 596 */
/*
  STATIC SEMANTICS - Operands of the '+' or '-' operators shall be of type integer
                     or float or derivations of integer or float (i.e. subrange).
*/
add_op
        : '+'
        | '-'
        | string_op
        ;

/* 597 */
/*
  STATIC SEMANTICS - Operands of the '*', '/', rem or mod operators shall be of
                     type integer or float or derivations of integer or float
                     (i.e. subrange).
*/
multiply_op
        : '*'
        | '/'
        | T_MOD
        | T_REM
        ;

/* 598 */
/*
  STATIC SEMANTICS - Operands of the '+' or '-' operators shall be of type integer
                     or float or derivations of integer or float (i.e. subrange).
*/
unary_op
        : '+'
        | '-'
        ;

/* 599 */
/*
  STATIC SEMANTICS - The precedence of the operators is defined in Table 7
*/
rel_op
        : T_LESS
        | T_GREATER
        | T_NOT_GREATER
        | T_NOT_LESS
        ;

/* 600 */
equal_op
        : T_EQUAL
        | T_NOT_EQUAL
        ;

/* 601 */
/*
  STATIC SEMANTICS - Operands of the string operator shall be bitstring, hexstring,
                     octetstring or character string
*/
string_op
        : '&'
        ;

/* 602 */
shift_op
        : T_SHIFT_LEFT
        | T_SHIFT_RIGHT
        | T_ROTATE_LEFT
        | T_ROTATE_RIGHT
        ;

/* 603 */
log_statement
        : log_keyword '(' my_log_item_list ')'
        | log_keyword '(' error ')'
                { yyerrok; }
        ;
        
/* 604 */
log_keyword
        : T_LOG
        ;

/* 605 */
log_item
        : free_text
        | template_instance
        ;

/* 606 */
loop_construct
        : for_statement
        | while_statement
        | do_while_statement
        ;

/* 607 */
for_statement
        : for_keyword '(' initial ';' final ';' step ')'
          statement_block
        | for_keyword '(' error ')' statement_block
                { yyerrok; }
        ;

/* 608 */
for_keyword
        : T_FOR
        ;

/* 609 */
initial
        : var_instance | assignment
        ;

/* 610 */
final
        : boolean_expression
        ;

/* 611 */
step
        : assignment
        ;

/* 612 */
while_statement
        : while_keyword '(' boolean_expression ')' statement_block
        | while_keyword '(' error ')' statement_block
                { yyerrok; }
        ;

/* 613 */
while_keyword
        : T_WHILE
        ;

/* 614 */
do_while_statement
        : do_keyword statement_block
          while_keyword '(' boolean_expression ')'
        | do_keyword statement_block
          while_keyword '(' error ')'
                { yyerrok; }
        ;

/* 615 */
do_keyword
        : T_DO
        ;

/* 616 */
conditional_construct
        : if_keyword '(' boolean_expression ')'
          statement_block
          opt_else_if_clause opt_else_clause
        | if_keyword '(' error ')'
          statement_block
          opt_else_if_clause opt_else_clause
                { yyerrok; }
        ;

/* 617 */
if_keyword
        : T_IF
        ;

/* 618 */
opt_else_if_clause
        : /* empty */
        | else_keyword if_keyword '(' boolean_expression ')' statement_block
        | else_keyword if_keyword '(' error ')' statement_block
                { yyerrok; }
        ;

/* 619 */
else_keyword
        : T_ELSE
        ;

/* 620 */
opt_else_clause
        : /* empty */
        | else_keyword statement_block
        ;

/* 621 */
select_case_construct
        : select_keyword '(' single_expression ')' select_case_body
        | select_keyword '(' error ')' select_case_body
                { yyerrok; }
        ;

/* 622 */
select_keyword
        : T_SELECT
        ;

/* 623 */
select_case_body
        : '{' my_select_case_list '}'
        ;

/* 624 */
select_case
        : case_keyword my_select_case statement_block
        ;

/* 625 */
case_keyword
        : T_CASE
        ;





my_type
        : type    
        | nested_type_def
                { $$ = TTCN3_NONE; }
        ;

my_opt_type_prefix
        : /* empty */
        | proc_or_type ':'
        ;

my_struct_type
        : my_struct_type_id
        | address_keyword
        ;

my_struct_type2
        : identifier
                { $1->Type(T_STRUCT_TYPE_ID); }
        | address_keyword
        ;

my_struct_type_id
        : identifier opt_struct_def_formal_par_list
                { $1->Type(T_STRUCT_TYPE_ID); }
        ;

my_opt_struct_def_formal_par_list
        : struct_def_formal_par
        | my_opt_struct_def_formal_par_list ',' struct_def_formal_par
        ;

my_opt_struct_def_item
        : /* empty */
        | my_opt_struct_def_item_list
        ;

my_opt_struct_def_item_list
        : struct_field_def
        | my_opt_struct_def_item_list ',' struct_field_def
        ;

my_union_def_item
        : union_field_def
        | my_union_def_item ',' union_field_def
        ;

my_enum_type
        : identifier
                { $1->Type(T_ENUM_TYPE_ID); }
        | address_keyword
        ;

my_opt_enum_initializer
        : /* empty */
        | '(' my_signed_number ')'
        | '(' error ')'
                { yyerrok; }
        ;

my_sub_type_type
        : identifier
                { $1->Type(T_SUB_TYPE_ID); }
        | address_keyword
        ;

my_allowed_value
        : my_value_or_range_list
        | charstring_match
        ;

my_value_or_range_list
        : value_or_range
        | my_value_or_range_list ',' value_or_range
        ;

my_opt_upper_bound
        : /* empty */
        | T_RANGE upper_bound
        ;

my_opt_module_prefix
        : /* empty */
        | module_id '.'
        ;

my_message_list
        : message_list
        | my_message_list ';' message_list
        | error ';'
        ;

my_procedure_list
        : procedure_list
        | my_procedure_list ';' procedure_list
        | my_procedure_list ';' error ';'
                { yyerrok; }
        ;

my_mixed_list
        : mixed_list
        | my_mixed_list ';' mixed_list
        | my_mixed_list ';' error ';'
                { yyerrok; }
        ;

my_proc_or_type_list
        : proc_or_type
        | my_proc_or_type_list ',' proc_or_type
        ;

my_opt_extends_component
        : /* empty */
        | extends_keyword my_component_type_list
        ;

my_component_type_list
        : component_type
        | my_component_type_list ',' component_type
        ;

my_port_element_list
        : port_element
        | my_port_element_list ',' port_element
        ;

my_opt_component_def_list
        : component_element_def
        | my_opt_component_def_list ';' component_element_def
        | error ';'
        ;

my_opt_derived_def
        : /* empty */
        | derived_def
        ;

my_opt_template_formal_par_list
        : /* empty */
        | '(' template_formal_par_list ')'
        | '(' error ')'
                { yyerrok; }
        ;

my_template_spec
        : simple_spec
        | field_spec_list
        | array_value_or_attrib
        | '{' error '}'
                { yyerrok; }
        ;

my_opt_field_spec_list
        : field_spec
        | my_opt_field_spec_list ',' field_spec
        ;

my_constant_expression_list
        : constant_expression
        | my_constant_expression_list ',' constant_expression
        ;

my_template_body_list
        : template_body
        | my_template_body_list ',' template_body
        ;

my_template_body_list2
        : template_body ',' template_body
        | my_template_body_list2 ',' template_body
        ;

my_opt_derived_ref_with_par_list
        : /* empty */
        | derived_ref_with_par_list '='
        ;

my_template_actual_par_list
        : template_actual_par
        | my_template_actual_par_list ',' template_actual_par
        ;

my_opt_function_statement_or_def_list
        : function_statement_or_def
        | my_opt_function_statement_or_def_list ';' function_statement_or_def
        ;

my_function_identifier
        : function_identifier
        | ext_function_identifier
        ;

my_opt_signature_type
        : return_type
        | no_block_keyword
        ;

my_opt_testcase_timer_value
        : /* empty */
        | ',' timer_value
        ;

my_altstep_local_def_list
        : altstep_local_def
        | my_altstep_local_def_list ';' altstep_local_def
        ;

my_import_spec
        : all_with_excepts
        | '{' import_spec '}'
                { $$ = 0; }
        ;

my_except_spec
        : except_element
                { 
                  if ($1) {
                    $$ = new TTCN3::CSemicolonList(file, @1);
                    $$->Add(*$1);
                  }
                  else
                    $$ = 0;  
                }
        | my_except_spec ';' except_element
                { 
                  if ($3) {
                    if (!$1)
                      $$ = new TTCN3::CSemicolonList(file, @1);
                    else
                      $$ = $1;
                    $$->Add(*$3);
                  }
                  else
                    $$ = 0;
                }
        ;

my_import_spec_list
        : import_element
        | my_import_spec_list ';' import_element
        ;

my_opt_except_group_ref_list
        : /* empty */
        | except_keyword group_ref_list
        ;

my_opt_except_type_ref_list
        : /* empty */
        | except_keyword type_ref_list
        ;

my_opt_except_template_ref_list
        : /* empty */
        | except_keyword template_ref_list
        ;

my_opt_except_const_ref_list
        : /* empty */
        | except_keyword const_ref_list
        ;

my_opt_except_altstep_ref_list
        : /* empty */
        | except_keyword altstep_ref_list
        ;

my_opt_except_testcase_ref_list
        : /* empty */
        | except_keyword testcase_ref_list
        ;

my_opt_except_function_ref_list
        : /* empty */
        | except_keyword function_ref_list
        ;

my_opt_except_signature_ref_list
        : /* empty */
        | except_keyword signature_ref_list
        ;

my_opt_except_module_par_ref_list
        : /* empty */
        | except_keyword module_par_ref_list
        ;

my_opt_assign_constant
        : /* empty */
        | '=' constant_expression
        ;

my_opt_control_statement_or_def_list
        : control_statement_or_def
        | my_opt_control_statement_or_def_list ';' control_statement_or_def
        ;

my_opt_assign_init_value
        : /* empty */
        | '=' var_initial_value
        ;

my_opt_assign_temp_init_value
        : /* empty */
        | '=' temp_var_initial_value
        ;

my_opt_assign_timer_value
        : /* empty */
        | '=' timer_value
        ;

my_opt_array_or_bit_ref_list
        : /* empty */
        | my_array_or_bit_ref_list
        ;

my_array_or_bit_ref_list
        : array_or_bit_ref
        | my_array_or_bit_ref_list array_or_bit_ref
        ;

my_opt_single_expression
        : /* empty */
        | '(' single_expression ')'
        | '(' error ')'
                { yyerrok; }
        ;

my_any_or_all_keyword
        : any_keyword
        | all_keyword
        ;

my_address_ref_list
        : address_ref
        | my_address_ref_list ',' address_ref
        ;

my_opt_call_timer_value
        : /* empty */
        | ',' call_timer_value
        ;

my_opt_receive_parameter
        : /* empty */
        | '(' receive_parameter ')'
        | '(' error ')'
                { yyerrok; }
        ;

my_opt_receive_parameter_with_match
        : /* empty */
        | '(' receive_parameter opt_value_match_spec ')'
        | '(' error ')'
                { yyerrok; }
        ;

my_opt_check_parameter
        : /* empty */
        | '(' check_parameter ')'
        | '(' error ')'
                { yyerrok; }
        ;

my_opt_catch_op_parameter
        : /* empty */
        | '(' catch_op_parameter ')'
        | '(' error ')'
                { yyerrok; }
        ;

my_opt_timer_value
        : /* empty */
        | '(' timer_value ')'
        | '(' error ')'
                { yyerrok; }
        ;

my_type_actual_par_list
        : type_actual_par
        | my_type_actual_par_list ',' type_actual_par
        ;

my_array_bounds
        : '[' array_bounds my_opt_end_array_bounds ']'
        ;

my_opt_end_array_bounds
        : /* empty */
        | T_RANGE array_bounds
        ;

my_opt_dir_spec
        : /* empty */
        | in_par_keyword
        | out_par_keyword
        | inout_par_keyword
        ;

my_opt_string_action_text_list
        : /* empty */
        | my_string_action_text_list
        ;

my_string_action_text_list
        : string_op action_text
        | my_string_action_text_list string_op action_text
        ;

my_multi_with_attrib
        : single_with_attrib
        | my_multi_with_attrib ';' single_with_attrib
        ;

my_alt_guard_list
        : my_alt_guard_list_item
        | my_alt_guard_list my_alt_guard_list_item
        ;

my_alt_guard_list_item
        : guard_statement
        | else_statement opt_semicolon
        ;

my_field_expression_list
        : field_expression_spec
        | my_field_expression_list ',' field_expression_spec
        ;

my_opt_array_element_expression_list
        : not_used_or_expression
        | my_opt_array_element_expression_list ',' not_used_or_expression
        ;

my_field_const_expression_list
        : field_const_expression_spec
        | my_field_const_expression_list ',' field_const_expression_spec
        ;

my_opt_array_element_const_expression_list
        : constant_expression
        | my_opt_array_element_const_expression_list ',' constant_expression
        ;

my_extended_field_reference_list
        : my_extended_field_reference
        | my_extended_field_reference_list my_extended_field_reference
        ;

my_extended_field_reference
        : '.' struct_field_identifier
        | '.' type_def_identifier
        | array_or_bit_ref
        ;

my_log_item_list
        : log_item
        | my_log_item_list ',' log_item
        ;

my_select_case_list
        : select_case
        | my_select_case_list select_case
        ;

my_select_case
        : '(' my_template_list ')'
        | else_keyword
        | '(' error ')'
                { yyerrok; }
        ;

my_template_list
        : template_instance
        | my_template_list ',' template_instance
        ;

my_signed_number
        : number
        | '-' number
        ;

opt_semicolon
        : /* empty */
        | ';'
        ;

%%

