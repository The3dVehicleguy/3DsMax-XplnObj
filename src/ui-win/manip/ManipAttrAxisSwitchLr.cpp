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

#include "ManipAttrAxisSwitchLr.h"

#pragma warning(push, 0)
#include <3dsmaxport.h>
#pragma warning(pop)

#include <xpln/enums/ECursor.h>
#include "ui-win/Utils.h"
#include "resource/resource.h"
#include "common/Logger.h"
#include "resource/ResHelper.h"
#include "ui-win/Factory.h"

namespace ui {
namespace win {

    /**************************************************************************************************/
    //////////////////////////////////////////* Static area *///////////////////////////////////////////
    /**************************************************************************************************/

    INT_PTR CALLBACK ManipAttrAxisSwitchLr::panelProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        ManipAttrAxisSwitchLr * theDlg;
        if (msg == WM_INITDIALOG) {
            theDlg = reinterpret_cast<ManipAttrAxisSwitchLr*>(lParam);
            DLSetWindowLongPtr(hWnd, lParam);
            theDlg->initWindow(hWnd);
        }
        else if (msg == WM_DESTROY) {
            theDlg = DLGetWindowLongPtr<ManipAttrAxisSwitchLr*>(hWnd);
            theDlg->destroyWindow(hWnd);
        }
        else {
            theDlg = DLGetWindowLongPtr<ManipAttrAxisSwitchLr *>(hWnd);
            if (!theDlg) {
                return FALSE;
            }
        }

        //--------------------------------------

        switch (msg) {
            case WM_COMMAND: {
                switch (LOWORD(wParam)) {
                    case BTN_DATAREF: {
                        Factory::showNotImplemented();
                        break;
                    }
                    case CMB_CURSOR: {
                        if (HIWORD(wParam) == CBN_SELCHANGE) {
                            theDlg->mData.setCursor(xobj::ECursor::fromUiString(sts::toMbString(theDlg->cCmbCursor.currSelectedText()).c_str()));
                            theDlg->save();
                        }
                        break;
                    }
                    default: break;
                }
                break;
            }
            case WM_CUSTEDIT_ENTER: {
                switch (LOWORD(wParam)) {
                    case EDIT_DATAREF: {
                        theDlg->mData.setDataref(sts::toMbString(Utils::getText(theDlg->cEdtDataRef)));
                        theDlg->save();
                        break;
                    }
                    case EDIT_TOOLTIP: {
                        theDlg->mData.setToolTip(sts::toMbString(Utils::getText(theDlg->cEdtToolType)));
                        theDlg->save();
                        break;
                    }
                    default: break;
                }
                break;
            }
            case CC_SPINNER_CHANGE: {
                switch (LOWORD(wParam)) {
                    case SPN_CLICK_DELTA: {
                        theDlg->mData.setClickDelta(theDlg->mSpnClick->GetFVal());
                        theDlg->save();
                        break;
                    }
                    case SPN_HOLD_DELTA: {
                        theDlg->mData.setHoldDelta(theDlg->mSpnHold->GetFVal());
                        theDlg->save();
                        break;
                    }
                    case SPN_MIN: {
                        theDlg->mData.setMinimum(theDlg->mSpnMim->GetFVal());
                        theDlg->save();
                        break;
                    }
                    case SPN_MAX: {
                        theDlg->mData.setMaximum(theDlg->mSpnMax->GetFVal());
                        theDlg->save();
                        break;
                    }
                    default: break;
                }
                break;
            }
            default: break;
        }
        return 0;
    }

    /**************************************************************************************************/
    ////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
    /**************************************************************************************************/

    ManipAttrAxisSwitchLr::ManipAttrAxisSwitchLr(MdManip * modelData)
        : mModelData(modelData) {
        assert(mModelData);
    }

    ManipAttrAxisSwitchLr::~ManipAttrAxisSwitchLr() {
        ManipAttrAxisSwitchLr::destroy();
    }

    /**************************************************************************************************/
    ///////////////////////////////////////////* Functions *////////////////////////////////////////////
    /**************************************************************************************************/

    void ManipAttrAxisSwitchLr::create(HWND inParent) {
        assert(inParent);
        mHwnd.setup(CreateDialogParam(ResHelper::hInstance,
                                      MAKEINTRESOURCE(ROLL_MANIP_AXIS_KNOB), /* the same template */
                                      inParent, panelProc,
                                      reinterpret_cast<LPARAM>(this)));
        assert(mHwnd);
        if (mHwnd) {
            toWindow();
            mWheel.create(inParent);
            calculateSize();
            mHwnd.show(true);
        }
        else {
            LError << WinCode(GetLastError());
        }
    }

    void ManipAttrAxisSwitchLr::destroy() {
        if (mHwnd) {
            BOOL res = DestroyWindow(mHwnd.hwnd());
            if (!res) {
                LError << WinCode(GetLastError());
            }
            mHwnd.release();
        }
    }

    RECT ManipAttrAxisSwitchLr::rect() const {
        return mSize;
    }

    void ManipAttrAxisSwitchLr::move(const POINT & point) {
        if (mHwnd) {
            mHwnd.move(point);
            calculateSize();
        }
    }

    /**************************************************************************************************/
    //////////////////////////////////////////* Functions */////////////////////////////////////////////
    /**************************************************************************************************/

    void ManipAttrAxisSwitchLr::calculateSize() {
        if (mHwnd) {
            mSize = mHwnd.rect();
            mWheel.move(POINT{0, mSize.bottom});
            RECT wheelRect = mWheel.rect();
            mSize.bottom += (wheelRect.bottom - wheelRect.top);
        }
    }

    /**************************************************************************************************/
    //////////////////////////////////////////* Functions */////////////////////////////////////////////
    /**************************************************************************************************/

    void ManipAttrAxisSwitchLr::setManip(const xobj::AttrManipBase & manip) {
        if (manip.type() != mData.type()) {
            LError << "Incorrect manipulator: " << manip.type().toString();
            return;
        }
        mData = static_cast<const xobj::AttrManipAxisSwitchLeftRight &>(manip);
        mWheel.setManip(mData.wheel());
    }

    /**************************************************************************************************/
    ///////////////////////////////////////////* Functions *////////////////////////////////////////////
    /**************************************************************************************************/

    void ManipAttrAxisSwitchLr::initWindow(HWND hWnd) {
        mLblName.setup(hWnd, LBL_NAME);
        mLblName.setText("Axis switch left-right");

        std::function<void(const xobj::AttrManipWheel &)> callback = [this](const xobj::AttrManipWheel & wheel) mutable {
            mData.setWheel(wheel);
            mModelData->saveToNode(mData);
        };
        mWheel.setCallBack(callback);

        mSpnClick = SetupFloatSpinner(hWnd, SPN_CLICK_DELTA, SPN_CLICK_DELTA_EDIT, -10000.0f, 10000.0f, 0.0f, 0.1f);
        mSpnHold = SetupFloatSpinner(hWnd, SPN_HOLD_DELTA, SPN_HOLD_DELTA_EDIT, -10000.0f, 10000.0f, 0.0f, 0.1f);

        mSpnMim = SetupFloatSpinner(hWnd, SPN_MIN, SPN_MIN_EDIT, -10000.0f, 10000.0f, 0.0f, 0.1f);
        mSpnMax = SetupFloatSpinner(hWnd, SPN_MAX, SPN_MAX_EDIT, -10000.0f, 10000.0f, 0.0f, 0.1f);

        cBtnDataRef.setup(hWnd, BTN_DATAREF);
        cEdtDataRef = GetICustEdit(GetDlgItem(hWnd, EDIT_DATAREF));
        cEdtToolType = GetICustEdit(GetDlgItem(hWnd, EDIT_TOOLTIP));
        cCmbCursor.setup(hWnd, CMB_CURSOR);

        for (auto & curr : xobj::ECursor::list()) {
            cCmbCursor.addItem(sts::toString(curr.toUiString()));
        }
        cCmbCursor.setCurrSelected(0);
    }

    void ManipAttrAxisSwitchLr::destroyWindow(HWND /*hWnd*/) {
        mLblName.release();
        ReleaseISpinner(mSpnClick);
        ReleaseISpinner(mSpnHold);
        ReleaseISpinner(mSpnMim);
        ReleaseISpinner(mSpnMax);
        cBtnDataRef.release();
        ReleaseICustEdit(cEdtDataRef);
        ReleaseICustEdit(cEdtToolType);
        cCmbCursor.release();
    }

    void ManipAttrAxisSwitchLr::toWindow() {
        mSpnClick->SetValue(mData.clickDelta(), FALSE);
        mSpnHold->SetValue(mData.holdDelta(), FALSE);
        mSpnMim->SetValue(mData.minimum(), FALSE);
        mSpnMax->SetValue(mData.maximum(), FALSE);
        Utils::setText(cEdtDataRef, sts::toString(mData.dataref()));
        Utils::setText(cEdtToolType, sts::toString(mData.toolTip()));
        cCmbCursor.setCurrSelected(sts::toString(mData.cursor().toUiString()));
    }

    /********************************************************************************************************/
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /********************************************************************************************************/
}
}
