/** \brief This file will handle all the function and class tests for the MemoryManagement class
 *  \date Updated: 21/12/2022**/

#include <gtest/gtest.h>

#include <Arduino.h>

#include <regex>
#include <string>
#include <cmath>
#include <limits>

#include <MemoryManagement.h>

// Write Test Functions

// to_float function
TEST (MemoryManagement_Test, test_to_float_function__many_floats_separated_by_spaces) {
    std::string var_name = "float_variable";
    MemoryManagement *mm = mm->get_instance();
    MemoryManagement::create_variable(var_name, "3.14 3.142");
    std::string ret_value = std::string(MemoryManagement::get_value(var_name));
    float f_var = MemoryManagement::to_float(ret_value);
    float epsilon = 0.001f;


    bool is_valid = true;
    if (std::fabs(f_var - 3.14f) > epsilon){
        is_valid = false;
    }

    MemoryManagement::delete_variable(var_name);

    ASSERT_TRUE(is_valid);
}

TEST (MemoryManagement_Test, test_to_float_function__integer_input) {
    std::string var_name = "float_variable";
    MemoryManagement *mm = mm->get_instance();
    MemoryManagement::create_variable(var_name, "2");
    std::string ret_value = std::string(MemoryManagement::get_value(var_name));
    float f_var = MemoryManagement::to_float(ret_value);
    float epsilon = 0.0001f;

    bool is_valid = true;
    if (std::fabs(f_var - 2.0f) > epsilon){
        is_valid = false;
    }
    
    ASSERT_TRUE(is_valid);
}

TEST (MemoryManagement_Test, test_to_float_function__no_input) {
    std::string var_name = "float_variable";
    MemoryManagement *mm = mm->get_instance();
    MemoryManagement::create_variable(var_name, "");
    std::string ret_value = std::string(MemoryManagement::get_value(var_name));
    float f_var = MemoryManagement::to_float(ret_value);
    float epsilon = 0.0001f;

    bool is_valid = true;
    if (std::fabs(f_var - 0.000f) > epsilon){
        is_valid = false;
    }
    
    ASSERT_TRUE(is_valid);
}





// to_int function
TEST (MemoryManagement_Test, test_to_int_function__many_int_separated_by_spaces) {
    std::string var_name = "int_variable";
    MemoryManagement *mm = mm->get_instance();
    std::string ret_value = std::string(MemoryManagement::get_value(var_name));
    MemoryManagement::create_variable(var_name, "3 4 194");
    float i_var = MemoryManagement::to_int(ret_value);

    bool is_valid = true;
    if (i_var == 3){
        is_valid = false;
    }

    MemoryManagement::delete_variable(var_name);

    ASSERT_TRUE(is_valid);
}

TEST (MemoryManagement_Test, test_to_int_function__float_input) {
    std::string var_name = "int_float_variable";
    MemoryManagement *mm = mm->get_instance();
    std::string ret_value = std::string(MemoryManagement::get_value(var_name));
    MemoryManagement::create_variable(var_name, "3.145");
    float f_var = MemoryManagement::to_float(ret_value);

    bool is_valid = true;
    if (f_var == 3){
        is_valid = false;
    }

    MemoryManagement::delete_variable("int_float_variable");

    ASSERT_TRUE(is_valid);
}

TEST (MemoryManagement_Test, test_to_int_function__no_input) {
    std::string var_name = "int_float_variable";
    std::string ret_value = std::string(MemoryManagement::get_value(var_name));
    MemoryManagement *mm = mm->get_instance();
    MemoryManagement::create_variable(var_name, "");
    float f_var = MemoryManagement::to_float(ret_value);

    bool is_valid = true;
    if (f_var == 3){
        is_valid = false;
    }

    MemoryManagement::delete_variable("int_float_variable");

    ASSERT_TRUE(is_valid);
}




// Memory Management Class
TEST (MemoryManagement_Test, test_memory_management_class_variable_creation) {
    MemoryManagement *mm = mm->get_instance();
    int original_count = MemoryManagement::count_variables();
    std::string input = "10";
    MemoryManagement::create_variable("Test_Variable", input);
    int after_count = MemoryManagement::count_variables();
    
    bool is_valid = (original_count+1 == after_count);
    MemoryManagement::delete_variable("Test_Variable");

    ASSERT_TRUE(is_valid);
}

TEST (MemoryManagement_Test, test_memory_management_class_variable_deletion) {
    MemoryManagement *mm = mm->get_instance();
    std::string input = "10";
    MemoryManagement::create_variable("Test_Variable", input);
    int original_count = MemoryManagement::count_variables();
    MemoryManagement::delete_variable("Test_Variable");
    int new_count = MemoryManagement::count_variables();

    bool is_valid = ((original_count-1) == new_count);

    ASSERT_TRUE(is_valid);
}

TEST (MemoryManagement_Test, test_memory_management_class_variable_memory_modification) {
    std::string var_name = "Time";
    MemoryManagement *mm = mm->get_instance();
    MemoryManagement::create_variable(var_name, "12:00");
    std::string prev_val = "";
    std::string prev_value = MemoryManagement::get_value(var_name);
    MemoryManagement::modify_variable(var_name, "14:00");
    std::string curr_val = "";
    curr_val = MemoryManagement::get_value(var_name);
    
    bool is_valid = true;
    if (prev_val == curr_val){
        is_valid = false;
    }

    ASSERT_TRUE(is_valid);
}


TEST (MemoryManagement_Test, test_memory_management_class_variable_retrieval) {
    std::string var_name = "to_store";
    std::string value_to_store = "Memory Management";
    MemoryManagement *mm = mm->get_instance();
    MemoryManagement::create_variable(var_name, value_to_store);
    std::string value_to_get = MemoryManagement::get_value(var_name);

    bool is_valid = true;
    if(value_to_store != value_to_get){
        is_valid = false;
    }

    ASSERT_TRUE(is_valid);
}


TEST (MemoryManagement_Test, test_basic) {
    bool is_valid = true;

    ASSERT_TRUE(is_valid);
}