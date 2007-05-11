//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) library.

// This library is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

/**
 * @file   command.h
 * @author Mateusz Pusz
 * @date   Thu May 10 20:00:53 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __COMMAND_H__
#define __COMMAND_H__

extern "C" {
#include <freettcn/ttcn3/tri.h>
}
#include <freettcn/te/testComponent.h>



namespace freettcn {
  
  namespace TE {
    
    class CTestCase;
    
    class CCommand {
      CTestComponentType::CInstance &_comp;
      const CSourceData *_srcData;
      
    protected:
      CTestComponentType::CInstance &Component() const { return _comp; }
      const CSourceData *SrcData() const { return _srcData; }
      
    public:
      CCommand(CTestComponentType::CInstance &comp, const CSourceData *srcData);
      virtual ~CCommand();
      virtual bool Run() = 0;
    };
    
    // <execute-without-timeout> [9.17.1]
    class CCmdExecuteWithoutTimeout : public CCommand {
      freettcn::TE::CTestCase &_testCase;
      const TciParameterListType *_parameterList;
      
      bool Run();
    public:
      CCmdExecuteWithoutTimeout(CTestComponentType::CInstance &comp, const CSourceData *srcData,
                                freettcn::TE::CTestCase &testCase,
                                const TciParameterListType *parameterList);
    };
    
    
    // <execute-without-timeout> [9.17.2]
    class CCmdExecuteTimeout : public CCommand {
      bool Run();
    public:
      CCmdExecuteTimeout(CTestComponentType::CInstance &comp, const CSourceData *srcData);
    };
    

    // <init-component-scope> [9.20]
//     class CCmdInitComponentScope : public CCommand {
//       CTestComponentType::CInstance &_comp;
      
//       bool Run()
//       {
//         // new scopes for varaibles, timers and ports are created
// //         comp.InitVarScope();
// //         comp.InitTimerScope();
// //         comp.InitPortScope();
        
//         return true;
//       }
      
//     public:
//       CCmdInitComponentScope(CTestComponentType::CInstance &comp):
//         _comp(comp)
//       {
//       }
//     };
    
    
//     // <init-scope-with-runs-on> [9.20a]
//     class CCmdInitScopeWithRunsOn : public CCommand {
//       CTestComponentType::CInstance &_comp;
      
//       bool Run()
//       {
//         // create local scope
//         /// @todo copy/reference upper scope
        
//         // new scopes for varaibles, timers and ports are created
// //         comp.InitVarScope();
// //         comp.InitTimerScope();
// //         comp.InitPortScope();
        
//         return true;
//       }
      
//     public:
//       CCmdInitScopeWithRunsOn(CTestComponentType::CInstance &comp):
//         _comp(comp)
//       {
//       }
//     };
    
    
    // <stop-entity-op> [9.50.1 ???]
    class CCmdStopEntityOp : public CCommand {
      bool Run();
    public:
      CCmdStopEntityOp(CTestComponentType::CInstance &comp, const CSourceData *srcData);
    };
    
    
    // <stop-mtc> [9.49.1 ???]
    class CCmdStopMTC : public CCommand {
      bool Run();
    public:
      CCmdStopMTC(CTestComponentType::CInstance &comp, const CSourceData *srcData);
    };

    
//     class CReceiveCommand : public CCommand {
//       enum {
//         RECEIVE,
//         TRIGGER,
//         GETCALL,
//         GETREPLY,
//         CATCH,
//         CHECK,
//         TIMEOUT,
//         DONE
//       };
      
//       bool Run()
//       {
// //         return tc.Done();

//         return false;
//       }
//     };
    
//     class CReceivePortCommand : public CReceiveCommand {
//       enum {
//         RECEIVE,
//         TRIGGER,
//         GETCALL,
//         GETREPLY,
//         CATCH,
//         CHECK
//       };
      
//       bool Run()
//       {
// //         return tc.Done();

//         return false;
//       }
//     };
    

    
//     class CTestComponentDoneCommand : public CCommand {
//       bool Run()
//       {
//         return tc.Done();
//       }
//     };
    
//     class CAltCommand : public CCommand {
//       bool Run()
//       {
// //         for(i=0; i<altNum; i++) {
// //           if (alt[i].Cmd().Run()) {
// //             alt[i].Behavior().Load();
// //             return true;
// //           }
// //         }
        
//         return false;
//       }
//     public:
      
//     };


  } // namespace TE
  
} // namespace freettcn


#endif /* __COMMAND_H__ */
