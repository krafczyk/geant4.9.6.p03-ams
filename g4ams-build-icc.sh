#!/bin/sh

if [ $# -ne 2 ]; then

echo usage: $0  \<install_dir\> \<arch_name\>
echo       arch_name example Linux-g++

exit -1
fi

GINST=$1
ARCH=$2

if [ ! -d $GINST ]; then
echo 
echo Destination directory $GINST is not existing
echo I will create it now, please confirm
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

mkdir -p  $GINST

fi

if [ -d g4-build-icc ]; then rm -fr g4-build-icc; fi
mkdir g4-build-icc

cd g4-build-icc
export INTEL_LICENSE_FILE=/afs/cern.ch/ams/opt/intel/licenses/
export PATH=/afs/cern.ch/ams/opt/intel/composer_xe_2013_sp1.3.174/bin/intel64/:$PATH
export LD_LIBRARY_PATH=/afs/cern.ch/ams/opt/intel/composer_xe_2013_sp1.3.174/compiler/lib/intel64/:$LD_LIBRARY_PATH

export CC=icc
export CXX=icc

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


make install


export CMPDIR=$PWD
cd ..
cp -a config $GINST/
rm -fr $GINST/config/CVS
cd $GINST/include/
ln -sf Geant4 geant4
cd $CMPDIR

if [ $# -ne 2 ]; then

echo usage: $0  \<install_dir\> \<arch_name\>
echo       arch_name example Linux-g++

exit -1
fi

GINST=$1
ARCH=$2

if [ ! -d $GINST ]; then
echo 
echo Destination directory $GINST is not existing
echo I will create it now, please confirm
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

mkdir -p  $GINST

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

make -i -j 

make install


export CMPDIR=$PWD
cd ..
cp -a config $GINST/
rm -fr $GINST/config/CVS
cd $GINST/include/
ln -sf Geant4 geant4
cd $CMPDIR
cd ..
