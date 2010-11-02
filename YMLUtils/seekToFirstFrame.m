function ret =seekToFirstFrame(fid)
% This function seeks to the the first frame of a YAML data file produced
% by the MindControl software.
%
% Andrew Leifer
% leifer@fas.harvard.edu
% 11 November 2010

disp('Seeking to first frame of YAML file.');
%Find Where the Frames Begin
k=1;
while 1 
     k=k+1;
     tline = fgets(fid); 
     if ~ischar(tline)
         ret=-1;
         disp('A frame was not found');
         disp(k);
         break
     end
     if regexp(tline,'^[ \t\r\n\v\f]*Frames:[ \t\r\n\v\f]*$')
         disp('Found beginning of frames');
         disp(tline);
         ret=1;
         break;
     end
end
