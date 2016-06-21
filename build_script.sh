#!/bin/bash

# This is the build script for the Quaternion project in Linux
# It sets up CMake for building and installing the project.
# This script should be at the root folder of the project, i.e.:
# /build_script.sh
# /src/
# /build/   (created automatically)
# /install/ (created automatically)

set -e # Exit if there is an error

# One of many ways to get root directory
# (assumes that this script is at root)
scriptname=$0
fqname=`readlink -f $scriptname`
QuaternionTop=`dirname $fqname`

# Print root directory
echo -- QuaternionTop $QuaternionTop

# Check if the underlying paths are correct
if [[ `expr match "${QuaternionTop}" '\(.*src$\)'` ]]; then
	QuaternionBuild=$QuaternionTop/build
	QuaternionInstall=$QuaternionTop/install
else
	QuaternionBuild=$QuaternionTop/build
	QuaternionInstall=$QuaternionTop/install
fi
echo -- Build dir is $QuaternionBuild
echo -- Install dir is $QuaternionInstall

# Process input arguments
while getopts "j:t:r" flag
do
	case ${flag} in
	  j) CPUS=${OPTARG};;    # Number of CPUs for parallel compilation
	  t) toolset=${OPTARG};; # compiler
	  r) resetBuild=true;;   # if flag was provided, delete install and build dirs (handy for debugging)
	  *) echo>&2 "invalid option ${flag}i"; usage; exit 1;;
	esac
done

# Enable parallel compilation in the Linux environment
if [[ ${CPUS} -gt 1 ]]; then
  echo -- Compiling with $CPUS cores
  export MAKEFLAGS="${MAKEFLAGS} -j ${CPUS}"
fi

# Delete all previous build and install folders (if -r flag was passed)
if [[ "$resetBuild" == "true" ]]; then
	rm -rf build install
fi

# Set CMake variables for more portable use (currently a placeholder)
CMAKE=cmake
CPACK=cpack

# Set toolset to use default compiler versions
case $toolset in
	llvm) 
	  export CC=clang
	  export CXX=clang++
	;;
	gcc)
	  export CC=gcc
	  export CXX=g++
	;;
	*)
	  export CC=gcc
	  export CXX=g++
	;;
esac

# Assign build and install dirs
BUILDDIR=${QuaternionBuild}
INSTALLDIR=${QuaternionInstall}

# Save source directory
QuaternionSrc=${TOP}/src

# Create new dir for build, if one does not exist, and pushd to build and cd back to root
mkdir -p ${BUILDDIR}
pushd ${BUILDDIR}

${SBCMAKE} ${CMAKE} \
	${QuaternionTop}
# Make and install project in the appropriate directories
${CMAKE} --build .
${CMAKE} --build . --target install

popd
