cmake_minimum_required(VERSION 3.18)
project(libsail)
add_library(sail sail.cc)
target_include_directories(sail PUBLIC  "D://repos///research00//libs//include")
