# CMake generated Testfile for 
# Source directory: /home/abdo/Cti_Project/zeek-6.0.2/auxil/spicy/spicy/toolchain
# Build directory: /home/abdo/Cti_Project/zeek-6.0.2/build/auxil/spicy/spicy/toolchain
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(spicy-toolchain-tests "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/spicy/bin/spicy-toolchain-tests")
set_tests_properties(spicy-toolchain-tests PROPERTIES  _BACKTRACE_TRIPLES "/home/abdo/Cti_Project/zeek-6.0.2/auxil/spicy/spicy/toolchain/CMakeLists.txt;185;add_test;/home/abdo/Cti_Project/zeek-6.0.2/auxil/spicy/spicy/toolchain/CMakeLists.txt;0;")
subdirs("bin/spicy-dump")
