file(REMOVE_RECURSE
  "../../lib/libhilti-rt-debug.a"
  "../../lib/libhilti-rt-debug.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang ASM C CXX)
  include(CMakeFiles/hilti-rt-debug.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
