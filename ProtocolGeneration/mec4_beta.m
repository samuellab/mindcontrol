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
filename='mec4_beta.yml';
gridHeight=100;
gridWidth=21; %must be odd
%Note: No carriage return at the end of the description
description= sprintf('Illuminate ALM, AVM, PLM, PVM, first attempt. This is based off fluorescent imaging data taken in D:\WormIllum\100521\Analysis\worm11');





%Index notation
X=1; Y=2;

%Defualt Radii
dRad(X)=6;
dRad(Y)=4;

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



writeProto(filename,description,gridWidth,gridHeight,protocol)

figure;
for n=1:length(protocol)
plotProtocol(protocol{n},gridHeight,gridWidth)
pause
end


