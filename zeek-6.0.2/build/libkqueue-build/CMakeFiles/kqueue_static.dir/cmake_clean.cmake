file(REMOVE_RECURSE
  "libkqueue.a"
  "libkqueue.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/kqueue_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
