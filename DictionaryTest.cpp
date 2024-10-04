/*
 Name - Vaishnavi Jaligama
 Student Id- 1936593
 Cruz id - vjaligam
 Course - CSE101
 Quarter - Winter 2024
 Professor - Mr. Patrick Tantalo
 Programming assignment - 8
 Due date - March 13th, 2024
 File name - DictionaryTest.h
*/

#include "Dictionary.h"
#include <iostream>
#include <cassert>
#include <string>

void testConstructors() {
    Dictionary dict;
    assert(dict.size() == 0 && "Default constructor test failed.");

    dict.setValue("hello", 1);
    Dictionary copyDict(dict);
    assert(copyDict.size() == 1 && "Copy constructor test failed.");
    assert(copyDict.contains("hello") && "Copy constructor test failed.");
}

void testAssignmentOperator() {
    Dictionary dict;
    dict.setValue("hello", 1);
    Dictionary assignDict;
    assignDict = dict;
    assert(assignDict.size() == 1 && "Assignment operator test failed.");
    assert(assignDict.contains("hello") && "Assignment operator contains test failed.");
}

void testSizeAndClear() {
    Dictionary dict;
    dict.setValue("hello", 1);
    dict.setValue("world", 2);
    assert(dict.size() == 2 && "Size test failed.");
    dict.clear();
    assert(dict.size() == 0 && "Clear test failed.");
}

void testSetValueAndGetValue() {
    Dictionary dict;
    dict.setValue("hello", 1);
    assert(dict.getValue("hello") == 1 && "SetValue/GetValue test failed.");
    dict.setValue("hello", 2);
    assert(dict.getValue("hello") == 2 && "SetValue update test failed.");
}

void testRemove() {
    Dictionary dict;
    dict.setValue("hello", 1);
    dict.remove("hello");
    assert(!dict.contains("hello") && "Remove test failed.");
}

void testContains() {
    Dictionary dict;
    dict.setValue("hello", 1);
    assert(dict.contains("hello") && "Contains true test failed.");
    assert(!dict.contains("world") && "Contains false test failed.");
}

void testIteration() {
    Dictionary dict;
    dict.setValue("a", 1);
    dict.setValue("b", 2);
    dict.setValue("c", 3);
    dict.begin();
    assert(dict.currentKey() == "a" && "Begin test failed.");
    dict.next();
    assert(dict.currentKey() == "b" && "Next test failed.");
    dict.prev();
    assert(dict.currentKey() == "a" && "Prev test failed.");
    dict.end();
    assert(dict.currentKey() == "c" && "End test failed.");
}

int main() {
    testConstructors();
    testAssignmentOperator();
    testSizeAndClear();
    testSetValueAndGetValue();
    testRemove();
    testContains();
    testIteration();

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}

/*
Expected Output -
All tests passed successfully.
*/