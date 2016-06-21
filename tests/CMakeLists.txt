
#set(CMAKE_LEGACY_CYGWIN_WIN32 0)
#set(CMAKE_CXX_FLAGS " -std=gnu++0x")

project(tests)

add_subdirectory(lib/gtest-1.7.0)
add_subdirectory(test_suite)

#no targets get defined here. They are in the subdirectories