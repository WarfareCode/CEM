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
    tempData = h5read('CEMOutput.h5','/EField',offset,info.ChunkSize);
    tt(counter) = tempData(end);
    data = [data tempData(1:end-1)];
end

y = linspace(0,info.ChunkSize);
x = linspace(0,timeLength);

figure
imagesc(x,y,data);
xlabel('Time Index (n)')
ylabel('Spatial Index (m)')