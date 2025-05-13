file(REMOVE_RECURSE
  "../../lib/libhilti.pdb"
  "../../lib/libhilti.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang ASM C CXX)
  include(CMakeFiles/hilti.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
