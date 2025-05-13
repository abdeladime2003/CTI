file(REMOVE_RECURSE
  ".0"
  "libkqueue.pdb"
  "libkqueue.so"
  "libkqueue.so.0"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/kqueue.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
