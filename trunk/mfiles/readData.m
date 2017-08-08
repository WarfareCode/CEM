info = h5info('MyTest.h5','/Ex');
figure;

for counter = 1:250
    offset = 1 + (counter-1)*info.ChunkSize;
    data = h5read('MyTest.h5','/Ex',offset,info.ChunkSize);
    plot(data);
    tstring = sprintf('Index: %d',counter);
    title(tstring);
    pause(0.1);
end