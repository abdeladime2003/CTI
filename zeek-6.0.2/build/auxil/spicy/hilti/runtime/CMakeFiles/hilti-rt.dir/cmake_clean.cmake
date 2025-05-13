file(REMOVE_RECURSE
  "../../lib/libhilti-rt.a"
  "../../lib/libhilti-rt.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang ASM C CXX)
  include(CMakeFiles/hilti-rt.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
