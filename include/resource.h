// resource.h
#ifndef RESOURCE_H
#define RESOURCE_H

#define ID_FILE_OPEN  1
#define ID_FILE_EXIT  2

// Inline resource definitions
#define MAINMENU 101
#define IDR_MAINMENU 102

#ifdef APSTUDIO_INVOKED
#include "windows.h"
#endif

// Menu resource
#define IDC_MYICON                  2
#define IDS_APP_TITLE               103
#define IDI_MYAPP                   107
#define IDI_SMALL                   108
#define IDC_MYAPP                   109

// Main menu
#define MENU_MAIN                    \
    POPUP "File"                   \
    BEGIN                           \
        MENUITEM "Open", ID_FILE_OPEN   \
        MENUITEM "Exit", ID_FILE_EXIT   \
    END                             \

#endif // RESOURCE_H
