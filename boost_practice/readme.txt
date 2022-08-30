----------------------------------------------------------------------------------
                            Lab ASsignment 1
----------------------------------------------------------------------------------

Name: Mitchell VanderHoek
Course: CS2910 Winter 2022
Date: 2021 Febuary 04

----------------------------------------------------------------------------------
                            Description
----------------------------------------------------------------------------------

This program reads in a database stores as a CSV(comma seperated values) file that
turns its contents into a STL map and serialized it as an XML document using the
BOOST library. Once created, the database can be read or modified by executing 
commands following the CRUD convention(create, read, update and delete). 

Example reads the .csv file then outputs it to an XML. Database reads that XML file
and creates a CPP map so it may be manipulated using the Command Line Interface.

----------------------------------------------------------------------------------
                            Limitations
----------------------------------------------------------------------------------

The name of the XML file is hardcoded between example and database, so fred.xml is
the only .xml file that can be used without modifying the source of both programs.

The SCHEMA in the .csv file must be in all uppercase. 
Example of a SCHEMA: SCHEMA,ID,FNAME,LNAME,MAJOR

----------------------------------------------------------------------------------
                    Provided Files & Requirements
----------------------------------------------------------------------------------


Included:   db.csv
            fred.XML
            example.cpp
            makefile
            readme.txt
            database.hpp

This program uses the BOOST library. I have only tested it while also having it
installed. Additionally, this program has only been tested in Ubuntu 20.14.

----------------------------------------------------------------------------------
                        Build Instructions
----------------------------------------------------------------------------------

I have provided a makefile to make compilation easier. Compilation is done using
GCC. Flags are: -g -std=c++11 -lboost_serialization. You may use the "make clean"
functionality to delete the .exe and .o files.

The following is enter into the command line:

To compile, type:       make

In this order, type:    ./example < db.csv      
                        ./database

You must at least perform the first step before running the database in order to
populate the XML file.

To make clean, type:    make clean