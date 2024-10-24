#pragma once
#ifndef STATES_H 
#define STATES_H

#include <iostream>
#include <string>

using namespace std;

class State {
private:
    string name;
    string capital;
    string government;
    string language;
    string religion;
    int area;
    long long population;
    string continent;
public:
    // Getters
    const string get_name();
    const string get_capital();
    const string get_government();
    const string get_language();
    const string get_religion();
    const int get_area();
    const long long get_population();
    const string get_continent();

    // Setters
    void set_name(string VALUE);
    void set_capital(string VALUE);
    void set_government(string VALUE);
    void set_language(string VALUE);
    void set_religion(string VALUE);
    void set_area(int VALUE);
    void set_population(long long VALUE);
    void set_continent(string VALUE);

    // Constructors
    State();
    State(string set_name, string set_capital, string set_government, string set_language, string set_religion, int set_area, long long set_population, string set_continent);
    State(const State& STACK);

    // Methods
    bool initFromFile(ifstream& infile);

    // Operators
    bool operator==(const State& other) const;
    bool operator!=(const State& other) const;
    friend ostream& operator<<(ostream& os, State& state);
    friend istream& operator>>(istream& is, State& state);
};

// Another Functions
int getStatesCount(const string FILE_PATH);
int getUserAction();
#endif