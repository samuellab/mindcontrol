#This is the makefile for the entire OpticalMindControl Project.
#There are a number of executibles here. See the line marked Executables for a list of them all.
# At the moment this includes: 
#   CalibrateApparatus.exe -> Calibrates the position of the camera relative to the DLP. 
#   ClosedLoop.exe   ->   Run's the Apparatus in a closed loop, imaging while projecting (formerly RunApparatus)
#	VirtualMC.exe -> 	Same as ClosedLoop.exe except compiled without camera or DLP dependent libraries. 
#						Thus it must be run in simulation mode.

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
GIT=C:/Program\ Files/Git/bin/git

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
hw_ind= version.o AndysComputations.o AndysOpenCVLib.o TransformLib.o IllumWormProtocol.o $(WormSpecificLibs) $(TimerLibrary) $(CVlibs)

#Virtual HArdware Libraries
virtual_hardware =DontTalk2DLP.o DontTalk2Camera.o DontTalk2FrameGrabber.o 


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



$(targetDir)/CalibrateApparatus.exe : $(calib_objects)
	$(CXX) -o $(targetDir)/CalibrateApparatus.exe $(calib_objects) $(TailOpts)

calibrate.o : calibrate.c $(3rdPartyLibs)/tisgrabber.h $(3rdPartyLibs)/TISGrabberGlobalDefs.h $(MyLibs)/Talk2DLP.h $(MyLibs)/Talk2Camera.h $(MatlabIncDir)/engine.h
	$(CXX) $(CXXFLAGS) calibrate.c -I"inc" -I$(MyLibs) $(openCVincludes) $(TailOpts) 

$(targetDir)/ClosedLoop.exe : main.o $(objects)
	$(CXX) -o $(targetDir)/ClosedLoop.exe main.o $(objects) $(TailOpts)
	
	
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
Talk2STage.o: $(MyLibs)/Talk2Stage.c $(MyLibs)/Talk2Stage.h
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
	$(CXX) -o $(targetDir)/Test.exe Test.o IllumWormProtocol.o AndysOpenCvLib.o version.o $(TimerLibrary) $(CVlibs) $(TailOpts)

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
$(targetDir)/FG_DLP.exe : FG_DLP.o FGMindControl.o Talk2FrameGrabber.o $(BFObj)  Talk2DLP.o   DontTalk2Camera.o $(3rdPartyLibs)/alp4basic.lib $(hw_ind)  
	$(CXX) -o $(targetDir)/FG_DLP.exe FGMindControl.o Talk2FrameGrabber.o $(BFObj)  Talk2DLP.o   DontTalk2Camera.o $(3rdPartyLibs)/alp4basic.lib $(hw_ind) $(LinkerWinAPILibObj) $(TailOpts) 

FG_DLP.o : main.cpp  
	$(CXX) $(CXXFLAGS) main.cpp -oFG_DLP.o -I$(MyLibs) -I$(bfIncDir) $(openCVincludes) $(TailOpts)

#Calibrate FG and DLP
$(targetDir)/calibrateFG_DLP.exe : calibrateFG_DLP.o Talk2FrameGrabber.o $(BFObj)  Talk2DLP.o  $(3rdPartyLibs)/alp4basic.lib  Talk2Matlab.o $(MatlabLibs) $(hw_ind)
	$(CXX) -o $(targetDir)/calibrateFG_DLP.exe  calibrateFG_DLP.o Talk2FrameGrabber.o $(BFObj)  Talk2DLP.o   $(3rdPartyLibs)/alp4basic.lib  Talk2Matlab.o  $(MatlabLibs) $(hw_ind) $(TailOpts)

calibrateFG_DLP.o : calibrateFG.cpp 
	$(CXX) $(CXXFLAGS) calibrateFG.cpp -ocalibrateFG_DLP.o -I$(MyLibs) -I$(bfIncDir) -I$(MatlabIncDir) $(openCVincludes) $(TailOpts)

#
##Calibrate FG and Stage
#calibrateStageObjs= calibratestage.o Talk2Stage.o Talk2FrameGrabber.o $(BFObj) AndysOpenCVLib.o AndysComputations.o $(LinkerWinAPILibObj)
#
#$(targetDir)/calibrateStage.exe : $(calibrateStageObjs)
#	$(CXX) -o $(targetDir)/calibrateStage.exe $(calibrateStageObjs)
#	
#calibrateStage.o : calibrateStage.c 
#	$(CXX) $(CXXFLAGS) calibrateStage.c -ocalibrateFG_DLP.o -I$(MyLibs) -I$(bfIncDir)  $(openCVincludes) $(TailOpts)

## framegrabberonly FGMindControl.exe
$(targetDir)/FGMindControl.exe : FGMindControl.o DontTalk2DLP.o DontTalk2Camera.o $(hw_ind) 
	$(CXX) -o $(targetDir)/FGMindControl.exe FGMindControl.o Talk2FrameGrabber.o $(BFObj)    DontTalk2DLP.o DontTalk2Camera.o $(hw_ind) $(LinkerWinAPILibObj) $(TailOpts) 

FGMindControl.o : main.cpp $(myOpenCVlibraries) $(WormSpecificLibs) 
	$(CXX) $(CXXFLAGS) main.cpp -oFGMindControl.o -I$(MyLibs) -I$(bfIncDir) $(openCVincludes) $(TailOpts)

		
###### VirtualMC.exe
# This is the software suite that does not depend on any hardware. It is hardware independent.
#Write a DontTalk2FrameGrabber.h
$(targetDir)/VirtualMC.exe : VirtualMC.o $(virtual_hardware) $(hw_ind) 
	$(CXX) -o $(targetDir)/VirtualMC.exe VirtualMC.o $(virtual_hardware) $(hw_ind)  $(TailOpts) 

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
	
	
#File List
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

