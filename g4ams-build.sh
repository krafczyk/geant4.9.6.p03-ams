#!/bin/sh

if [ $# -ne 2 ]; then

echo usage: $0  \<install_dir\> \<arch_name\>
echo       arch_name example Linux-g++

exit -1
fi

GINST=$1
ARCH=$2

if [ -d $GINST ]; then
echo 
echo Destination directory $GINST is not empty
echo I will clear it now, please confirm
OPTIONS="yes no"
select opt in $OPTIONS;do
  if [ "$opt" = "yes" ];then
     break
  elif [ "$opt" = "no" ];then
     exit -1
     break
  else
     echo bad option
  fi
done

rm -rvf $GINST/*

fi

if [ -d g4-build ]; then rm -fr g4-build; fi
mkdir g4-build

cd g4-build

cmake -DCMAKE_INSTALL_PREFIX=$GINST  \
-DCMAKE_BUILD_TYPE=Release \
-DGEANT4_INSTALL_DATA=ON \
-DGEANT4_USE_GDML=ON \
-DGEANT4_USE_XM=ON \
-DGEANT4_USE_OPENGL_X11=ON \
-DBUILD_STATIC_LIBS=ON \
-DBUILD_SHARED_LIBS=ON \
-DCMAKE_INSTALL_INCLUDEDIR=include/ \
-DGEANT4_BUILD_STORE_TRAJECTORY=ON \
-DCMAKE_INSTALL_LIBDIR=lib/geant4/$ARCH/ ../

make -j 

make install

export CMPDIR=$PWD
cd $GINST/include/
ln -sf Geant4 geant4
cd $CMPDIR
cd ..
