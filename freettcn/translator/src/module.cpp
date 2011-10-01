//
// Copyright (C) 2007 Mateusz Pusz
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

/**
 * @file   module.cpp
 * @author Mateusz Pusz
 * @date   
 * 
 * @brief  
 * 
 * 
 */


#include "module.h"
#include "identifier.h"
#include "expression.h"
#include "type.h"
#include "dumper.h"
#include "freettcn/tools/tools.h"



freettcn::translator::CModule::CDefinition::CDefinition(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type):
  _id(move(id)), _type(type)
{
}


freettcn::translator::CModule::CDefinition::~CDefinition()
{
}

        
void freettcn::translator::CModule::CDefinition::Dump(CDumper &dumper) const
{
}



freettcn::translator::CModule::CDefinitionParameter::CDefinitionParameter(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type, std::shared_ptr<const CExpression> expr):
  CDefinition(id, type), _expr(expr)
{
}


void freettcn::translator::CModule::CDefinitionParameter::Dump(CDumper &dumper) const
{
}



freettcn::translator::CModule::CDefinitionConstValue::CDefinitionConstValue(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type, std::shared_ptr<const CExpression> expr):
  CDefinition(id, type), _expr(expr)
{
}


void freettcn::translator::CModule::CDefinitionConstValue::Dump(CDumper &dumper) const
{
}


freettcn::translator::CModule::CDefinitionTypeLocal::CDefinitionTypeLocal(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CTypeLocal> type):
  CDefinition(id, type), _type(type)
{
}


void freettcn::translator::CModule::CDefinitionTypeLocal::Dump(CDumper &dumper) const
{
}
      

freettcn::translator::CModule::CDefinitionFormalParameter::CDefinitionFormalParameter(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type, TDirection dir):
  CDefinition(id, type), _dir(dir)
{
}


void freettcn::translator::CModule::CDefinitionFormalParameter::Dump(CDumper &dumper) const
{
}



freettcn::translator::CModule::CDefinitionMethod::CDefinitionMethod(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type):
  CDefinition(id, type)
{
}


freettcn::translator::CModule::CDefinitionMethod::~CDefinitionMethod()
{
}


void freettcn::translator::CModule::CDefinitionMethod::Register(std::shared_ptr<const CDefinitionFormalParameter> par)
{
  _params.push_back(par);
}



freettcn::translator::CModule::CDefinitionTestcase::CDefinitionTestcase(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type):
  CDefinitionMethod(id, type)
{
}


void freettcn::translator::CModule::CDefinitionTestcase::Dump(CDumper &dumper) const
{
}


freettcn::translator::CModule::CDefinitionTemplate::CDefinitionTemplate(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type):
  CDefinitionMethod(id, type)
{
}


void freettcn::translator::CModule::CDefinitionTemplate::Dump(CDumper &dumper) const
{
}




freettcn::translator::CModule::CModule(std::shared_ptr<const CIdentifier> id, TLanguage language):
  _id(id), _language(language)
{
}


freettcn::translator::CModule::~CModule()
{
}


void freettcn::translator::CModule::Register(std::shared_ptr<CDefinition> def)
{
  _defList.push_back(def);
}


void freettcn::translator::CModule::Dump(CDumper &dumper) const
{
  dumper.PrintLine(nullptr);
  dumper.PrintLine("namespace " + _id->Name() + " {");
  dumper.IndentIncr();
  
  
  
  dumper.IndentDecr();
  dumper.PrintLine(nullptr);
  dumper.PrintLine("} // namespace " + _id->Name());
}




// /** 
//  * @brief CModule class constructor.
//  * 
//  * @param f TTCN-3 module file.
//  * @param loc The location of a compiler node in a TTCN-3 source file.
//  * @param id TTCN-3 node identifier.
//  */
// TTCN3::CModule::CModule(CFile &f, const YYLTYPE &loc, CIdentifier &id):
//   CNamedNode(f, loc, id), control(0)
// {
// }


// /**
//  * @brief CModule class destructor.
//  */
// TTCN3::CModule::~CModule()
// {
//   // delete all the definitions in a list
//   std::for_each(definitionList.begin(), definitionList.end(), ptr_fun(operator delete));
// //   for(Iterator it = definitionList.begin(); it != definitionList.end(); ++it)
// //     delete *it;
//   definitionList.clear();
  
//   // delete control part if present
//   if (control)
//     delete control;
// }


// /** 
//  * @brief Dump class contents into TTCN-3 source code.
//  *
//  * Method is used to dump TTCN-3 source code to a file based on information
//  * tree described by classes in memory.
//  * 
//  * @param fdout File descriptor to use.
//  */
// void TTCN3::CModule::DumpTTCN3(FILE *fdout) const
// {
//   fprintf(fdout, "\nmodule %s {\n", Name().c_str());
  
//   for(Container::const_iterator it = definitionList.begin(); it != definitionList.end(); ++it)
//     (*it)->DumpTTCN3(fdout);
  
//   if (control)
//     control->DumpTTCN3(fdout);
  
//   fprintf(fdout, "}\n\n");
// }


// /** 
//  * @brief Dump class contents into C++ source code.
//  *
//  * Method is used to translate TTCN-3 source code loaded into memory to
//  * a file with C++ code.
//  * 
//  * @param fdout File descriptor to use.
//  */
// void TTCN3::CModule::DumpCPP(FILE *fdout) const
// {
// }



// /** 
//  * @brief CDefinition class constructor.
//  * 
//  * @param f TTCN-3 module file.
//  * @param loc The location of a compiler node in a TTCN-3 source file.
//  * @param id TTCN-3 node identifier.
//  * @param mod TTCN-3 module in witch altstep is defined.
//  */
// TTCN3::CModule::CDefinition::CDefinition(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod):
//   CNamedNode(f, loc, id), module(mod)
// {
//   mod.definitionList.push_back(this);
// }

// /**
//  * @brief CDefinition class destructor.
//  */
// TTCN3::CModule::CDefinition::~CDefinition()
// {
// }




// /** 
//  * @brief CControl class constructor.
//  * 
//  * @param f TTCN-3 module file.
//  * @param loc The location of a compiler node in a TTCN-3 source file.
//  * @param mod TTCN-3 module in witch altstep is defined.
//  */
// TTCN3::CModule::CControl::CControl(CFile &f, const YYLTYPE &loc, CModule &mod):
//   CNode(f, loc), module(mod)
// {
// }


// /**
//  * @brief CControl class destructor.
//  */
// TTCN3::CModule::CControl::~CControl()
// {
// }


// /** 
//  * @brief Dump dupa class contents into TTCN-3 source code.
//  *
//  * Method is used to dump TTCN-3 source code to a file based on information
//  * tree described by classes in memory.
//  * 
//  * @param fdout File descriptor to use.
//  */
// void TTCN3::CModule::CControl::DumpTTCN3(FILE *fdout) const
// {
//   fprintf(fdout, "Control Part\n");
// }


// /** 
//  * @brief Dump dupa class contents into C++ source code.
//  *
//  * Method is used to translate TTCN-3 source code loaded into memory to
//  * a file with C++ code.
//  * 
//  * @param fdout File descriptor to use.
//  */
// void TTCN3::CModule::CControl::DumpCPP(FILE *fdout) const
// {
// }
