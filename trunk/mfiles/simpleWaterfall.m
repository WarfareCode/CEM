function  simpleWaterfall( data )

data = data';
offset = 1;
scale = 1.9;
plot(scale*data(1,:),'b');
hold on
for i=2:size(data,1)
    plot(scale*data(i,:) + offset*(i-1),'b');
end
end

