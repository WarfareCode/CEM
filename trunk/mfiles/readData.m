function data = readData(timeIndex,varargin)

if nargin == 1
    fileName = 'CEMOutput.h5';
    group = '/Ex';
elseif nargin == 2
    fileName = varargin{1};
    group = '/Ex';
elseif nargin == 3
    fileName = varargin{1};
    group = varargin{2};
end

info = h5info(fileName,group);
data =[];

timeLength = info.Dataspace.Size/info.ChunkSize;

if (timeIndex > timeLength)
    error('Requested Index exceeds data file length, Requested = %s, Recorded = %s',timeIndex,timeLength);
else
    offset = 1 + (timeIndex-1)*info.ChunkSize;
    data = h5read('CEMOutput.h5','/Ex',offset,info.ChunkSize);
    plot(data);
    tstring = sprintf('Index: %d',timeIndex);
    title(tstring);
    xlabel('Spatial Index (m)');
    ylabel('E Field');
end
