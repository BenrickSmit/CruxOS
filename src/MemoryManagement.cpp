#include "MemoryManagement.h"

MemoryManagement *MemoryManagement::m_instance = nullptr;

MemoryManagement* MemoryManagement::get_instance() {
    if (!m_instance){
        m_instance = new MemoryManagement();
    }

    return m_instance;
}

void MemoryManagement::delete_variable(const std::string& variable_name) {
    // Deletes the variable from the map
    MemoryManagement* instance = get_instance();
    instance->m_pointer_map_data.erase(variable_name);
}


void MemoryManagement::display_variables() {
    // Displays the list of variables using the default display method
    std::string complete_list = "";

    MemoryManagement* instance = get_instance();

    /* // Does not work for Embedded Systems
    for (std::map<std::string, std::shared_ptr<std::string&>>::key_type variable_name : instance->m_pointer_map_data){
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
    MemoryManagement* instance = get_instance();
    return instance->m_pointer_map_data.size();
}

void MemoryManagement::create_variable(const std::string& variable_name, const std::string& pointer_value) {
    // This function creates a variable and assigns it to the map. This can be accessed later.

    MemoryManagement* instance = get_instance();
    std::string value_to_insert = pointer_value;
    instance->m_pointer_map_data[variable_name] = std::shared_ptr<std::string>(new std::string(value_to_insert));
}

void MemoryManagement::modify_variable(const std::string& variable_name, const std::string& new_value) {
    //This function will change the value stored in the unique pointer in  the singleton map
    // Find the variable if it exists and then modify the data.
    auto iterator = get_instance()->m_pointer_map_data.find(variable_name.c_str());

    if (iterator != get_instance()->m_pointer_map_data.end()) {
        *get_instance()->m_pointer_map_data[variable_name.c_str()] = new_value.c_str();
    }else{
        std::string output = "MM_VAR_FIND_ISSUE: Variable \'"+variable_name+"\' not found";
        Serial.println(output.c_str());
    }
}


float MemoryManagement::to_float(std::string& input) {
    // This function will take the string and convert it to a float to return
    // This function will use istringstream and stoi()

    // Shouldn't find spaces for safety purposes. But continue in any case.
    //assert(!has_whitespace(input));

    std::istringstream ss(clean_string(input));
    std::string float_string;
    float float_to_return;
    ss >> float_string;                             // This takes care of any separated values
    if(!float_string.empty()){
        float_to_return = std::stof(float_string);
    } else if(has_alpha(input)){
        float_to_return = std::numeric_limits<float>::min();
    } else {
        // If it is empty just set it to zero
        float_to_return = 0.0f;
    }

    return float_to_return;
}

int MemoryManagement::to_int(std::string& input) {
    // This function will take the string and convert it to an integer to return

    // Shouldn't find spaces for safety purposes. But continue in any case.
    //assert(!has_whitespace(input));

    std::istringstream ss(clean_string(input));
    std::string int_string;
    float int_to_return;
    ss >> int_string;
    if(!int_string.empty()){
        int_to_return = std::stoi(int_string);
    } else if(has_alpha(input)){
        int_to_return = std::numeric_limits<int>::min();
    } else {
        // If it is empty just set it to zero
        int_to_return = 0;
    }

    return int_to_return;
}


std::string MemoryManagement::get_value(const std::string& variable_name) {
    // This function will retrieve the pointer necessary by using the variable name, but should the variable not exist
    // it will return the empty string
    // MemoryManagement* instance = get_instance();
    std::shared_ptr<std::string> pointer_to_return;
    // Find the variable if it exists and then return the data.
    auto iterator = get_instance()->m_pointer_map_data.find(variable_name.c_str());

    if (iterator != get_instance()->m_pointer_map_data.end()) {
        pointer_to_return = get_instance()->m_pointer_map_data.at(variable_name);
    }else{
        pointer_to_return = std::make_shared<std::string>();
        std::string output = "\nMM_VAR_FIND_ISSUE: Variable \'"+variable_name+"\' not found\n";
        output += output + "\t - Possible Reasons:\n";
        output += output + "\t\t - Variable not yet declared?\n";
        output += output + "\t\t - Variable name mispelled?\n";
        Serial.println(output.c_str());
    }

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

bool MemoryManagement::has_alpha(std::string& input) {
    return std::all_of(input.begin(), input.end(), isalpha);
}

std::string MemoryManagement::clean_string(std::string &input){
  // find the position of the comma if it exists, otherwise return the whole string
  auto pos = input.find_first_of(", ");
  if (pos == std::string::npos) {
    // No comma found, return the whole string
    return input;
  } else {
    // Return the substring up to the first comma or space
    return input.substr(0, pos);
  }

}
