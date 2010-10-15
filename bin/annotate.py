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
import string, sys

from optparse import OptionParser
usage = "usage: %prog [options] recentFrameInfo.txt output.yml\n\nOptical Mind Control annotation engine\nby Andrew Leifer, leifer@fas.harvard.edu"
parser = OptionParser(usage)
parser.add_option("-u", "--user", action="store", type="string", dest="user", default="default", help="specify a username")
(options, args)=parser.parse_args()


if len(args) !=2:
	print 'Error: incorrect number of arguments'	
	parser.print_help()
	sys.exit(2)


#Main 
print 'Welcome to the Optical Mind Control annotation system.'




recentframefile=args[0]
outfile=args[1]


s =''
prevExperiment=''
prevFrame=''

# Main Loop
while (s!='q'): #While the user doesn't quit
	s=raw_input('Enter annotation (q to quit):\n')
	if (s=='q'):
		continue
	
	newExperiment=False
	

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
		print '\tError! ' +recentframefile + ' does not have expected format!\n'
		continue

	if ( (prevFrame!=frameInfo[0].strip()) ):
		newFrame=True
	else:
		newFrame=False

	prevFrame=frameInfo[0].strip()
	
	#If the user just hit enter, don't do anything.
	if (s==''):
		continue
	out= open(outfile,'a')
	#If this is a new experiment, set up the new experiment
	if prevExperiment!=frameInfo[1].strip():
		out.write('---\nExperiment:\n\tFile: "'+frameInfo[1].strip()+'"\n\tVersion: "'+frameInfo[2].strip()+'"\n')
		out.write('\tAuthor: "' + options.user +'"\n')
		out.write('\tAnnotations:\n')
		prevExperiment=frameInfo[1].strip()
		newExperiment=True
		firstGenAnnote=True


	#If the frame number has incremented since last time 
	if ( newFrame==True ):
		out.write('\t\t- Frame: ' + frameInfo[0].strip()+ '\n\t\t  Description: "'+s+'"\n')
		print '\tFrame ' +frameInfo[0].strip() +  ' recorded.'

	else:
		if (firstGenAnnote==True):
			out.write('\tOverview:\n')
			firstGenAnnote=False
		out.write('\t\t- Description: "'+s+'"\n')
		print 'Experiment overview recorded.'
	out.close()


print "Good bye!"

