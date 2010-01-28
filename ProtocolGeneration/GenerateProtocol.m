%% Notes
% Tip of head is (0, 0). 
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



%% Header informatoin
filename='crudeRasterScan.yml';
description= 'This protocol consists of a crude rasterscan. It divides the worms up into 10 by 4 segmants.';
gridHeight=99;
gridWidth=9;

%% Guts
%Fundamental unit

primitive=[0,0, 1,0, 1,9, 0,9];

mvLATERAL=[1,0, 1,0 ,1,0, 1,0];
mvHEADTAIL=[0,10, 0,10, 0,10, 0,10];

current=primitive-4*mvLATERAL;
m=1;

for j=1:10
    protocol{m}=current;

    for k=1:7     
        m=m+1;
        current=current+mvLATERAL
        protocol{m}=current;
    end
    current=current-7*mvLATERAL; %reset lateral position
    current=current+mvHEADTAIL %increment head position
    m=m+1;
end

figure;
for n=1:length(protocol)
plotProtocol(protocol{n},gridHeight,gridWidth)
pause
end

writeProto('rasterProto.yml','First raster scan',gridWidth,gridHeight,protocol)
