grammar ttcn3;

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
}



/* A.1.6.0 - TTCN-3 module*/

ttcn3Module		: ttcn3ModuleKeyword ttcn3ModuleId
			'{'
			moduleDefinitionsPart?
			moduleControlPart?
			'}'
			withStatement? SEMICOLON?;
ttcn3ModuleKeyword	: MODULE;
ttcn3ModuleId		: moduleId;
moduleId		: globalModuleId languageSpec?;
globalModuleId		: moduleIdentifier;
moduleIdentifier	: identifier;
languageSpec		: languageKeyword freeText;
languageKeyword		: LANGUAGE;


/* A.1.6.1 - Module definitions part */

/* A.1.6.1.0 - General */

moduleDefinitionsPart	: moduleDefinitionsList;
moduleDefinitionsList	: ( moduleDefinition SEMICOLON? )+;
moduleDefinition	: ( typeDef |
			constDef |
			templateDef |
			modulePartDef |
			functionDef |
			signatureDef |
			testCaseDef |
			altstepDef |
			importDef |
			groupDef |
			extFunctionDef |
			extConstDef ) withStatement?;

/* A.1.6.1.1 Typedef definitions */

typeDef			: typeDefKeyword typeDefBody;
typeDefBody		: structuredTypeDef | subTypeDef;
typeDefKeyword		: TYPE;
structuredTypeDef	: recordDef |
			unionDef |
			setDef |
			recordOfDef |
			setOfDef |
			enumDef |
			portDef |
			componentDef;
recordDef		: recordKeyword structDefBody;
recordKeyword		: RECORD;
structDefBody		: ( ( structTypeIdentifier structDefFormalParList? ) | addressKeyword )
			'{' ( structFieldDef ( ',' structFieldDef )* )? '}';
structTypeIdentifier	: identifier;
structDefFormalParList	: '(' structDefFormalPar ( ',' structDefFormalPar )* ')';
structDefFormalPar	: formalValuePar;
structFieldDef		: ( type | nestedTypeDef ) structFieldIdentifier arrayDef? subTypeSpec?
			optionalKeyword?;
nestedTypeDef		: nestedRecordDef |
			nestedUnionDef |
			nestedSetDef |
			nestedRecordDef |
			nestedSetOfDef |
			nestedEnumDef;
nestedRecordDef		: recordKeyword '{' ( structFieldDef ( ',' structFieldDef )* )? '}';
nestedUnionDef		: unionKeyword '{' unionFieldDef ( ',' unionFieldDef )* '}';
nestedSetDef		: setKeyword '{' ( structFieldDef ( ',' structFieldDef )* )? '}';
nestedRecordOfDef	: recordKeyword stringLength? ofKeyword ( type | nestedTypeDef );
nestedSetOfDef		: setKeyword stringLength? ofKeyword ( type | nestedTypeDef );
nestedEnumDef		: enumKeyword '{' enumerationList '}';
structFieldIdentifier	: identifier;
optionalKeyword		: OPTIONAL;
unionDef		: unionKeyword unionDefBody;
unionKeyword		: UNION;
unionDefBody		: ( structTypeIdentifier structDefFormalParList? | addressKeyword )
			'{' unionFieldDef ( ',' unionFieldDef )* '}';
unionFiedDef		: ( type | nestedTypeDef ) structFieldIdentifier arrayDef? subTypeSpec?;
setDef			: setKeyword structDefBody;
setKeyword		: SET;
recordOfDef		: recordKeyword stringLength? ofKeyword structOfDefBody;
ofKeyword		: OF;
structOfDefBody		: ( type | nestedTypeDef ) ( structTypeIdentifier | addressKeyword ) subTypeSpec?;
setOfDef		: setKeyword stringLength? ofKeyword structOfDefBody;
enumDef			: enumKeyword ( enumTypeIdentifier | addressKeyword )
			'{'  enumerationList '}';
enumKeyword		: ENUMERATED;
enumTypeIdentifier	: identifier;
enumerationList		: enumeration ( ',' enumeration )*;
enumeration		: enumerationIdentifer ( '(' MINUS? number ')' )?;
enumerationIdentifer	: identifier;
subTypeDef		: type ( subTypeIdentifer | address keyword ) arrayDef? subTypeSpec?;
subTypeIdentifer	: identifier;
subTypeSpec		: allowedValues stringLength? | stringLength;
/* STATIC SEMATICS - allowedValues shall be of the same type as the field being subtyped */
allowedValues		: '(' ( ( valueOrRange ( ',' valueOfRange )* ) | charStringMatch ) ')';
/* ---A--- BUG ---A--- */
valueOrRange		: rangeDef | constantExpression;
/* STATIC SEMANTICS - rangeDef production shall only be used with integer, charstring, universal charstring or float based types */
/* STATIC SEMANTICS - When subtyping charstring or universal charstring range and values shall not be mixed in the same subTypeSpec */
rangeDef		: lowerBound '..' upperBound;
stringLength		: lengthKeyword '(' singleConstExpression ( '..' upperBound )? ')';
/* STATIC SEMANTICS - stringLength shall only be used with string types or to limit set of and record of. singleConstExpression
and upperBound shall evaluate to non-negative integervalues (in case of upperBound including infinity) */
lengthKeyword		: LENGTH;
portType		: ( globalModuleId DOT )? portTypeIdentifier;
portDef			: portKeyword portDefBody;
portDefBody		: portTypeIdentifier portDefAttribs;
portKeyword		: PORT;
portTypeIdentifier	: identifier;
portDefAttribs		: messageAttribs | procedureAttribs | mixedAttribs;
messageAttribs		: messageKeyword
			'{' ( messageList SEMICOLON? )+ '}';
messageList		: direction allOrTypeList;
direction		: inParKeyword | outParKeyword | inOutParKeyword;
messageKeyword		: MESSAGE;
allOrTypeList		: allKeyword | typeList;
/* NOTE: The use of allKeyword in port definitions is deprecated */
allKeyword		: ALL;
typeList		: type ( ',' type )*;
procedureAttribs	: procedureKeyword
			'{'



SEMICOLON		: ';';
