function [data,tt] = readData(timeIndex,varargin)

tGroup = '/Time';
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
tinfo = h5info(fileName,tGroup);
data =[];
timeLength = info.Dataspace.Size/info.ChunkSize;

tt = zeros(timeLength,1);

if (timeIndex > timeLength)
    error('Requested Index exceeds data file length, Requested = %s, Recorded = %s',timeIndex,timeLength);
else
    offset = 1 + (timeIndex-1)*info.ChunkSize;
    data = h5read(fileName,group,offset,info.ChunkSize);
    tt = h5read(fileName,tGroup,timeIndex,1);
    plot(data);
    tstring = sprintf('Time: %0.3f, Index: %d',tt,timeIndex);
    title(tstring);
    xlabel('Spatial Index (m)');
    ylabel('E Field');
end
