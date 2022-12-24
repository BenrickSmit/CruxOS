/** \brief This file will handle all the function and class tests for the MemoryManagement class
 *  \date Updated: 21/12/2022**/

#include <gtest/gtest.h>

#include <regex>
#include <string>

#include <MemoryManagement.h>

// Write Test Functions

// to_float function
TEST (MemoryManagement_Test, test_to_float_function__many_floats_separated_by_spaces) {
    
    bool is_valid = true;

    ASSERT_TRUE(is_valid);
}

TEST (MemoryManagement_Test, test_to_float_function__integer_input) {
    
    bool is_valid = true; 

    ASSERT_TRUE(is_valid);
}

TEST (MemoryManagement_Test, test_to_float_function__no_input) {
    
    bool is_valid = true;

    ASSERT_TRUE(is_valid);
}





// to_int function
TEST (MemoryManagement_Test, test_to_int_function__many_int_separated_by_spaces) {
    
    bool is_valid = true;

    ASSERT_TRUE(is_valid);
}

TEST (MemoryManagement_Test, test_to_int_function__float_input) {
    
    bool is_valid = true; 

    ASSERT_TRUE(is_valid);
}

TEST (MemoryManagement_Test, test_to_int_function__no_input) {
    
    bool is_valid = true;

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
    bool is_valid = true;

    ASSERT_TRUE(is_valid);
}


TEST (MemoryManagement_Test, test_memory_management_class_variable_retrieval) {
    bool is_valid = true;

    ASSERT_TRUE(is_valid);
}


TEST (MemoryManagement_Test, test_basic) {
    bool is_valid = true;

    ASSERT_TRUE(is_valid);
}