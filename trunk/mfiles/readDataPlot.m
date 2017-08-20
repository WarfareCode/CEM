info = h5info('CEMOutput.h5','/EField');
figure;

for counter = 1:250
    offset = 1 + (counter-1)*info.ChunkSize;
    data = h5read('CEMOutput.h5','/EField',offset,info.ChunkSize);
    plot(data);
    tstring = sprintf('Index: %d',counter);
    title(tstring);
    pause(0.1);
end
