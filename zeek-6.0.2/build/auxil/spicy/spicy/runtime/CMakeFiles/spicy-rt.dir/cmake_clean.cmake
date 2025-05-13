file(REMOVE_RECURSE
  "../../lib/libspicy-rt.a"
  "../../lib/libspicy-rt.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C CXX)
  include(CMakeFiles/spicy-rt.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
