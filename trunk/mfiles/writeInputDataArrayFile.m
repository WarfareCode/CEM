function  writeInputDataArrayFile( fileName,datasetname, inputArray,varargin)
%writeInputDataArrayFile( fileName,datasetname, inputArray)
%writes an unchunked data set to the file

if (nargin == 4)
    deleteFile = varargin{1}
else
    deleteFile = false;
   
if (deleteFile && exist(fileName))
    delete(fileName);
end

if (datasetname(1) ~= '/')
    datasetname = char(strcat({'/'},{datasetname}));
end

h5create(fileName,datasetname,length(inputArray));
h5write(fileName,datasetname,inputArray);
end


