file(REMOVE_RECURSE
  "../../lib/libjrx.pdb"
  "../../lib/libjrx.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/jrx.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
