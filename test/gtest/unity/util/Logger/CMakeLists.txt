find_package(Threads)
find_package (PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)
add_definitions(
  ${GLIB_CLFAGS}
  ${GLIB_CFLAGS_OTHER}
  -DG_LOG_DOMAIN="Logger_test"
)
include_directories(${GLIB_INCLUDE_DIRS})

add_executable(Logger_test Logger_test.cpp)
target_link_libraries(Logger_test
  ${LIBS}
  ${TESTLIBS}
  ${GLIB_LDFLAGS}
  ${CMAKE_THREAD_LIBS_INIT}
)

add_test(Logger Logger_test)
