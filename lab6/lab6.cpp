#include "lab6.h"

void Table_Note::print()
{
    cout << "------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Key word : " << key_word <<
        " | Hash : " << hash <<
        " | Numerical key word : " << numeral_key_word <<
        " | C : " << collision <<
        " | D : " << D <<
        " | U : " << U <<
        " | T : " << T <<
        " | next : " << next <<
        endl << "Data : " << data << endl << "------------------------------------------------------------------------------------------------------------------" << endl;
}
Hash_table::Hash_table(int table_size) : table(table_size, NULL), table_size(table_size), current_notes_amount(0) {}
bool Hash_table::encode_checker(string& key_word)
{
    int min_key_word_size = 2;
    if (key_word.size() < min_key_word_size) {
        cout << "Deny!" << endl;
        return false;
    }
    int first_letter_code = (int)(key_word[0]), second_letter_code = (int)(key_word[1]), a_code = (int)('a'), A_code = (int)('A'), z_code = (int)('z'), Z_code = (int)('Z');
    if (first_letter_code < A_code || (first_letter_code > Z_code && first_letter_code < a_code) || first_letter_code > z_code) {
        cout << "Deny!" << endl;
        return false;
    }
    if (second_letter_code < A_code || (second_letter_code > Z_code && second_letter_code < a_code) || second_letter_code > z_code) {
        cout << "Deny!" << endl;
        return false;
    }
    return true;
}
int Hash_table::numeral_key_word(string& key_word)
{
    return (int)(key_word[0]) + 2 * (int)(key_word[1]);
}
int Hash_table::hash_function(int numeral_key_word)
{
    return numeral_key_word % table_size;
}
void Hash_table::push(string& key_word, string& data)
{
    if (!encode_checker(key_word)) return;
    Table_Note* Note = new Table_Note;
    Note->key_word = key_word;
    Note->data = data;
    Note->numeral_key_word = numeral_key_word(key_word);
    Note->hash = hash_function(Note->numeral_key_word);
    Note->D = false;
    Note->U = true;
    Note->T = true;
    Note->next = NULL;
    Table_Note* example = table[Note->hash], * previous = NULL;
    while (example != NULL)
    {
        if (example->key_word == key_word) {
            cout << Note->key_word << " deny!" << endl;
            delete Note;
            return;
        }
        previous = example;
        example = example->next;
    }
    if (previous == NULL) {
        table[Note->hash] = Note;
        Note->collision = false;
    }
    else {
        previous->next = Note;
        previous->T = false;
        previous->collision = true;
        Note->collision = true;
    }
    current_notes_amount++;
}
void Hash_table::delete_with_key(string& key_word)
{
    if (!encode_checker(key_word)) return;
    int hash_we_try_to_delete = hash_function(numeral_key_word(key_word));
    Table_Note* deleting = table[hash_we_try_to_delete], * previous = NULL;
    int collision_counter = 0, min_collision_amount = 2;
    while (deleting != NULL)
    {
        collision_counter++;
        if (deleting->key_word == key_word && previous == NULL) {
            if (deleting->collision && deleting->next->next == NULL) {
                deleting->next->collision = false;
            }
            table[hash_we_try_to_delete] = deleting->next;
            delete deleting;
            deleting = table[hash_we_try_to_delete];
            current_notes_amount--;
        }
        else if (deleting->key_word == key_word && previous != NULL) {
            if (deleting->next == NULL) {
                previous->T = true;
                if (collision_counter == min_collision_amount) previous->collision = false;
            }
            previous->next = deleting->next;
            delete deleting;
            deleting = previous->next;
            current_notes_amount--;
        }
        else {
            previous = deleting;
            deleting = deleting->next;
        }
    }
}
Table_Note* Hash_table::find_with_key(string& key_word)
{
    if (!encode_checker(key_word)) return NULL;
    int hash_we_try_to_find = hash_function(numeral_key_word(key_word));
    Table_Note* looking_for = table[hash_we_try_to_find];
    while (looking_for != NULL)
    {
        if (looking_for->key_word == key_word) looking_for->print();
        looking_for = looking_for->next;
    }
    return looking_for;
}
int Hash_table::Get_curr_amount()
{
    return current_notes_amount;
}
void Hash_table::output()
{
    cout << "Total notes : " << current_notes_amount << endl;
    for (int i = 0; i < table.size(); i++)
    {
        Table_Note* example = table[i];
        while (example != NULL)
        {
            example->print();
            example = example->next;
        }
    }
}
void Hash_table::clear()
{
    for (int i = 0; i < table.size(); i++)
    {
        Table_Note* deleting = table[i];
        while (deleting != NULL)
        {
            table[i] = table[i]->next;
            delete deleting;
            deleting = table[i];
        }
    }
}
Hash_table::~Hash_table()
{
    clear();
    table.clear();
}
void task()
{
    string table_size_string;
    cout << "Enter table size : ";
    cin >> table_size_string;
    if (!checker(table_size_string)) {
        cout << "Enter something possible to work with!" << endl;
        return;
    }
    int table_size = stoi(table_size_string);
    if (table_size <= 20 || table_size > 100) {
        cout << "Enter something higher than 20 and lower than 100!" << endl;
        return;
    }
    Hash_table math(table_size);
    string a, a_def;
    a = "Infinity";
    a_def = "Number of points on a continuous line or as the size of the endless sequence of counting numbers";
    math.push(a, a_def);
    a = "Inequality";
    a_def = "Relation which makes a non-equal comparison between two numbers or other mathematical expressions";
    math.push(a, a_def);
    a = "Inequation";
    a_def = "Statement that an inequality holds between two values";
    math.push(a, a_def);
    a = "Division";
    a_def = "Method of distributing a group of things into equal parts";
    math.push(a, a_def);
    a = "Diagonal";
    a_def = "Straight line connecting the opposite corners of a polygon through its vertex";
    math.push(a, a_def);
    a = "Diameter";
    a_def = "The distance from one point on a circle through the center to another point on the circle";
    math.push(a, a_def);
    a = "Oval";
    a_def = "Figure constructed from two pairs of arcs, with two different radii";
    math.push(a, a_def);
    a = "Cube";
    a_def = "Solid three-dimensional figure, which has 6 square faces, 8 vertices and 12 edges";
    math.push(a, a_def);
    a = "Pyramid";
    a_def = "Polyhedron formed by connecting a polygonal base and a point, called the apex";
    math.push(a, a_def);
    a = "Addition";
    a_def = "Bringing two or more numbers (or things) together to make a new total";
    math.push(a, a_def);
    a = "Angle";
    a_def = "Figure formed by two rays, called the sides of the angle";
    math.push(a, a_def);
    a = "Multiplication";
    a_def = "Multiply means to add equal groups. When we multiply, the number of things in the group increases";
    math.push(a, a_def);
    a = "Square";
    a_def = "Result of multiplying a number by itself";
    math.push(a, a_def);
    a = "Radius";
    a_def = "Distance from the center outwards";
    math.push(a, a_def);
    bool sign = true;
    while (true)
    {
        cout << "What do you want?  :: 1)enter something :: 2)delete something :: 3)output all the information :: 4)find something :: 5)finish" << endl;
        string choice;
        if (!checker(choice)) {
            continue;
        }
        string example_one, example_two;
        cin >> choice;
        switch (stoi(choice))
        {
        case 1: cout << "Enter key word : ";
            cin >> example_one;
            cout << "Enter data : ";
            cin.ignore();
            getline(cin, example_two);
            math.push(example_one, example_two);
            break;
        case 2: cout << "Enter key word : ";
            cin >> example_one;
            math.delete_with_key(example_one);
            break;
        case 3: math.output();
            break;
        case 4: cout << "Enter key word : ";
            cin >> example_one;
            math.find_with_key(example_one);
            break;
        case 5:
            return;
        default: cout << "Enter something posible to work with!" << endl;
            break;
        }
    }
}
bool checker(string number)
{
    for (int i = 0; i < number.size(); i++)
    {
        if (number[i] != '1' && number[i] != '2' && number[i] != '3' && number[i] != '4' && number[i] != '5' && number[i] != '6' && number[i] != '7' && number[i] != '8' && number[i] != '9')
            return false;
    }
    return true;
}

bool Test1()
{
    int min_table_size = 21, difference = 1, before_size;
    Hash_table example(min_table_size);
    string a = "Infinity";
    string a_def = "Number of points on a continuous line or as the size of the endless sequence of counting numbers";
    example.push(a, a_def);
    a = "Inequality";
    a_def = "Relation which makes a non-equal comparison between two numbers or other mathematical expressions";
    example.push(a, a_def);
    before_size = example.Get_curr_amount();
    example.delete_with_key(a);
    if (before_size - example.Get_curr_amount() == difference) {
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
    int min_table_size = 21, difference = 1, before_size;
    Hash_table example(min_table_size);
    string a, a_def, deleting;
    a = "Division";
    a_def = "Method of distributing a group of things into equal parts";
    example.push(a, a_def);
    a = "Diagonal";
    a_def = "Straight line connecting the opposite corners of a polygon through its vertex";
    example.push(a, a_def);
    a = "Diameter";
    a_def = "The distance from one point on a circle through the center to another point on the circle";
    example.push(a, a_def);
    before_size = example.Get_curr_amount();
    deleting = "Division";
    example.delete_with_key(deleting);
    if (before_size - example.Get_curr_amount() == difference) {
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
    int min_table_size = 21, difference = 3, before_size;
    Hash_table example(min_table_size);
    string a, a_def, deleting;
    a = "Oval";
    a_def = "Figure constructed from two pairs of arcs, with two different radii";
    example.push(a, a_def);
    a = "Cube";
    a_def = "Solid three-dimensional figure, which has 6 square faces, 8 vertices and 12 edges";
    example.push(a, a_def);
    a = "Pyramid";
    a_def = "Polyhedron formed by connecting a polygonal base and a point, called the apex";
    example.push(a, a_def);
    before_size = example.Get_curr_amount();
    deleting = "Oval";
    example.delete_with_key(deleting);
    deleting = "Cube";
    example.delete_with_key(deleting);
    deleting = "Pyramid";
    example.delete_with_key(deleting);
    if (before_size - example.Get_curr_amount() == difference) {
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
    int min_table_size = 21, difference = 1, before_size;
    Hash_table example(min_table_size);
    string a, a_def, deleting;
    a = "Multiplication";
    a_def = "Multiply means to add equal groups. When we multiply, the number of things in the group increases";
    example.push(a, a_def);
    a = "Square";
    a_def = "Result of multiplying a number by itself";
    example.push(a, a_def);
    before_size = example.Get_curr_amount();
    deleting = "Square";
    example.delete_with_key(deleting);
    if (before_size - example.Get_curr_amount() == difference) {
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
    int min_table_size = 21;
    Hash_table example(min_table_size);
    string a, a_def;
    a = "M5ltiplication";
    a_def = "Multiply means to add equal groups. When we multiply, the number of things in the group increases";
    example.push(a, a_def);
    if (example.Get_curr_amount() == 0) {
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
    int min_table_size = 21;
    Hash_table example(min_table_size);
    string a, a_def;
    a = "7";
    a_def = "Multiply means to add equal groups. When we multiply, the number of things in the group increases";
    example.push(a, a_def);
    if (example.Get_curr_amount() == 0) {
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
    int min_table_size = 21;
    Hash_table example(min_table_size);
    string a, a_def;
    a = "math";
    a_def = "Multiply means to add equal groups. When we multiply, the number of things in the group increases";
    example.push(a, a_def);
    a = "math";
    a_def = "Multiply means to add equal groups. When we multiply, the number of things in the group increases";
    example.push(a, a_def);
    if (example.Get_curr_amount() == 1) {
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
    int min_table_size = 21;
    Hash_table example(min_table_size);
    string a, a_def;
    a = "Radius";
    a_def = "Distance from the center outwards";
    example.push(a, a_def);
    a = "Radius";
    a_def = "Distance from the center outwards";
    example.push(a, a_def);
    if (example.Get_curr_amount() == 1) {
        cout << "Test8 correct!" << endl;
        return true;
    }
    else {
        cout << "Test8 incorrect!" << endl;
        return false;
    }
}
void tests()
{
    int correct_amount = 0;
    cout << "Deleting tests" << endl;
    correct_amount += Test1();
    correct_amount += Test2();
    correct_amount += Test3();
    correct_amount += Test4();
    cout << "Denial tests (deny means correct!!!!)" << endl;
    correct_amount += Test5();
    correct_amount += Test6();
    correct_amount += Test7();
    correct_amount += Test8();
    if (correct_amount == 8) cout << "All tests passed correctly!" << endl;
}
void our_own_input()
{
    int choice;
    cout << "1)Tests :: 2)Task" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1: tests();
        break;
    case 2: task();
        break;
    default: cout << "Enter something possible to work with!" << endl;
        return;
    }
}