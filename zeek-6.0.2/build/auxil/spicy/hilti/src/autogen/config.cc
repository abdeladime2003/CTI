// Copyright (c) 2020-2023 by the Zeek Project. See LICENSE for details.

#include <algorithm>
#include <cctype>
#include <cstring>
#include <system_error>

#include <hilti/rt/autogen/version.h>

#include <hilti/autogen/config.h>
#include <hilti/base/util.h>

using namespace hilti;

const auto flatten = util::flattenParts;
const auto prefix = util::prefixParts;

namespace {
std::optional<hilti::rt::filesystem::path> precompiled_libhilti(const Configuration& configuration, bool debug) {
    // We disable use of precompiled headers for sanitizers builds since the
    // sanitizer flags are not exposed on the config level.
    //
    // TODO(bbannier): Allow using of precompiled headers for sanitizer builds.
#ifdef HILTI_HAVE_ASAN
    return {};
#endif

    if ( auto&& cache = util::cacheDirectory(configuration) ) {
        const rt::filesystem::path file_name = rt::fmt("precompiled_libhilti%s.h.gch", (debug ? "_debug" : ""));

        std::error_code ec;
        if ( auto pch = (*cache) / file_name; rt::filesystem::exists(pch, ec) )
            return pch.replace_extension();
    }

    return {};
}
} // namespace

hilti::Configuration::Configuration() { initLocation(false); }

void hilti::Configuration::initLocation(bool use_build_directory) { init(use_build_directory); }

void hilti::Configuration::initLocation(const char* argv0) { initLocation(std::string(argv0)); }

void hilti::Configuration::initLocation(const hilti::rt::filesystem::path& argv0) {
    try {
        auto exec = hilti::rt::filesystem::canonical(argv0).native();
        auto prefix = hilti::rt::filesystem::canonical("/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/spicy").native();
        init(util::startsWith(hilti::rt::normalizePath(exec), hilti::rt::normalizePath(prefix)));
    } catch ( const hilti::rt::filesystem::filesystem_error& ) {
        init(false);
    }
}

void Configuration::init(bool use_build_directory) {
    uses_build_directory = use_build_directory;
    std::string installation_tag = (use_build_directory ? "BUILD" : "INSTALL");

    compiler_id = "GNU";
    std::transform(compiler_id.begin(), compiler_id.end(), compiler_id.begin(),
                   [](auto& c) { return std::tolower(c); });

    // Allow to set a compiler wrapper through the environment.
    if ( auto hilti_cxx = getenv("HILTI_CXX"); hilti_cxx && *hilti_cxx )
        cxx = hilti_cxx;
    else
        cxx = "/usr/bin/c++";

    // Allow to set the compiler launcher through the environment variable `HILTI_CXX_COMPILER_LAUNCHER`.
    //
    // - if the environment variable is set it overrides any automatism. If it
    //   contains a value we assume this to be an executable; if the environment
    //   variable is empty no launcher will be used.
    // - next we check whether any compiler launcher was set during the build and reuse it
    // - else we disable use of a compiler launcher.
    if ( auto hilti_cxx_launcher = getenv("HILTI_CXX_COMPILER_LAUNCHER"); hilti_cxx_launcher ) {
        if ( std::strlen(hilti_cxx_launcher) == 0 ) {
            cxx_launcher = {};
        }
        else
            cxx_launcher = hilti_cxx_launcher;
    }
    else if ( std::string cmake_cxx_launcher = ""; ! cmake_cxx_launcher.empty() )
        cxx_launcher = cmake_cxx_launcher;
    else
        cxx_launcher = {};

    distbase = "/home/abdo/Cti_Project/zeek-6.0.2/auxil/spicy";
    install_prefix = "/usr/local/zeek";
    build_directory = "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/spicy";
    lib_directory = (uses_build_directory ? "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/spicy/lib" : "/usr/local/zeek/lib");
    hiltic = (uses_build_directory ? "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/spicy/bin/hiltic" : "/usr/local/zeek/bin/hiltic");
    version_number = PROJECT_VERSION_NUMBER;
    version_string = PROJECT_VERSION_STRING_SHORT;
    version_string_long = PROJECT_VERSION_STRING_LONG;

    std::vector<std::string> library_paths;

    if ( auto hilti_library_paths = std::getenv("HILTI_PATH") ) {
        library_paths =
            util::transform(hilti::rt::split(hilti_library_paths, ":"), [](auto s) { return std::string(s); });
    }
    else {
        library_paths = flatten({".", prefix("!INSTALL!/usr/local/zeek/share/hilti !BUILD!/home/abdo/Cti_Project/zeek-6.0.2/auxil/spicy/hilti/lib", "", installation_tag)});
    }

    hilti_library_paths = util::transform(library_paths, [](auto s) { return hilti::rt::filesystem::path(s); });

    runtime_cxx_include_paths =
        util::transform(hilti::util::split(prefix("!INSTALL!/usr/local/zeek/include !BUILD!/home/abdo/Cti_Project/zeek-6.0.2/auxil/spicy/hilti/runtime/include !BUILD!/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/spicy/include", "", installation_tag)),
                        [](auto s) { return hilti::rt::filesystem::path(s); });

    runtime_cxx_library_paths =
        util::transform(hilti::util::split(prefix("!BUILD!/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/spicy/lib !INSTALL!/usr/local/zeek/lib", "", installation_tag)),
                        [](auto s) { return hilti::rt::filesystem::path(s); });

    toolchain_cxx_include_paths =
        util::transform(hilti::util::split(prefix("!INSTALL!/usr/local/zeek/include !BUILD!/home/abdo/Cti_Project/zeek-6.0.2/auxil/spicy/hilti/toolchain/include !BUILD!/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/spicy/include", "", installation_tag)),
                        [](auto s) { return hilti::rt::filesystem::path(s); });

    toolchain_cxx_library_paths =
        util::transform(hilti::util::split(prefix("!BUILD!/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/spicy/lib !INSTALL!/usr/local/zeek/lib", "", installation_tag)),
                        [](auto s) { return hilti::rt::filesystem::path(s); });

    // We hardcode the main compiler flags here instead of injecting them from
    // CMake to make it clear that they are really independent on what CMake
    // uses to compile the toolchain. This localizes the options here, and also
    // allows us to customize them by use-case (JIT vs AOT). We do still inject
    // some additional flags from CMake where we rely on stuff that CMake
    // inferred about the environment.
    //
    // We compile generated code with hidden default symbol visibility because
    // that:
    //
    // (1) reflects the public/non-public distinction at the HILTI level
    //
    // (2) avoids trouble when having the same symbols defined in multiple
    // translation units (which can happen, e.g., because of code reuse).
    //
    // (3) it helps the optimizer to know that symbols won't be accessed
    // externally.
    runtime_cxx_flags_debug = flatten({"-fPIC", "-std=c++17", "-g", "-fvisibility=hidden",
                                       prefix("!INSTALL!/usr/local/zeek/include !BUILD!/home/abdo/Cti_Project/zeek-6.0.2/auxil/spicy/hilti/runtime/include !BUILD!/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/spicy/include", "-I", installation_tag),
                                       prefix("-Wall -Wno-unused -Wno-register -Werror=vla", "", installation_tag)});

    runtime_cxx_flags_release = flatten({"-fPIC", "-std=c++17", "-g", "-O3", "-DNDEBUG", "-fvisibility=hidden",
                                         prefix("!INSTALL!/usr/local/zeek/include !BUILD!/home/abdo/Cti_Project/zeek-6.0.2/auxil/spicy/hilti/runtime/include !BUILD!/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/spicy/include", "-I", installation_tag),
                                         prefix("-Wall -Wno-unused -Wno-register -Werror=vla", "", installation_tag)});


    if ( auto libhilti_pch = precompiled_libhilti(*this, true) )
        runtime_cxx_flags_debug.push_back(rt::fmt("-include%s", libhilti_pch->c_str()));

    if ( auto libhilti_pch = precompiled_libhilti(*this, false) )
        runtime_cxx_flags_release.push_back(rt::fmt("-include%s", libhilti_pch->c_str()));

    runtime_ld_flags_debug = flatten(
        {prefix("!BUILD!/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/spicy/lib !INSTALL!/usr/local/zeek/lib", "-L", installation_tag),
         prefix("!BUILD!/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/spicy/lib !INSTALL!/usr/local/zeek/lib", "-Wl,-rpath,", installation_tag),
         prefix("hilti-rt-debug", "-l", installation_tag),
         prefix("", "", installation_tag),
         prefix(CMAKE_THREAD_LIBS_INIT, "-l", installation_tag), prefix(CMAKE_DL_LIBS, "-l", installation_tag)});

    runtime_ld_flags_release = flatten(
        {prefix("!BUILD!/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/spicy/lib !INSTALL!/usr/local/zeek/lib", "-L", installation_tag),
         prefix("!BUILD!/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/spicy/lib !INSTALL!/usr/local/zeek/lib", "-Wl,-rpath,", installation_tag),
         prefix("hilti-rt", "-l", installation_tag),
         prefix("", "", installation_tag),
         prefix(CMAKE_THREAD_LIBS_INIT, "-l", installation_tag), prefix(CMAKE_DL_LIBS, "-l", installation_tag)});

    hlto_cxx_flags_debug = runtime_cxx_flags_debug;
    hlto_cxx_flags_release = runtime_cxx_flags_release;

    hlto_ld_flags_debug = flatten({"-shared", "-Wl,-undefined", "-Wl,dynamic_lookup",
                                   prefix("", "", installation_tag)});
    hlto_ld_flags_release = flatten({"-shared", "-Wl,-undefined", "-Wl,dynamic_lookup",
                                     prefix("", "", installation_tag)});

#ifdef __APPLE__
    // Recent macOS versions have started to report `ld: warning: -undefined
    // dynamic_lookup may not work with chained fixups`. This suppresses that.
    hlto_ld_flags_debug.emplace_back("-Wl,-w");
    hlto_ld_flags_release.emplace_back("-Wl,-w");
#endif
};

Configuration& hilti::configuration() {
    static Configuration singleton;
    return singleton;
}
