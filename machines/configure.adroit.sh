#!/bin/bash

# Edit the paths and options in the following command to suit your system
# The following modules should be loaded to configure on Adroit.
# module load intel
# module load openmpi/cuda-10.2/intel-19.1/4.0.3/64
# module load cudatoolkit/10.2
# module load rh/devtoolset/8

# Build directory
OUT=build
# Install location
PREFIX=$HOME/gkylsoft/gkyl

# Compile flags (set optimization/debug flags here)
CC=mpicc
CXX=mpicxx
CXXFLAGS='-O3,-std=c++17'

# LuaJIT options
LUAJIT_INC_DIR=$HOME/gkylsoft/luajit/include/luajit-2.1
LUAJIT_LIB_DIR=$HOME/gkylsoft/luajit/lib
LUAJIT_SHARE_DIR=$HOME/gkylsoft/luajit/share/luajit-2.1.0-beta3

## MPI options
MPICC=mpicc
MPICXX=mpicxx
ENABLE_MPI="--enable-mpi"
MPI_INC_DIR=/usr/local/openmpi/cuda-10.2/4.0.3/intel191/x86_64/include
MPI_LIB_DIR=/usr/local/openmpi/cuda-10.2/4.0.3/intel191/x86_64/lib64
MPI_LINK_LIBS="mpi"

# ADIOS options
ENABLE_ADIOS="--enable-adios" # set to blank to disable ADIOS
ADIOS_INC_DIR=$HOME/gkylsoft/adios/include
ADIOS_LIB_DIR=$HOME/gkylsoft/adios/lib

# EIGEN options
EIGEN_INC_DIR=$HOME/gkylsoft/eigen3/include/eigen3

# CUDA options
ENABLE_CUDA="--enable-cuda"
CUTOOLS_INC_DIR=$CPATH
CUTOOLS_LIB_DIR=$LIBRARY_PATH
CUTOOLS_LINK_LIBS="cudart,cublas"

# You probably do not need to modify the command itself
cmd="./waf CC=$CC CXX=$CXX MPICC=$MPICC MPICXX=$MPICXX --out=$OUT --prefix=$PREFIX --cxxflags=$CXXFLAGS --luajit-inc-dir=$LUAJIT_INC_DIR --luajit-lib-dir=$LUAJIT_LIB_DIR --luajit-share-dir=$LUAJIT_SHARE_DIR $ENABLE_MPI --mpi-inc-dir=$MPI_INC_DIR --mpi-lib-dir=$MPI_LIB_DIR --mpi-link-libs=$MPI_LINK_LIBS $ENABLE_ADIOS --adios-inc-dir=$ADIOS_INC_DIR --adios-lib-dir=$ADIOS_LIB_DIR $ENABLE_CUDA --cuda-inc-dir=$CUTOOLS_INC_DIR --cuda-lib-dir=$CUTOOLS_LIB_DIR --cuda-link-libs=$CUTOOLS_LINK_LIBS configure"
# if we are in machines directory, go up a directory before executing cmd
if [ `dirname "$0"` == "." ] 
  then
    cd ..
fi
echo $cmd
$cmd
