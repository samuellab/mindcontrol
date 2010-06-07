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
filename='mec4_combined.yml';
gridHeight=100;
gridWidth=21; %must be odd
%Note: No carriage return at the end of the description
description= sprintf('Illuminate ALM, AVM, PLM, PVM, anterior processes, posterior processes, whole worm, anterior, posterior.');





%Index notation
X=1; Y=2;

%Defualt Radii
dRad(X)=6;
dRad(Y)=4;

r=12;  %radius to a little bit outside of the worm
HEAD=0;
TAIL=99;

%We have to convert from the slider bar manual illumination coordinate convention
%To the protocol illumiantion convention.
annoyingXOffset=-10;
%Neuron centroid & radii
AVM(X)=13+annoyingXOffset;
AVM(Y)=34;

ALM(X)=annoyingXOffset+7;
ALM(Y)=42

PVM(X)=annoyingXOffset+11;
PVM(Y)=66;

PLM(X)=annoyingXOffset+12;
PLM(Y)=90;



%predefine protocol
protocol=cell(0);

% Protocol = [x1, y1, x2,y2, etc..]

%AVM
protocol{end+1}=rect(AVM(X)-dRad(X), AVM(Y)-dRad(Y), AVM(X)+dRad(X), AVM(Y)+dRad(Y) );

%ALM
protocol{end+1}=rect(ALM(X)-dRad(X), ALM(Y)-dRad(Y), ALM(X)+dRad(X), ALM(Y)+dRad(Y) );

%PVM
protocol{end+1}=rect(PVM(X)-dRad(X), PVM(Y)-dRad(Y), PVM(X)+dRad(X), PVM(Y)+dRad(Y) );

%PLM
protocol{end+1}=rect(PLM(X)-dRad(X), PLM(Y)-dRad(Y), PLM(X)+dRad(X), PLM(Y)+dRad(Y) );

%anterior processes
protocol{end+1}=rect(-r, AVM(Y)-dRad(Y), r, HEAD);

%posterior processes
protocol{end+1}=rect(-r, PLM(Y)-dRad(Y),r,PVM(Y)+dRad(Y));



%% Include more broad illumination from protocol mec4_alpha.m
r; %radius to a little bit outside of the worm
HEAD;
TAIL;
CENTERLINE=0;

neckregion=ALM(Y)+dRad(Y);
midbottom=PVM(Y)-dRad(Y);

%whole worm
protocol{end+1}=rect(-r, HEAD, r, TAIL);

%neck region
protocol{end+1}=rect(-r, HEAD , r, neckregion);

%tail
protocol{end+1}=rect(-r, midbottom, r, TAIL);






writeProto(filename,description,gridWidth,gridHeight,protocol)

figure;
for n=1:length(protocol)
plotProtocol(protocol{n},gridHeight,gridWidth)
pause
end


