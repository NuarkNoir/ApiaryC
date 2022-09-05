install(
    TARGETS ApiaryC_exe
    RUNTIME COMPONENT ApiaryC_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
