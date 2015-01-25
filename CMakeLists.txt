cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
if (NOT DEFINED PROJECT_NAME)
    project (Tank)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

find_package(SFML 2.0 REQUIRED system window graphics audio)
find_package(Threads REQUIRED)
find_package(Boost 1.53.0 REQUIRED)

set(TANK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Tank/Audio)
add_subdirectory(Tank/Graphics)
add_subdirectory(Tank/System)
add_subdirectory(Tank/Utility)
add_subdirectory(Tank/Geometry)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/customdoxygen.css.in
      ${CMAKE_CURRENT_BINARY_DIR}/doxygen.css)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/header.html.in
      ${CMAKE_CURRENT_BINARY_DIR}/header.html)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/footer.html.in
      ${CMAKE_CURRENT_BINARY_DIR}/footer.html)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/doc/bootstrap3
            ${CMAKE_CURRENT_BINARY_DIR}/doc/html/bootstrap3
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/doc/jquery-2.1.3.min.js
            ${CMAKE_CURRENT_BINARY_DIR}/doc/html
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/doc/doxy-boot.js
            ${CMAKE_CURRENT_BINARY_DIR}/doc/html
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation" VERBATIM
    )
endif(DOXYGEN_FOUND)

add_library(tank ${audio_src} ${gfx_src} ${geom_src} ${sys_src} ${util_src})

# Use only standard C++.
set(CMAKE_CXX_EXTENSIONS OFF)
# Required C++14 features.
target_compile_features(tank PUBLIC cxx_alias_templates cxx_auto_type
  cxx_constexpr cxx_decltype
  cxx_default_function_template_args cxx_defaulted_functions
  cxx_defaulted_move_initializers cxx_delegating_constructors
  cxx_deleted_functions cxx_explicit_conversions
  cxx_final cxx_generalized_initializers cxx_generic_lambdas
  cxx_inheriting_constructors cxx_lambdas cxx_lambda_init_captures
  cxx_local_type_template_args cxx_long_long_type cxx_noexcept
  cxx_nonstatic_member_init cxx_nullptr cxx_override cxx_range_for
  cxx_raw_string_literals cxx_return_type_deduction cxx_right_angle_brackets
  cxx_rvalue_references cxx_static_assert cxx_strong_enums
  cxx_trailing_return_types cxx_uniform_initialization cxx_user_literals
  cxx_variadic_templates)

target_include_directories(tank PUBLIC ${SFML_INCLUDE_DIR} ${Boost_INCLUDE_DIR}
  ${TANK_INCLUDE_DIR})

target_link_libraries(tank ${SFML_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

include(CTest)
add_subdirectory(tests)
