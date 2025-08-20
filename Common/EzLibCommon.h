#ifndef EZLIB_COMMON_INCLUDE
#define EZLIB_COMMON_INCLUDE
// This file will be used by more than 1 library, hence it's not following the typical EZLOGGER_..._H pattern.

#include <chrono>
#include <csignal>
#include <filesystem>
#include <format>
#include <fstream>
#include <map>
#include <mutex>
#include <ostream>
#include <queue>
#include <string_view>
#include <thread>
#include <iostream>

#if !defined(NDEBUG)
#define EZLIB_DEBUG
#endif

#if defined(WIN64) || defined(WIN32)
#define EZLIB_WORKING_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <processthreadsapi.h>

/**
 * Provide a set of APIs that are OS-specific.
 * TODO: Move this to its own project (EzOsAbstractor).
 */
namespace OsDependant
{
inline int GetThreadId()
{
    return int(GetCurrentThreadId());
}
};

#elif defined(__unix__)
#define EZLIB_WORKING_UNIX
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

namespace OsDependant
{
    inline int GetThreadId()
    {
        return pthread_self();
    }
};

#elif defined(__APPLE__)
#define EZLIB_WORKING_APPLE
#endif

#ifdef EZLIB_DEBUG
#endif

#endif