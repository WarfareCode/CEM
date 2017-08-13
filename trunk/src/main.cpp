/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.                                               *
 * Copyright by the Board of Trustees of the University of Illinois.         *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF5.  The full HDF5 copyright notice, including     *
 * terms governing use, modification, and redistribution, is contained in    *
 * the COPYING file, which can be found at the root of the source code       *
 * distribution tree, or in https://support.hdfgroup.org/ftp/HDF5/releases.  *
 * If you do not have access to either file, you may request a copy from     *
 * help@hdfgroup.org.                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 *   This example shows how to work with extendible dataset.
 *   In the current version of the library dataset MUST be
 *   chunked.
 *
 */

#ifdef OLD_HEADER_FILENAME
#include <iostream.h>
#else
#include <iostream>
#endif
#include <string>
#include <vector>

using std::cout;
using std::endl;

#include <string>
#include <math.h>
#include <algorithm>

#include "DataLogger/DataLogger_HDF5.h"
#include "FDTD_Engine/FDTD_1D.h"
#include "InputParser/InputParser_YAML.h"

#define SIZE 200
 
int main (int argc, char *argv[])
{
    /*
     * Try block to detect exceptions raised by any of the calls inside it
     */
    try
    {
       std::string inputFileName;
       std::string outputFileName;
       InputParserYAML ip;

       //check the inputs
       if (argc == 3)
	 {
	   inputFileName = argv[1];
	   outputFileName = argv[2];
	 }
       else if (argc == 2)
	 {
	   inputFileName = argv[1];
	   outputFileName = "CEMOutput.h5";
	 }
       else if (argc == 1)
	 {
	   inputFileName = "CEMInput.yaml";
	   outputFileName = "CEMOutput.h5";
	 }
       else
	 {
	   std::cout<< "ERROR: " << argc - 1 << " arguments, expecting 0, 1, or 2" << std::endl;
	   exit(1);
	 }


       std::cout << "Executing ... Input File: " << inputFileName << " Output File: " << outputFileName << std::endl;
       DataLoggerHDF5 dLogger;
       dLogger.CreateFile(outputFileName);
        
       FDTD_1D fdtd;
       fdtd.InitializeEngine(SIZE,0,0);
        
       for(int time = 0; time < 250; time++)
       {
         fdtd.UpdateFields(time);
         fdtd.SetEFieldSource(0,time);
         dLogger.WriteDataArray(fdtd.getEField());   
       }
  
        
    }  // end of try block
    
    // catch failure caused by the H5File operations
    catch( FileIException error )
    {
        error.printError();
        return -1;
    }
    
    // catch failure caused by the DataSet operations
    catch( DataSetIException error )
    {
        error.printError();
        return -1;
    }
    
    // catch failure caused by the DataSpace operations
    catch( DataSpaceIException error )
    {
        error.printError();
        return -1;
    }
    
    // catch failure caused by the DataSpace operations
    catch( DataTypeIException error )
    {
        error.printError();
        return -1;
    }
    
    return 0;
}
