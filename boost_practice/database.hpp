/*
    Lab Assignment 1
    cs2910
    Mitchell VanderHoek
    Purpose: Declarations of functions that'll be defined in the database.cpp file.
*/
#ifndef database_hpp
#define database_hpp

#include <boost/algorithm/string.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/map.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::string> REC;
typedef std::map<std::string, std::string> DB;

bool isAttribute(std::string);
int getSchemaSize();
std::string getKeyFieldName();
std::string queryAttribute(std::string, std::string);
void add(std::string, std::string);
void deleteEntry(std::string);
void exportData();
void importData();
void showSchema();
void program();

#endif