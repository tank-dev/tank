include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
    catch
    PREFIX ${CMAKE_BINARY_DIR}/catch
    GIT_REPOSITORY https://github.com/philsquared/Catch.git
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
   )

ExternalProject_Get_Property(catch source_dir)
set(CATCH_INCLUDE_DIR ${source_dir}/include)

enable_testing(true)

function(add_tank_test test_name)
  set(exe_name "${test_name}_test")
  set(sources "${exe_name}.cpp")
  add_executable(${exe_name} ${sources})
  target_include_directories(${exe_name} PRIVATE ${CATCH_INCLUDE_DIR})
  target_link_libraries(${exe_name} tank)
  add_test(${test_name} ${exe_name})
  add_dependencies(${exe_name} catch)
endfunction(add_tank_test)

add_subdirectory(Utility)
