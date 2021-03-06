#!/bin/sh

# set env to use an appropriate version of ROOT that comes with CMSSW_7_1_0
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /cvmfs/cms.cern.ch/slc6_amd64_gcc490/cms/cmssw/CMSSW_7_1_0/src
cmsenv
cd -

# compile scripts
#  - note that fastsim path is correctly set
g++ process_nano.cpp  `fastjet-config --cxxflags --libs --plugins` `root-config --cflags --glibs` -o process_nano.exe
g++ skim.cpp  `root-config --cflags --glibs` -o skim.exe

# copy executables to home directory so that they can be picked up by condor
cp process_nano.exe /cms/ldap_home/yjeong
cp skim.exe         /cms/ldap_home/yjeong
cp process_nano.exe /cms/scratch/yjeong/CMSSW_7_1_0/src/nanoprocessing/condor/submit_scripts/2016
cp process_nano.exe /cms/scratch/yjeong/CMSSW_7_1_0/src/nanoprocessing/condor/submit_scripts/2017
cp process_nano.exe /cms/scratch/yjeong/CMSSW_7_1_0/src/nanoprocessing/condor/submit_scripts/2018

# make folders for flists
mkdir -p ~/flist/2016
mkdir -p ~/flist/2017
mkdir -p ~/flist/2018
