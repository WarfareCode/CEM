function [data,tt] = readAllData(varargin)

tGroup = '/Time';
if nargin == 0
    fileName = 'CEMOutput.h5';
    group = '/EField';
elseif nargin == 1
    fileName = varargin{1};
    group = '/EField';
elseif nargin ==2
    fileName = varargin{1};
    group = varargin{2};
end
 
info = h5info(fileName,group);
tinfo = h5info(fileName,tGroup);
data =[];
tt = [];
timeLength = info.Dataspace.Size./info.ChunkSize;


for counter = 1:timeLength(1)
    [tempData,tt] = readData(counter,fileName,group);
    data = [data; tempData];
end

y = linspace(0,info.ChunkSize(2));

figure
imagesc(tt,y,data);
xlabel('Time (s)')
ylabel('Spatial Index (m)');