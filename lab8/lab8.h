#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "windows.h"

using namespace std;

const int amount_of_words_and_symbols = 16;
const int recursion_border_index = -1;

vector<bool> multiplication(vector<bool> term_one, vector<bool> term_two);
bool summary(bool first, bool second);
pair<bool, bool> recursion_compare(vector<bool>& term_one, const vector<bool>& term_two, int position);
bool fromStringToVector(string& input, vector<bool>& output);

class Word
{
    int word_size;
    vector<bool> data;
public:
    Word();
    Word(int size);
    Word(vector<bool>& data);
    void shiftUp();
    void shiftDown();
    string print();
    Word operator*(Word& term);
    Word operator=(Word term);
    bool operator==(Word& term);
    Word operator!();
    bool operator<(Word& term);
    bool operator>(Word& term);
    vector<bool> GetV();
    void SetS();
    friend vector<bool> A_B_summary(Word& term);
};
class AsociatedMemory
{
    vector<Word>table;
public:
    AsociatedMemory();
    void push(int position, vector<bool> term);
    void print();
    void print_diagonalized();
    void F1(int position_one, int position_two);
    void F14(int position_one, int position_two);
    void F3(int position_one, int position_two);
    void F12(int position_one, int position_two);
    void near_above(vector<bool> term);
    void near_below(vector<bool> term);
    void fields_summary(vector<bool>& V);
};
vector<bool> A_B_summary(Word& term);

void my_own_task();
bool Test1();
bool Test2();
bool Test3();
bool Test4();
bool Test5();
bool Test6();
bool Test7();
bool Test8();
bool Test9();
bool Test10();
void tests();
void our_own_input();