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
    language = C;
    backtrack = true;
//    k = 10;
}


tokens {
	MODULE = 'module';
	LANGUAGE = 'language';
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



@lexer::members {

}


// $<A.1.6.0 TTCN-3 module

ttcn3Module		: ttcn3ModuleKeyword ttcn3ModuleId
			'{'
			moduleDefinitionsPart?
			moduleControlPart?
			'}'
			withStatement? SEMICOLON? EOF;
fragment ttcn3ModuleKeyword	: MODULE;
fragment ttcn3ModuleId		: moduleId;
moduleId			: globalModuleId languageSpec?;
fragment globalModuleId		: moduleIdentifier;
fragment moduleIdentifier	: IDENTIFIER;
languageSpec		: languageKeyword FREE_TEXT;
fragment languageKeyword		: LANGUAGE;

// $>


// $<A.1.6.1 Module definitions part

// $<A.1.6.1.0 General

fragment moduleDefinitionsPart	: moduleDefinitionsList;
moduleDefinitionsList	: ( moduleDefinition SEMICOLON? )+;
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

typeDef			: typeDefKeyword typeDefBody;
typeDefBody		: structuredTypeDef | subTypeDef;
fragment typeDefKeyword		: TYPE;
structuredTypeDef
			: recordDef |
			unionDef |
			setDef |
			recordOfDef |
			setOfDef |
			enumDef |
			portDef |
			componentDef;
recordDef		: recordKeyword structDefBody;
fragment recordKeyword		: RECORD;
structDefBody		: ( ( structTypeIdentifier structDefFormalParList? ) | addressKeyword )
			'{' ( structFieldDef ( ',' structFieldDef )* )? '}';
fragment structTypeIdentifier	: IDENTIFIER;
structDefFormalParList	: '(' structDefFormalPar ( ',' structDefFormalPar )* ')';
fragment structDefFormalPar	: formalValuePar;
structFieldDef		: ( type | nestedTypeDef ) structFieldIdentifier arrayDef? subTypeSpec?
			optionalKeyword?;
nestedTypeDef
			: nestedRecordDef |
			nestedUnionDef |
			nestedSetDef |
			nestedRecordOfDef |
			nestedSetOfDef |
			nestedEnumDef;
nestedRecordDef		: recordKeyword '{' ( structFieldDef ( ',' structFieldDef )* )? '}';
nestedUnionDef		: unionKeyword '{' unionFieldDef ( ',' unionFieldDef )* '}';
nestedSetDef		: setKeyword '{' ( structFieldDef ( ',' structFieldDef )* )? '}';
nestedRecordOfDef	: recordKeyword stringLength? ofKeyword ( type | nestedTypeDef );
nestedSetOfDef		: setKeyword stringLength? ofKeyword ( type | nestedTypeDef );
nestedEnumDef		: enumKeyword '{' enumerationList '}';
fragment structFieldIdentifier	: IDENTIFIER;
fragment optionalKeyword		: OPTIONAL;
unionDef		: unionKeyword unionDefBody;
fragment unionKeyword		: UNION;
unionDefBody		: ( structTypeIdentifier structDefFormalParList? | addressKeyword )
			'{' unionFieldDef ( ',' unionFieldDef )* '}';
unionFieldDef		: ( type | nestedTypeDef ) structFieldIdentifier arrayDef? subTypeSpec?;
setDef			: setKeyword structDefBody;
fragment setKeyword		: SET;
recordOfDef		: recordKeyword stringLength? ofKeyword structOfDefBody;
fragment ofKeyword		: OF;
structOfDefBody		: ( type | nestedTypeDef ) ( structTypeIdentifier | addressKeyword ) subTypeSpec?;
setOfDef		: setKeyword stringLength? ofKeyword structOfDefBody;
enumDef			: enumKeyword ( enumTypeIdentifier | addressKeyword )
			'{'  enumerationList '}';
fragment enumKeyword		: ENUMERATED;
fragment enumTypeIdentifier	: IDENTIFIER;
enumerationList		: enumeration ( ',' enumeration )*;
enumeration		: enumerationIdentifier ( '(' MINUS? NUMBER ')' )?;
fragment enumerationIdentifier	: IDENTIFIER;
subTypeDef		: type ( subTypeIdentifier | addressKeyword ) arrayDef? subTypeSpec?;
fragment subTypeIdentifier	: IDENTIFIER;
subTypeSpec		: allowedValues stringLength? | stringLength;
/* STATIC SEMATICS - allowedValues shall be of the same type as the field being subtyped */
allowedValues		: '(' ( ( valueOrRange ( ',' valueOrRange )* ) | charStringMatch ) ')';
/* ---A--- BUG ---A--- */
valueOrRange		: rangeDef | constantExpression;
/* STATIC SEMANTICS - rangeDef production shall only be used with integer, charstring, universal charstring or float based types */
/* STATIC SEMANTICS - When subtyping charstring or universal charstring range and values shall not be mixed in the same subTypeSpec */
rangeDef		: lowerBound '..' upperBound;
stringLength		: lengthKeyword '(' singleConstExpression ( '..' upperBound )? ')';
/* STATIC SEMANTICS - stringLength shall only be used with string types or to limit set of and record of. singleConstExpression
and upperBound shall evaluate to non-negative integervalues (in case of upperBound including infinity) */
fragment lengthKeyword		: LENGTH;
portType		: ( globalModuleId DOT )? portTypeIdentifier;
portDef			: portKeyword portDefBody;
portDefBody		: portTypeIdentifier portDefAttribs;
fragment portKeyword		: PORT;
fragment portTypeIdentifier	: IDENTIFIER;
portDefAttribs		: messageAttribs | procedureAttribs | mixedAttribs;
messageAttribs		: messageKeyword
			'{' ( messageList SEMICOLON? )+ '}';
messageList		: direction allOrTypeList;
direction		: inParKeyword | outParKeyword | inOutParKeyword;
fragment messageKeyword		: MESSAGE;
allOrTypeList		: allKeyword | typeList;
/* NOTE: The use of allKeyword in port definitions is deprecated */
fragment allKeyword		: ALL;
typeList		: type ( ',' type )*;
procedureAttribs	: procedureKeyword
			'{' ( procedureList SEMICOLON? )+ '}';
fragment procedureKeyword	: PROCEDURE;
procedureList		: direction allOrSignatureList;
allOrSignatureList	: allKeyword | signatureList;
signatureList		: signature ( ',' signature )*;
mixedAttribs		: mixedKeyword
			'{' ( mixedList SEMICOLON? )+ '}';
fragment mixedKeyword		: MIXED;
mixedList 		: direction procOrTypeList;
procOrTypeList		: allKeyword | ( procOrType ( ',' procOrType )* );
procOrType		: signature | type;
componentDef		: componentKeyword componentTypeIdentifier
			( extendsKeyword componentType ( ',' componentType )* )?
			'{' componentDefList? '}';
fragment componentKeyword	: COMPONENT;
fragment extendsKeyword		: EXTENDS;
componentType		: ( globalModuleId DOT )? componentTypeIdentifier;
fragment componentTypeIdentifier	: IDENTIFIER;
componentDefList	: ( componentElementDef SEMICOLON? )*;
componentElementDef	: portInstance | varInstance | timerInstance | constDef;
portInstance		: portKeyword portType portElement ( ',' portElement )*;
portElement		: portIdentifier arrayDef?;
fragment portIdentifier		: IDENTIFIER;

// $>


// $<A.1.6.1.2 Constant definitions

constDef		: constKeyword type constList;
constList		: singleConstDef ( ',' singleConstDef )*;
singleConstDef		: constIdentifier arrayDef? ASSIGNMENT_CHAR constantExpression;
fragment constKeyword		: CONST;
fragment constIdentifier		: IDENTIFIER;

// $>


// $<A.1.6.1.3 Template definitions

templateDef		: templateKeyword baseTemplate derivedDef? ASSIGNMENT_CHAR templateBody;
baseTemplate		: ( type | signature ) templateIdentifier ( '(' templateFormalParList ')' )?;
fragment templateKeyword		: TEMPLATE;
fragment templateIdentifier	: IDENTIFIER;
derivedDef		: modifiesKeyword templateRef;
fragment modifiesKeyword		: MODIFIES;
templateFormalParList	: templateFormalPar ( ',' templateFormalPar )*;
templateFormalPar	: formalValuePar | formalTemplatePar;
/* STATIC SEMANTICS - formalValuePar shall resolve to an in parameter */
templateBody		: ( simpleSpec | fieldSpecList | arrayValueOrAttrib ) | extraMatchingAttributes?;
/* STATIC SEMANTICS - Within templateBody the arrayValueOrAttrib can be used for array, record, record of and set of types. */
fragment simpleSpec		: singleValueOrAttrib;
fieldSpecList		: '{' ( fieldSpec ( ',' fieldSpec )* )? '}';
fieldSpec		: fieldReference ASSIGNMENT_CHAR templateBody;
fieldReference		: structFieldRef | arrayOrBitRef | parRef;
/* STATIC SEMANTICS - Within fieldReference arrayOrBitRef can be used for record of and set of templates/template fields
in modified templates only. */
structFieldRef		: structFieldIdentifier | predefinedType | typeReference;
/* STATIC SEMANTICS - predefinedType and typeReference shall be used for anytype value notation only. predefinedType shall
not be anyTypeKeyword. */
fragment parRef			: signatureParIdentifier;
/* STATIC SEMANTICS - signatureParIdentifier shall be a formal parameter identifier from the associated signature definition. */
fragment signatureParIdentifier	: valueParIdentifier;
arrayOrBitRef		: '[' fieldOrBitNumber ']';
/* STATIC SEMANTICS - arrayRef shall be optionally used for array types and TTCN-3 record of and set of. The same notation
can be used for a bit reference inside an TTCN-3 charstring, universal charstring, bitstring, octetstring and hexstring type. */
fragment fieldOrBitNumber	: singleExpression;
/* STATIC SEMANTICS - singleExpression will resolve to a value of integer type */
singleValueOrAttrib	: matchingSymbol |
			singleExpression |
			templateRefWithParList;
/* STATIC SEMANTICS - variableIdentifier (accessed via singleExpression) may only be used in in-line template definitions
to reference variables in the current scope. */
arrayValueOrAttrib	: '{' arrayElementSpecList '}';
arrayElementSpecList	: arrayElementSpec ( ',' arrayElementSpec )*;
arrayElementSpec	: notUsedSymbol | permutationMatch | templateBody;
fragment notUsedSymbol		: dash;
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
extraMatchingAttributes	: lengthMatch | ifPresentMatch | lengthMatch ifPresentMatch;
bitStringMatch		: '\'' binOrMatch* '\'' 'B';
binOrMatch		: BIN | ANY_VALUE | ANY_OR_OMIT;
hexStringMatch		: '\'' hexOrMatch* '\'' 'H';
hexOrMatch		: HEX | ANY_VALUE | ANY_OR_OMIT;
octetStringMatch	: '\'' octOrMatch* '\'' 'O';
octOrMatch		: OCT | ANY_VALUE | ANY_OR_OMIT;
charStringMatch		: patternKeyword cString;
fragment patternKeyword		: PATTERN;
complement		: complementKeyword valueOrAttribList; // valueOrAttribListValueList;
/* ---A--- BUG ---A--- */
fragment complementKeyword	: COMPLEMENT;
valueList		: '(' constantExpression ( ',' constantExpression )* ')';
subsetMatch		: subsetKeyword valueList;
fragment subsetKeyword		: SUBSET;
supersetMatch		: supersetKeyword valueList;
fragment supersetKeyword		: SUPERSET;
permutationMatch	: permutationKeyword permutationList;
fragment permutationKeyword	: PERMUTATION;
permutationList		: '(' templateBody ( ',' templateBody )* ')';
/* STATIC SEMANTICS - Restrictions on the content of templateBody are given in clause B.1.3.3 */
ANY_VALUE		: '?';
ANY_OR_OMIT		: '*';
valueOrAttribList	: '(' templateBody ( ',' templateBody )+ ')';
fragment lengthMatch		: stringLength;
fragment ifPresentMatch		: ifPresentKeyword;
fragment ifPresentKeyword	: IF_PRESENT;
range			: '(' lowerBound '..' upperBound ')';
lowerBound		: singleConstExpression | MINUS infinityKeyword;
upperBound		: singleConstExpression | infinityKeyword;
/* STATIC SEMANTICS - lowerBound and upperBound shall evaluate to types integer, charstring, universal charstring
or float. In case lowerBound or upperBound evaluates to types charstring or universal charstring, only
singleConstExpression may be present and the string length shall be 1 */
fragment infinityKeyword		: INFINITY;
fragment templateInstance	: inLineTemplate;
templateRefWithParList	: ( globalModuleId DOT )? templateIdentifier templateActualParList? |
			templateParIdentifier;
templateRef		: ( globalModuleId DOT )? templateIdentifier | templateParIdentifier;
inLineTemplate		: ( ( type | signature ) COLON )? ( derivedRefWithParList ASSIGNMENT_CHAR )?
			templateBody;
derivedRefWithParList	: modifiesKeyword templateRefWithParList;
templateActualParList	: '(' templateActualPar ( ',' templateActualPar )* ')';
fragment templateActualPar	: templateInstance;
/* STATIC SEMANTICS - When the corresponding formal parameter is not of template type the templateInstance
production shall resolve to one or more singleExpressions. */
templateOps		: matchOp | valueofOp;
matchOp			: matchKeyword '(' expression ',' templateInstance ')';
fragment matchKeyword		: MATCH;
valueofOp		: valueofKeyword '(' templateInstance ')';
fragment valueofKeyword		: VALUE_OF;

// $>


// $<A.1.6.1.4 Function definitions

functionDef		: functionKeyword functionIdentifier
			'(' functionFormalParList? ')' runsOnSpec? returnType?
			statementBlock;
fragment functionKeyword		: FUNCTION;
fragment functionIdentifier	: IDENTIFIER;
functionFormalParList	: functionFormalPar ( ',' functionFormalPar )*;
functionFormalPar
			: formalValuePar |
			formalTimerPar |
			formalTemplatePar | 
			formalPortPar;
returnType		: returnKeyword ( templateKeyword | restrictedTemplate )? type;
fragment returnKeyword		: RETURN;
runsOnSpec		: runsKeyword onKeyword componentType;
fragment runsKeyword		: RUNS;
fragment onKeyword		: ON;
fragment mtcKeyword		: MTC;
statementBlock		: '{' functionStatementOrDefList? '}';
functionStatementOrDefList	: ( functionStatementOrDef SEMICOLON? )+;
functionStatementOrDef	: functionLocalDef |
			functionLocalInst |
			functionStatement;
functionLocalInst	: varInstance | timerInstance;
functionLocalDef	: constDef | templateDef;
functionStatement
			: configurationStatements |
			timerStatements |
			communicationStatements |
			basicStatements |
			behaviourStatements |
			verdictStatements |
			sutStatements;
functionInstance	: functionRef '(' functionActualParList? ')';
functionRef		: ( globalModuleId DOT )? ( functionIdentifier | extFunctionIdentifier ) |
			preDefFunctionIdentifier;
fragment preDefFunctionIdentifier	: IDENTIFIER;
/* STATIC SEMANTICS - The identifier shall be one of the pre-defined TTCN-3 Function Identifiers from Annex C of
ES 201 873-1 */
functionActualParList	: functionActualPar ( ',' functionActualPar )*;
functionActualPar
			: timerRef |
			templateInstance |
			port |
			componentRef;
/* STATIC SEMANTICS - When the corresponding formal parameter is not of template type the templateInstance production
shall resolve to one or more singleExpressions i.e. equivalent to the expression production. */

// $>


// $<A.1.6.1.5 Signature definitions

signatureDef		: signatureKeyword signatureIdentifier
			'(' signatureFormalParList? ')' ( returnType | noBlockKeyword )?
			exceptionSpec?;
fragment signatureKeyword	: SIGNATURE;
fragment signatureIdentifier	: IDENTIFIER;
signatureFormalParList	: signatureFormalPar ( ',' signatureFormalPar )*;
signatureFormalPar	: formalValuePar;
exceptionSpec		: exceptionKeyword '(' exceptionTypeList ')';
fragment exceptionKeyword	: TTCN_EXCEPTION;
exceptionTypeList	: type ( ',' type )*;
fragment noBlockKeyword		: NO_BLOCK;
signature		: ( globalModuleId DOT )? signatureIdentifier;

// $>


// $<A.1.6.1.6 Testcase definitions

testcaseDef		: testcaseKeyword testcaseIdentifier
			'(' testcaseFormalParList? ')' configSpec
			statementBlock;
fragment testcaseKeyword		: TESTCASE;
fragment testcaseIdentifier	: IDENTIFIER;
testcaseFormalParList	: testcaseFormalPar ( ',' testcaseFormalPar )*;
testcaseFormalPar
			: formalValuePar |
			formalTemplatePar;
configSpec		: runsOnSpec systemSpec?;
systemSpec		: systemKeyword componentType;
fragment systemKeyword		: SYSTEM;
testcaseInstance	: executeKeyword '(' testcaseRef '(' testcaseActualParList? ')'
			( ',' timerValue )? ')';
fragment executeKeyword		: EXECUTE;
testcaseRef		: ( globalModuleId DOT )? testcaseIdentifier;
testcaseActualParList	: testcaseActualPar ( ',' testcaseActualPar )*;
fragment testcaseActualPar	: templateInstance;
/* STATIC SEMANTICS - When the corresponding formal parameter is not of template type the templateInstance
production shall resolve to one or more singleExpressions i.e. equivalent to the expression production. */

// $>


// $<A.1.6.1.7 Altstep definitions

altstepDef		: altstepKeyword altstepIdentifier
			'(' altstepFormalParList? ')' runsOnSpec?
			'{' altstepLocalDefList altGuardList '}';
fragment altstepKeyword		: ALTSTEP;
fragment altstepIdentifier	: IDENTIFIER;
fragment altstepFormalParList	: functionFormalParList;
altstepLocalDefList	: ( altstepLocalDef SEMICOLON? )*;
altstepLocalDef		: varInstance | timerInstance | constDef | templateDef;
altstepInstance		: altstepRef '(' functionActualParList? ')';
altstepRef		: ( globalModuleId DOT )? altstepIdentifier;

// $>


// $<A.1.6.1.8 Import definitions

importDef		: importKeyword importFromSpec ( allWithExcepts | ( '{' importSpec '}' ) );
fragment importKeyword		: IMPORT;
allWithExcepts		: allKeyword exceptsDef?;
exceptsDef		: exceptKeyword '{' exceptSpec '}';
fragment exceptKeyword		: EXCEPT;
exceptSpec		: ( exceptElement SEMICOLON? )*;
exceptElement		: exceptGroupSpec |
			exceptTypeDefSpec |
			exceptTemplateSpec |
			exceptConstSpec |
			exceptTestcaseSpec |
			exceptAltstepSpec |
			exceptFunctionSpec |
			exceptSignatureSpec |
			exceptModuleParSpec;
exceptGroupSpec		: groupKeyword ( exceptGroupRefList | allKeyword );
exceptTypeDefSpec	: typeDefKeyword ( typeRefList | allKeyword );
exceptTemplateSpec	: templateKeyword ( templateRefList | allKeyword );
exceptConstSpec		: constKeyword ( constRefList | allKeyword );
exceptTestcaseSpec	: testcaseKeyword ( testcaseRefList | allKeyword );
exceptAltstepSpec	: altstepKeyword ( altstepRefList | allKeyword );
exceptFunctionSpec	: functionKeyword ( functionRefList | allKeyword );
exceptSignatureSpec	: signatureKeyword ( signatureRefList | allKeyword );
exceptModuleParSpec	: moduleParKeyword ( moduleParRefList | allKeyword );
importSpec		: ( importElement SEMICOLON? )*;
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
importFromSpec		: fromKeyword moduleId recursiveKeyword?;
fragment recursiveKeyword	: RECURSIVE;
importGroupSpec		: groupKeyword ( groupRefListWithExcept | allGroupsWithExcept );
groupRefList		: fullGroupIdentifier ( ',' fullGroupIdentifier )*;
groupRefListWithExcept	: fullGroupIdentifierWithExcept ( ',' fullGroupIdentifierWithExcept )*;
allGroupsWithExcept	: allKeyword ( exceptKeyword groupRefList )?;
fullGroupIdentifier	: groupIdentifier ( DOT groupIdentifier )*;
fullGroupIdentifierWithExcept	: fullGroupIdentifier exceptsDef?;
exceptGroupRefList	: exceptFullGroupIdentifier ( ',' exceptFullGroupIdentifier )*;
exceptFullGroupIdentifier	: fullGroupIdentifier;
importTypeDefSpec	: typeDefKeyword ( typeRefList | allTypesWithExcept );
typeRefList		: typeDefIdentifier ( ',' typeDefIdentifier )*;
allTypesWithExcept	: allKeyword ( exceptKeyword typeRefList )?;
typeDefIdentifier
			: structTypeIdentifier |
			enumTypeIdentifier |
			portTypeIdentifier |
			componentTypeIdentifier |
			subTypeIdentifier;
importTemplateSpec	: templateKeyword ( templateRefList | allTemplsWithExcept );
templateRefList		: templateIdentifier ( ',' templateIdentifier )*;
allTemplsWithExcept	: allKeyword ( exceptKeyword templateRefList )?;
importConstSpec		: constKeyword ( constRefList | allConstsWithExcept );
constRefList		: constIdentifier ( ',' constIdentifier )*;
allConstsWithExcept	: allKeyword ( exceptKeyword constRefList )?;
importAltstepSpec	: altstepKeyword ( altstepRefList | allAltstepsWithExcept );
altstepRefList		: altstepIdentifier ( ',' altstepIdentifier )*;
allAltstepsWithExcept	: allKeyword ( exceptKeyword altstepRefList )?;
importTestcaseSpec	: testcaseKeyword ( testcaseRefList | allTestcasesWithExcept );
testcaseRefList		: testcaseIdentifier ( ',' testcaseIdentifier )*;
allTestcasesWithExcept	: allKeyword ( exceptKeyword testcaseRefList )?;
importFunctionSpec	: functionKeyword ( functionRefList | allFunctionsWithExcept );
functionRefList		: functionIdentifier ( ',' functionIdentifier )*;
allFunctionsWithExcept	: allKeyword ( exceptKeyword functionRefList )?;
importSignatureSpec	: signatureKeyword ( signatureRefList | allSignaturesWithExcept );
signatureRefList	: signatureIdentifier ( ',' signatureIdentifier )*;
allSignaturesWithExcept	: allKeyword ( exceptKeyword signatureRefList )?;
importModuleParSpec	: moduleParKeyword ( moduleParRefList | allModuleParWithExcept );
moduleParRefList	: moduleParIdentifier ( ',' moduleParIdentifier )*;
allModuleParWithExcept	: allKeyword ( exceptKeyword moduleParRefList )?;

// $>


// $<A.1.6.1.9 Group definitions

groupDef		: groupKeyword groupIdentifier
			'{' moduleDefinitionsPart? '}';
fragment groupKeyword		: TTCN_GROUP;
fragment groupIdentifier		: IDENTIFIER;

// $>


// $<A.1.6.1.10 External function definitions

extFunctionDef		: extKeyword functionKeyword extFunctionIdentifier
			'(' functionFormalParList? ')' returnType?;
fragment extKeyword		: EXTERNAL;
fragment extFunctionIdentifier	: IDENTIFIER;

// $>


// $<A.1.6.1.11 External constant definitions

extConstDef		: extKeyword constKeyword type extConstIdentifierList;
extConstIdentifierList	: extConstIdentifier ( ',' extConstIdentifier )*;
fragment extConstIdentifier	: IDENTIFIER;

// $>


// $<A.1.6.1.12 Module parameter definitions

moduleParDef		: moduleParKeyword ( modulePar | ( '{' multitypedModuleParList '}' ) );
fragment moduleParKeyword	: MODULE_PAR;
multitypedModuleParList	: ( modulePar SEMICOLON? )*;
modulePar		: moduleParType moduleParList;
fragment moduleParType		: type;
moduleParList		: moduleParIdentifier ( ASSIGNMENT_CHAR constantExpression )?
			( ',' moduleParIdentifier ( ASSIGNMENT_CHAR constantExpression )? )*;
fragment moduleParIdentifier	: IDENTIFIER;

// $>

// $>



// $<A.1.6.2 Control part

// $<A.1.6.2.0 General

moduleControlPart	: controlKeyword
			'{' moduleControlBody '}'
			withStatement? SEMICOLON?;
fragment controlKeyword		: CONTROL;
fragment moduleControlBody	: controlStatementOrDefList?;
controlStatementOrDefList	: ( controlStatementOrDef SEMICOLON? )+;
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

varInstance		: varKeyword ( ( type varList ) | ( ( templateKeyword | restrictedTemplate ) type tempVarList ) );
varList			: singleVarInstance ( ',' singleVarInstance )*;
singleVarInstance	: varIdentifier arrayDef? ( ASSIGNMENT_CHAR varInitialValue )?;
fragment varInitialValue		: expression;
fragment varKeyword		: VAR;
fragment varIdentifier		: IDENTIFIER;
tempVarList		: singleTempVarInstance ( ',' singleTempVarInstance )*;
singleTempVarInstance	: varIdentifier arrayDef? ( ASSIGNMENT_CHAR tempVarInitialValue )?;
fragment tempVarInitialValue	: templateBody;
variableRef		: ( varIdentifier | valueParIdentifier ) extendedFieldReference?;

// $>


// $<A.1.6.2.2 Timer instantiation

timerInstance		: timerKeyword timerList;
timerList		: singleTimerInstance ( ',' singleTimerInstance )*;
singleTimerInstance	: timerIdentifier arrayDef? ( ASSIGNMENT_CHAR timerValue )?;
fragment timerKeyword		: TIMER;
fragment timerIdentifier		: IDENTIFIER;
fragment timerValue		: expression;
timerRef		: ( timerIdentifier | timerParIdentifier ) arrayOrBitRef*;

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
configurationOps	: createOp | selfOp | systemOp | mtcOp | runningOp | aliveOp;
createOp		: componentType DOT createKeyword ( '(' singleExpression ')' )? aliveKeyword?;
fragment systemOp		: systemKeyword;
fragment selfOp			: SELF;
fragment mtcOp			: mtcKeyword;
doneStatement		: componentId DOT doneKeyword;
killedStatement		: componentId DOT killedKeyword;
componentId		: componentOrDefaultReference | ( ( anyKeyword | allKeyword ) componentKeyword );
/* ---A--- BUG ---A--- */
fragment doneKeyword		: DONE;
fragment killedKeyword		: KILLED;
runningOp		: componentId DOT runningKeyword;
fragment runningKeyword		: RUNNING;
aliveOp			: componentId DOT aliveKeyword;
fragment createKeyword		: CREATE;
fragment aliveKeyword		: ALIVE;
connectStatement	: connectKeyword singleConnectionSpec;
fragment connectKeyword		: CONNECT;
singleConnectionSpec	: '(' portRef ',' portRef ')';
portRef			: componentRef COLON port;
componentRef		: componentOrDefaultReference | systemOp | selfOp | mtcOp;
disconnectStatement	: disconnectKeyword singleOrMultiConnectionSpec?;
singleOrMultiConnectionSpec
				: singleConnectionSpec |
				allConnectionsSpec |
				allPortsSpec |
				allCompsAllPortsSpec;
allConnectionsSpec	: '(' portRef ')';
allPortsSpec		: '(' componentRef ':' allKeyword portKeyword ')';
allCompsAllPortsSpec	: '(' allKeyword componentKeyword ':' allKeyword portKeyword ')';
fragment disconnectKeyword	: DISCONNECT;
mapStatement		: mapKeyword singleConnectionSpec;
fragment mapKeyword		: MAP;
unmapStatement		: unmapKeyword singleOrMultiConnectionSpec?;
fragment unmapKeyword		: UNMAP;
startTCStatement	: componentOrDefaultReference DOT startKeyword '(' functionInstance ')';
fragment startKeyword		: START;
stopTCStatement		: stopKeyword | ( componentReferenceOrLiteral DOT stopKeyword ) |
			( allKeyword componentKeyword DOT stopKeyword );
componentReferenceOrLiteral	: componentOrDefaultReference | mtcOp | selfOp;
killTCStatement		: killKeyword | ( componentReferenceOrLiteral DOT killKeyword ) |
			( allKeyword componentKeyword DOT killKeyword );
componentOrDefaultReference	: variableRef | functionInstance;
fragment killKeyword		: KILL;

// $>


// $<A.1.6.2.4 Port operations

port			: ( portIdentifier | portParIdentifier ) arrayOrBitRef*;
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
sendStatement		: port DOT portSendOp;
portSendOp		: sendOpKeyword '(' sendParameter ')' toClause?;
fragment sendOpKeyword		: SEND;
fragment sendParameter		: templateInstance;
toClause		: toKeyword ( addressRef |
			addressRefList |
			( allKeyword componentKeyword ) );
/* ---A--- BUG ---A--- */
addressRefList		: '(' addressRef ( ',' addressRef )* ')';
fragment toKeyword		: TO;
fragment addressRef		: templateInstance;
callStatement		: port DOT portCallOp portCallBody?;
portCallOp		: callOpKeyword '(' callParameters ')' toClause?;
fragment callOpKeyword		: CALL;
callParameters		: templateInstance ( ',' callTimerValue )?;
callTimerValue		: timerValue | nowaitKeyword;
fragment nowaitKeyword		: NO_WAIT;
portCallBody		: '{' callBodyStatementList '}';
callBodyStatementList	: ( callBodyStatement SEMICOLON? )+;
callBodyStatement	: callBodyGuard statementBlock;
callBodyGuard		: altGuardChar callBodyOps;
callBodyOps		: getReplyStatement | catchStatement;
replyStatement		: port DOT portReplyOp;
portReplyOp		: replyKeyword '(' templateInstance replyValue? ')' toClause?;
fragment replyKeyword		: REPLY;
replyValue		: valueKeyword expression;
raiseStatement		: port DOT portRaiseOp;
portRaiseOp		: raiseKeyword '(' signature ',' templateInstance ')' toClause?;
fragment raiseKeyword		: RAISE;
receiveStatement	: portOrAny DOT portReceiveOp;
portOrAny		: port | anyKeyword portKeyword;
portReceiveOp		: receiveOpKeyword ( '(' receiveParameter ')' )? fromClause? portRedirect?;
fragment receiveOpKeyword	: RECEIVE;
fragment receiveParameter	: templateInstance;
fromClause		: fromKeyword ( addressRef |
			addressRefList |
			( anyKeyword componentKeyword ) );
/* ---A--- BUG ---A--- */
fragment fromKeyword		: FROM;
portRedirect		: PORT_REDIRECT_SYMBOL ( valueSpec senderSpec? | senderSpec );
fragment PORT_REDIRECT_SYMBOL	: '->';
valueSpec		: valueKeyword variableRef;
fragment valueKeyword		: VALUE;
senderSpec		: senderKeyword variableRef;
fragment senderKeyword		: SENDER;
triggerStatement	: portOrAny DOT portTriggerOp;
portTriggerOp		: triggerOpKeyword ( '(' receiveParameter ')' )? fromClause? portRedirect?;
fragment triggerOpKeyword	: TRIGGER;
getCallStatement	: portOrAny DOT portGetCallOp;
portGetCallOp		: getCallOpKeyword ( '(' receiveParameter ')' )? fromClause?
			portRedirectWithParam?;
fragment getCallOpKeyword	: GET_CALL;
portRedirectWithParam	: PORT_REDIRECT_SYMBOL redirectWithParamSpec;
redirectWithParamSpec	: (paramSpec senderSpec?) |
			senderSpec;
/* ---A--- BUG ---A--- */
paramSpec		: paramKeyword paramAssignmentList;
fragment paramKeyword		: PARAM;
paramAssignmentList	: '(' ( assignmentList | variableList ) ')';
assignmentList		: variableAssignment ( ',' variableAssignment )*;
variableAssignment	: variableRef ASSIGNMENT_CHAR parameterIdentifier;
fragment parameterIdentifier	: valueParIdentifier;
variableList		: variableEntry ( ',' variableEntry )*;
variableEntry		: variableRef | notUsedSymbol;
getReplyStatement	: portOrAny DOT portGetReplyOp;
portGetReplyOp		: getReplyOpKeyword ( '(' receiveParameter valueMatchSpec? ')' )?
			fromClause? portRedirectWithValueAndParam?;
portRedirectWithValueAndParam	: PORT_REDIRECT_SYMBOL redirectWithValueAndParamSpec;
redirectWithValueAndParamSpec	: valueSpec paramSpec? senderSpec? |
				redirectWithParamSpec;
fragment getReplyOpKeyword	: GET_REPLY;
valueMatchSpec		: valueKeyword templateInstance;
checkStatement		: portOrAny DOT portCheckOp;
portCheckOp		: checkOpKeyword ( '(' checkParameter ')' )?;
fragment checkOpKeyword		: CHECK;
checkParameter		: checkPortOpsPresent | fromClausePresent | redirectPresent;
fromClausePresent	: fromClause ( PORT_REDIRECT_SYMBOL senderSpec )?;
redirectPresent		: PORT_REDIRECT_SYMBOL senderSpec;
checkPortOpsPresent	: portReceiveOp | portGetCallOp | portGetReplyOp | portCatchOp;
catchStatement		: portOrAny DOT portCatchOp;
portCatchOp		: catchOpKeyword ( '(' catchOpParameters ')' )? fromClause? portRedirect?;
fragment catchOpKeyword		: CATCH;
catchOpParameters	: signature ',' templateInstance | timeoutKeyword;
clearStatement		: portOrAll DOT portClearOp;
portOrAll		: port | allKeyword portKeyword;
fragment portClearOp		: clearOpKeyword;
fragment clearOpKeyword		: CLEAR;
startStatement		: portOrAll DOT portStartOp;
fragment portStartOp		: startKeyword;
stopStatement		: portOrAll DOT portStopOp;
fragment portStopOp		: stopKeyword;
fragment stopKeyword		: STOP;
fragment anyKeyword		: ANY;

// $>


// $<A.1.6.2.5 Timer operations

timerStatements		: startTimerStatement | stopTimerStatement | timeoutStatement;
timerOps		: readTimerOp | runningTimerOp;
startTimerStatement	: timerRef DOT startKeyword ( '(' timerValue ')' )?;
stopTimerStatement	: timerRefOrAll DOT stopKeyword;
timerRefOrAll		: timerRef | allKeyword timerKeyword;
readTimerOp		: timerRef DOT readKeyword;
fragment readKeyword		: READ;
runningTimerOp		: timerRefOrAny DOT runningKeyword;
timeoutStatement	: timerRefOrAny DOT timeoutKeyword;
timerRefOrAny		: timerRef | anyKeyword timerKeyword;
fragment timeoutKeyword		: TIMEOUT;

// $>

// $>


// $<A.1.6.3 Type

type			: predefinedType | referencedType;
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
fragment bitstringKeyword	: BIT_STRING;
fragment booleanKeyword		: BOOLEAN;
fragment integerKeyword		: INTEGER;
fragment octetStringKeyword	: OCTET_STRING;
fragment hexStringKeyword	: HEX_STRING;
fragment verdictTypeKeyword	: VERDICT_TYPE;
fragment floatKeyword		: FLOAT;
fragment addressKeyword		: ADDRESS;
fragment defaultKeyword		: DEFAULT;
fragment anyTypeKeyword		: ANY_TYPE;
fragment charStringKeyword	: CHAR_STRING;
fragment universalCharString	: universalKeyword charStringKeyword;
fragment universalKeyword	: UNIVERSAL;
referencedType		: ( globalModuleId DOT )? typeReference extendedFieldReference?;
typeReference		: ( structTypeIdentifier typeActualParList?) |
			enumTypeIdentifier |
			subTypeIdentifier |
			componentTypeIdentifier;
/* ---A--- BUG ---A--- */
typeActualParList	: '(' typeActualPar ( ',' typeActualPar )* ')';
fragment typeActualPar		: constantExpression;
arrayDef		: ( '[' arrayBounds ( '..' arrayBounds )? ']' )+;
fragment arrayBounds		: singleConstExpression;
/* STATIC SEMANTICS - arrayBounds will resolve to a non negative value of integer type */

// $>


// $<A.1.6.4 Value

value			: predefinedValue | referencedValue;
predefinedValue
			: bitStringValue |
			booleanValue |
			charStringValue |
			INTEGER_VALUE |
			octetStringValue |
			hexStringValue |
			verdictTypeValue |
			enumeratedValue |
			floatValue |
			addressValue |
			omitValue;
fragment bitStringValue		: B_STRING;
fragment booleanValue		: TRUE | FALSE;
INTEGER_VALUE		: NUMBER;
fragment octetStringValue	: O_STRING;
fragment hexStringValue		: H_STRING;
verdictTypeValue	: PASS | FAIL | INCONC | NONE | ERROR;
fragment enumeratedValue		: enumerationIdentifier;
charStringValue		: cString | QUADRUPLE;
QUADRUPLE		    : CHAR_KEYWORD '(' GROUP ',' PLANE ',' ROW ',' CELL ')';
fragment CHAR_KEYWORD	: TTCN_CHAR;
fragment GROUP			: NUMBER;
fragment PLANE			: NUMBER;
fragment ROW		   	: NUMBER;
fragment CELL			: NUMBER;
floatValue		    : FLOAT_DOT_NOTATION | FLOAT_E_NOTATION;
FLOAT_DOT_NOTATION	: NUMBER DOT DECIMAL_NUMBER;
FLOAT_E_NOTATION	: NUMBER ( DOT DECIMAL_NUMBER )? EXPONENTIAL MINUS? NUMBER;
fragment EXPONENTIAL		: 'E';
referencedValue		: valueReference extendedFieldReference?;
valueReference		: ( globalModuleId DOT )? ( constIdentifier | extConstIdentifier |
			moduleParIdentifier ) |
			valueParIdentifier |
			varIdentifier;
fragment NUMBER		: ( NON_ZERO_NUM NUM* ) | '0';
fragment NON_ZERO_NUM	: '1'..'9';
fragment DECIMAL_NUMBER	: NUM+;
fragment NUM		: '0' | NON_ZERO_NUM;
B_STRING		: '\'' BIN* '\'' 'B';
fragment BIN		: '0' | '1';
H_STRING		: '\'' HEX* '\'' 'H';
fragment HEX		: NUM | 'A'..'F' | 'a'..'f';
O_STRING		: '\'' OCT* '\'' 'O';
fragment OCT		: HEX HEX;
cString         : C_STRING | UC_STRING;
C_STRING		: '"' CHAR* '"';
fragment CHAR		: '\u0000'..'\u0021' | '\\"' | '\u0023'..'\u007F';
/* ---A--- BUG (special escape needed for " sign) ---A--- */
/* REFERENCE - A character defined by the relevant CharacterString type. For charstring a character from the character
set defined in ISO/IEC 646. For universal charstring a character from any character set defined in ISO/IEC 10646 */
FREE_TEXT       : '"' EXTENDED_ALPHA_NUM* '"';
fragment EXTENDED_ALPHA_NUM	: '\u0020' | '\u0021' | '\\"' | '\u0023'..'\u007E' | '\u00A1'..'\u00AC' | '\u00AE'..'\u00FF';
/* ---A--- BUG (special escape needed for " sign) ---A--- */
/* REFERENCE - A graphical character from the BASIC LATIN or from the LATIN-1 SUPPLEMENT character sets defined in
ISO/IEC 10646 (characters from char (0,0,0,32) to char (0,0,0,126), from char (0,0,0,161) to char (0,0,0,172) and
from char (0,0,0,174) to char (0,0,0,255). */
UC_STRING		: '"' UNIVERSAL_CHAR* '"';
fragment UNIVERSAL_CHAR		: '\u0000'..'\u0021' | '\\"' | '\u0023'..'\u00FF';
/* ---A--- ADDED (universal string support) ---A--- */
IDENTIFIER		: ALPHA ( ALPHA_NUM | UNDERSCORE )*;
fragment ALPHA		: UPPER_ALPHA | LOWER_ALPHA;
fragment ALPHA_NUM	: ALPHA | NUM;
fragment UPPER_ALPHA	: 'A'..'Z';
fragment LOWER_ALPHA	: 'a'..'z';
fragment addressValue    : TTCN_NULL;
fragment omitValue		: omitKeyword;
fragment omitKeyword		: OMIT;

// $>


// $<A.1.6.5 Parametrization

fragment inParKeyword		: IN;
fragment outParKeyword		: OUT;
fragment inOutParKeyword		: INOUT;
formalValuePar		: ( inParKeyword | inOutParKeyword | outParKeyword )? type valueParIdentifier;
fragment valueParIdentifier	: IDENTIFIER;
formalPortPar		: inOutParKeyword? portTypeIdentifier portParIdentifier;
fragment portParIdentifier	: IDENTIFIER;
formalTimerPar		: inOutParKeyword? timerKeyword timerParIdentifier;
fragment timerParIdentifier	: IDENTIFIER;
formalTemplatePar	: ( inParKeyword | outParKeyword | inOutParKeyword )?
			( templateKeyword | restrictedTemplate ) type templateParIdentifier;
fragment templateParIdentifier	: IDENTIFIER;
restrictedTemplate  : omitKeyword | ( templateKeyword templateRestriction );
templateRestriction : '(' omitKeyword ')';

// $>


// $<A.1.6.6 With statement

withStatement		: withKeyword withAttribList;
fragment withKeyword		: WITH;
withAttribList		: '{' multiWithAttrib '}';
multiWithAttrib		: ( singleWithAttrib SEMICOLON? )*;
singleWithAttrib	: attribKeyword overrideKeyword? attribQualifier? attribSpec;
attribKeyword
			: encodeKeyword |
			variantKeyword |
			displayKeyword |
			extensionKeyword;
fragment encodeKeyword		: ENCODE;
fragment variantKeyword		: VARIANT;
fragment displayKeyword		: DISPLAY;
fragment extensionKeyword	: EXTENSION;
fragment overrideKeyword		: OVERRIDE;
attribQualifier		: '(' defOrFieldRefList ')';
defOrFieldRefList	: defOrFieldRef ( ',' defOrFieldRef )*;
defOrFieldRef		: definitionRef | fieldReference | allRef;
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
fragment attribSpec		: FREE_TEXT;

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
fragment verdictStatements	: setLocalVerdict;
fragment verdictOps		: getLocalVerdict;
setLocalVerdict		: setVerdictKeyword '(' singleExpression ')';
fragment setVerdictKeyword	: SET_VERDICT;
fragment getLocalVerdict		: GET_VERDICT;
sutStatements		: actionKeyword '(' actionText? ( stringOp actionText )* ')';
fragment actionKeyword		: ACTION;
actionText		: FREE_TEXT | expression;
returnStatement		: returnKeyword expression?;
altConstruct		: altKeyword '{' altGuardList '}';
fragment altKeyword		: ALT;
altGuardList		: ( guardStatement | elseStatement SEMICOLON? )*;
guardStatement		: altGuardChar ( altstepInstance statementBlock? | guardOp statementBlock );
elseStatement		: '[' elseKeyword ']' statementBlock;
altGuardChar		: '[' booleanExpression? ']';
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
interleavedConstruct	: interleavedKeyword '{' interleavedGuardList '}';
fragment interleavedKeyword	: INTERLEAVE;
interleavedGuardList	: ( interleavedGuardElement SEMICOLON? )+;
interleavedGuardElement	: interleavedGuard interleavedAction;
interleavedGuard	: '[' ']' guardOp;
fragment interleavedAction	: statementBlock;
labelStatement		: labelKeyword labelIdentifier;
fragment labelKeyword		: LABEL;
fragment labelIdentifier		: IDENTIFIER;
gotoStatement		: gotoKeyword labelIdentifier;
fragment gotoKeyword		: GOTO;
fragment repeatStatement		: REPEAT;
activateOp		: activateKeyword '(' altstepInstance ')';
fragment activateKeyword		: ACTIVATE;
deactivateStatement	: deactivateKeyword ( '(' componentOrDefaultReference ')' )?;
fragment deactivateKeyword	: DEACTIVATE;
fragment breakStatement		: BREAK;
fragment continueStatement	: CONTINUE;

// $>


// $<A.1.6.8 Basic statements

basicStatements		: assignment | logStatement | loopConstruct | conditionalConstruct |
			selectCaseConstruct;
expression		: singleExpression | compoundExpression;
compoundExpression	: fieldExpressionList | arrayExpression;
/* STATIC  SEMANTICS - Within compoundExpression the arrayExpression can be used for arrays, record, record of
and set of types. */
fieldExpressionList	: '{' fieldExpressionSpec ( ',' fieldExpressionSpec )* '}';
fieldExpressionSpec	: fieldReference ASSIGNMENT_CHAR notUsedOrExpression;
arrayExpression		: '{' arrayElementExpressionList? '}';
arrayElementExpressionList	: notUsedOrExpression ( ',' notUsedOrExpression )*;
notUsedOrExpression	: expression | notUsedSymbol;
constantExpression	: singleConstExpression | compoundConstExpression;
fragment singleConstExpression	: singleExpression;
/* STATIC SEMANTICS - singleConstExpression shall not contain variables or module parameters and shall resolve
to a constant value at compile time */
fragment booleanExpression	: singleExpression;
/* STATIC SEMANTICS - booleanExpression shall resolve to a value of type boolean */
compoundConstExpression	: fieldConstExpressionList | arrayConstExpression;
/* STATIC SEMANTICS - Within compoundConstExpression the arrayConstExpression can be used for arrays, record,
record of and set of types. */
fieldConstExpressionList	: '{' fieldConstExpressionSpec ( ',' fieldConstExpressionSpec ) '}';
fieldConstExpressionSpec	: fieldReference ASSIGNMENT_CHAR constantExpression;
arrayConstExpression	: '{' arrayElementConstExpressionList? '}';
arrayElementConstExpressionList	: constantExpression ( ',' constantExpression )*;
assignment		: variableRef ASSIGNMENT_CHAR ( expression | templateBody );
/* STATIC SEMANTICS - The expression on the right hand side of assignment shall evaluate to an explicit
value of a type compatible with the type of the left hand side for value variables and shall evaluate to
an explicit value, template (literal or a template instance) or a matching mechanism compatible with the
type of the left hand side for template variables. */
singleExpression	: xorExpression ( OR xorExpression )*;
/* STATIC SEMANTICS - If more than one xorExpression exists, then the xorExpressions shall evaluate to
specific values of compatible types. */
xorExpression		: andExpression ( XOR andExpression )*;
/* STATIC SEMANTICS - If more than one andExpression exists, then the andExpressions shall evaluate to
specific values of compatible types. */
andExpression		: notExpression ( AND notExpression )*;
/* STATIC SEMANTICS - If more than one notExpression exists, then the notExpressions shall evaluate to
specific values of compatible types. */
notExpression		: NOT? equalExpression;
/* STATIC SEMANTICS - Operands of the not operator shall be of type boolean or derivates of type boolean. */
equalExpression		: relExpression ( equalOp relExpression )*;
/* STATIC SEMANTICS - If more than one relExpression exists, then the relExpressions shall evaluate to
specific values of compatible types. */
relExpression		: shiftExpression ( relOp shiftExpression )?;
/* STATIC SEMANTICS - If both shiftExpressions exist, then each shiftExpression shall evaluate to a specific
integer, enumerated or float value or derivates of these types. */
shiftExpression		: bitOrExpression ( shiftOp bitOrExpression )*;
/* STATIC SEMANTICS - Each result shall resolve to a specific value. If more than one result exists the right-hand
operand shall be of type integer or derivates and if the shift op is '<<' or '>>' then the left-hand operand shall
resolve to either bitstring, hexstring or octetstring type or derivates of these types. If the shift op is
'<@' or '@>' then the left-handoperand shall be of type bitstring, hexstring, octetstring, charstring, universal
charstriing, record of, set of, o array, or derivatives of these types. */
bitOrExpression		: bitXorExpression ( OR4B bitXorExpression )*;
/* STATIC SEMANTICS - If more than one bitXorExpression exists, then the bitXorExpressions shall evaluate to
specific values of compatible types. */
bitXorExpression	: bitAndExpression ( XOR4B bitAndExpression )*;
/* STATIC SEMANTICS - If more than one bitAndExpression exists, then the bitAndExpressions shall evaluate to
specific values of compatible types. */
bitAndExpression	: bitNotExpression (AND4B bitNotExpression )*;
/* STATIC SEMANTICS - If more than one bitNotExpression exists, then the bitNotExpressions shall evaluate to
specific values of compatible types. */
bitNotExpression	: NOT4B? addExpression;
/* STATIC SEMANTICS - If the not4b operator exist, the operand shall be of type bitstring, octetstring or
hexstring or derivates of these types. */
addExpression		: mulExpression ( addOp mulExpression )*;
/* STATIC SEMANTICS - Each mulExpression shall resolve to a specific value. If more than one mulExpression
exists and the addOp resolves to stringOp then the mulExpressions shall be valid operands for stringOp. If
more than one mulExpression exists and the addOp does not resolve to stringOp then the mulExpression shall
both resolve to type integer or float or derivatives of these types. */
mulExpression		: unaryExpression ( multiplyOp unaryExpression )*;
/* STATIC SEMANTICS - Each unaryExpression shall resolve to a specific value. If more than one unaryExpression
exists then the unaryExpressions shall resolve to type integer or float or derivatives of these types. */
unaryExpression		: unaryOp? primary;
/* STATIC SEMANTICS - primary shall resolve to a specific value of type integer or float or derivatives of
these types. */
primary			: opCall | value | '(' singleExpression ')';
extendedFieldReference	: ( ( DOT ( structFieldIdentifier | typeDefIdentifier ) )
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
addOp			: '+' | '-' | stringOp;
/* STATIC SEMANTICS - Operands of the '+' or '-' operators shall be of type integer of float or derivations
of integer or float (i.e. subrange) */
multiplyOp		: '*' | '/' | MOD | REM;
/* STATIC SEMANTICS - Operands of the '*', '/', rem or mod operators shall be of type integer or float or
derivations of integer or float (i.e. subrange). */
unaryOp			: '+' | '-';
/* STATIC SEMANTICS - Operands of the '+' or '-' operators shall be of type integer or float or derivations
of integer or float (i.e. subrange). */
relOp			: '<' | '>' | '>=' | '<=';
/* STATIC SEMANTICS - the precedence of the operators is defined in Table 6 */
equalOp			: '==' | '!=';
fragment stringOp		: '&';
/* STATIC SEMANTICS - Operands of the string operator shall be bitstring, hexstring, octetstring, (universal) 
character string, record of, set of, or array types, or derivates of these types */
shiftOp			: '<<' | '>>' | '<@' | '>@';
logStatement		: logKeyword '(' logItem ( ',' logItem )* ')';
fragment logKeyword		: LOG;
logItem			: FREE_TEXT | templateInstance;
loopConstruct
			: forStatement |
			whileStatement |
			doWhileStatement;
forStatement		: forKeyword '(' initial SEMICOLON final SEMICOLON step ')'
			statementBlock;
fragment forKeyword		: FOR;
initial			: varInstance | assignment;
fragment final			: booleanExpression;
fragment step			: assignment;
whileStatement		: whileKeyword '(' booleanExpression ')'
			statementBlock;
fragment whileKeyword		: WHILE;
doWhileStatement	: doKeyword statementBlock
			whileKeyword '(' booleanExpression ')';
fragment doKeyword		: DO;
conditionalConstruct	: ifKeyword '(' booleanExpression ')'
			statementBlock
			elseIfClause* elseClause?;
fragment ifKeyword		: IF;
elseIfClause		: elseKeyword ifKeyword '(' booleanExpression ')' statementBlock;
fragment elseKeyword		: ELSE;
elseClause		: elseKeyword statementBlock;
selectCaseConstruct	: selectKeyword '(' singleExpression ')' selectCaseBody;
fragment selectKeyword		: SELECT;
selectCaseBody		: '{' selectCase+ '}';
selectCase		: caseKeyword ( '(' templateInstance ( ',' templateInstance )* ')' | elseKeyword )
			statementBlock;
fragment caseKeyword		: CASE;

// $>


// $<A.1.6.9 - Miscellaneous productions

fragment dash			: MINUS;

// $>


WHITESPACE		: ( '\t' | ' ' | '\r' | '\n'| '\u000C' )+
			{ $channel = HIDDEN; };

COMMENT			: '/*' ( options { greedy=false; } : . )* '*/'
			{ $channel = HIDDEN; };
LINE_COMMENT		: '//' ~('\n'|'\r')* '\r'? '\n'
			{ $channel = HIDDEN; };
