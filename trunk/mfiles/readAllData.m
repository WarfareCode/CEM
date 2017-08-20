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
timeLength = info.Dataspace.Size/info.ChunkSize;

tt = zeros(timeLength,1);

for counter = 1:timeLength
    offset = 1 + (counter-1)*info.ChunkSize;
    tempData = h5read(fileName,group,offset,info.ChunkSize);
    tt(counter) = h5read(fileName,tGroup,1,1);
    data = [data tempData];
end

y = linspace(0,info.ChunkSize);

figure
imagesc(tt,y,data);
xlabel('Time (s)')
ylabel('Spatial Index (m)');