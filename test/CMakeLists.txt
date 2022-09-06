# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(ApiaryCTests LANGUAGES C)

function(add_test_executable name)
  add_executable(${name} source/${name}.c)
  target_link_libraries(${name} PRIVATE ApiaryC_beekeeper)
  target_link_libraries(${name} PRIVATE ApiaryC_hive)
  target_link_libraries(${name} PRIVATE ApiaryC_melipona)
  target_compile_features(${name} PRIVATE c_std_11)

  add_test(NAME ${name} COMMAND ${name})
endfunction()

# ---- Tests ----

add_test_executable(ApiaryC_test_trim)
add_test_executable(ApiaryC_test_tokenizer)
add_test_executable(ApiaryC_test_hive)
add_test_executable(ApiaryC_test_hive_long)
add_test_executable(ApiaryC_test_melipona)
add_test_executable(ApiaryC_test_hive_attributic)

# add_executable(ApiaryC_test source/ApiaryC_test.c)
# target_link_libraries(ApiaryC_test PRIVATE ApiaryC_beekeeper)
# target_link_libraries(ApiaryC_test PRIVATE ApiaryC_hive)
# target_link_libraries(ApiaryC_test PRIVATE ApiaryC_melipona)
# target_compile_features(ApiaryC_test PRIVATE c_std_11)
# 
# add_test(NAME ApiaryC_test COMMAND ApiaryC_test)

# ---- End-of-file commands ----

add_folders(Test)
