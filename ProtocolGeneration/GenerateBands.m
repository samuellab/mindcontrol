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
filename='BandsProto.yml';
description= '20percent Bands incremented by 10percent.';
gridHeight=100; %Note these are zero indexed, so the largets coordinate should be 99
gridWidth=21;
%% Guts
%Fundamental unit

primitive=[-20,0, 20,0, 20,20, -20,20];

%mvLATERAL=[1,0, 1,0 ,1,0, 1,0];
mvHEADTAIL=[0,10, 0,10, 0,10, 0,10];



protocol{1}= primitive - [0,0,  0,0,   0,10, 0,10  ]
for j=2:11
    protocol{j}=min(99,primitive+(j-2).*mvHEADTAIL);
end


figure;
for n=1:length(protocol)
plotProtocol(protocol{n},gridHeight,gridWidth)
pause
end

writeProto(filename,description,gridWidth,gridHeight,protocol)