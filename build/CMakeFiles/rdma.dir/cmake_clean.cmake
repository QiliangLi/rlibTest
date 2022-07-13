file(REMOVE_RECURSE
  "librdma.pdb"
  "librdma.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/rdma.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
