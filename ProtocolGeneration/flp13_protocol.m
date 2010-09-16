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
filename='flip13_ventral.yml';
gridHeight=100;
gridWidth=21; %must be odd
%Note: No carriage return at the end of the description
description= sprintf('Heuristic ventral illumination of DD motor neurons.');


%Index notation
X=1; Y=2;

%Defualt Radii
dRad(X)=5;
dRad(Y)=37;

%We have to convert from the slider bar manual illumination coordinate convention
%To the protocol illumiantion convention.
annoyingXOffset=-10;
%Neuron centroid & radii
VentralNerveCord(X)=3+annoyingXOffset;
VentralNerveCord(Y)=57;

%predefine protocol
protocol=cell(0);

% Protocol = [x1, y1, x2,y2, etc..]

%VentralNerveCord
protocol{end+1}=rect(VentralNerveCord(X)-dRad(X), VentralNerveCord(Y)-dRad(Y), VentralNerveCord(X)+dRad(X), VentralNerveCord(Y)+dRad(Y) );

% %ALM
% protocol{end+1}=rect(ALM(X)-dRad(X), ALM(Y)-dRad(Y), ALM(X)+dRad(X), ALM(Y)+dRad(Y) );
% 
% %PVM
% protocol{end+1}=rect(PVM(X)-dRad(X), PVM(Y)-dRad(Y), PVM(X)+dRad(X), PVM(Y)+dRad(Y) );
% 
% %PLM
% protocol{end+1}=rect(PLM(X)-dRad(X), PLM(Y)-dRad(Y), PLM(X)+dRad(X), PLM(Y)+dRad(Y) );
% 


writeProto(filename,description,gridWidth,gridHeight,protocol)

figure;
for n=1:length(protocol)
plotProtocol(protocol{n},gridHeight,gridWidth)
pause
end


