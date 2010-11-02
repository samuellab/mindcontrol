function mcdf=readOneFrame(fid)
% ret=readOneFrame(fid)
% This function reads in a frame of data in a YAML file created by
% MindControl. It expects to already be at the line of the first frame (not
% the line with the dash in it) as would be teh cast if seekToFirstFrame()
% had been run previously.
%
% Andrew Leifer
% leifer@fas.harvard.edu
% 2 November 2010

% Read the line after the dash.. this should be a field
tline = fgets(fid); 
mcdf=MCD_FRAME;

sElapsed=[];
msRemElapsed=[];

while ~isEndOfFrame(tline)
    if isField(tline)
        fname=getField(tline);
        switch fname
            case 'FrameNumber'
                [mcdf.FrameNumber tline]=getVal(fid,tline);
            case 'sElapsed'
                [sElapsed tline]=getVal(fid,tline);
            case 'msRemElapsed'
                [msRemElapsed tline]=getVal(fid,tline);
            case 'Head'
                [mcdf.Head tline]=getxy(fid,tline);
            case 'Tail'
                [mcdf.Tail tline]=getxy(fid,tline);
            otherwise
                disp(['fname matched nothing: ',fname])
                tline=fgets(fid);
                
                
        end
        
        
        
    else
        %Advance to the Next Line
        tline=fgets(fid);
    end
    
    
end

mcdf.TimeElapsed=sElapsed+.001*msRemElapsed;
disp('Done')
end

function ret=isEndOfFrame(tline)
%This function checks to see if the line in str represents an end of frame
%character. In this case an end of frame is either another `-` or a
%non-charector which would be indicitave of the end of the file
ret=0;
if ~ischar(tline)
    ret=1;
end

if regexp(tline,'^[ \t\r\n\v\f]*-[ \t\r\n\v\f]*$')
    ret=1;
end

end

function ret=isField(str)
%This function checks to see if this is a field in the form of
% `field:`
%
% If no field is present it returns 0
% If a field is present it returns 1
 if regexp(str,'^[ \t\r\n\v\f]*[a-z,A-Z]*:[ \t\r\n\v\f]')
     ret=1;
 else
     ret=0;
 end

end

function ret=isFieldWithValue(str)
%This function checks to see if this is a field in the form of
% `field: "[349, 345, balh balh`
%
% If no returns 0
% If yes returns 1

if regexp(str,'^[ \t\r\n\v\f]*[a-z,A-Z]*:[ \t\r\n\v\f]*[^ \t\r\n\v\f]+')
    ret=1;
else
    ret=0;
end

end

function fieldName=getField(str)
q=textscan(str,'%q','Delimiter',':');
fieldName=q{1}{1};
end

function [val tline]=getVal(fid,str)
% Functio to parse an integer value
% And increment ot the nextg line
if isFieldWithValue(str)
    tmp=textscan(str,'%s','Delimiter',':');
    val=str2num(tmp{1}{2});
else
    val=NaN;
end
tline=fgets(fid);
end    

function [xy tline] = getxy(fid,tline)
% Get the xy values from a field that has two subfields, x & y

%The current line should be a field with no values, only children
if ~isFieldWithValue(tline)
    %Advance to the next line
    tline=fgets(fid);
    fname= getField(tline);
    while strcmp(fname,'x') || strcmp(fname,'y')
        switch fname
          case 'x'
            [xy(1) tline]=getVal(fid,tline);
            fname= getField(tline);
          case 'y'
            [xy(2) tline]=getVal(fid, tline);
            fname= getField(tline);

        end
    end
            
      
    
else
	%Something was wrong
    xy=NaN;
    end
end

function ij = getij(fid,tline)
end


function data=parseCVseq(fid)
end
