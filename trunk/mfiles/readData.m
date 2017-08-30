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

chunkSize = info.ChunkSize;
totalSize = info.Dataspace.Size;
totalEntries = totalSize./chunkSize;


if (timeIndex > totalEntries)
    error('Requested Index exceeds data file length, Requested = %s, Recorded = %s',timeIndex,totalEntries);
end
    
offsetIndex = find(totalEntries ~= 1);
if (length(offsetIndex) ~=1)
    error('Read Error: Expected offset does not match ... size: %d, expected: 1',length(offsetIndex));
end

dataIndex = find(totalEntries == 1);
offset(dataIndex) = 1;
offset(offsetIndex) = timeIndex;
data = h5read(fileName,group,offset,chunkSize);
tt = h5read(fileName,tGroup,timeIndex,1);

