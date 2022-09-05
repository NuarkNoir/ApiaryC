# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(ApiaryCTests LANGUAGES C)

# ---- Tests ----

add_executable(ApiaryC_test source/ApiaryC_test.c)
target_link_libraries(ApiaryC_test PRIVATE ApiaryC_beekeeper)
target_link_libraries(ApiaryC_test PRIVATE ApiaryC_hive)
target_link_libraries(ApiaryC_test PRIVATE ApiaryC_melipona)
target_compile_features(ApiaryC_test PRIVATE c_std_11)

add_test(NAME ApiaryC_test COMMAND ApiaryC_test)

# ---- End-of-file commands ----

add_folders(Test)
