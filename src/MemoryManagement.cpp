#include "MemoryManagement.h"

MemoryManagement& MemoryManagement::get_instance() {
    static MemoryManagement instance;

    return instance;
}

void MemoryManagement::delete_variable(const std::string& variable_name) {
    // Deletes the variable from the map
    MemoryManagement& instance = get_instance();
    instance.m_pointer_map_data.erase(variable_name);
}


void MemoryManagement::display_variables() {
    // Displays the list of variables using the default display method
    std::string complete_list = "";

    MemoryManagement& instance = get_instance();

    /* // Does not work for Embedded Systems
    for (std::map<std::string, std::shared_ptr<std::string&>>::key_type variable_name : instance.m_pointer_map_data){
        complete_list += complete_list + variable_name + "\n";
    }

    // Create a file to output the data.
    std::ofstream output_file("variable_names.txt");

    if(!output_file){
        return;
    }

    output_file << complete_list << "\n";

    output_file.close();*/
}

int MemoryManagement::count_variables() {
    // returns a number representing the number of stored variables in the map
    MemoryManagement& instance = get_instance();
    return instance.m_pointer_map_data.size();
}

void MemoryManagement::create_variable(const std::string& variable_name, const std::string& pointer_value) {
    // This function creates a variable and assigns it to the map. This can be accessed later.

    MemoryManagement& instance = get_instance();
    std::string value_to_insert = pointer_value;
    instance.m_pointer_map_data[variable_name] = std::shared_ptr<std::string>(new std::string(value_to_insert));
}

void MemoryManagement::modify_variable(const std::string& variable_name, const std::string& new_value) {
    //This function will change the value stored in the unique pointer in  the singleton map
}


float MemoryManagement::to_float(std::string& input) {
    // This function will take the string and convert it to a float to return
    // This function will use istringstream and stoi()

    // Shouldn't find spaces for safety purposes. But continue in any case.
    assert(!has_whitespace(input));

    std::istringstream ss(input);
    std::string float_string;
    float float_to_return;
    ss >> float_string;
    if(!float_string.empty()){
        float_to_return = std::stof(float_string);
    }

    return float_to_return;
}

int MemoryManagement::to_int(std::string& input) {
    // This function will take the string and convert it to an integer to return

    // Shouldn't find spaces for safety purposes. But continue in any case.
    assert(!has_whitespace(input));

    std::istringstream ss(input);
    std::string int_string;
    float int_to_return;
    ss >> int_string;
    if(!int_string.empty()){
        int_to_return = std::stoi(int_string);
    }

    return int_to_return;
}


std::string MemoryManagement::get_value(const std::string& variable_name) {
    // This function will retrieve the pointer necessary by using the variable name, but should the variable not exist
    // it will return the empty string
    // MemoryManagement& instance = get_instance();
    auto pointer_to_return = MemoryManagement::get_instance().m_pointer_map_data.at(variable_name);

    return *pointer_to_return;
}

std::string MemoryManagement::lowercase(std::string& input) {
    // This function will return the text in a lowercase variation of the string for case insensitive comparisons.
    
    // Iterate over the input string and change them all to lowercase
    for (auto iter = 0; iter < input.length(); iter++){
        input[iter] = tolower(input[iter]);
    }

    return input;
}

bool MemoryManagement::has_whitespace(std::string& input) {
    // This function will return true should any of the characters in the string contain whitespace
    bool con1 = input.find(' ') != std::string::npos;
    bool con2 = input.find('\t') != std::string::npos;
    bool con3 = input.find('\n') != std::string::npos;
    
    return (con1) || (con2) || (con3);
}
