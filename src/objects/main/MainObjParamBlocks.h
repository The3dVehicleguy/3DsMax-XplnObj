/*
**  Copyright(C) 2017, StepToSky
**
**  Redistribution and use in source and binary forms, with or without
**  modification, are permitted provided that the following conditions are met:
**
**  1.Redistributions of source code must retain the above copyright notice, this
**    list of conditions and the following disclaimer.
**  2.Redistributions in binary form must reproduce the above copyright notice,
**    this list of conditions and the following disclaimer in the documentation
**    and / or other materials provided with the distribution.
**  3.Neither the name of StepToSky nor the names of its contributors
**    may be used to endorse or promote products derived from this software
**    without specific prior written permission.
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
**  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**  Contacts: www.steptosky.com
*/

#pragma once

#pragma warning(push, 0)
#include <iparamb2.h>
#pragma warning(pop)

#include "MainObjectParams.h"

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class MainObjParamBlocks {
    MainObjParamBlocks() = default;
    virtual ~MainObjParamBlocks() = default;
public:

    enum eVersions {
        PbVersionAttr = 1,
        PbVersionExport = 1,
        PbVersionDisplay = 1,
    };

    enum eOrder {
        PbOrderAttr = eMainObjParamsBlocks::MainObjAttrParams,
        PbOrderExport = eMainObjParamsBlocks::MainObjExpParams,
        PbOrderDisplay = eMainObjParamsBlocks::MainObjDisplay,
    };

    enum eRollups {
        // Rollouts list
        RollGlobShading,
        RollGlobAttrCockpit,
        RollGlobAttr,
        // Rollouts count
        RollCount,
    };

    static ParamBlockDesc2 mAttr;
    static ParamBlockDesc2 mExport;
    static ParamBlockDesc2 mDisplay;

    static void postLoadAttr(IParamBlock2 * paramBlock);
    static void postLoadExport(IParamBlock2 * paramBlock);
    static void postLoadDisplay(IParamBlock2 * paramBlock);

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
