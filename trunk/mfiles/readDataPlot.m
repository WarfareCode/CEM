info = h5info('CEMOutput.h5','/EField');
chunkSize = info.ChunkSize;
totalSize = info.Dataspace.Size;
totalEntries = totalSize./chunkSize;

offsetIndex = find(totalEntries ~= 1);
if (length(offsetIndex) ~=1)
    error('Read Error: Expected offset does not match ... size: %d, expected: 1',length(offsetIndex));
end
dataIndex = find(totalEntries == 1);

figure;
offset = [0 0];
for counter = 1:totalEntries
    offset(dataIndex) = 1;
    offset(offsetIndex) = counter;

    data = h5read('CEMOutput.h5','/EField',offset,chunkSize);
    plot(data);
    tstring = sprintf('Index: %d',counter);
    title(tstring);
    pause(0.1);
end
