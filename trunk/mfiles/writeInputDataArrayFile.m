function  writeInputDataArrayFile( fileName,datasetname, inputArray)
%writeInputDataArrayFile( fileName,datasetname, inputArray)
%writes an unchunked data set

if (exist(fileName))
    delete(fileName);
end

if (datasetname(1) ~= '/')
    datasetname = char(strcat({'/'},{datasetname}));
end

h5create(fileName,datasetname,length(inputArray));
h5write(fileName,datasetname,inputArray);
end


