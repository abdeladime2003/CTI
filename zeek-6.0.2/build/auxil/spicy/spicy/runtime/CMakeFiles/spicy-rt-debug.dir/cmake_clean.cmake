file(REMOVE_RECURSE
  "../../lib/libspicy-rt-debug.a"
  "../../lib/libspicy-rt-debug.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C CXX)
  include(CMakeFiles/spicy-rt-debug.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
