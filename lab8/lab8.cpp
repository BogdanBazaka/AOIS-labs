#include "lab8.h"

vector<bool> multiplication(vector<bool> term_one, vector<bool> term_two)
{
    if (term_one.size() < term_two.size()) {
        while (term_one.size() != term_two.size())
        {
            term_one.insert(term_one.begin(), 0);
        }
    }
    else if (term_one.size() > term_two.size()) {
        while (term_one.size() != term_two.size())
        {
            term_two.insert(term_one.begin(), 0);
        }
    }
    vector<bool> result;
    for (int i = 0; i < term_one.size(); i++)
    {
        result.push_back(term_one[i] * term_two[i]);
    }
    return result;
}
bool summary(bool first, bool second)
{
    if (first && second) return true;
    else return (first + second);
}
pair<bool, bool> recursion_compare(vector<bool>& term_one, const vector<bool>& term_two, int position)
{
    pair<bool, bool> result;
    if (position == recursion_border_index) {
        result.first = false;
        result.second = false;
        return result;
    }
    else {
        pair<bool, bool> previous_result = recursion_compare(term_one, term_two, position - 1);
        result.first = summary(previous_result.first, !term_one[position] * term_two[position] * !previous_result.second);
        result.second = summary(previous_result.second, term_one[position] * !term_two[position] * !previous_result.first);
        return result;
    }
}
bool fromStringToVector(string& input, vector<bool>& output)
{
    output.clear();
    if (input.size() != amount_of_words_and_symbols) return false;
    for (int i = 0; i < amount_of_words_and_symbols; i++)
    {
        if (input[i] == '1') output.push_back(true);
        else if (input[i] == '0') output.push_back(false);
        else {
            output.clear();
            return false;
        }
    }
    return true;
}

Word::Word() {}
Word::Word(int size) : word_size(size)
{
    srand(time(NULL));
    for (int i = 0; i < word_size; i++)
    {
        int positive_sign = rand() % 2;
        if (positive_sign == 1) {
            data.push_back(true);
        }
        else {
            data.push_back(false);
        }
    }
    Sleep(1000);
}
Word::Word(vector<bool>& data) : word_size(data.size())
{
    this->data = data;
}
void Word::shiftUp()
{
    if (word_size == 0) return;
    bool temp = data[data.size() - 1];
    data.erase(data.begin() + (data.size() - 1));
    data.insert(data.begin(), temp);
}
void Word::shiftDown()
{
    if (word_size == 0) return;
    bool temp = data[0];
    data.erase(data.begin());
    data.insert(data.begin() + data.size(), temp);
}
string Word::print()
{
    string result;
    for (int i = 0; i < word_size; i++)
    {
        if (data[i]) result.push_back('1');
        else result.push_back('0');
    }
    return result;
}
Word Word::operator*(Word& term)
{
    vector<bool> output = multiplication(data, term.data);
    Word result(output);
    return result;
}
Word Word::operator!()
{
    vector<bool> output;
    for (int i = 0; i < word_size; i++)
    {
        output.push_back(!data[i]);
    }
    Word result(output);
    return result;
}
Word Word::operator=(Word term)
{
    data = term.data;
    word_size = term.word_size;
    return *this;
}
bool Word::operator==(Word& term)
{
    if (data == term.data) return true;
    return false;
}
bool Word::operator<(Word& term)
{
    pair<bool, bool> example = recursion_compare(data, term.data, data.size() - 1);
    if (example.first && !example.second) return true;
    else return false;
}
bool Word::operator>(Word& term)
{
    pair<bool, bool> example = recursion_compare(data, term.data, data.size() - 1);
    if (!example.first && example.second) return true;
    else return false;
}
vector<bool> Word::GetV()
{
    vector<bool> result;
    int V_border = 3;
    for (int i = 0; i < V_border; i++)
    {
        result.push_back(data[i]);
    }
    return result;
}
void Word::SetS()
{
    vector<bool> insertion = A_B_summary(*this);
    int s_border = 11;
    for (int i = s_border; i < data.size(); i++)
    {
        data.erase(data.begin() + i);
        data.insert(data.begin() + i, insertion[i - s_border]);
    }
}
vector<bool> A_B_summary(Word& term)
{
    vector<bool> term_one, term_two, result;
    int A_first = 3, A_second = 7, B_first = 7, B_second = 11;
    bool mind = false;
    for (int i = A_first; i < A_second; i++)
    {
        term_one.push_back(term.data[i]);
    }
    for (int i = B_first; i < B_second; i++)
    {
        term_two.push_back(term.data[i]);
    }
    for (int i = term_one.size() - 1; i >= 0; i--)
    {
        if (term_one[i] && term_two[i] && mind) {
            result.insert(result.begin(), true);
        }
        else if (term_one[i] && term_two[i] && !mind) {
            result.insert(result.begin(), false);
            mind = true;
        }
        else if (((!term_one[i] && term_two[i]) || (term_one[i] && !term_two[i])) && mind) {
            result.insert(result.begin(), false);
        }
        else if (((!term_one[i] && term_two[i]) || (term_one[i] && !term_two[i])) && !mind) {
            result.insert(result.begin(), true);
        }
        else if (!term_one[i] && !term_two[i] && !mind) {
            result.insert(result.begin(), false);
        }
        else if (!term_one[i] && !term_two[i] && mind) {
            result.insert(result.begin(), true);
            mind = false;
        }
    }
    result.insert(result.begin(), mind);
    return result;
}

AsociatedMemory::AsociatedMemory()
{
    table.resize(amount_of_words_and_symbols);
    for (int i = 0; i < amount_of_words_and_symbols; i++)
    {
        Word example(amount_of_words_and_symbols);
        table[i] = example;
    }
}
void AsociatedMemory::push(int position, vector<bool> term)
{
    if (position > amount_of_words_and_symbols - 1 || position < 0) return;
    if (term.size() != amount_of_words_and_symbols) return;
    table.insert(table.begin() + position, term);
    table.erase(table.begin() + table.size() - 1);
}
void AsociatedMemory::print()
{
    cout << "Table : " << endl << "-------------------------------------" << endl;
    for (int i = 0; i < table.size(); i++)
    {
        cout << "word[" << i << "] = " << table[i].print() << endl;
    }
    cout << "-------------------------------------" << endl;
}
void AsociatedMemory::print_diagonalized()
{
    vector<Word> example = table;
    cout << "Diagonalized table : " << endl << "-------------------------------------" << endl;
    for (int i = 0; i < example.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            example[i].shiftUp();
        }
        cout << "word[" << i << "] = " << example[i].print() << endl;
    }
    cout << "-------------------------------------" << endl;
}
void AsociatedMemory::F1(int position_one, int position_two)
{
    if (position_one < 0 || position_one > amount_of_words_and_symbols - 1) return;
    if (position_two < 0 || position_two > amount_of_words_and_symbols - 1) return;
    Word example = table[position_one] * table[position_two];
    cout << "F1(word[" << position_one << "], word[" << position_two << "]) = " << example.print() << endl;
}
void AsociatedMemory::F3(int position_one, int position_two)
{
    if (position_one < 0 || position_one > amount_of_words_and_symbols - 1) return;
    if (position_two < 0 || position_two > amount_of_words_and_symbols - 1) return;
    cout << "F3(word[" << position_one << "], word[" << position_two << "]) = " << table[position_one].print() << endl;
}
void AsociatedMemory::F12(int position_one, int position_two)
{
    if (position_one < 0 || position_one > amount_of_words_and_symbols - 1) return;
    if (position_two < 0 || position_two > amount_of_words_and_symbols - 1) return;
    Word example = !table[position_one];
    cout << "F12(word[" << position_one << "], word[" << position_two << "]) = " << example.print() << endl;
}
void AsociatedMemory::F14(int position_one, int position_two)
{
    if (position_one < 0 || position_one > amount_of_words_and_symbols - 1) return;
    if (position_two < 0 || position_two > amount_of_words_and_symbols - 1) return;
    Word example = !(table[position_one] * table[position_two]);
    cout << "F14(word[" << position_one << "], word[" << position_two << "]) = " << example.print() << endl;
}
void AsociatedMemory::near_above(vector<bool> term)
{
    vector<bool>near_current_vector(term.size(), true);
    Word example(term), near_current(near_current_vector);
    bool overlap = false;
    for (int i = 0; i < table.size(); i++)
    {
        if ((table[i] < near_current || table[i] == near_current) && (table[i] > example || table[i] == example)) {
            near_current = table[i];
            overlap = true;
        }
    }
    if (!overlap) {
        cout << "Nothing found compare with this above!" << endl;
    }
    else {
        cout << "Nearest word above found : " << near_current.print() << endl;
    }
}
void AsociatedMemory::near_below(vector<bool> term)
{
    vector<bool>near_current_vector(term.size(), false);
    Word example(term), near_current(near_current_vector);
    bool overlap = false;
    for (int i = 0; i < table.size(); i++)
    {
        if ((table[i] > near_current || table[i] == near_current) && (table[i] < example || table[i] == example)) {
            near_current = table[i];
            overlap = true;
        }
    }
    if (!overlap) {
        cout << "Nothing found compare with this below!" << endl;
    }
    else {
        cout << "Nearest word below found : " << near_current.print() << endl;
    }
}
void AsociatedMemory::fields_summary(vector<bool>& V)
{
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i].GetV() == V) {
            table[i].SetS();
        }
    }
}

void my_own_task()
{
    AsociatedMemory memory;
    bool flag = true;
    string word;
    int choice, position_one, position_two;
    vector<bool> example, v1{ 1,1,1 }, v2{ 0,0,0 }, test{ 0,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,1 };
    while (flag)
    {
        cout << "Enter 1)Push :: 2)Print :: 3)Print diagonalized :: 4)F1, F3, F12, F14 :: 5)Near_above :: 6)Near_below :: 7)fields summary :: 8)All :: 9)Finish : ";
        cin >> choice;
        switch (choice)
        {
        case 1: cout << "Enter position for insertion : ";
            cin >> position_one;
            cout << "Enter line with " << amount_of_words_and_symbols << " elements : ";
            cin >> word;
            if (!fromStringToVector(word, example))
            {
                cout << "Enter something possible to work with!" << endl;
                return;
            }
            memory.push(position_one, example);
            example.clear();
            break;
        case 2:
            memory.print();
            break;
        case 3:
            memory.print_diagonalized();
            break;
        case 4:
            cout << "Enter positions for insertion : ";
            cin >> position_one;
            cin.ignore();
            cin >> position_two;
            memory.F1(position_one, position_two);
            memory.F3(position_one, position_two);
            memory.F12(position_one, position_two);
            memory.F14(position_one, position_two);
            break;
        case 5:
            cout << "Enter line with " << amount_of_words_and_symbols << " elements : ";
            cin >> word;
            if (!fromStringToVector(word, example))
            {
                cout << "Enter something possible to work with!" << endl;
                return;
            }
            memory.near_above(example);
            example.clear();
            break;
        case 6:
            cout << "Enter line with " << amount_of_words_and_symbols << " elements : ";
            cin >> word;
            if (!fromStringToVector(word, example))
            {
                cout << "Enter something possible to work with!" << endl;
                return;
            }
            memory.near_below(example);
            example.clear();
            break;
        case 7: cout << "For V = 111 and 000 done!" << endl;
            memory.fields_summary(v1);
            memory.fields_summary(v2);
            break;
        case 8:
            cout << "For positions 4 and 12 and search above/below for 01011110111011011: " << endl;
            position_one = 4;
            position_two = 12;
            memory.print();
            memory.print_diagonalized();
            memory.F1(position_one, position_two);
            memory.F3(position_one, position_two);
            memory.F12(position_one, position_two);
            memory.F14(position_one, position_two);
            memory.near_above(test);
            memory.near_below(test);
            memory.fields_summary(v1);
            memory.fields_summary(v2);
            break;
        case 9: flag = false;
            break;;
        default:
            cout << endl << "Enter something possible to work with!" << endl;
            return;
        }
    }

}
bool Test1()
{
    vector<bool> A{ 0, 0, 0, 0 }, S{ 0,0,0,1 };
    pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
    if (compare_result.first && !compare_result.second) {
        cout << "Test1 correct!" << endl;
        return true;
    }
    else {
        cout << "Test1 incorrect!" << endl;
        return false;
    }
}
bool Test2()
{
    vector<bool> A{ 0, 1, 1, 1 }, S{ 0,0,0,1 };
    pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
    if (!compare_result.first && compare_result.second) {
        cout << "Test2 correct!" << endl;
        return true;
    }
    else {
        cout << "Test2 incorrect!" << endl;
        return false;
    }
}
bool Test3()
{
    vector<bool> A{ 0, 0, 0, 1 }, S{ 0,0,0,1 };
    pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
    if (!compare_result.first && !compare_result.second) {
        cout << "Test3 correct!" << endl;
        return true;
    }
    else {
        cout << "Test3 incorrect!" << endl;
        return false;
    }
}
bool Test4()
{
    vector<bool> A{ 1, 1, 1, 1 }, S{ 0,1,1,1 };
    pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
    if (!compare_result.first && compare_result.second) {
        cout << "Test4 correct!" << endl;
        return true;
    }
    else {
        cout << "Test4 incorrect!" << endl;
        return false;
    }
}
bool Test5()
{
    vector<bool> A{ 1, 1, 1, 1 }, S{ 1,1,1,1 };
    pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
    if (!compare_result.first && !compare_result.second) {
        cout << "Test5 correct!" << endl;
        return true;
    }
    else {
        cout << "Test5 incorrect!" << endl;
        return false;
    }
}
bool Test6()
{
    vector<bool> A{ 0, 1, 0, 0, 0, 0 }, S{ 0,0,1,1,1,0 };
    pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
    if (!compare_result.first && compare_result.second) {
        cout << "Test6 correct!" << endl;
        return true;
    }
    else {
        cout << "Test6 incorrect!" << endl;
        return false;
    }
}
bool Test7()
{
    vector<bool> A{ 1, 1, 0, 0, 0, 0 }, S{ 1,1,0,0,0,0 };
    pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
    if (!compare_result.first && !compare_result.second) {
        cout << "Test7 correct!" << endl;
        return true;
    }
    else {
        cout << "Test7 incorrect!" << endl;
        return false;
    }
}
bool Test8()
{
    vector<bool> A{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, S{ 1,0,0,0,0,0,0,0,0,0 };
    pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
    if (compare_result.first && !compare_result.second) {
        cout << "Test8 correct!" << endl;
        return true;
    }
    else {
        cout << "Test8 incorrect!" << endl;
        return false;
    }
}
bool Test9()
{
    vector<bool> A{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, S{ 0,1,1,1,1,1,1,1,1,1 };
    pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
    if (!compare_result.first && !compare_result.second) {
        cout << "Test9 correct!" << endl;
        return true;
    }
    else {
        cout << "Test9 incorrect!" << endl;
        return false;
    }
}
bool Test10()
{
    vector<bool> A{ 0, 1, 1, 1, 1, 0, 1, 1, 1, 1 }, S{ 0,1,1,1,1,1,1,1,1,1 };
    pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
    if (compare_result.first && !compare_result.second) {
        cout << "Test10 correct!" << endl;
        return true;
    }
    else {
        cout << "Test10 incorrect!" << endl;
        return false;
    }
}
void tests()
{
    int correct_counter = 0;
    correct_counter += Test1();
    correct_counter += Test2();
    correct_counter += Test3();
    correct_counter += Test4();
    correct_counter += Test5();
    correct_counter += Test6();
    correct_counter += Test7();
    correct_counter += Test8();
    correct_counter += Test9();
    correct_counter += Test10();
    if (correct_counter == 10) {
        cout << "All tests passed correctly!" << endl;
    }
}
void our_own_input()
{
    int choice;
    cout << "1)Tests :: 2)Task  : ";
    cin >> choice;
    switch (choice)
    {
    case 1: tests();
        break;
    case 2: my_own_task();
        break;
    default:
        cout << "Enter something possible to work with!" << endl;
        return;
    }
}
