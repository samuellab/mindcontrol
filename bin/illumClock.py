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




#Optical Mind Control Annotation system
#Andrew Leifer
#leifer@fas.harvard.edu
import string, sys, time
import msvcrt #note windows/DOS only

print 'Welcome to the Optical Mind Control Illumination Clock.'


# Handle Command Line Arguments
if len(sys.argv)!=2:
	print 'Optical Mind Control Illumination Clock.\n'
	print 'by Andrew Leifer, leifer@fas.harvard.edu\n\n'
	print 'This script must be run with a command-line argument specifying the location of the recent frame information, which is outputted by the mindcontrol software.\n'
	print '\n\tillumClock.py D:/Path/To/recentframe.txt' 
	sys.exit(0)

recentframefile=sys.argv[1]


#Set the start time
start = time.time()


# Main Loop
while not msvcrt.kbhit(): #While the user doesn't hit any key
	
	time.sleep(0.1)
	#Open the the recent frame file
	try:
		r=open(recentframefile,'r')
	except:
		print '\tError! ' +recentframefile + ' not found!\n'
		continue


	frameInfo=r.readlines()
	r.close()
	
	# We expect there to be exactly four lines.
	# The first line is the frame number
	# The second line is the filename
	# And the third line is the GIT SHA1 version hash
	# And the fourth is an integer value 0 or 1 specifiying whether the DLP is on or not
	if len(frameInfo) != 4: 
		sys.stdout.write('\r' +recentframefile + ' does not have expected format!')
		continue
	
	illumStatus=int(frameInfo[3])
	#If the illumination is on (e.g. 1) reset the timer
	if (illumStatus):
		start=time.time()

	sys.stdout.write('\r\t')
	sys.stdout.write( str( round((time.time()-start),1))  )
	sys.stdout.write('\t\t')


print "\rGood bye!"

