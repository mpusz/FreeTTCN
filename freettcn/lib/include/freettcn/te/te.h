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
 * @file   te.h
 * @author Mateusz Pusz
 * @date   Sat Apr  7 22:10:55 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TE_H__
#define __TE_H__

#include <freettcn/etsi/TciTmRequired.h>
#include <freettcn/etsi/TciChRequired.h>
#include <freettcn/etsi/TciCdRequired.h>
#include <freettcn/etsi/TriPlatformTE.h>
#include <freettcn/etsi/TriCommunicationTE.h>
#include <freettcn/tools/entity.h>
#include <freettcn/te/ets.h>
#include <freettcn/te/eds.h>
#include <freettcn/te/t3rts.h>


namespace freettcn {
  
  namespace TE {

    class CEnvironment;
    
    using namespace ORG_ETSI_TTCN3_TCI;
    using namespace ORG_ETSI_TTCN3_TRI;
    
    class CTTCN3Executable : public freettcn::CEntity,
                             public ORG_ETSI_TTCN3_TCI::TciTmRequired, 
                             public ORG_ETSI_TTCN3_TCI::TciChRequired,
                             public ORG_ETSI_TTCN3_TCI::TciCdRequired,
                             public ORG_ETSI_TTCN3_TRI::TriPlatformTE,
                             public ORG_ETSI_TTCN3_TRI::TriCommunicationTE
    {
      std::unique_ptr<const CEnvironment> _env;
      CExecutableTestSuite _ets;
      CEncodingDecodingSystem _eds;
      CTTCN3RuntimeSystem _t3rts;
      
    public:
      CTTCN3Executable();
      ~CTTCN3Executable() = default;
      
      void Environment(std::unique_ptr<const CEnvironment> env);
      
      // TM requests
      void tciRootModule(const TciModuleId *moduleName) override;
      const TciModuleIdList *getImportedModules() const override;
      const TciModuleParameterList *tciGetModuleParameters(const TciModuleId *moduleName) override;
      const TciTestCaseIdList *tciGetTestCases() const override;
      const TciParameterTypeList *tciGetTestCaseParameters(const TciTestCaseId *testCaseId) const override;
      const TriPortIdList *tciGetTestCaseTSI(const TciTestCaseId &testCaseId) const override;
      void tciStartTestCase(const TciTestCaseId *testCaseId, const TciParameterList *parameterList) override;
      void tciStopTestCase() override;
      const TriComponentId *tciStartControl() override;
      void tciStopControl() override;
      
      // CH requests
      void tciEnqueueMsgConnected(const TriPortId *sender, const TriComponentId *receiver,
                                  const TciValue *rcvdMessage) override;
      void tciEnqueueCallConnected(const TriPortId *sender, const TriComponentId *receiver,
                                   const TriSignatureId *signature, const TciParameterList *parameterList) override;
      void tciEnqueueReplyConnected(const TriPortId *sender, const TriComponentId *receiver,
                                    const TriSignatureId *signature, const TciParameterList *parameterList,
                                    const TciValue *returnValue) override;
      void tciEnqueueRaiseConnected(const TriPortId *sender, const TriComponentId *receiver,
                                    const TriSignatureId *signature, const TciValue *exception) override;
      const TriComponentId *tciCreateTestComponent(const TciTestComponentKind *kind,
                                                   const TciType *componentType, const Tstring *name) override;
      void tciStartTestComponent(const TriComponentId *component, const TciBehaviourId *behaviour,
                                 const TciParameterList *parameterList) override;
      void tciStopTestComponent(const TriComponentId *component) override;
      void tciConnect(const TriPortId *fromPort, const TriPortId *toPort) override;
      void tciDisconnect(const TriPortId *fromPort, const TriPortId *toPort) override;
      void tciMap(const TriPortId *fromPort, const TriPortId *toPort) override;
      void tciUnmap(const TriPortId *fromPort, const TriPortId *toPort) override;
      void tciTestComponentTerminated(const TriComponentId *component, const VerdictValue *verdict) const override;
      Tboolean tciTestComponentRunning(const TriComponentId *component) const override;
      Tboolean tciTestComponentDone(const TriComponentId *comp) const override;
      const TriComponentId *tciGetMTC() const override;
      void tciExecuteTestCase(const TciTestCaseId *testCaseId, const TriPortIdList *tsiPortList) override;
      void tciReset() override;
      void tciKillTestComponent(const TriComponentId *comp) override;
      Tboolean tciTestComponentAlive(const TriComponentId *comp) const override;
      Tboolean tciTestComponentKilled(const TriComponentId *comp) const override;
      
      // CD requests
      const TciType *getTypeForName(const Tstring typeName) const override;
      const TciType &getInteger() const override;
      const TciType &getFloat() const override;
      const TciType &getBoolean() const override;
      const TciType &getCharstring() const override;
      const TciType &getUniversalCharstring() const override;
      const TciType &getHexstring() const override;
      const TciType &getBitstring() const override;
      const TciType &getOctetstring() const override;
      const TciType &getVerdict() const override;
      void tciErrorReq(const Tstring message) override;
      
      // PA requests
      void triTimeout(const TriTimerId *timerId) override;

      // SA requests
      void triEnqueueMsg(const TriPortId *tsiPortId, const TriAddress *SUTaddress,
                         const TriComponentId *componentId, const TriMessage *receivedMessage) override;
      void triEnqueueCall(const TriPortId *tsiPortId, const TriAddress *SUTaddress,
                          const TriComponentId *componentId, const TriSignatureId *signatureId,
                          const TriParameterList *parameterList) override;
      void triEnqueueReply(const TriPortId *tsiPortId, const TriAddress *SUTaddress,
                           const TriComponentId *componentId, const TriSignatureId *signatureId,
                           const TriParameterList *parameterList, const TriParameter *returnValue) override;
      void triEnqueueException(const TriPortId *tsiPortId, const TriAddress *SUTaddress,
                               const TriComponentId *componentId, const TriSignatureId *signatureId,
                               const TriException *exc) override;
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __TE_H__ */
