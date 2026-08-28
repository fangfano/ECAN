file(REMOVE_RECURSE
  "output/demo.elf"
  "output/demo.elf.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/demo.elf.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
