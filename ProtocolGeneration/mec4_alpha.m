%% Notes
% Tip of HEAD is (0, 0). 
% Tail is (99,0)
%
% 
% Pictorially:
%      (-10,0)  (0,0)  (10,0)
%             Head
%                ^ 
%              /  \
%             /    \
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             \    /
%              \  /
%               \/
%             Tail  
%        (-10,99)  (0,99)  (10,99)
%
%
%    y
%    ^
%    |     (axis)
%    |
%    ------------> x
%
% Note also, you can walk off the worm in y (but not in x).


clear all; close all;


% Header informatoin
filename='mec4_alpha.yml';
gridHeight=100;
gridWidth=5; %must be odd
%Note: No carriage return at the end of the description
description= sprintf('This protocol is designed to illuminate posterior and anterior systematically and dorsal ventral, so as to cover different regions of the mec-4 circuit.');



% Protocol = [x1, y1, x2,y2, etc..]
r=3; %radius to a little bit outside of the worm
HEAD=0;
TAIL=99;
CENTERLINE=0;

neckregion=35;
middle=50
midbottom=75;


%predefine protocol
protocol=cell(0);


%whole worm
protocol{end+1}=rect(-r, HEAD, r, TAIL);

%neck region
protocol{end+1}=rect(-r, HEAD , r, neckregion);

%tail
protocol{end+1}=rect(-r, midbottom, r, TAIL);

%neck to mid region
protocol{end+1}=rect(-r, neckregion, r, middle);

%mid region to midbottom
protocol{end+1}=rect(-r ,middle, r, midbottom);


%ventral/dorsal A
protocol{end+1}=rect(-r, HEAD, CENTERLINE-1, TAIL);

%ventral/dorsal B
protocol{end+1}=rect(CENTERLINE+1, HEAD,  r, TAIL);


writeProto(filename,description,gridWidth,gridHeight,protocol)

figure;
for n=1:length(protocol)
plotProtocol(protocol{n},gridHeight,gridWidth)
pause
end


