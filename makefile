#
# Copyright 2010 Andrew Leifer et al <leifer@fas.harvard.edu>
# This file is part of MindControl.
#
# MindControl is free software: you can redistribute it and/or modify
# it under the terms of the GNU  General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# MindControl is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with MindControl. If not, see <http://www.gnu.org/licenses/>.
#
# For the most up to date version of this software, see:
# http://github.com/samuellab/mindcontrol
# 
#
# 
# NOTE: If you use any portion of this code in your research, kindly cite:
#  Leifer, A.M., Fang-Yen, C., Gershow, M., Alkema, M., and Samuel A. D.T. 
#	 "Optogenetic manipulation of neural activity with high spatial resolution in 
#	 freely moving Caenorhabditis elegans," Nature Methods, Submitted (2010). 
#

#
# This is the makefile for the entire OpticalMindControl Project.
#
# The makefile is a computer program in its own right. 
# It's job is to compile the source code for different components of the 
# MindControl  software suite for different hardware and computer environments.
# 
# The MindControl software consists mostly of two components: the Calibration Routines
# and the main closed-loop component.
#
# The MindControl software is designed to work with a variety of different hardware and 
# software components. These include two different camera systems, (the BitFlow frame grabber
# system and the deprecated ImagingSource camera system), the OpenCV computer vision library
# the numerical software package MATLAB, the ALP Basic VIALUX USB interface to the 
# TexasInstruments DLP Digital Micromirror Device and other ancillary components such as 
# the version control system `git` and the programming language `awk`.
# For the MindControl software to  interface with any of these third party systems, 
# it must acess third party static and dynamic libraries or executables both at compile 
# time and often at runtime.  This makefile generates a variety of executables that 
# use different subsets of these third party libraries components.
# 
#
# This makefile creates a number of different executables:
#
# Deprecated:
#  ClosedLoop.exe  		  -	Older version of the MindControl software designed to work 
#							with the ImagingSource USB camera.
#  CalibrateApparatus.exe - Older version of the calibration routine. Calibrates 
#							the DLP and Camera for an ImagingSource camera.
#
# Current
#  VirtualMC.exe 		  -	"Virtual MindControl" This is a stand-alone piece of software that simulates 
#							the functionality of the MindControl suite for setups that have no camera or
#							DLP hardware present. It requires having only the OpenCV libraries, 
#							git, and awk. It can simulate a closed loop system by analyzing video of a 
#							swimming worm from a file. 
#
#
#  FG_DLP.exe			  - Run the closed-loop MindControl system using the BitFlow FrameGrabber and the DLP. 
#
#  calibrateFG_DLP.exe	  -	Calibrate the MindControl system using the BitFlow FrameGrabber and the DLP.
#
#
#
# There are four make targets in this makefile:
# 	make all			  -	This assumes the presence of all libraries that the system has every worked with: 
#							including OpenCV, git, awk, ImagingSource Libraries, MATLAB, BitFlow
#							FrameGrabber libraries, and the DLP libraries
#
# 	make FGandDLP		  - This is the make target to use if you have the DLP and FrameGrabber installed. 
#							it also requires OpenCV, git, awk and MATLAB. 
#
#	make farmegrabberonly - This is the make target to use if you have the BitFlow Framegrabber installed
#							as well as OpenCV, git and awk, but not MATLAB, the DLP libraries or the 
#							imagingsource librares.
#	
#	make virtual		  - This is the make target to use if you have no special hardware. It requires only 
#							openCV, git and awk. 
#
#
#
#


CXX = g++
CXXFLAGS= -c -v -Wall -mwindows


#TailOpts =-pg # This generates output for a profiler such as gprof
TailOpts= -O2 #optimize the code	
LinkerWinAPILibObj= -lsetupapi

#Location of directories
MyLibs=MyLibs
3rdPartyLibs=3rdPartyLibs
bfIncDir=$(3rdPartyLibs)/BitFlowSDK
targetDir=bin
CVdir=C:/Progra~1/OpenCV
GIT=C:/Program\ Files/Git/bin/git #version control system

#Matlab Include directory for header files
MatlabIncDir= C:/Progra~1/MATLAB/R2009a/extern/include

#Matlab Compiled Libraries Directgory
MatlabLibsDir= C:/Progra~1/MATLAB/R2009a/extern/lib/win32/microsoft/

#OpenCV Include directories (for header files)
openCVincludes = -I$(CVdir)/cxcore/include -I$(CVdir)/otherlibs/highgui -I$(CVdir)/cv/include


# objects that I have written, in order of dependency. 
# e.g. Objects that depend on nothing go left.
#Objects that depend on other objects go right.

mylibraries=  version.o AndysComputations.o Talk2DLP.o Talk2Camera.o Talk2FrameGrabber.o AndysOpenCVLib.o Talk2Matlab.o TransformLib.o IllumWormProtocol.o
WormSpecificLibs= WormAnalysis.o WriteOutWorm.o experiment.o

#3rd party statically linked objects
CVlibs=$(CVdir)/lib/cv.lib $(CVdir)/lib/highgui.lib $(CVdir)/lib/cxcore.lib
MatlabLibs=$(MatlabLibsDir)/libeng.lib $(MatlabLibsDir)/libmx.lib
TimerLibrary=tictoc.o timer.o
HardwareLibrary=$(3rdPartyLibs)/alp4basic.lib $(3rdPartyLibs)/tisgrabber.lib 
3rdpartyobjects= $(TimerLibrary) $(HardwareLibrary)

##BitFlow SDK
BFLibDir = C:/BitFlow\ SDK\ 5.20/Lib
BFObj = $(BFLibDir)/BFD.lib   $(BFLibDir)/BFDiskIO.lib $(BFLibDir)/BFDrv.lib $(BFLibDir)/BFEr.lib $(BFLibDir)/BFOS.lib $(BFLibDir)/BFS.lib $(BFLibDir)/Bid.lib $(BFLibDir)/BufferInterface.lib $(BFLibDir)/Cid.lib  $(BFLibDir)/R2Cam.lib $(BFLibDir)/R2D.lib $(BFLibDir)/R64D.lib $(BFLibDir)/RvD.lib $(BFLibDir)/clallserial.lib $(BFLibDir)/clserbit.lib $(BFLibDir)/DispSurf.lib




#All Library Objects 
objects= $(mylibraries) $(WormSpecificLibs) $(3rdpartyobjects) $(BFObj) $(CVlibs)  $(MatlabLibs)
calib_objects= calibrate.o $(objects)

#Hardware Independent objects
hw_ind= version.o AndysComputations.o AndysOpenCVLib.o TransformLib.o IllumWormProtocol.o  $(WormSpecificLibs) $(TimerLibrary) $(CVlibs)

#Virtual HArdware Libraries
virtual_hardware =DontTalk2DLP.o DontTalk2Camera.o DontTalk2FrameGrabber.o Talk2Stage.o


############DIFFERENT TARGETS
## NOTE: depending on what hardware libraries you have installed, you should choose
## Different targets of your make command
##
## For example, if you have installed: OpenCV, MATLAB, the FrameGrabber, Imaging Source, and the DLP,
## Then go head and and "make all"
## If you only have installed the framegrabber & OpenCV, but not the DLP or matlab or anything else, then
## use "make framegrabberonly"
##
## If you only: MATLAB, OpenCV, the DLP and FrameGrabber use "make FGandDLP"


all : $(targetDir)/ClosedLoop.exe $(targetDir)/CalibrateApparatus.exe FGandDLP  virtual

FGandDLP : framegrabberonly $(targetDir)/FG_DLP.exe  $(targetDir)/calibrateFG_DLP.exe version.o $(targetDir)/Test.exe

framegrabberonly :  $(targetDir)/FGMindControl.exe version.o $(targetDir)/Test.exe

virtual: $(targetDir)/VirtualMC.exe version.o $(targetDir)/Test.exe



$(targetDir)/CalibrateApparatus.exe : $(calib_objects) Talk2Stage.o
	$(CXX) -o $(targetDir)/CalibrateApparatus.exe $(calib_objects) Talk2Stage.o $(LinkerWinAPILibObj) $(TailOpts)

calibrate.o : calibrate.c $(3rdPartyLibs)/tisgrabber.h $(3rdPartyLibs)/TISGrabberGlobalDefs.h $(MyLibs)/Talk2DLP.h $(MyLibs)/Talk2Camera.h $(MatlabIncDir)/engine.h
	$(CXX) $(CXXFLAGS) calibrate.c -I"inc" -I$(MyLibs) $(openCVincludes) $(TailOpts) 

$(targetDir)/ClosedLoop.exe : main.o $(objects) Talk2Stage.o
	$(CXX) -o $(targetDir)/ClosedLoop.exe main.o $(objects) Talk2Stage.o $(LinkerWinAPILibObj) $(TailOpts)
	
	
main.o : main.cpp $(3rdPartyLibs)/tisgrabber.h $(3rdPartyLibs)/TISGrabberGlobalDefs.h $(MyLibs)/Talk2DLP.h $(MyLibs)/Talk2Camera.h  $(MyLibs)/TransformLib.h $(MatlabIncDir)/engine.h
	$(CXX) $(CXXFLAGS) main.cpp -I"inc" -I$(MyLibs) $(openCVincludes) -I$(bfIncDir) $(TailOpts) 
	
Talk2DLP.o : $(MyLibs)/Talk2DLP.h $(MyLibs)/Talk2DLP.cpp $(3rdPartyLibs)/alp4basic.lib
	$(CXX) $(CXXFLAGS) $(MyLibs)/Talk2DLP.cpp -I$(MyLibs) -I$(3rdPartyLibs) $(TailOpts)

Talk2Camera.o : $(MyLibs)/Talk2Camera.cpp $(MyLibs)/Talk2Camera.h \
$(3rdPartyLibs)/tisgrabber.h $(3rdPartyLibs)/TISGrabberGlobalDefs.h \
$(3rdPartyLibs)/tisgrabber.lib 
	$(CXX) $(CXXFLAGS) $(MyLibs)/Talk2Camera.cpp -I$(3rdPartyLibs) -ITalk2Camera $(TailOpts)

AndysOpenCVLib.o : $(MyLibs)/AndysOpenCVLib.c $(MyLibs)/AndysOpenCVLib.h 
	$(CXX) $(CXXFLAGS) $(MyLibs)/AndysOpenCVLib.c $(openCVincludes) $(TailOpts)

Talk2Matlab.o : $(MyLibs)/Talk2Matlab.c $(MyLibs)/Talk2Matlab.h 
	$(CXX) $(CXXFLAGS) $(MyLibs)/Talk2Matlab.c $(openCVincludes) -I$(MatlabIncDir) $(TailOpts)

AndysComputations.o : $(MyLibs)/AndysComputations.c $(MyLibs)/AndysComputations.h
	$(CXX) $(CXXFLAGS) $(MyLibs)/AndysComputations.c  $(TailOpts)

TransformLib.o: $(MyLibs)/TransformLib.c
	$(CXX) $(CXXFLAGS) $(MyLibs)/TransformLib.c $(openCVincludes) $(TailOpts)
	
experiment.o: $(MyLibs)/experiment.c $(MyLibs)/experiment.h 
	$(CXX) $(CXXFLAGS) $(MyLibs)/experiment.c $ -I$(MyLibs) $(openCVincludes) -I$(bfIncDir) $(TailOpts)

tictoc.o: $(3rdPartyLibs)/tictoc.cpp $(3rdPartyLibs)/tictoc.h 
	$(CXX) $(CXXFLAGS) $(3rdPartyLibs)/tictoc.cpp $ -I$(3rdPartyLibs)  $(TailOpts)

timer.o: $(3rdPartyLibs)/Timer.cpp $(3rdPartyLibs)/Timer.h 
	$(CXX) $(CXXFLAGS) $(3rdPartyLibs)/Timer.cpp $ -I$(3rdPartyLibs)  $(TailOpts)

IllumWormProtocol.o : $(MyLibs)/IllumWormProtocol.h $(MyLibs)/IllumWormProtocol.c
	$(CXX) $(CXXFLAGS) $(MyLibs)/IllumWormProtocol.c -I$(MyLibs) $(openCVincludes) $(TailOpts)

# if talk to stage causes trouble try compiling without -mwindows flag.
Talk2Stage.o: $(MyLibs)/Talk2Stage.c $(MyLibs)/Talk2Stage.h
	$(CXX) $(CXXFLAGS) $(MyLibs)/Talk2Stage.c -I$(MyLibs)



###### version.c & version.h
# note that version.c is generated at the very top. under "timestamp"
version.o : $(MyLibs)/version.c $(MyLibs)/version.h 
	$(CXX) $(CXXFLAGS) $(MyLibs)/version.c  -I$(MyLibs)  $(TailOpts)

#Trick so that git generates a version.c file
$(MyLibs)/version.c: FORCE 
	$(GIT) rev-parse HEAD | awk ' BEGIN {print "#include \"version.h\""} {print "extern const char * build_git_sha = \"" $$0"\";"} END {}' > $(MyLibs)/version.c
	date | awk 'BEGIN {} {print "extern const char * build_git_time = \""$$0"\";"} END {} ' >> $(MyLibs)/version.c	
		
FORCE:




###### Test.exe
$(targetDir)/Test.exe : test.o $(CVlibs) IllumWormProtocol.o AndysOpenCvLib.o version.o $(TimerLibrary)
	echo "attempting to make executable."
	$(CXX) -o $(targetDir)/Test.exe test.o IllumWormProtocol.o AndysOpenCvLib.o version.o $(TimerLibrary) $(CVlibs) $(TailOpts)

test.o : test.c
	$(CXX) $(CXXFLAGS) test.c -I$(MyLibs) $(openCVincludes) $(TailOpts) 
	echo "Compiling test.c"
	

####### Worm Specific Libraries
WormAnalysis.o : $(MyLibs)/WormAnalysis.c $(MyLibs)/WormAnalysis.h $(myOpenCVlibraries)  
	$(CXX) $(CXXFLAGS) $(MyLibs)/WormAnalysis.c -I$(MyLibs) $(openCVincludes) $(TailOpts)

WriteOutWorm.o : $(MyLibs)/WormAnalysis.c $(MyLibs)/WormAnalysis.h $(MyLibs)/WriteOutWorm.c $(MyLibs)/WriteOutWorm.h $(myOpenCVlibraries) 
	$(CXX) $(CXXFLAGS) $(MyLibs)/WriteOutWorm.c -I$(MyLibs) $(openCVincludes) $(TailOpts)

$(MyLibs)/WriteOutWorm.c :  $(MyLibs)/version.h 



########## framegrabb+DLP only 

#FG_DLP.exe
FG_DLP_objs=  Talk2FrameGrabber.o $(BFObj)  Talk2DLP.o Talk2Stage.o  DontTalk2Camera.o $(3rdPartyLibs)/alp4basic.lib $(hw_ind) 
$(targetDir)/FG_DLP.exe : FG_DLP.o $(FG_DLP_objs)
	$(CXX) -o $(targetDir)/FG_DLP.exe FG_DLP.o $(FG_DLP_objs) $(LinkerWinAPILibObj) $(TailOpts) 

FG_DLP.o : main.cpp  
	$(CXX) $(CXXFLAGS) main.cpp -oFG_DLP.o -I$(MyLibs) -I$(bfIncDir) $(openCVincludes) $(TailOpts)

#Calibrate FG and DLP
$(targetDir)/calibrateFG_DLP.exe : calibrateFG_DLP.o Talk2FrameGrabber.o $(BFObj)  Talk2DLP.o Talk2Stage.o  DontTalk2Camera.o $(3rdPartyLibs)/alp4basic.lib  Talk2Matlab.o $(MatlabLibs) $(hw_ind)
	$(CXX) -o $(targetDir)/calibrateFG_DLP.exe  calibrateFG_DLP.o Talk2FrameGrabber.o $(BFObj)  Talk2DLP.o Talk2Stage.o DontTalk2Camera.o $(3rdPartyLibs)/alp4basic.lib  Talk2Matlab.o  $(MatlabLibs) $(hw_ind) $(LinkerWinAPILibObj) $(TailOpts)

calibrateFG_DLP.o : calibrateFG.cpp 
	$(CXX) $(CXXFLAGS) calibrateFG.cpp -ocalibrateFG_DLP.o -I$(MyLibs) -I$(bfIncDir) -I$(MatlabIncDir) $(openCVincludes) $(TailOpts)


## framegrabberonly FGMindControl.exe
$(targetDir)/FGMindControl.exe : FGMindControl.o DontTalk2DLP.o DontTalk2Camera.o Talk2FrameGrabber.o Talk2Stage.o  $(hw_ind) 
	$(CXX) -o $(targetDir)/FGMindControl.exe FGMindControl.o Talk2FrameGrabber.o $(BFObj)    DontTalk2DLP.o DontTalk2Camera.o Talk2Stage.o $(hw_ind) $(LinkerWinAPILibObj) $(TailOpts) 

FGMindControl.o : main.cpp $(myOpenCVlibraries) $(WormSpecificLibs) 
	$(CXX) $(CXXFLAGS) main.cpp -oFGMindControl.o -I$(MyLibs) -I$(bfIncDir) $(openCVincludes) $(TailOpts)

		
###### VirtualMC.exe
# This is the software suite that does not depend on any hardware. It is hardware independent.
#Write a DontTalk2FrameGrabber.h
$(targetDir)/VirtualMC.exe : VirtualMC.o $(virtual_hardware) $(hw_ind) 
	$(CXX) -o $(targetDir)/VirtualMC.exe VirtualMC.o $(virtual_hardware) $(hw_ind)   $(LinkerWinAPILibObj) $(TailOpts) 

VirtualMC.o : main.cpp $(myOpenCVlibraries) $(WormSpecificLibs) 
	$(CXX) $(CXXFLAGS) main.cpp -oVirtualMC.o -I$(MyLibs) -I$(bfIncDir) $(openCVincludes) $(TailOpts)
	
## Hardware independent hack
DontTalk2Camera.o : $(MyLibs)/DontTalk2Camera.c $(MyLibs)/Talk2Camera.h
	$(CXX) $(CXXFLAGS) $(MyLibs)/DontTalk2Camera.c -I$(MyLibs)  $(TailOpts)

DontTalk2DLP.o : $(MyLibs)/DontTalk2DLP.c $(MyLibs)/Talk2DLP.h
	$(CXX) $(CXXFLAGS) $(MyLibs)/DontTalk2DLP.c -I$(MyLibs)  $(TailOpts)

DontTalk2FrameGrabber.o : $(MyLibs)/DontTalk2FrameGrabber.cpp $(MyLibs)/Talk2FrameGrabber.h
	$(CXX) $(CXXFLAGS) $(MyLibs)/DontTalk2FrameGrabber.cpp -I$(MyLibs) -I$(bfIncDir)  $(TailOpts)

##### BitFlow FrameGrabber based libraries
Talk2FrameGrabber.o: $(MyLibs)/Talk2FrameGrabber.cpp $(MyLibs)/Talk2FrameGrabber.h
	$(CXX) $(CXXFLAGS) $(MyLibs)/Talk2FrameGrabber.cpp -I$(bfIncDir)
	


.PHONY: clean	
clean:
	rm -rf *.o 
	
	
#Partial File List
#### DLP

#OpenCV Libraries have to be available on the environment path.

#fmteos.dll DLL for the encryption software that unlocks the DLL
#alp4basic.dll DLL control library for the DLP


#IMAGING SOURCE SOFTWARE to talk to Camera
#Tisgrabber.lib ImagingSource Statically Linked Library to Control Camera
#tisgrabber.h ImagingSource C wrapper Library header file
#tisgrabberGlobalDefs.h Imaging Source C wrpaper Global Definitions file
#tisgrabber.dll Imgaing Source Dynamically Linked Library

#### DLL's from Imaging Source
#DemoFilters.ftf
#ICFilterContainer.dll
#TIS_DShowLib07_vc71.dll
#TIS_UDSHL07_vc6.dll
#TIS_UDSHL07_vc6.lib
#TIS_UDSHL07_vc71.dll
#TIS_UDSHL07_vc71.lib
#TIS_UDSHL07_vc8.dll
#TIS_UDSHL07_vc8.lib
#dvdevice.vda
#mjpeg.tca
#stdfilters.ftf
#tisdcam.vda
#tisgrabber.dll
#tisgrabber.lib
#uvc_driver.vda
#vcc_vp.vda



### MATLAB
# engine.h    include file for matlab engine
# C:/Progra~1/MATLAB/R2008a/extern/lib/win32/microsoft/libeng.lib    Matlab's libraries to access the matlab engine
# C:/Progra~1/MATLAB/R2008a/extern/lib/win32/microsoft/libmx.lib   Matlab's Libraries to access the matlab engine

