file(REMOVE_RECURSE
  "../../lib/libspicy.pdb"
  "../../lib/libspicy.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang C CXX)
  include(CMakeFiles/spicy.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
