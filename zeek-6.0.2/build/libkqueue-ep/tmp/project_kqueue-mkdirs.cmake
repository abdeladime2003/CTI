# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/abdo/Cti_Project/zeek-6.0.2/build/libkqueue-ep/src/project_kqueue"
  "/home/abdo/Cti_Project/zeek-6.0.2/build/libkqueue-build"
  "/home/abdo/Cti_Project/zeek-6.0.2/build/libkqueue-ep"
  "/home/abdo/Cti_Project/zeek-6.0.2/build/libkqueue-ep/tmp"
  "/home/abdo/Cti_Project/zeek-6.0.2/build/libkqueue-ep/src/project_kqueue-stamp"
  "/home/abdo/Cti_Project/zeek-6.0.2/build/libkqueue-ep/src"
  "/home/abdo/Cti_Project/zeek-6.0.2/build/libkqueue-ep/src/project_kqueue-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/abdo/Cti_Project/zeek-6.0.2/build/libkqueue-ep/src/project_kqueue-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/abdo/Cti_Project/zeek-6.0.2/build/libkqueue-ep/src/project_kqueue-stamp${cfgdir}") # cfgdir has leading slash
endif()
