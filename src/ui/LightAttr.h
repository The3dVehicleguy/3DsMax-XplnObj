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
#include <map>
#include "common/String.h"
#include "ui/controls/Combo.h"
#include "models/MdLight.h"
#include "light/AbstractLight.h"
#include "ui/controls/RollupBase.h"
#include "additional/utils/Signal.h"

namespace ui {

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/

class LightAttr : public maxwin::RollupBase, LightIO::ILightIO, public sts::HasSlots {
public:

    void create(IRollupWindow * rollWin);
    void destroy() override;

    void show(MdLight * inOutData);

    LightAttr();
    virtual ~LightAttr();

private:

    void create() override;
    void createSubWindow();
    void destroyAllSubWindows();
    void recalculateSize();

    IRollupWindow * getInterface() override {
        return mIp;
    }

    INT_PTR panelProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
    void initWindow(HWND hWnd) override;
    void destroyWindow(HWND hWnd) override;

    win::Combo cCmbLightType;

    void toWindow();

    void enableControls();
    void disableControls();

    void onParamChanged(bool);

    MdLight * mData = nullptr;
    IRollupWindow * mIp = nullptr;
    RECT mThisSize;

    std::map<const sts::Str, AbstractLight *> mChildren;
    win::Base * currSubWin = nullptr;

    //-------------------------------------------------------------------------

    void setCurrLight(xobj::ObjAbstract * inManip) {
        delete mCurrLight;
        mCurrLight = inManip;
    }

    template<typename T>
    T * currentLight() {
        return dynamic_cast<T*>(mCurrLight);
    }

    xobj::ObjAbstract * mCurrLight = nullptr;

    //-------------------------------------------------------------------------

    void gotLight(const xobj::ObjLightCustom & inLight) override;
    void gotLight(const xobj::ObjLightNamed & inLight) override;
    void gotLight(const xobj::ObjLightParam & inLight) override;
    void gotLight(const xobj::ObjLightPoint & inLight) override;
    void gotLight(const xobj::ObjLightSpillCust & inLight) override;
    void gotNoLight() override;

    //-------------------------------------------------------------------------
};

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/
}
