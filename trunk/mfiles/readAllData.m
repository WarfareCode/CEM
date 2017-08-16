function data = readAllData(varargin)

if nargin == 0
    fileName = 'CEMOutput.h5';
    group = '/Ex';
elseif nargin == 1
    fileName = varargin{1};
    group = '/Ex';
elseif nargin ==2
    fileName = varargin{1};
    group = varargin{2};
end
 
info = h5info(fileName,group);
data =[];

timeLength = info.Dataspace.Size/info.ChunkSize;

for counter = 1:timeLength
    offset = 1 + (counter-1)*info.ChunkSize;
    tempData = h5read('CEMOutput.h5','/Ex',offset,info.ChunkSize);
    data = [data tempData];
end

y = linspace(0,info.ChunkSize);
x = linspace(0,timeLength);

figure
imagesc(x,y,data);
xlabel('Time Index (n)')
ylabel('Spatial Index (m)')