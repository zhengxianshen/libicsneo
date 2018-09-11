#ifndef __DYNAMICLIB_H_WINDOWS_
#define __DYNAMICLIB_H_WINDOWS_

#include <Windows.h>

#ifdef ICSNEOC_MAKEDLL
#define DLLExport __declspec(dllexport)
#else
#define DLLExport __declspec(dllimport)
#endif

// MSVC does not have the ability to specify a destructor
#define ICSNEO_DESTRUCTOR

#define icsneoDynamicLibraryLoad() LoadLibrary(L"C:\\Users\\Phollinsky\\Code\\icsneonext\\build\\icsneoc.dll")
#define icsneoDynamicLibraryGetFunction(handle, func) GetProcAddress((HMODULE) handle, func)
#define icsneoDynamicLibraryClose(handle) FreeLibrary((HMODULE) handle)

#endif