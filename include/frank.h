#pragma once

#if defined(BUILD_FRANK)
#define FRANK_EXPORT __declspec(dllexport)
#else
#define FRANK_EXPORT __declspec(dllimport)
#endif