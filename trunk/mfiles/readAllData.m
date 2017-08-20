function [data,tt] = readAllData(varargin)

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
data =[];
tt = [];
timeLength = info.Dataspace.Size/info.ChunkSize;

for counter = 1:timeLength
    offset = 1 + (counter-1)*info.ChunkSize;
    tempData = h5read(fileName,group,offset,info.ChunkSize);
    data = [data tempData];
end

y = linspace(0,info.ChunkSize);

figure
imagesc(tt,y,data);
xlabel('Time (s)')
ylabel('Spatial Index (m)')