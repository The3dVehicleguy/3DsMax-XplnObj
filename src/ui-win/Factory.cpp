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

#include "Factory.h"
#include "DlgAbout.h"
#include "main-menu/MainMenu.h"
#include "UpdatedObjects.h"
#include "gup/Settings.h"
#include "gup/ObjCommon.h"
#include "Info.h"
#include "DlgSettings.h"

namespace ui {
namespace win {

    /**************************************************************************************************/
    ///////////////////////////////////////////* Functions *////////////////////////////////////////////
    /**************************************************************************************************/

    void Factory::showAboutWindow() {
        DlgAbout::show();
    }

    void Factory::showSettingsWindow() {
        DlgSettings::show();
    }

    void Factory::showNotImplemented() {
        MessageBoxA(GetActiveWindow(), "It is not implemented yet", "Info", MB_ICONINFORMATION);
    }

    void Factory::showVersionIncompatible() {
        std::string msg = sts::MbStrUtils::joinStr("The scene you are trying to open was made with (",
                                                   ObjCommon::instance()->pSettings.sceneVersion().toString(false, false),
                                                   ") ", XIO_PROJECT_NAME,
                                                   " plugin version which is newer than you have installed (",
                                                   ObjCommon::instance()->pSettings.pluginVersion().toString(false, false),
                                                   ")\r\n\r\nYou must update your ", XIO_PROJECT_NAME,
                                                   " plugin before open this scene. Please use X-Plane menu to get the latest plugin version.");
        MessageBoxA(GetActiveWindow(), msg.c_str(), "Incompatible Version", MB_ICONWARNING);
    }

    /**************************************************************************************************/
    ///////////////////////////////////////////* Functions *////////////////////////////////////////////
    /**************************************************************************************************/

    presenters::MainMenu::IView * Factory::createMainMenuView() {
        return new MainMenu();
    }

    void Factory::sceneUpdateInfo(const TCHAR * text) {
        DbgAssert(text);
        MessageBox(GetActiveWindow(), text ? text : _T("undefined text"), _T("Update required"), MB_ICONINFORMATION);
    }

    void Factory::showUpdatedObjects(const std::vector<INode *> & nodes) {
        UpdatedObjects().show(&nodes, GetActiveWindow());
    }

    /**************************************************************************************************/
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /**************************************************************************************************/
}
}
