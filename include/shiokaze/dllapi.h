#pragma once

//#ifdef DLLEXPORT
//#define DLLAPI __declspec(dllexport)
//#else
//#define DLLAPI //__declspec(dllimport)
//#endif

#define DLLAPI_EXPORT __declspec(dllexport)
#define DLLAPI_IMPORT //__declspec(dllimport)
