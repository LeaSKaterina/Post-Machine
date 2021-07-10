//
// Created by HP on 23.09.2020.
//

#ifndef POSTMACHINE_TESTS_H
#define POSTMACHINE_TESTS_H

#include "PostMachineLibrary.h"

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <cstdio>
#include <vector>

using namespace std;

const char NAME1[] = "Input1.txt"; //увеличить число на 1
const char NAME2[] = "Input2.txt"; //разность двух (большее - меньшее)
const char NAME3[] = "Input3.txt"; //сумма двух (но ошибка с вводом в ленте)


TEST_CASE() {
    SECTION("Testing the \"inputFromFile\" function.") {
        PostMachine machine;
        REQUIRE(machine.inputFromFile(NAME1));
        REQUIRE(machine.getActionOfCommand(1) == MOVE_TO_THE_RIGHT);
        REQUIRE(machine.getIndexOfNextCommand(2) == 301);
    }SECTION("Testing the \"Input3.txt\" file with an input error.") {
        PostMachine machine;
        REQUIRE(machine.run(NAME3));
    }SECTION("Testing the implementation of the algorithm from file \"Input1.txt\".") {
        PostMachine machine;
        machine.run(NAME1);
        vector<int> result = {1, 1, 1, 0, 0};
        REQUIRE(result == machine.getTape());
    }SECTION("Testing the implementation of the algorithm from file \"Input2.txt\".") {
        PostMachine machine;
        machine.run(NAME2);
        vector<int> result = {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
        REQUIRE(result == machine.getTape());
    }SECTION("Testing the \"setNewTape\" function with an input error.") {
        PostMachine machine;
        vector<int> newTape = {0, 0, 11, 1, 0};
        machine.setNewTape(newTape);
        REQUIRE(machine.setNewTape(newTape));
    }SECTION("Testing the \"setNewTape\" function") {
        PostMachine machine;
        vector<int> newTape = {1, 1, 1, 0, 0, 0, 0};
        machine.setNewTape(newTape);
        REQUIRE(machine.getTape() == newTape);
    }SECTION("Testing the \"setNewTape\" function for a single-cell tape.") {
        PostMachine machine;
        vector<int> newTape = {1};
        machine.setNewTape(newTape);
        REQUIRE(machine.getTape() == newTape);
    }SECTION("Testing the \"setNewTape\" function with an element \"01\".") {
        PostMachine machine;
        vector<int> newTape = {1, 01, 1};
        machine.setNewTape(newTape);
        REQUIRE(machine.getTape() == newTape);
    }SECTION("Testing the \"addTheRule\" function with the invalid index of command.") {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 7;
        REQUIRE(machine.addTheRule(index, STOP));
    }SECTION("Testing the \"addTheRule\" function with an input error.") {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 2;
        REQUIRE(machine.addTheRule(index, '1'));
    }SECTION("Testing the \"addTheRule\" function for the branching.") {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 4;
        machine.addTheRule(index, BRANCHING, 3, 6);
        REQUIRE(machine.getActionOfCommand(index) == BRANCHING);
        REQUIRE(machine.getIndexOfNextCommand(index) == 306);
    }SECTION("Testing the \"addTheRule\" function for all commands except branching.") {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 6;
        machine.addTheRule(index, MOVE_TO_THE_LEFT);
        REQUIRE(machine.getActionOfCommand(index) == MOVE_TO_THE_LEFT);
    }SECTION("Testing the \"editTheRule\" function for all commands except branching.") {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 2;
        machine.editTheRule(index, MOVE_TO_THE_LEFT);
        REQUIRE(machine.getActionOfCommand(index) == MOVE_TO_THE_LEFT);
    }SECTION("Testing the \"editTheRule\" function for branching.") {
        PostMachine machine;
        machine.inputFromFile(NAME2);
        const int index = 2;
        machine.editTheRule(index, BRANCHING, 1, 3);
        REQUIRE(machine.getActionOfCommand(index) == BRANCHING);
    }SECTION("Testing the \"editTheRule\" function with an input error.") {
        PostMachine machine;
        machine.inputFromFile(NAME2);
        const int index = 3;
        REQUIRE(machine.editTheRule(index, 'A'));
    }SECTION("Testing the \"editTheRule\" function with the invalid index of command.") {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 9;
        REQUIRE(machine.editTheRule(index, PUT_MARK));
    }SECTION("Testing the \"editTheRule\" function for the branching with a non-existent link.") {
        PostMachine machine;
        machine.inputFromFile(NAME2);
        const int index = 4;
        REQUIRE(machine.editTheRule(index, BRANCHING, 0, 11));
    }SECTION("Testing the \"deleteTheRule\" function for all commands except branching.") {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 2;
        machine.deleteTheRule(index);
        REQUIRE(machine.getActionOfCommand(index) == MOVE_TO_THE_LEFT);
    }SECTION("Testing the \"deleteTheRule\" function for branching.") {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 1;
        machine.deleteTheRule(index);
        REQUIRE(machine.getActionOfCommand(index) == BRANCHING);
    }SECTION("Testing the \"deleteTheRule\" function for all commands except branching.") {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 4;
        machine.deleteTheRule(index);
        REQUIRE(machine.getActionOfCommand(index) == STOP);
    }SECTION("Testing the \"deleteTheRule\" function for the last command.") {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 5;
        machine.deleteTheRule(index);
        REQUIRE(machine.getActionOfCommand(index) == NULL_ACTION);
    }SECTION("Testing the \"deleteTheRule\" function with invalid index of command.") {
        PostMachine machine;
        machine.inputFromFile(NAME2);
        const int index = 18;
        REQUIRE(machine.deleteTheRule(index));
    }SECTION("Testing the \"changeMarkOnTape\" function with the invalid index of cell.") {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 8;
        REQUIRE(machine.changeMarkOnTape(index));
    }SECTION("Testing the \"changeMarkOnTape\" function with a negative index of cell.") {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = -1;
        REQUIRE(machine.changeMarkOnTape(index));
    }SECTION("Testing the \"changeMarkOnTape\" function for the 1st cell.") {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 1;
        machine.changeMarkOnTape(index);
        REQUIRE(machine.getTape()[index - 1] == 1);
    }SECTION("Testing the \"changeMarkOnTape\" function for the unmarked cell.") {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 5;
        machine.changeMarkOnTape(index);
        REQUIRE(machine.getTape()[index - 1] == 1);
    }SECTION("Testing the \"changeMarkOnTape\" function for the marked cell.") {
        PostMachine machine;
        machine.inputFromFile(NAME2);
        const int index = 7;
        machine.changeMarkOnTape(index);
        REQUIRE(machine.getTape()[index - 1] == 0);
    }SECTION(
            "Testing the \"showTheRules\" function by demonstration of machine's state before and after realisation of \"deleteTheRule\" function.") {
        PostMachine machine;
        machine.inputFromFile(NAME2);
        const int index = 4;
        machine.showTheRules();
        cout << "\nDelete the 4th command.\n\n";
        machine.deleteTheRule(index);
        REQUIRE(machine.getActionOfCommand(index) == MOVE_TO_THE_RIGHT);
        machine.showTheRules();
    }SECTION("Realisation with the step-by-step demonstration of the algorithm implementation.") {
        PostMachine machine;
        REQUIRE(machine.runWithTheStepByStepDemonstration(NAME1));
    }
}

#endif //POSTMACHINE_TESTS_H
