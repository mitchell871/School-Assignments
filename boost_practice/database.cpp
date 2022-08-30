/*
    Lab Assignment 1
    cs2910
    Mitchell VanderHoek
    Purpose: To facilitate the manipulation and reading of the database.
*/

#include "database.hpp"

REC strs;
std::string line;
DB orig_map;

/*
    Checks if attribute is found in schema.
    @param string The attribute to check.
*/
bool isAttribute(std::string attribute){

    std::string schema = orig_map["SCHEMA"]; // Retrieve schema string from map.
    REC attributes; // Initialize vector for splitting into component attributes.
    bool found = false; // Is the attribute found?

    
    boost::split(attributes, schema, boost::is_any_of(",")); // Split the string using boost 
    attributes.erase(attributes.begin()); // Take "SCHEMA" out of the attributes section

    // Find if attribute is in the vector
    for(int i = 0; i < attributes.size(); i++){
        if(attribute == attributes[i]){
            found = true;
            break;
        }
    }

    return found;
}

/*
    @return The size of the schema.
*/
int getSchemaSize(){
    std::string schema = orig_map["SCHEMA"]; // Retrieve schema string from map.
    REC attributes;

    boost::split(attributes, schema, boost::is_any_of(",")); // Split string using boost
    attributes.erase(attributes.begin()); // Remove "SCHEMA" from attributes section

    return attributes.size();
}

/*
    Ensure the attribute exists before executing.
    @param string The attribute
    @param string Its id
    @return The attribute queried. 
*/
std::string queryAttribute(std::string attribute, std::string id){
    std::string schema = orig_map["SCHEMA"];
    REC attributes;
    
    // Split and remove schema.
    boost::split(attributes, schema, boost::is_any_of(","));
    attributes.erase(attributes.begin());

    int i; // selected line index.
    for(i = 0; i < attributes.size(); i++) {
        // Found it.
        if(attribute == attributes[i]){
            break;
        }
    }

    std::string output = orig_map[id]; // get contents with id
    std::vector<std::string> selectedLine; // container for splitting
    boost::split(selectedLine, output, boost::is_any_of(",")); // split

    return selectedLine[i];
}

/*
    Gets the second field of the SCHEMA line which should be the name of the
    keyfield.

    @return the second field of the SCHEMA
*/
std::string getKeyFieldName(){
    std::string schema = orig_map["SCHEMA"];
    REC attributes;

    boost::split(attributes, schema, boost::is_any_of(","));

    return attributes[1];
}

/*
    Deletes an entry from the database.
    @param string Delete by id.
*/
void deleteEntry(std::string id){
    orig_map.erase(id);
}

/*
    Adds an entry to the database.
    @param string The key
    @param string Value to add.
*/
void add(std::string key, std::string value){
    std::string newValue = key + "," + value;
    orig_map[key] = newValue;
}

/*
    Gets data from the XML file.
*/
void importData(){
    std::ifstream ifile;

    ifile.open("fred.xml");
    {
        boost::archive::xml_iarchive iarch(ifile);
        iarch & BOOST_SERIALIZATION_NVP(orig_map);
    }

    ifile.close();
}

/*
    Function that exports data to the XML upon closing.
*/
void exportData(){
    std::ofstream ofile;

    ofile.open("fred.xml");
    {
        boost::archive::xml_oarchive oarch(ofile);
        oarch & BOOST_SERIALIZATION_NVP(orig_map);
    }

    ofile.close();
}


/*
    This is where the commands and manipulations are executed from. Includes an initial instruction
    screen displaying the CRUD commands.
*/
void program(){
    std::vector<std::string> menuSelect;

    std::cout << "Welcome" << std::endl << std::endl
              << "Please select an operation by typing it exactly as displyed." << std::endl
              << "Operations should be considered case sensitive." << std::endl 
              << "Options: " << std::endl << std::endl
              << "CLOSE"  << std::endl
              << "DELETE" << std::endl
              << "SELECT" << std::endl
              << "ADD"    << std::endl << std::endl
              << "Type command: ";

    while(getline(std::cin, line)){

        boost::algorithm::to_upper(line); // Use boost to boost the input to uppercase.

        // Tokenizes then stores in menuSelect.
        boost::split(menuSelect, line, boost::is_any_of(" "));

        // Check for whether the user has selected to terminate interaction with the database.
        if (menuSelect[0] == "CLOSE"){
            std::cout << "Exporting data to .xml then closing database." << std::endl;
            exportData(); 
            exit(0);
        }
        /*
            Delete Option

            Delete only works iff the command follows the format: 
                DELETE WHERE KEYFIELD='some keyfield'
            Formality is cofirmed to prevent error.
        */
        else if(menuSelect[0] == "DELETE") {

            // Formality check with a short-circuit.
            if (menuSelect.size() == 3 && menuSelect[1] == "WHERE"){
                std::vector<std::string> keyfield;

                boost::split(keyfield, menuSelect[2], boost::is_any_of("="));

                // Includes prevention for splitting an empty keyfield. Sometimes keyfields can be empty.
                if(keyfield[0] != getKeyFieldName()) {
                    std::cout << "Input invalid. Triggered due to mismatched keyfield names." << std::endl;
                }
                // There was no match for the keyfield.
                else if(orig_map.find(keyfield[1]) == orig_map.end()) {
                    std::cout << "Please type your command with a valid " << getKeyFieldName() << std::endl;
                }
                // Found a match for the keyfield.
                else {
                    
                    std::cout << getKeyFieldName() << "#" << keyfield[1] << " deleted. " << std::endl;
                    deleteEntry(keyfield[1]);
                }

            }
        }
        /*
            SELECT option

            This option can only be used in two ways.
            First : SELECT <fieldnames>
            Second: SELECT <fieldnames> WHERE KEYFIELD='some keyfield'
            Following the formality check, another check is performed for a valid keyfield. Then the validity
            of every word and attribute is confirmed. The length determines how SELECT is used.
        */
        else if (menuSelect[0] == "SELECT") {           
            // Perform size check then check for even number. The size for valid use is 4 or 2.
            if(menuSelect.size() <= 4 && menuSelect.size() % 2 == 0){

                // SELECT <fieldnames>
                if(menuSelect.size() == 2){
                    std::vector<std::string> attributes;

                    boost::split(attributes, menuSelect[1], boost::is_any_of(","));
                    // Iterate through the list of attributes.
                    for(int i = 0; i < attributes.size(); i++){
                        // Attribute must be valid.
                        if(isAttribute(attributes[i])) {
                            std::cout << "Displaying " << attributes[i] << " for all entries:" << std::endl
                                      << "-------------" << std::endl;
                            
                            /* 
                                Create an iterator for iterating through the map. Then output the content
                                of the selected attribute of all the entries.
                            */
                            DB::iterator pos;

                            for(pos = orig_map.begin(); pos!= orig_map.end(); ++pos){
                                // Don't show the SCHEMA in output
                                if(pos->first == "SCHEMA"){
                                    continue;
                                }
                                std::cout << queryAttribute(attributes[i], pos->first) << std::endl;
                            }
                            
                        }
                        // Attribute doesn't exist.
                        else {
                            std::cout << attributes[i] << " is not an attribute." << std::endl;
                        }
                    }
                }
                // SELECT <fieldnames> WHERE KEYFIELD='some keyfield'
                else {
                    std::vector<std::string> attributes;

                    boost::split(attributes, menuSelect[1], boost::is_any_of(","));

                    std::vector<std::string> keyfield; // Store the keyfield

                    boost::split(keyfield, menuSelect[3], boost::is_any_of("="));

                    // Ensure that all the commands follow the rules.
                    if(menuSelect[2] != "WHERE" || keyfield[0] != getKeyFieldName()){
                        std::cout << "Input invalid. Please try again." << std::endl;
                    }
                    // Check keyfield is in map.
                    else if(orig_map.find(keyfield[1]) == orig_map.end()){
                        std::cout << "Type the command again with a valid " 
                                  << getKeyFieldName() << "." << std::endl;
                    }
                    // Found
                    else{
                        std::cout << "Attributes for " << getKeyFieldName() << "#"
                                  << keyfield[1] << std::endl
                                  << "-------------" << std::endl;

                        // Iterate through the attributes while confirming each is valid.
                        for(int i = 0; i < attributes.size(); i++) {
                            // Check if it's in the map.
                            if(isAttribute(attributes[i])) {
                                std::cout << attributes[i] << ": " << queryAttribute(attributes[i], keyfield[1]) << std::endl;
                            }else{    
                                std::cout << attributes[i] << " is not a valid attributes." << std::endl;
                            }
                        }
                    }
                }
            }
            else{
                std::cout << "Input invalid. Type: SELECT <fieldnames> or SELECT <fieldnames> WHERE KEYFIELD='somekeyfield'" << std::endl;
            }
        }
        /*
            ADD option
            
            The ADD command must follow the format: ADD RECORD WHERE KEYFIELD='some keyfield'
            Checks formality then error checks the 4th word of menuSelect to ensure validity.
        */
        else if (menuSelect[0] == "ADD") {
            if(menuSelect.size() != 4 || menuSelect[2] != "WHERE"){
                std::cout << "Input invalid. Ensure format follows: ADD RECORD WHERE KEYFIELD='some keyfield'" << std::endl;
            }
            else{
                std::vector<std::string> keyfield;
                boost::split(keyfield, menuSelect[3], boost::is_any_of("="));
                std::vector<std::string> attributes;
                boost::split(attributes, menuSelect[1], boost::is_any_of(","));

                // Store as lowercase.
                boost::algorithm::to_lower(menuSelect[1]);

                // The keyfield hasn't been added to the string yet.
                if(attributes.size() != (getSchemaSize() - 1)) {
                    std::cout << "Record attributes do not match SCHEMA's size." << std::endl;
                }
                else{
                    // Grab 'some keyfield' and check if it is in the map.
                    if(keyfield[0] != getKeyFieldName()) {
                        std::cout << "Input invalid. Keyfield name mismatch." << std::endl;
                    }
                    // It wasn't found, so a new entry is created.
                    else if(orig_map.find(keyfield[1]) == orig_map.end()){
                        add(keyfield[1], menuSelect[1]);
                        std::cout << menuSelect[1] << " has been added to record " << getKeyFieldName() << "#" << keyfield[1] << std::endl;
                    }
                    // Found, so the existing entry is updated.
                    else {
                        add(keyfield[1], menuSelect[1]);
                        std::cout << "Updated the record" << getKeyFieldName() << "#" << keyfield[1] << std::endl;
                    }
                }
            }
        }
        else if(menuSelect[0] == "SCHEMA"){
            showSchema();
        }
        else{
            std::cout << "Input invalid. Try again" << std::endl;
        }

        std::cout << "Type a command: ";
    }

}

/*
    This shows the format of the SCHEMA.
*/
void showSchema(){
    std::string schema = orig_map["SCHEMA"];
    REC attributes;

    boost::split(attributes, schema, boost::is_any_of(","));

    attributes.erase(attributes.begin());
    schema = boost::algorithm::join(attributes, ",");

    std::cout << schema << std::endl;
}

int main() {
    importData();
    program();
    return 0;
}