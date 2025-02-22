#!/bin/bash

# Edit the paths and options in the following command to suit your system
module load mpi-hpe/mpt
module load comp-intel

CC=icc
CXX=icpc
MPICC=icc
MPICXX=icpc

# Build directory
OUT=build
# Install location
export GKYLSOFT=$HOME/gkylsoft
export PREFIX=$GKYLSOFT/gkyl

# Compile flags (set optimization/debug flags here)
CXXFLAGS='-O3,-std=c++17,-xAVX'

# LuaJIT options
LUAJIT_INC_DIR=$GKYLSOFT/luajit/include/luajit-2.1
LUAJIT_LIB_DIR=$GKYLSOFT/luajit/lib
LUAJIT_SHARE_DIR=$GKYLSOFT/luajit/share/luajit-2.1.0-beta3

# MPI options
ENABLE_MPI="--enable-mpi"
MPI_INC_DIR=$MPI_ROOT/include
MPI_LIB_DIR=$MPI_ROOT/lib
MPI_LINK_LIBS="mpi,mpi++"

# ADIOS options
ENABLE_ADIOS="--enable-adios" 
ADIOS_INC_DIR=
ADIOS_LIB_DIR=
ADIOS_LINK_LIBS=

# EIGEN options
EIGEN_INC_DIR=

# You probably do not need to modify the command itself
cmd="./waf CC=$CC CXX=$CXX MPICC=$MPICC MPICXX=$MPICXX --out=$OUT --prefix=$PREFIX --cxxflags=$CXXFLAGS --luajit-inc-dir=$LUAJIT_INC_DIR --luajit-lib-dir=$LUAJIT_LIB_DIR --luajit-share-dir=$LUAJIT_SHARE_DIR  $ENABLE_MPI --mpi-inc-dir=$MPI_INC_DIR --mpi-lib-dir=$MPI_LIB_DIR --mpi-link-libs=$MPI_LINK_LIBS $ENABLE_ADIOS --adios-inc-dir=$ADIOS_INC_DIR --adios-lib-dir=$ADIOS_LIB_DIR --adios-link-libs=$ADIOS_LINK_LIBS --eigen-inc-dir=$EIGEN_INC_DIR configure"
# if we are in machines directory, go up a directory before executing cmd
if [ `dirname "$0"` == "." ] 
  then
    cd ..
fi
echo $cmd
$cmd
