/*
    Lab Assignment 1
    cs2910
    Mitchell VanderHoek
    Purpose: This performs the initial intake from the csv file to populate the
             xml file.
    Source:  FRANCO
*/

#include "database.hpp"

REC strs;
std::string line;
DB orig_map;

void dumpDict( DB d) {
   for ( auto &e :d ) {
         std::cout << e.first;
		   std::cout << "<" << e.second << ">";
         std::cout << std::endl;
   }
}

int main() {

   while (std::getline(std::cin, line) ) {
      boost::split(strs,line,boost::is_any_of(",;:"));
      
      // add a record to database
            
      orig_map[strs[0]] = boost::algorithm::join(strs, ",");
   }	
   /*
      serialize map as an XML document
   */
   std::cout << "Dumping map" << std::endl << "---------" << std::endl << std::endl;
   dumpDict(orig_map);   
   std::ofstream ofile;
   ofile.open("fred.xml");
   {
      boost::archive::xml_oarchive oarch(ofile);
      oarch & BOOST_SERIALIZATION_NVP (orig_map);
   }
   ofile.close();
}