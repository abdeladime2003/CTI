// Copyright (c) 2020-2023 by the Zeek Project. See LICENSE for details.

#pragma once

#define PROJECT_VERSION_NUMBER 10802
#define PROJECT_VERSION_STRING_SHORT "1.8.2"
#define PROJECT_VERSION_STRING_LONG "1.8.2"

// A C function that has our version encoded into its name. One can link a
// target against this to ensure that it won't load if the versions differ
// between when the target was compiled vs when it's run.
//
// We name this `spicy_version_*` because it might become user-visible, to avoid confusion.
#define HILTI_VERSION_FUNCTION spicy_version_1_8_2
#define HILTI_VERSION_FUNCTION_STRING "spicy_version_1_8_2"
extern "C" const char* HILTI_VERSION_FUNCTION();
