# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/alex/Processus de dev/include/_deps/crow-src"
  "/home/alex/Processus de dev/include/_deps/crow-build"
  "/home/alex/Processus de dev/include/_deps/crow-subbuild/crow-populate-prefix"
  "/home/alex/Processus de dev/include/_deps/crow-subbuild/crow-populate-prefix/tmp"
  "/home/alex/Processus de dev/include/_deps/crow-subbuild/crow-populate-prefix/src/crow-populate-stamp"
  "/home/alex/Processus de dev/include/_deps/crow-subbuild/crow-populate-prefix/src"
  "/home/alex/Processus de dev/include/_deps/crow-subbuild/crow-populate-prefix/src/crow-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/alex/Processus de dev/include/_deps/crow-subbuild/crow-populate-prefix/src/crow-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/alex/Processus de dev/include/_deps/crow-subbuild/crow-populate-prefix/src/crow-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
