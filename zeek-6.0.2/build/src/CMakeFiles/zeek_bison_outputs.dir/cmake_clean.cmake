file(REMOVE_RECURSE
  "../scripts/base/bif"
  "CMakeFiles/zeek_bison_outputs"
  "p.cc"
  "parse.cc"
  "re-parse.cc"
  "re-parse.h"
  "re-scan.cc"
  "rep.cc"
  "rule-parse.cc"
  "rule-parse.h"
  "rule-scan.cc"
  "rup.cc"
  "rup.h"
  "scan.cc"
  "zeekparse.h"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/zeek_bison_outputs.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
