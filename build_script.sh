#!/bin/bash

set -e # Exit if there is an error

scriptname=$0
fqname=`readlink -f $scriptname`
QuaternionTop=`dirname $fqname`

# Print root directory
echo -- QuaternionTop $QuaternionTop

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
	  j) CPUS=${OPTARG};;
	  t) toolset=${OPTARG};;
	  r) resetBuild=true;;
	  *) echo>&2 "invalid option ${flag}i"; usage; exit 1;;
	esac
done

# Enable parallel compilation in the Linux environment
if [[ ${CPUS} -gt 1 ]]; then
  echo -- Compiling with $CPUS cores
  export MAKEFLAGS="${MAKEFLAGS}" -j ${CPUS}
fi

# Delete all previous build and install folders
if [[ "$resetBuild" == "true" ]]; then
	rm -rf build install
fi

CMAKE=cmake
CPACK=cpack

# Use default compiler versions
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

BUILDDIR=${QuaternionBuild}
INSTALLDIR=${QuaternionInstall}

QuaternionSrc=${TOP}/src

mkdir -p ${BUILDDIR}
pushd ${BUILDDIR}

${SBCMAKE} ${CMAKE} \
	${QuaternionTop}

${CMAKE} --build .
${CMAKE} --build . --target install

popd
