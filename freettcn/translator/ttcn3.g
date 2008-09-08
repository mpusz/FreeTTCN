//
// Copyright (C) 2008 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) compiler.

// freettcn is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// freettcn is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with freettcn; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA


grammar ttcn3;

options
{
    backtrack = true;
    memoize = true;
    k = 2;
    language = C;
}


tokens {
    MODULE = 'module';
    TYPE = 'type';
    RECORD = 'record';
    OPTIONAL = 'optional';
    UNION = 'union';
    SET = 'set';
    OF = 'of';
    ENUMERATED = 'enumerated';
    LENGTH = 'length';
    PORT = 'port';
    MESSAGE = 'message';
    ALL = 'all';
    PROCEDURE = 'procedure';
    MIXED = 'mixed';
    COMPONENT = 'component';
    EXTENDS = 'extends';
    CONST = 'const';
    TEMPLATE = 'template';
    MODIFIES = 'modifies';
    PATTERN = 'pattern';
    COMPLEMENT = 'complement';
    SUBSET = 'subset';
    SUPERSET = 'superset';
    PERMUTATION = 'permutation';
    IF_PRESENT = 'ifpresent';
    INFINITY = 'infinity';
    MATCH = 'match';
    VALUE_OF = 'valueof';
    FUNCTION = 'function';
    RETURN = 'return';
    RUNS = 'runs';
    ON = 'on';
    MTC = 'mtc';
    SIGNATURE = 'signature';
    TTCN_EXCEPTION = 'exception';
    NO_BLOCK = 'noblock';
    TESTCASE = 'testcase';
    SYSTEM = 'system';
    EXECUTE = 'execute';
    ALTSTEP = 'altstep';
    IMPORT = 'import';
    EXCEPT = 'except';
    RECURSIVE = 'recursive';
    TTCN_GROUP = 'group';
    EXTERNAL = 'external';
    MODULE_PAR = 'modulepar';
    CONTROL = 'control';
    VAR = 'var';
    TIMER = 'timer';
    SELF = 'self';
    DONE = 'done';
    KILLED = 'killed';
    RUNNING = 'running';
    CREATE = 'create';
    ALIVE = 'alive';
    CONNECT = 'connect';
    DISCONNECT = 'disconnect';
    MAP = 'map';
    UNMAP = 'unmap';
    START = 'start';
    KILL = 'kill';  
    SEND = 'send';
    TO = 'to';
    CALL = 'call';
    NO_WAIT = 'nowait';
    REPLY = 'reply';
    RAISE = 'raise';
    RECEIVE = 'receive';
    FROM = 'from';
    VALUE = 'value';
    SENDER = 'sender';
    TRIGGER = 'trigger';
    GET_CALL = 'getcall';
    PARAM = 'param';
    GET_REPLY = 'getreply';
    CHECK = 'check';
    CATCH = 'catch';
    CLEAR = 'clear';    
    STOP = 'stop';
    ANY = 'any';
    READ = 'read';
    TIMEOUT = 'timeout';
    BIT_STRING = 'bitstring';
    BOOLEAN = 'boolean';
    INTEGER = 'integer';
    OCTET_STRING = 'octetstring';
    HEX_STRING = 'hexstring';
    VERDICT_TYPE = 'verdicttype';
    FLOAT = 'float';
    ADDRESS = 'address';
    DEFAULT = 'default';
    ANY_TYPE = 'anytype';
    CHAR_STRING = 'charstring';
    UNIVERSAL = 'universal';
    TRUE = 'true';
    FALSE = 'false';
    PASS = 'pass';
    FAIL = 'fail';
    INCONC = 'inconc';
    NONE = 'none';
    ERROR = 'error';
    TTCN_CHAR = 'char';
    TTCN_NULL = 'null';
    OMIT = 'omit';
    IN = 'in';
    OUT = 'out';
    INOUT = 'inout';
    WITH = 'with';
    ENCODE = 'encode';
    VARIANT = 'variant';
    DISPLAY = 'display';
    EXTENSION = 'extension';
    OVERRIDE = 'override';
    SET_VERDICT = 'setverdict';
    GET_VERDICT = 'getverdict';
    ACTION = 'action';
    ALT = 'alt';
    INTERLEAVE = 'interleave';
    LABEL = 'label';
    GOTO = 'goto';
    REPEAT = 'repeat';
    ACTIVATE = 'activate';
    DEACTIVATE = 'deactivate';
    BREAK = 'break';
    CONTINUE = 'continue';
    OR = 'or';
    XOR = 'xor';
    AND = 'and';
    NOT = 'not';
    OR4B = 'or4b';
    XOR4B = 'xor4b';
    AND4B = 'and4b';
    NOT4B = 'not4b';
    MOD = 'mod';
    REM = 'rem';
    LOG = 'log';
    FOR = 'for';
    WHILE = 'while';
    DO = 'do';
    IF = 'if';
    ELSE = 'else';
    SELECT = 'select';
    CASE = 'case';
    MINUS = '-';
    DOT = '.';
    SEMICOLON = ';';
    COLON = ':';
    UNDERSCORE = '_';
    ASSIGNMENT_CHAR = ':=';
}



@lexer::includes
{
#define ANTLR3_INLINE_INPUT_ASCII
}


@lexer::postinclude {
#include "translator.h"

using namespace freettcn::translator;
}


@lexer::members {
    bool freeTextExpected = false;
}


@parser::includes
{
#include "identifier.h"
}


@parser::postinclude {
#include "translator.h"
#include "logger.h"
#include "dumper.h"
#include "location.h"

using namespace freettcn::translator;
}


@parser::members {
    freettcn::translator::CTranslator *translator = 0;
    freettcn::translator::CLogger *logger = 0;
    freettcn::translator::CDumper *dumper = 0;  /// @todo Dumper used for debugging only
}




// $<A.1.6.0 TTCN-3 module

ttcn3Module
        scope { const char *language; }
        @init
        {
            // init translator
            translator = &CTranslator::Instance();
            logger = &translator->Logger();
            dumper = &CDumper::Instance();
        }
        :
        ttcn3ModuleKeyword ttcn3ModuleId
        {
            CIdentifier *id = $ttcn3ModuleId.id;
            logger->GroupPush(translator->File(), "In module '" + id->Name() + "':");
            translator->Module(id, $ttcn3Module::language ? $ttcn3Module::language : "");
        }
        '{'
        moduleDefinitionsPart?
        moduleControlPart?
        '}'
        withStatement? SEMICOLON? EOF
        {
            logger->GroupPop();
        }
        ;
ttcn3ModuleKeyword
        : MODULE;
ttcn3ModuleId returns [ freettcn::translator::CIdentifier *id ]
        : moduleId
        { $id = $moduleId.id; };
moduleId returns [ freettcn::translator::CIdentifier *id ]
        : globalModuleId
        {
            pANTLR3_COMMON_TOKEN token = LT(-1);
            $id = new CIdentifier(CLocation(translator->File(), token->line, token->charPosition + 1),
                                  (char *)token->getText(token)->chars);
        }
        languageSpec?;
globalModuleId
        : moduleIdentifier;
moduleIdentifier
        : IDENTIFIER;
languageSpec
        : LANGUAGE_KEYWORD txt=FREE_TEXT
        { $ttcn3Module::language = strcmp((char *)$txt.text->chars, "<missing FREE_TEXT>") ? (char *)$txt.text->chars : ""; };
LANGUAGE_KEYWORD
        : 'language' { freeTextExpected = true; };

// $>


// $<A.1.6.1 Module definitions part

// $<A.1.6.1.0 General

moduleDefinitionsPart
        : moduleDefinitionsList;
moduleDefinitionsList
        : ( moduleDefinition SEMICOLON? )+;
moduleDefinition
        : ( typeDef |
        constDef |
        templateDef |
        moduleParDef |
        functionDef |
        signatureDef |
        testcaseDef |
        altstepDef |
        importDef |
        groupDef |
        extFunctionDef |
        extConstDef ) withStatement?;

// $>


// $<A.1.6.1.1 Typedef definitions

typeDef
        : typeDefKeyword typeDefBody;
typeDefBody
        : structuredTypeDef | subTypeDef;
typeDefKeyword
        : TYPE;
structuredTypeDef
        : recordDef |
        unionDef |
        setDef |
        recordOfDef |
        setOfDef |
        enumDef |
        portDef |
        componentDef;
recordDef
        : recordKeyword structDefBody;
recordKeyword
        : RECORD;
structDefBody
        : ( ( structTypeIdentifier structDefFormalParList? ) | addressKeyword )
        '{' ( structFieldDef ( ',' structFieldDef )* )? '}';
structTypeIdentifier
        : IDENTIFIER;
structDefFormalParList
        : '(' structDefFormalPar ( ',' structDefFormalPar )* ')';
structDefFormalPar
        : formalValuePar;
structFieldDef
        : ( type | nestedTypeDef ) structFieldIdentifier arrayDef? subTypeSpec?
        optionalKeyword?;
nestedTypeDef
        : nestedRecordDef |
        nestedUnionDef |
        nestedSetDef |
        nestedRecordOfDef |
        nestedSetOfDef |
        nestedEnumDef;
nestedRecordDef
        : recordKeyword '{' ( structFieldDef ( ',' structFieldDef )* )? '}';
nestedUnionDef
        : unionKeyword '{' unionFieldDef ( ',' unionFieldDef )* '}';
nestedSetDef
        : setKeyword '{' ( structFieldDef ( ',' structFieldDef )* )? '}';
nestedRecordOfDef
        : recordKeyword stringLength? ofKeyword ( type | nestedTypeDef );
nestedSetOfDef
        : setKeyword stringLength? ofKeyword ( type | nestedTypeDef );
nestedEnumDef
        : enumKeyword '{' enumerationList '}';
structFieldIdentifier
        : IDENTIFIER;
optionalKeyword
        : OPTIONAL;
unionDef
        : unionKeyword unionDefBody;
unionKeyword
        : UNION;
unionDefBody
        : ( structTypeIdentifier structDefFormalParList? | addressKeyword )
        '{' unionFieldDef ( ',' unionFieldDef )* '}';
unionFieldDef
        : ( type | nestedTypeDef ) structFieldIdentifier arrayDef? subTypeSpec?;
setDef
        : setKeyword structDefBody;
setKeyword
        : SET;
recordOfDef
        : recordKeyword stringLength? ofKeyword structOfDefBody;
ofKeyword
        : OF;
structOfDefBody
        : ( type | nestedTypeDef ) ( structTypeIdentifier | addressKeyword ) subTypeSpec?;
setOfDef
        : setKeyword stringLength? ofKeyword structOfDefBody;
enumDef
        : enumKeyword ( enumTypeIdentifier | addressKeyword )
        '{'  enumerationList '}';
enumKeyword
        : ENUMERATED;
enumTypeIdentifier
        : IDENTIFIER;
enumerationList
        : enumeration ( ',' enumeration )*;
enumeration
        : enumerationIdentifier ( '(' MINUS? number ')' )?;
enumerationIdentifier
        : IDENTIFIER;
subTypeDef
        : type ( subTypeIdentifier | addressKeyword ) arrayDef? subTypeSpec?;
subTypeIdentifier
        : IDENTIFIER;
subTypeSpec
        : allowedValues stringLength? | stringLength;
/* STATIC SEMATICS - allowedValues shall be of the same type as the field being subtyped */
allowedValues
        : '(' ( ( valueOrRange ( ',' valueOrRange )* ) | charStringMatch ) ')';
/* ---A--- BUG ---A--- */
valueOrRange
        : rangeDef | constantExpression;
/* STATIC SEMANTICS - rangeDef production shall only be used with integer, charstring, universal charstring or float based types */
/* STATIC SEMANTICS - When subtyping charstring or universal charstring range and values shall not be mixed in the same subTypeSpec */
rangeDef
        : lowerBound '..' upperBound;
stringLength
        : lengthKeyword '(' singleConstExpression ( '..' upperBound )? ')';
/* STATIC SEMANTICS - stringLength shall only be used with string types or to limit set of and record of. singleConstExpression
and upperBound shall evaluate to non-negative integervalues (in case of upperBound including infinity) */
lengthKeyword
        : LENGTH;
portType
        : ( globalModuleId DOT )? portTypeIdentifier;
portDef
        : portKeyword portDefBody;
portDefBody
        : portTypeIdentifier portDefAttribs;
portKeyword
        : PORT;
portTypeIdentifier
        : IDENTIFIER;
portDefAttribs
        : messageAttribs | procedureAttribs | mixedAttribs;
messageAttribs
        : messageKeyword
        '{' ( messageList SEMICOLON? )+ '}';
messageList
        : direction allOrTypeList;
direction
        : inParKeyword | outParKeyword | inOutParKeyword;
messageKeyword
        : MESSAGE;
allOrTypeList
        : allKeyword | typeList;
/* NOTE: The use of allKeyword in port definitions is deprecated */
allKeyword
        : ALL;
typeList
        : type ( ',' type )*;
procedureAttribs
        : procedureKeyword
        '{' ( procedureList SEMICOLON? )+ '}';
procedureKeyword
        : PROCEDURE;
procedureList
        : direction allOrSignatureList;
allOrSignatureList
        : allKeyword | signatureList;
signatureList
        : signature ( ',' signature )*;
mixedAttribs
        : mixedKeyword
        '{' ( mixedList SEMICOLON? )+ '}';
mixedKeyword
        : MIXED;
mixedList
        : direction procOrTypeList;
procOrTypeList
        : allKeyword | ( procOrType ( ',' procOrType )* );
procOrType
        : signature | type;
componentDef
//        scope Symbols;
        : componentKeyword componentTypeIdentifier
        ( extendsKeyword componentType ( ',' componentType )* )?
        '{' componentDefList? '}'
        {
            /// @todo copy scope data to component class
        };
componentKeyword
        : COMPONENT;
extendsKeyword
        : EXTENDS;
componentType
        : ( globalModuleId DOT )? componentTypeIdentifier;
componentTypeIdentifier
        : IDENTIFIER;
componentDefList
        : ( componentElementDef SEMICOLON? )*;
componentElementDef
        : portInstance | varInstance | timerInstance | constDef;
portInstance
        : portKeyword portType portElement ( ',' portElement )*;
portElement
        : portIdentifier arrayDef?;
portIdentifier
        : IDENTIFIER;

// $>


// $<A.1.6.1.2 Constant definitions

constDef
        : constKeyword type constList;
constList
        : singleConstDef ( ',' singleConstDef )*;
singleConstDef
        : constIdentifier arrayDef? ASSIGNMENT_CHAR constantExpression;
constKeyword
        : CONST;
constIdentifier
        : IDENTIFIER;

// $>


// $<A.1.6.1.3 Template definitions

templateDef
        : templateKeyword baseTemplate derivedDef? ASSIGNMENT_CHAR templateBody;
baseTemplate
        : ( type | signature ) templateIdentifier ( '(' templateFormalParList ')' )?;
templateKeyword
        : TEMPLATE;
templateIdentifier
        : IDENTIFIER;
derivedDef
        : modifiesKeyword templateRef;
modifiesKeyword
        : MODIFIES;
templateFormalParList
        : templateFormalPar ( ',' templateFormalPar )*;
templateFormalPar
        : formalValuePar | formalTemplatePar;
/* STATIC SEMANTICS - formalValuePar shall resolve to an in parameter */
templateBody
        : ( simpleSpec | fieldSpecList | arrayValueOrAttrib ) | extraMatchingAttributes?;
/* STATIC SEMANTICS - Within templateBody the arrayValueOrAttrib can be used for array, record, record of and set of types. */
simpleSpec
        : singleValueOrAttrib;
fieldSpecList
        : '{' ( fieldSpec ( ',' fieldSpec )* )? '}';
fieldSpec
        : fieldReference ASSIGNMENT_CHAR templateBody;
fieldReference
        : structFieldRef | arrayOrBitRef | parRef;
/* STATIC SEMANTICS - Within fieldReference arrayOrBitRef can be used for record of and set of templates/template fields
in modified templates only. */
structFieldRef
        : structFieldIdentifier | predefinedType | typeReference;
/* STATIC SEMANTICS - predefinedType and typeReference shall be used for anytype value notation only. predefinedType shall
not be anyTypeKeyword. */
parRef
        : signatureParIdentifier;
/* STATIC SEMANTICS - signatureParIdentifier shall be a formal parameter identifier from the associated signature definition. */
signatureParIdentifier
        : valueParIdentifier;
arrayOrBitRef
        : '[' fieldOrBitNumber ']';
/* STATIC SEMANTICS - arrayRef shall be optionally used for array types and TTCN-3 record of and set of. The same notation
can be used for a bit reference inside an TTCN-3 charstring, universal charstring, bitstring, octetstring and hexstring type. */
fieldOrBitNumber
        : singleExpression;
/* STATIC SEMANTICS - singleExpression will resolve to a value of integer type */
singleValueOrAttrib
        : matchingSymbol |
        singleExpression |
        templateRefWithParList;
/* STATIC SEMANTICS - variableIdentifier (accessed via singleExpression) may only be used in in-line template definitions
to reference variables in the current scope. */
arrayValueOrAttrib
        : '{' arrayElementSpecList '}';
arrayElementSpecList
        : arrayElementSpec ( ',' arrayElementSpec )*;
arrayElementSpec
        : notUsedSymbol | permutationMatch | templateBody;
notUsedSymbol
        : dash;
matchingSymbol
        : complement |
        ANY_VALUE |
        ANY_OR_OMIT |
        valueOrAttribList |
        range |
        bitStringMatch |
        hexStringMatch |
        octetStringMatch |
        charStringMatch |
        subsetMatch |
        supersetMatch;
extraMatchingAttributes
        : lengthMatch | ifPresentMatch | lengthMatch ifPresentMatch;
bitStringMatch
        : '\'' binOrMatch* '\'' 'B';
binOrMatch
        : BIN | ANY_VALUE | ANY_OR_OMIT;
hexStringMatch
        : '\'' hexOrMatch* '\'' 'H';
hexOrMatch
        : HEX | ANY_VALUE | ANY_OR_OMIT;
octetStringMatch
        : '\'' octOrMatch* '\'' 'O';
octOrMatch
        : OCT | ANY_VALUE | ANY_OR_OMIT;
charStringMatch
        : patternKeyword cString;
patternKeyword
        : PATTERN;
complement
        : complementKeyword valueOrAttribList; // valueOrAttribListValueList;
/* ---A--- BUG ---A--- */
complementKeyword
        : COMPLEMENT;
valueList
        : '(' constantExpression ( ',' constantExpression )* ')';
subsetMatch
        : subsetKeyword valueList;
subsetKeyword
        : SUBSET;
supersetMatch
        : supersetKeyword valueList;
supersetKeyword
        : SUPERSET;
permutationMatch
        : permutationKeyword permutationList;
permutationKeyword
        : PERMUTATION;
permutationList
        : '(' templateBody ( ',' templateBody )* ')';
/* STATIC SEMANTICS - Restrictions on the content of templateBody are given in clause B.1.3.3 */
ANY_VALUE
        : '?';
ANY_OR_OMIT
        : '*';
valueOrAttribList
        : '(' templateBody ( ',' templateBody )+ ')';
lengthMatch
        : stringLength;
ifPresentMatch
        : ifPresentKeyword;
ifPresentKeyword
        : IF_PRESENT;
range
        : '(' lowerBound '..' upperBound ')';
lowerBound
        : singleConstExpression | (MINUS infinityKeyword);
/* ---A--- BUG ---A--- */
upperBound
        : singleConstExpression | infinityKeyword;
/* STATIC SEMANTICS - lowerBound and upperBound shall evaluate to types integer, charstring, universal charstring
or float. In case lowerBound or upperBound evaluates to types charstring or universal charstring, only
singleConstExpression may be present and the string length shall be 1 */
infinityKeyword
        : INFINITY;
templateInstance
        : inLineTemplate;
templateRefWithParList
        : ( globalModuleId DOT )? templateIdentifier templateActualParList? |
        templateParIdentifier;
templateRef
        : ( globalModuleId DOT )? templateIdentifier | templateParIdentifier;
inLineTemplate
        : ( ( type | signature ) COLON )? ( derivedRefWithParList ASSIGNMENT_CHAR )?
        templateBody;
derivedRefWithParList
        : modifiesKeyword templateRefWithParList;
templateActualParList
        : '(' templateActualPar ( ',' templateActualPar )* ')';
templateActualPar
        : templateInstance;
/* STATIC SEMANTICS - When the corresponding formal parameter is not of template type the templateInstance
production shall resolve to one or more singleExpressions. */
templateOps
        : matchOp | valueofOp;
matchOp
        : matchKeyword '(' expression ',' templateInstance ')';
matchKeyword
        : MATCH;
valueofOp
        : valueofKeyword '(' templateInstance ')';
valueofKeyword
        : VALUE_OF;

// $>


// $<A.1.6.1.4 Function definitions

functionDef
//        scope Symbols;
        : functionKeyword functionIdentifier
        '(' functionFormalParList? ')' runsOnSpec? returnType?
        statementBlock;
functionKeyword
        : FUNCTION;
functionIdentifier
        : IDENTIFIER;
functionFormalParList
        : functionFormalPar ( ',' functionFormalPar )*;
functionFormalPar
        : formalValuePar |
        formalTimerPar |
        formalTemplatePar | 
        formalPortPar;
returnType
        : returnKeyword ( templateKeyword | restrictedTemplate )? type;
returnKeyword
        : RETURN;
runsOnSpec
        : runsKeyword onKeyword componentType;
runsKeyword
        : RUNS;
onKeyword
        : ON;
mtcKeyword
        : MTC;
statementBlock
//        scope Symbols;
        : '{' functionStatementOrDefList? '}';
functionStatementOrDefList
        : ( functionStatementOrDef SEMICOLON? )+;
functionStatementOrDef
        : functionLocalDef |
        functionLocalInst |
        functionStatement;
functionLocalInst
        : varInstance | timerInstance;
functionLocalDef : constDef | templateDef;
functionStatement
        : configurationStatements |
        timerStatements |
        communicationStatements |
        basicStatements |
        behaviourStatements |
        verdictStatements | 
        sutStatements;
functionInstance
        : functionRef '(' functionActualParList? ')';
functionRef
        : ( globalModuleId DOT )? ( functionIdentifier | extFunctionIdentifier ) |
        preDefFunctionIdentifier;
preDefFunctionIdentifier
        : IDENTIFIER;
/* STATIC SEMANTICS - The identifier shall be one of the pre-defined TTCN-3 Function Identifiers from Annex C of
ES 201 873-1 */
functionActualParList
        : functionActualPar ( ',' functionActualPar )*;
functionActualPar
        : timerRef |
        templateInstance |
        port |
        componentRef;
/* STATIC SEMANTICS - When the corresponding formal parameter is not of template type the templateInstance production
shall resolve to one or more singleExpressions i.e. equivalent to the expression production. */

// $>


// $<A.1.6.1.5 Signature definitions

signatureDef
        : signatureKeyword signatureIdentifier
        '(' signatureFormalParList? ')' ( returnType | noBlockKeyword )?
        exceptionSpec?;
signatureKeyword
        : SIGNATURE;
signatureIdentifier
        : IDENTIFIER;
signatureFormalParList
        : signatureFormalPar ( ',' signatureFormalPar )*;
signatureFormalPar
        : formalValuePar;
exceptionSpec
        : exceptionKeyword '(' exceptionTypeList ')';
exceptionKeyword
        : TTCN_EXCEPTION;
exceptionTypeList
        : type ( ',' type )*;
noBlockKeyword
        : NO_BLOCK;
signature
        : ( globalModuleId DOT )? signatureIdentifier;

// $>


// $<A.1.6.1.6 Testcase definitions

testcaseDef
//        scope Symbols;
        : testcaseKeyword testcaseIdentifier
        '(' testcaseFormalParList? ')' configSpec
        statementBlock;
testcaseKeyword
        : TESTCASE;
testcaseIdentifier
        : IDENTIFIER;
testcaseFormalParList
        : testcaseFormalPar ( ',' testcaseFormalPar )*;
testcaseFormalPar
        : formalValuePar |
        formalTemplatePar;
configSpec
        : runsOnSpec systemSpec?;
systemSpec
        : systemKeyword componentType;
systemKeyword
        : SYSTEM;
testcaseInstance
        : executeKeyword '(' testcaseRef '(' testcaseActualParList? ')'
        ( ',' timerValue )? ')';
executeKeyword
        : EXECUTE;
testcaseRef
        : ( globalModuleId DOT )? testcaseIdentifier;
testcaseActualParList
        : testcaseActualPar ( ',' testcaseActualPar )*;
testcaseActualPar
        : templateInstance;
/* STATIC SEMANTICS - When the corresponding formal parameter is not of template type the templateInstance
production shall resolve to one or more singleExpressions i.e. equivalent to the expression production. */

// $>


// $<A.1.6.1.7 Altstep definitions

altstepDef
//        scope Symbols;
        : altstepKeyword altstepIdentifier
        '(' altstepFormalParList? ')' runsOnSpec?
        '{' altstepLocalDefList altGuardList '}';
altstepKeyword
        : ALTSTEP;
altstepIdentifier
        : IDENTIFIER;
altstepFormalParList
        : functionFormalParList;
altstepLocalDefList
        : ( altstepLocalDef SEMICOLON? )*;
altstepLocalDef
        : varInstance | timerInstance | constDef | templateDef;
altstepInstance
        : altstepRef '(' functionActualParList? ')';
altstepRef
        : ( globalModuleId DOT )? altstepIdentifier;

// $>


// $<A.1.6.1.8 Import definitions

importDef
        : importKeyword importFromSpec ( allWithExcepts | ( '{' importSpec '}' ) );
importKeyword
        : IMPORT;
allWithExcepts
        : allKeyword exceptsDef?;
exceptsDef
        : exceptKeyword '{' exceptSpec '}';
exceptKeyword
        : EXCEPT;
exceptSpec
        : ( exceptElement SEMICOLON? )*;
exceptElement
        : exceptGroupSpec |
        exceptTypeDefSpec |
        exceptTemplateSpec |
        exceptConstSpec |
        exceptTestcaseSpec |
        exceptAltstepSpec |
        exceptFunctionSpec |
        exceptSignatureSpec |
        exceptModuleParSpec;
exceptGroupSpec
        : groupKeyword ( exceptGroupRefList | allKeyword );
exceptTypeDefSpec
        : typeDefKeyword ( typeRefList | allKeyword );
exceptTemplateSpec
        : templateKeyword ( templateRefList | allKeyword );
exceptConstSpec
        : constKeyword ( constRefList | allKeyword );
exceptTestcaseSpec
        : testcaseKeyword ( testcaseRefList | allKeyword );
exceptAltstepSpec
        : altstepKeyword ( altstepRefList | allKeyword );
exceptFunctionSpec
        : functionKeyword ( functionRefList | allKeyword );
exceptSignatureSpec
        : signatureKeyword ( signatureRefList | allKeyword );
exceptModuleParSpec
        : moduleParKeyword ( moduleParRefList | allKeyword );
importSpec
        : ( importElement SEMICOLON? )*;
importElement
        : importGroupSpec |
        importTypeDefSpec |
        importTemplateSpec |
        importConstSpec |
        importTestcaseSpec |
        importAltstepSpec |
        importFunctionSpec |
        importSignatureSpec |
        importModuleParSpec;
importFromSpec
        : fromKeyword moduleId recursiveKeyword?;
recursiveKeyword
        : RECURSIVE;
importGroupSpec
        : groupKeyword ( groupRefListWithExcept | allGroupsWithExcept );
groupRefList
        : fullGroupIdentifier ( ',' fullGroupIdentifier )*;
groupRefListWithExcept
        : fullGroupIdentifierWithExcept ( ',' fullGroupIdentifierWithExcept )*;
allGroupsWithExcept
        : allKeyword ( exceptKeyword groupRefList )?;
fullGroupIdentifier
        : groupIdentifier ( DOT groupIdentifier )*;
fullGroupIdentifierWithExcept
        : fullGroupIdentifier exceptsDef?;
exceptGroupRefList
        : exceptFullGroupIdentifier ( ',' exceptFullGroupIdentifier )*;
exceptFullGroupIdentifier
        : fullGroupIdentifier;
importTypeDefSpec
        : typeDefKeyword ( typeRefList | allTypesWithExcept );
typeRefList
        : typeDefIdentifier ( ',' typeDefIdentifier )*;
allTypesWithExcept
        : allKeyword ( exceptKeyword typeRefList )?;
typeDefIdentifier
        : structTypeIdentifier |
        enumTypeIdentifier |
        portTypeIdentifier |
        componentTypeIdentifier |
        subTypeIdentifier;
importTemplateSpec
        : templateKeyword ( templateRefList | allTemplsWithExcept );
templateRefList
        : templateIdentifier ( ',' templateIdentifier )*;
allTemplsWithExcept
        : allKeyword ( exceptKeyword templateRefList )?;
importConstSpec
        : constKeyword ( constRefList | allConstsWithExcept );
constRefList
        : constIdentifier ( ',' constIdentifier )*;
allConstsWithExcept
        : allKeyword ( exceptKeyword constRefList )?;
importAltstepSpec
        : altstepKeyword ( altstepRefList | allAltstepsWithExcept );
altstepRefList
        : altstepIdentifier ( ',' altstepIdentifier )*;
allAltstepsWithExcept
        : allKeyword ( exceptKeyword altstepRefList )?;
importTestcaseSpec
        : testcaseKeyword ( testcaseRefList | allTestcasesWithExcept );
testcaseRefList
        : testcaseIdentifier ( ',' testcaseIdentifier )*;
allTestcasesWithExcept
        : allKeyword ( exceptKeyword testcaseRefList )?;
importFunctionSpec
        : functionKeyword ( functionRefList | allFunctionsWithExcept );
functionRefList
        : functionIdentifier ( ',' functionIdentifier )*;
allFunctionsWithExcept
        : allKeyword ( exceptKeyword functionRefList )?;
importSignatureSpec
        : signatureKeyword ( signatureRefList | allSignaturesWithExcept );
signatureRefList
        : signatureIdentifier ( ',' signatureIdentifier )*;
allSignaturesWithExcept
        : allKeyword ( exceptKeyword signatureRefList )?;
importModuleParSpec
        : moduleParKeyword ( moduleParRefList | allModuleParWithExcept );
moduleParRefList
        : moduleParIdentifier ( ',' moduleParIdentifier )*;
allModuleParWithExcept
        : allKeyword ( exceptKeyword moduleParRefList )?;

// $>


// $<A.1.6.1.9 Group definitions

groupDef
        : groupKeyword groupIdentifier
        '{' moduleDefinitionsPart? '}';
groupKeyword
        : TTCN_GROUP;
groupIdentifier
        : IDENTIFIER;

// $>


// $<A.1.6.1.10 External function definitions

extFunctionDef
        : extKeyword functionKeyword extFunctionIdentifier
        '(' functionFormalParList? ')' returnType?;
extKeyword
        : EXTERNAL;
extFunctionIdentifier
        : IDENTIFIER;

// $>


// $<A.1.6.1.11 External constant definitions

extConstDef
        : extKeyword constKeyword type extConstIdentifierList;
extConstIdentifierList
        : extConstIdentifier ( ',' extConstIdentifier )*;
extConstIdentifier
        : IDENTIFIER;

// $>


// $<A.1.6.1.12 Module parameter definitions

moduleParDef
        : moduleParKeyword
        {
            logger->GroupPush(translator->File(), "In module definitions part:");
        }
        ( modulePar | ( '{' multitypedModuleParList '}' ) )
        {
            logger->GroupPop();
        }
        ;
moduleParKeyword
        : MODULE_PAR;
multitypedModuleParList
        : ( modulePar SEMICOLON? )*;
modulePar
        scope { const char *parType; }
        : moduleParType 
        {
            $modulePar::parType = (const char *)$moduleParType.text->chars;
        }
        moduleParList;
moduleParType
        : type;
// Module parameters shall not be of port type, default type or component type.
// A module parameter shall only be of type address if the address type is explicitly defined within the associated
// module.
moduleParList
        : moduleParIdentifierDef ( ',' moduleParIdentifierDef )*;
moduleParIdentifierDef
        : moduleParIdentifier ( ASSIGNMENT_CHAR constantExpression )?
        {
            translator->ModulePar($moduleParIdentifier.id, $modulePar::parType, "");
        }
        ;
moduleParIdentifier returns [ freettcn::translator::CIdentifier *id ]
        : IDENTIFIER
        {
            pANTLR3_COMMON_TOKEN token = LT(-1);
            $id = new CIdentifier(CLocation(translator->File(), token->line, token->charPosition + 1),
                                  (char *)token->getText(token)->chars);
        }
        ;


// $>

// $>



// $<A.1.6.2 Control part

// $<A.1.6.2.0 General

moduleControlPart
        : controlKeyword
        '{' moduleControlBody '}'
        withStatement? SEMICOLON?;
controlKeyword
        : CONTROL;
moduleControlBody
//        scope Symbols;
        : controlStatementOrDefList?;
controlStatementOrDefList
        : ( controlStatementOrDef SEMICOLON? )+;
controlStatementOrDef
        : functionLocalDef |
        functionLocalInst |
        controlStatement;
controlStatement
        : timerStatements |
        basicStatements |
        behaviourStatements |
        sutStatements |
        stopKeyword;

// $>


// $<A.1.6.2.1 Variable instantiation

varInstance
        : varKeyword ( ( type varList ) | ( ( templateKeyword | restrictedTemplate ) type tempVarList ) );
varList
        : singleVarInstance ( ',' singleVarInstance )*;
singleVarInstance
        : varIdentifier arrayDef? ( ASSIGNMENT_CHAR varInitialValue )?;
varInitialValue
        : expression;
varKeyword
        : VAR;
varIdentifier
        : IDENTIFIER;
tempVarList
        : singleTempVarInstance ( ',' singleTempVarInstance )*;
singleTempVarInstance
        : varIdentifier arrayDef? ( ASSIGNMENT_CHAR tempVarInitialValue )?;
tempVarInitialValue
        : templateBody;
variableRef
        : ( varIdentifier | valueParIdentifier ) extendedFieldReference?;

// $>


// $<A.1.6.2.2 Timer instantiation

timerInstance
        : timerKeyword timerList;
timerList
        : singleTimerInstance ( ',' singleTimerInstance )*;
singleTimerInstance
        : timerIdentifier arrayDef? ( ASSIGNMENT_CHAR timerValue )?;
timerKeyword
        : TIMER;
timerIdentifier
        : IDENTIFIER;
timerValue
        : expression;
timerRef
        : ( timerIdentifier | timerParIdentifier ) arrayOrBitRef*;

// $>


// $<A.1.6.2.3 Component operations

configurationStatements
        : connectStatement |
        mapStatement |
        disconnectStatement |
        unmapStatement |
        doneStatement |
        killedStatement |
        startTCStatement |
        stopTCStatement |
        killTCStatement;
configurationOps
        : createOp | selfOp | systemOp | mtcOp | runningOp | aliveOp;
createOp
        : componentType DOT createKeyword ( '(' singleExpression ')' )? aliveKeyword?;
systemOp
        : systemKeyword;
selfOp
        : SELF;
mtcOp
        : mtcKeyword;
doneStatement
        : componentId DOT doneKeyword;
killedStatement
        : componentId DOT killedKeyword;
componentId
        : componentOrDefaultReference | ( ( anyKeyword | allKeyword ) componentKeyword );
/* ---A--- BUG ---A--- */
doneKeyword
        : DONE;
killedKeyword
        : KILLED;
runningOp
        : componentId DOT runningKeyword;
runningKeyword
        : RUNNING;
aliveOp
        : componentId DOT aliveKeyword;
createKeyword
        : CREATE;
aliveKeyword
        : ALIVE;
connectStatement
        : connectKeyword singleConnectionSpec;
connectKeyword
        : CONNECT;
singleConnectionSpec
        : '(' portRef ',' portRef ')';
portRef
        : componentRef COLON port;
componentRef
        : componentOrDefaultReference | systemOp | selfOp | mtcOp;
disconnectStatement
        : disconnectKeyword singleOrMultiConnectionSpec?;
singleOrMultiConnectionSpec
        : singleConnectionSpec |
        allConnectionsSpec |
        allPortsSpec |
        allCompsAllPortsSpec;
allConnectionsSpec
        : '(' portRef ')';
allPortsSpec
        : '(' componentRef ':' allKeyword portKeyword ')';
allCompsAllPortsSpec
        : '(' allKeyword componentKeyword ':' allKeyword portKeyword ')';
disconnectKeyword
        : DISCONNECT;
mapStatement
        : mapKeyword singleConnectionSpec;
mapKeyword
        : MAP;
unmapStatement
        : unmapKeyword singleOrMultiConnectionSpec?;
unmapKeyword
        : UNMAP;
startTCStatement
        : componentOrDefaultReference DOT startKeyword '(' functionInstance ')';
startKeyword
        : START;
stopTCStatement
        : stopKeyword | ( componentReferenceOrLiteral DOT stopKeyword ) |
        ( allKeyword componentKeyword DOT stopKeyword );
componentReferenceOrLiteral
        : componentOrDefaultReference | mtcOp | selfOp;
killTCStatement
        : killKeyword | ( componentReferenceOrLiteral DOT killKeyword ) |
        ( allKeyword componentKeyword DOT killKeyword );
componentOrDefaultReference
        : variableRef | functionInstance;
killKeyword
        : KILL;

// $>


// $<A.1.6.2.4 Port operations

port
        : ( portIdentifier | portParIdentifier ) arrayOrBitRef*;
communicationStatements
        : sendStatement |
        callStatement |
        replyStatement |
        raiseStatement |
        receiveStatement |
        triggerStatement |
        getCallStatement |
        getReplyStatement |
        catchStatement |
        checkStatement |
        clearStatement |
        startStatement |
        stopStatement;
sendStatement
        : port DOT portSendOp;
portSendOp
        : sendOpKeyword '(' sendParameter ')' toClause?;
sendOpKeyword
        : SEND;
sendParameter
        : templateInstance;
toClause
        : toKeyword ( addressRef |
        addressRefList |
        ( allKeyword componentKeyword ) );
/* ---A--- BUG ---A--- */
addressRefList
        : '(' addressRef ( ',' addressRef )* ')';
toKeyword
        : TO;
addressRef
        : templateInstance;
callStatement
        : port DOT portCallOp portCallBody?;
portCallOp
        : callOpKeyword '(' callParameters ')' toClause?;
callOpKeyword
        : CALL;
callParameters
        : templateInstance ( ',' callTimerValue )?;
callTimerValue
        : timerValue | nowaitKeyword;
nowaitKeyword
        : NO_WAIT;
portCallBody
        : '{' callBodyStatementList '}';
callBodyStatementList
        : ( callBodyStatement SEMICOLON? )+;
callBodyStatement
        : callBodyGuard statementBlock;
callBodyGuard
        : altGuardChar callBodyOps;
callBodyOps
        : getReplyStatement | catchStatement;
replyStatement
        : port DOT portReplyOp;
portReplyOp
        : replyKeyword '(' templateInstance replyValue? ')' toClause?;
replyKeyword
        : REPLY;
replyValue
        : valueKeyword expression;
raiseStatement
        : port DOT portRaiseOp;
portRaiseOp
        : raiseKeyword '(' signature ',' templateInstance ')' toClause?;
raiseKeyword
        : RAISE;
receiveStatement
        : portOrAny DOT portReceiveOp;
portOrAny
        : port | anyKeyword portKeyword;
portReceiveOp
        : receiveOpKeyword ( '(' receiveParameter ')' )? fromClause? portRedirect?;
receiveOpKeyword
        : RECEIVE;
receiveParameter
        : templateInstance;
fromClause
        : fromKeyword ( addressRef |
        addressRefList |
        ( anyKeyword componentKeyword ) );
/* ---A--- BUG ---A--- */
fromKeyword
        : FROM;
portRedirect
        : PORT_REDIRECT_SYMBOL ( valueSpec senderSpec? | senderSpec );
fragment
PORT_REDIRECT_SYMBOL
        : '->';
valueSpec
        : valueKeyword variableRef;
valueKeyword
        : VALUE;
senderSpec
        : senderKeyword variableRef;
senderKeyword
        : SENDER;
triggerStatement
        : portOrAny DOT portTriggerOp;
portTriggerOp
        : triggerOpKeyword ( '(' receiveParameter ')' )? fromClause? portRedirect?;
triggerOpKeyword
        : TRIGGER;
getCallStatement
        : portOrAny DOT portGetCallOp;
portGetCallOp
        : getCallOpKeyword ( '(' receiveParameter ')' )? fromClause?
        portRedirectWithParam?;
getCallOpKeyword
        : GET_CALL;
portRedirectWithParam
        : PORT_REDIRECT_SYMBOL redirectWithParamSpec;
redirectWithParamSpec
        : (paramSpec senderSpec?) |
        senderSpec;
/* ---A--- BUG ---A--- */
paramSpec
        : paramKeyword paramAssignmentList;
paramKeyword
        : PARAM;
paramAssignmentList
        : '(' ( assignmentList | variableList ) ')';
assignmentList
        : variableAssignment ( ',' variableAssignment )*;
variableAssignment
        : variableRef ASSIGNMENT_CHAR parameterIdentifier;
parameterIdentifier
        : valueParIdentifier;
variableList
        : variableEntry ( ',' variableEntry )*;
variableEntry
        : variableRef | notUsedSymbol;
getReplyStatement
        : portOrAny DOT portGetReplyOp;
portGetReplyOp
        : getReplyOpKeyword ( '(' receiveParameter valueMatchSpec? ')' )?
        fromClause? portRedirectWithValueAndParam?;
portRedirectWithValueAndParam
        : PORT_REDIRECT_SYMBOL redirectWithValueAndParamSpec;
redirectWithValueAndParamSpec
        : valueSpec paramSpec? senderSpec? |
        redirectWithParamSpec;
getReplyOpKeyword
        : GET_REPLY;
valueMatchSpec
        : valueKeyword templateInstance;
checkStatement
        : portOrAny DOT portCheckOp;
portCheckOp
        : checkOpKeyword ( '(' checkParameter ')' )?;
checkOpKeyword
        : CHECK;
checkParameter
        : checkPortOpsPresent | fromClausePresent | redirectPresent;
fromClausePresent
        : fromClause ( PORT_REDIRECT_SYMBOL senderSpec )?;
redirectPresent
        : PORT_REDIRECT_SYMBOL senderSpec;
checkPortOpsPresent
        : portReceiveOp | portGetCallOp | portGetReplyOp | portCatchOp;
catchStatement
        : portOrAny DOT portCatchOp;
portCatchOp
        : catchOpKeyword ( '(' catchOpParameters ')' )? fromClause? portRedirect?;
catchOpKeyword
        : CATCH;
catchOpParameters
        : signature ',' templateInstance | timeoutKeyword;
clearStatement
        : portOrAll DOT portClearOp;
portOrAll
        : port | allKeyword portKeyword;
portClearOp
        : clearOpKeyword;
clearOpKeyword
        : CLEAR;
startStatement
        : portOrAll DOT portStartOp;
portStartOp
        : startKeyword;
stopStatement
        : portOrAll DOT portStopOp;
portStopOp
        : stopKeyword;
stopKeyword
        : STOP;
anyKeyword
        : ANY;

// $>


// $<A.1.6.2.5 Timer operations

timerStatements
        : startTimerStatement | stopTimerStatement | timeoutStatement;
timerOps
        : readTimerOp | runningTimerOp;
startTimerStatement
        : timerRef DOT startKeyword ( '(' timerValue ')' )?;
stopTimerStatement
        : timerRefOrAll DOT stopKeyword;
timerRefOrAll
        : timerRef | allKeyword timerKeyword;
readTimerOp
        : timerRef DOT readKeyword;
readKeyword
        : READ;
runningTimerOp
        : timerRefOrAny DOT runningKeyword;
timeoutStatement
        : timerRefOrAny DOT timeoutKeyword;
timerRefOrAny
        : timerRef | anyKeyword timerKeyword;
timeoutKeyword
        : TIMEOUT;

// $>

// $>


// $<A.1.6.3 Type

type
        : predefinedType | referencedType;
predefinedType
        : bitstringKeyword |
        booleanKeyword |
        charStringKeyword |
        universalCharString |
        integerKeyword |
        octetStringKeyword |
        hexStringKeyword |
        verdictTypeKeyword |
        floatKeyword |
        addressKeyword |
        defaultKeyword |
        anyTypeKeyword;
bitstringKeyword
        : BIT_STRING;
booleanKeyword
        : BOOLEAN;
integerKeyword
        : INTEGER;
octetStringKeyword
        : OCTET_STRING;
hexStringKeyword
        : HEX_STRING;
verdictTypeKeyword
        : VERDICT_TYPE;
floatKeyword
        : FLOAT;
addressKeyword
        : ADDRESS;
defaultKeyword
        : DEFAULT;
anyTypeKeyword
        : ANY_TYPE;
charStringKeyword
        : CHAR_STRING;
universalCharString
        : universalKeyword charStringKeyword;
universalKeyword
        : UNIVERSAL;
referencedType
        : ( globalModuleId DOT )? typeReference extendedFieldReference?;
typeReference
        : ( structTypeIdentifier typeActualParList?) |
        enumTypeIdentifier |
        subTypeIdentifier |
        componentTypeIdentifier;
/* ---A--- BUG ---A--- */
typeActualParList
        : '(' typeActualPar ( ',' typeActualPar )* ')';
typeActualPar
        : constantExpression;
arrayDef
        : ( '[' arrayBounds ( '..' arrayBounds )? ']' )+;
arrayBounds
        : singleConstExpression;
/* STATIC SEMANTICS - arrayBounds will resolve to a non negative value of integer type */

// $>


// $<A.1.6.4 Value

value
        : predefinedValue | referencedValue;
predefinedValue
        : bitStringValue |
        booleanValue |
        charStringValue |
        integerValue |
        octetStringValue |
        hexStringValue |    
        verdictTypeValue |
        enumeratedValue |
        floatValue |    
        addressValue |
        omitValue;
bitStringValue
        : B_STRING;
booleanValue
        : TRUE | FALSE;
integerValue
        : number;
octetStringValue
        : O_STRING;
hexStringValue
        : H_STRING;
verdictTypeValue
        : PASS | FAIL | INCONC | NONE | ERROR;
enumeratedValue
        : enumerationIdentifier;
charStringValue
        : cString | quadruple;
quadruple
        : CHAR_KEYWORD '(' group ',' plane ',' row ',' cell ')';
fragment
CHAR_KEYWORD
        : TTCN_CHAR;
group
        : number;
plane
        : number;
row
        : number;
cell
        : number;
floatValue
        : floatDotNotation | floatENotation;
floatDotNotation
        : number DOT decimalNumber;
floatENotation
        : number ( DOT decimalNumber )? EXPONENTIAL MINUS? number;
fragment
EXPONENTIAL
        : 'E';
referencedValue
        : valueReference extendedFieldReference?;
valueReference
        : ( globalModuleId DOT )? ( constIdentifier | extConstIdentifier |
        moduleParIdentifier ) |
        valueParIdentifier |
        varIdentifier;
number
        : ( NON_ZERO_NUM num* ) | '0';
NON_ZERO_NUM
        : '1'..'9';
decimalNumber
        : num+;
num
        : '0' | NON_ZERO_NUM;
B_STRING
        : '\'' BIN* '\'' 'B';
fragment
BIN
        : '0' | '1';
H_STRING
        : '\'' HEX* '\'' 'H';
fragment
HEX
        : '0'..'9' | 'A'..'F' | 'a'..'f';
O_STRING
        : '\'' OCT* '\'' 'O';
fragment
OCT
        : HEX HEX;
cString
        : C_STRING | UC_STRING;
C_STRING
        : { !freeTextExpected }?=> '"' CHAR* '"';
fragment
CHAR
        : '\u0000'..'\u0021' | '\\"' | '\u0023'..'\u007F';
/* ---A--- BUG (special escape needed for " sign) ---A--- */
/* REFERENCE - A character defined by the relevant CharacterString type. For charstring a character from the character
set defined in ISO/IEC 646. For universal charstring a character from any character set defined in ISO/IEC 10646 */
FREE_TEXT
        : { freeTextExpected }?=> '"' EXTENDED_ALPHA_NUM* '"' { freeTextExpected = false; };
fragment
EXTENDED_ALPHA_NUM
        : '\u0020' | '\u0021' | '\\"' | '\u0023'..'\u007E' | '\u00A1'..'\u00AC' | '\u00AE'..'\u00FF';
/* ---A--- BUG (special escape needed for " sign) ---A--- */
/* REFERENCE - A graphical character from the BASIC LATIN or from the LATIN-1 SUPPLEMENT character sets defined in
ISO/IEC 10646 (characters from char (0,0,0,32) to char (0,0,0,126), from char (0,0,0,161) to char (0,0,0,172) and
from char (0,0,0,174) to char (0,0,0,255). */
UC_STRING
        : { !freeTextExpected }?=> '"' UNIVERSAL_CHAR* '"';
fragment
UNIVERSAL_CHAR
        : '\u0000'..'\u0021' | '\\"' | '\u0023'..'\u00FF';
/* ---A--- ADDED (universal string support) ---A--- */
IDENTIFIER
        : ALPHA ( ALPHA_NUM | UNDERSCORE )*;
fragment
ALPHA
        : UPPER_ALPHA | LOWER_ALPHA;
fragment
ALPHA_NUM
        : ALPHA | '0'..'9';
fragment
UPPER_ALPHA
        : 'A'..'Z';
fragment
LOWER_ALPHA
        : 'a'..'z';
addressValue
        : TTCN_NULL;
omitValue
        : omitKeyword;
omitKeyword
        : OMIT;

// $>


// $<A.1.6.5 Parametrization

inParKeyword
        : IN;
outParKeyword
        : OUT;
inOutParKeyword
        : INOUT;
formalValuePar
        : ( inParKeyword | inOutParKeyword | outParKeyword )? type valueParIdentifier;
valueParIdentifier
        : IDENTIFIER;
formalPortPar
        : inOutParKeyword? portTypeIdentifier portParIdentifier;
portParIdentifier
        : IDENTIFIER;
formalTimerPar
        : inOutParKeyword? timerKeyword timerParIdentifier;
timerParIdentifier
        : IDENTIFIER;
formalTemplatePar
        : ( inParKeyword | outParKeyword | inOutParKeyword )?
        ( templateKeyword | restrictedTemplate ) type templateParIdentifier;
templateParIdentifier
        : IDENTIFIER;
restrictedTemplate
        : omitKeyword | ( templateKeyword templateRestriction );
templateRestriction
        : '(' omitKeyword ')';

// $>


// $<A.1.6.6 With statement

withStatement
        : withKeyword withAttribList;
withKeyword
        : WITH;
withAttribList
        : '{' multiWithAttrib '}';
multiWithAttrib
        : ( singleWithAttrib SEMICOLON? )*;
singleWithAttrib
        : attribKeyword overrideKeyword? attribQualifier? attribSpec;
attribKeyword
        : encodeKeyword |
        variantKeyword |
        displayKeyword |
        extensionKeyword;
encodeKeyword
        : ENCODE;
variantKeyword
        : VARIANT;
displayKeyword
        : DISPLAY;
extensionKeyword
        : EXTENSION;
overrideKeyword
        : OVERRIDE;
attribQualifier
        : '(' defOrFieldRefList ')';
defOrFieldRefList
        : defOrFieldRef ( ',' defOrFieldRef )*;
defOrFieldRef
        : definitionRef | fieldReference | allRef;
definitionRef
        : structTypeIdentifier |
        enumTypeIdentifier |
        portTypeIdentifier |
        componentTypeIdentifier |
        subTypeIdentifier | 
        constIdentifier |
        templateIdentifier |
        altstepIdentifier |
        testcaseIdentifier |
        functionIdentifier |
        signatureIdentifier |   
        varIdentifier |
        timerIdentifier |
        portIdentifier |
        moduleParIdentifier |
        fullGroupIdentifier;
allRef
        : ( groupKeyword allKeyword ( exceptKeyword '{' groupRefList '}' )? ) |
        ( typeDefKeyword allKeyword ( exceptKeyword '{' typeRefList '}' )? ) |
        ( templateKeyword allKeyword ( exceptKeyword '{' templateRefList '}' )? ) |
        ( constKeyword allKeyword ( exceptKeyword '{' constRefList '}' )? ) |
        ( altstepKeyword allKeyword ( exceptKeyword '{' altstepRefList '}' )? ) |
        ( testcaseKeyword allKeyword ( exceptKeyword '{' testcaseRefList '}' )? ) |
        ( functionKeyword allKeyword ( exceptKeyword '{' functionRefList '}' )? ) |
        ( signatureKeyword allKeyword ( exceptKeyword '{' signatureRefList '}' )? ) |
        ( moduleParKeyword allKeyword ( exceptKeyword '{' moduleParRefList '}' )? );
attribSpec
        : FREE_TEXT;

// $>


// $<A.1.6.7 Behaviour statements

behaviourStatements
        : testcaseInstance |
        functionInstance |
        returnStatement |
        altConstruct |
        interleavedConstruct |
        labelStatement |    
        gotoStatement |
        repeatStatement |
        deactivateStatement |
        altstepInstance |
        activateOp |
        breakStatement |    
        continueStatement;
verdictStatements
        : setLocalVerdict;
verdictOps
        : getLocalVerdict;
setLocalVerdict
        : setVerdictKeyword '(' singleExpression ')';
setVerdictKeyword
        : SET_VERDICT;
getLocalVerdict
        : GET_VERDICT;
sutStatements
        : actionKeyword '(' actionText? ( stringOp actionText )* ')';
actionKeyword
        : ACTION;
actionText
        : FREE_TEXT | expression;
returnStatement
        : returnKeyword expression?;
altConstruct
        : altKeyword '{' altGuardList '}';
altKeyword
        : ALT;
altGuardList
        : ( guardStatement | elseStatement SEMICOLON? )*;
guardStatement
        : altGuardChar ( altstepInstance statementBlock? | guardOp statementBlock );
elseStatement
        : '[' elseKeyword ']' statementBlock;
altGuardChar
        : '[' booleanExpression? ']';
guardOp
        : timeoutStatement |
        receiveStatement |
        triggerStatement |
        getCallStatement |
        catchStatement |
        checkStatement |
        getReplyStatement |
        doneStatement |
        killedStatement;
interleavedConstruct
        : interleavedKeyword '{' interleavedGuardList '}';
interleavedKeyword
        : INTERLEAVE;
interleavedGuardList
        : ( interleavedGuardElement SEMICOLON? )+;
interleavedGuardElement
        : interleavedGuard interleavedAction;
interleavedGuard
        : '[' ']' guardOp;
interleavedAction
        : statementBlock;
labelStatement
        : labelKeyword labelIdentifier;
labelKeyword
        : LABEL;
labelIdentifier
        : IDENTIFIER;
gotoStatement
        : gotoKeyword labelIdentifier;
gotoKeyword
        : GOTO;
repeatStatement
        : REPEAT;
activateOp
        : activateKeyword '(' altstepInstance ')';
activateKeyword
        : ACTIVATE;
deactivateStatement
        : deactivateKeyword ( '(' componentOrDefaultReference ')' )?;
deactivateKeyword
        : DEACTIVATE;
breakStatement
        : BREAK;
continueStatement
        : CONTINUE;

// $>


// $<A.1.6.8 Basic statements

basicStatements
        : assignment | logStatement | loopConstruct | conditionalConstruct |
        selectCaseConstruct;
expression
        : singleExpression | compoundExpression;
compoundExpression
        : fieldExpressionList | arrayExpression;
/* STATIC  SEMANTICS - Within compoundExpression the arrayExpression can be used for arrays, record, record of
and set of types. */
fieldExpressionList
        : '{' fieldExpressionSpec ( ',' fieldExpressionSpec )* '}';
fieldExpressionSpec
        : fieldReference ASSIGNMENT_CHAR notUsedOrExpression;
arrayExpression
        : '{' arrayElementExpressionList? '}';
arrayElementExpressionList
        : notUsedOrExpression ( ',' notUsedOrExpression )*;
notUsedOrExpression
        : expression | notUsedSymbol;
constantExpression
        : singleConstExpression | compoundConstExpression;
singleConstExpression
        : singleExpression;
/* STATIC SEMANTICS - singleConstExpression shall not contain variables or module parameters and shall resolve
to a constant value at compile time */
booleanExpression
        : singleExpression;
/* STATIC SEMANTICS - booleanExpression shall resolve to a value of type boolean */
compoundConstExpression
        : fieldConstExpressionList | arrayConstExpression;
/* STATIC SEMANTICS - Within compoundConstExpression the arrayConstExpression can be used for arrays, record,
record of and set of types. */
fieldConstExpressionList
        : '{' fieldConstExpressionSpec ( ',' fieldConstExpressionSpec ) '}';
fieldConstExpressionSpec
        : fieldReference ASSIGNMENT_CHAR constantExpression;
arrayConstExpression
        : '{' arrayElementConstExpressionList? '}';
arrayElementConstExpressionList
        : constantExpression ( ',' constantExpression )*;
assignment
        : variableRef ASSIGNMENT_CHAR ( expression | templateBody );
/* STATIC SEMANTICS - The expression on the right hand side of assignment shall evaluate to an explicit
value of a type compatible with the type of the left hand side for value variables and shall evaluate to
an explicit value, template (literal or a template instance) or a matching mechanism compatible with the
type of the left hand side for template variables. */
singleExpression
        : xorExpression ( OR xorExpression )*;
/* STATIC SEMANTICS - If more than one xorExpression exists, then the xorExpressions shall evaluate to
specific values of compatible types. */
xorExpression
        : andExpression ( XOR andExpression )*;
/* STATIC SEMANTICS - If more than one andExpression exists, then the andExpressions shall evaluate to
specific values of compatible types. */
andExpression
        : notExpression ( AND notExpression )*;
/* STATIC SEMANTICS - If more than one notExpression exists, then the notExpressions shall evaluate to
specific values of compatible types. */
notExpression
        : NOT? equalExpression;
/* STATIC SEMANTICS - Operands of the not operator shall be of type boolean or derivates of type boolean. */
equalExpression
        : relExpression ( equalOp relExpression )*;
/* STATIC SEMANTICS - If more than one relExpression exists, then the relExpressions shall evaluate to
specific values of compatible types. */
relExpression
        : shiftExpression ( relOp shiftExpression )?;
/* STATIC SEMANTICS - If both shiftExpressions exist, then each shiftExpression shall evaluate to a specific
integer, enumerated or float value or derivates of these types. */
shiftExpression
        : bitOrExpression ( shiftOp bitOrExpression )*;
/* STATIC SEMANTICS - Each result shall resolve to a specific value. If more than one result exists the right-hand
operand shall be of type integer or derivates and if the shift op is '<<' or '>>' then the left-hand operand shall
resolve to either bitstring, hexstring or octetstring type or derivates of these types. If the shift op is
'<@' or '@>' then the left-handoperand shall be of type bitstring, hexstring, octetstring, charstring, universal
charstriing, record of, set of, o array, or derivatives of these types. */
bitOrExpression
        : bitXorExpression ( OR4B bitXorExpression )*;
/* STATIC SEMANTICS - If more than one bitXorExpression exists, then the bitXorExpressions shall evaluate to
specific values of compatible types. */
bitXorExpression
        : bitAndExpression ( XOR4B bitAndExpression )*;
/* STATIC SEMANTICS - If more than one bitAndExpression exists, then the bitAndExpressions shall evaluate to
specific values of compatible types. */
bitAndExpression
        : bitNotExpression (AND4B bitNotExpression )*;
/* STATIC SEMANTICS - If more than one bitNotExpression exists, then the bitNotExpressions shall evaluate to
specific values of compatible types. */
bitNotExpression
        : NOT4B? addExpression;
/* STATIC SEMANTICS - If the not4b operator exist, the operand shall be of type bitstring, octetstring or
hexstring or derivates of these types. */
addExpression
        : mulExpression ( addOp mulExpression )*;
/* STATIC SEMANTICS - Each mulExpression shall resolve to a specific value. If more than one mulExpression
exists and the addOp resolves to stringOp then the mulExpressions shall be valid operands for stringOp. If
more than one mulExpression exists and the addOp does not resolve to stringOp then the mulExpression shall
both resolve to type integer or float or derivatives of these types. */
mulExpression
        : unaryExpression ( multiplyOp unaryExpression )*;
/* STATIC SEMANTICS - Each unaryExpression shall resolve to a specific value. If more than one unaryExpression
exists then the unaryExpressions shall resolve to type integer or float or derivatives of these types. */
unaryExpression
        : unaryOp? primary;
/* STATIC SEMANTICS - primary shall resolve to a specific value of type integer or float or derivatives of
these types. */
primary
        : opCall | value | '(' singleExpression ')';
extendedFieldReference
        : ( ( DOT ( structFieldIdentifier | typeDefIdentifier ) )
        | arrayOrBitRef )+;
/* STATIC SEMANTIC - The typedefidentifier shall be used only if the type of the varInstance or referencedValue
in which the extendedFieldReference is used is anytype. */
opCall
        : configurationOps |
        verdictOps |
        timerOps |
        testcaseInstance |
        functionInstance |
        templateOps |
        activateOp;
addOp
        : '+' | '-' | stringOp;
/* STATIC SEMANTICS - Operands of the '+' or '-' operators shall be of type integer of float or derivations
of integer or float (i.e. subrange) */
multiplyOp
        : '*' | '/' | MOD | REM;
/* STATIC SEMANTICS - Operands of the '*', '/', rem or mod operators shall be of type integer or float or
derivations of integer or float (i.e. subrange). */
unaryOp
        : '+' | '-';
/* STATIC SEMANTICS - Operands of the '+' or '-' operators shall be of type integer or float or derivations
of integer or float (i.e. subrange). */
relOp
        : '<' | '>' | '>=' | '<=';
/* STATIC SEMANTICS - the precedence of the operators is defined in Table 6 */
equalOp
        : '==' | '!=';
stringOp
        : '&';
/* STATIC SEMANTICS - Operands of the string operator shall be bitstring, hexstring, octetstring, (universal) 
character string, record of, set of, or array types, or derivates of these types */
shiftOp
        : '<<' | '>>' | '<@' | '>@';
logStatement
        : logKeyword '(' logItem ( ',' logItem )* ')';
logKeyword
        : LOG;
logItem
        : FREE_TEXT | templateInstance;
loopConstruct
        : forStatement |
        whileStatement |
        doWhileStatement;
forStatement
//        scope Symbols;
        : forKeyword '(' initial SEMICOLON final SEMICOLON step ')'
        statementBlock;
forKeyword
        : FOR;
initial
        : varInstance | assignment;
final
        : booleanExpression;
step
        : assignment;
whileStatement
        : whileKeyword '(' booleanExpression ')'
        statementBlock;
whileKeyword
        : WHILE;
doWhileStatement
        : doKeyword statementBlock
        whileKeyword '(' booleanExpression ')';
doKeyword
        : DO;
conditionalConstruct
        : ifKeyword '(' booleanExpression ')'
        statementBlock
        elseIfClause* elseClause?;
ifKeyword
        : IF;
elseIfClause
        : elseKeyword ifKeyword '(' booleanExpression ')' statementBlock;
elseKeyword
        : ELSE;
elseClause
        : elseKeyword statementBlock;
selectCaseConstruct
        : selectKeyword '(' singleExpression ')' selectCaseBody;
selectKeyword
        : SELECT;
selectCaseBody
        : '{' selectCase+ '}';
selectCase
        : caseKeyword ( '(' templateInstance ( ',' templateInstance )* ')' | elseKeyword )
        statementBlock;
caseKeyword
        : CASE;

// $>


// $<A.1.6.9 - Miscellaneous productions

dash
        : MINUS;

// $>

fragment NEW_LINE
        : '\n';

WHITESPACE
        : ( '\t' | ' ' | '\r'
           | NEW_LINE
        {
            CTranslator::Instance().Line($NEW_LINE.line + 1);
        }
           | '\u000C' )+
           { $channel = HIDDEN; };

COMMENT
        : '/*' ( options { greedy=false; } : . )* '*/'
        { $channel = HIDDEN; };
LINE_COMMENT
        : '//' ~('\n'|'\r')* '\r'? '\n'
        { $channel = HIDDEN; };
