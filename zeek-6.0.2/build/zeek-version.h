// See the file "COPYING" in the main distribution directory for copyright.

#pragma once

/* Version number of package */
#define VERSION "6.0.2"

// Zeek version number.
// This is the result of (major * 10000 + minor * 100 + patch)
// For example, 3.1.2 becomes 30102.
#define ZEEK_VERSION_NUMBER 60002

/* A C function that has the Zeek version encoded into its name. */
#define ZEEK_VERSION_FUNCTION zeek_version_6_0_2_plugin_7
#ifdef __cplusplus
extern "C" {
#endif
extern const char* ZEEK_VERSION_FUNCTION();
#ifdef __cplusplus
}
#endif
