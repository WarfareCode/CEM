function [data,tt] = readData(timeIndex,varargin)

if nargin == 1
    fileName = 'CEMOutput.h5';
    group = '/EField';
elseif nargin == 2
    fileName = varargin{1};
    group = '/EField';
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
    data = h5read(fileName,group,offset,info.ChunkSize);
    tt = data(end);
    data = data(1:end-1);
    plot(data);
    tstring = sprintf('Index: %d',timeIndex);
    title(tstring);
    xlabel('Spatial Index (m)');
    ylabel('E Field');
end
