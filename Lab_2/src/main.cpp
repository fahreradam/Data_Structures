// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array_list.h>
#include <fstream>

#define MODE 2





#if MODE == 1
int get_int(std::string prompt, int deflt = -1)
{
    int result;
    std::string dummy;

    std::cout << prompt;
    if (std::cin.peek() == '\n')
    {
        std::getline(std::cin, dummy);
        return deflt;
    }
    else
    {
        std::cin >> result;
        if (std::cin.good())
        {
            std::getline(std::cin, dummy);
            return result;
        }
        else
        {
            return -1;
        }
    }
}

int get_menu_choice(bool show_menu)
{
    if (show_menu)
    {
        std::cout << "Main Menu" << std::endl;
        std::cout << "=========" << std::endl;
        std::cout << "1. Show data" << std::endl;
        std::cout << "2. Append string" << std::endl;
        std::cout << "3. Insert string" << std::endl;
        std::cout << "4. Remove string" << std::endl;
        std::cout << "5. Remove (all) string(s)" << std::endl;
        std::cout << "6. Find string" << std::endl;
        std::cout << "7. Clear data" << std::endl;
        std::cout << "9. Quit" << std::endl;
    }

    std::cout << std::endl;

    int result = get_int(">> ");
    if (result < 0)
        std::cout << "Unknown menu item.  Pleast try again." << std::endl;

    return result;
}


int main()
{
    // The basic test program
    /*ssuds::ArrayList test;
    test.append("Bob");
    test.append("Carl");
    std::cout << test.size() << std::endl;                  // 2
    std::cout << test.get(0) << std::endl;                  // Bob
    std::cout << test.get(1) << std::endl;                  // Carl
    test.insert("Abe", 0);
    test.insert("Doug", 3);
    test.insert("Barb", 1);                         
    for (int i = 0; i < test.size(); i++)                   // Abe Barb Bob Carl Doug
        std::cout << test.get(i) << " ";
    std::cout << std::endl;
    test.append("Barb");
    test.append("Barb");
    for (int i = 0; i < test.size(); i++)                   // Abe Barb Bob Carl Doug Barb Barb
        std::cout << test.get(i) << " ";
    std::cout << std::endl;
    std::cout << test.remove_all("Barb") << std::endl;      // 3
    for (int i = 0; i < test.size(); i++)                   // Abe Bob Carl Doug
            std::cout << test.get(i) << " ";
    std::cout << std::endl;
    */


    // The "application" problem
    ssuds::ArrayList<std::string> database;
    std::string database_fname("..\\..\\media\\data.txt");
    std::fstream fp(database_fname, std::ios::in);
    std::cout << "reading initial data" << std::endl;
    std::cout << "====================" << std::endl;
    while (fp.is_open() && !fp.eof())
    {
        std::string line;
        std::getline(fp, line);
        if (!fp.eof() && line.size() > 0)
        {
            std::cout << "\tread line '" + line + "'" << std::endl;
            database.append(line);
        }
    }
    fp.close();
    fp.clear();

    int choice = -1;
    bool show_menu = true;
    std::string new_str;
    int index;
    int num;
    while (choice != 9)
    {
        choice = get_menu_choice(show_menu);
        show_menu = false;
        std::cout << std::endl;
        switch (choice)
        {
        case 1:
            std::cout << "Current data" << std::endl;
            std::cout << "============" << std::endl;
            for (int i = 0; i < database.size(); i++)
                std::cout << i << "\t" << database.get(i) << std::endl;
            break;
        case 2:
            std::cout << "Enter new string: ";
            
            std::getline(std::cin, new_str);
            database.append(new_str);
            break;
        case 3:
            std::cout << "Enter new string: ";
            std::getline(std::cin, new_str);
            index = get_int("Enter insertion index: ");
            database.insert(new_str, index);
            break;
        case 4:
            index = get_int("Enter removal index: ");
            database.remove(index);
            break;
        case 5:
            std::cout << "Enter string: ";
            std::getline(std::cin, new_str);
            num = database.remove_all(new_str);
            std::cout << "Removed " << num << " instances." << std::endl;
            break;
        case 6:
            std::cout << "Enter string: ";
            std::getline(std::cin, new_str);
            index = get_int("Enter starting index (enter for 0): ", 0);
            if (index < 0)
                index = database.find(new_str);
            else
                index = database.find(new_str, index);
            std::cout << "Result: " << index << std::endl;
            break;
        case 7:
            database.clear();
            std::cout << "cleared" << std::endl;
            break;
        default:
            show_menu = true;
            break;
        }
    }

    // Write the data out to the file
    fp.open(database_fname, std::ios::out);
    for (int i = 0; i < database.size(); i++)
        fp << database.get(i) << std::endl;
    fp.close();
}
#else
class Foo
{
protected:
    std::string mString;
    int mInt;

public:
    Foo(std::string other, int i) : mString(other), mInt(i)
    { }
    Foo() : mString(""), mInt(0)
    { }
    void set_string(const std::string& s)
    {
        mString = s;
    }
    void set_int(int i)
    {
        mInt = i;
    }
    std::string get_string() const
    {
        return mString;
    }
    friend std::ostream& operator << (std::ostream& os, const Foo& f)
    {
        os << "Foo-" << f.mString << "-" << f.mInt;

        return os;
    }
    bool operator==(const Foo& other)
    {
        return mString == other.mString && mInt == other.mInt;
    }

};

int main()
{
    ssuds::ArrayList<float> tester;
    tester.append(4.2f);
    tester.append(56.2f);

    ssuds::ArrayList<float> tester2(tester); // copy constructor
    tester2.append(3.24f);

    std::cout << tester << std::endl; // [4.2, 56.2]
    tester2[0] = 45.3f;
    std::cout << tester2 << std::endl; // [45.3, 56.2, 3.24]

    tester2.clear();  // clear function
    tester2.append(24.21);

    tester2[0] = 256.20f; // using by reference with the [] operator

    std::cout << tester << std::endl; // [4.2, 56.2] 
    std::cout << tester2 << std::endl; // [256.2] testing single item printing

    tester2 = tester; // array copy funtion
    std::cout << tester2 << std::endl; // [4.2, 56.2]

    ssuds::ArrayList<Foo> flist;
    flist.append(Foo("Bob", 4));
    Foo temp_foo("Sue", 7);
    flist.append(temp_foo);

    ssuds::ArrayList<Foo> flist2(flist);

    std::cout << "flist = " << flist << std::endl; // flist = [Foo-Bob-4, Foo-Sue-7]


    flist.remove_all(Foo("Sue", 7));

    ssuds::ArrayList<float> list1;
    list1.append(4.3f);
    list1.append(5.5f);
    list1.append(6.6f);
    std::cout << list1[0] << std::endl;		// 4.3

    ssuds::ArrayList<float> list2(list1);	// copy-constructor
    list2.append(7.7f);
    std::cout << list2 << std::endl;	// [4.3, 5.5, 6.6, 7.7]
    std::cout << list1 << std::endl;	// [4.3, 5.5, 6.6]
    list2 = list1;						// = operator
    list2.append(8.8f);					
    std::cout << list2 << std::endl;	// [4.3, 5.5, 6.6, 8.8]


    std::cout << list1.find(6.6) << std::endl; // 2
    std::cout << list2.remove_all(6.6) << std::endl; // 1
    std::cout << list2 << std::endl;	// [4.3, 5.5, 8.8]
    std::cout << list1 << std::endl;	// [4.3, 5.5, 6.6]



    std::cout << list1.capactiy_size() << std::endl; // 5

    list1.append(1);
    list1.append(1);
    list1.append(1);
    list1.append(1);
    list1.append(1);
    list1.append(1);
    std::cout << list1 << std::endl; // [4.3, 5.5, 6.6, 1, 1, 1, 1, 1, 1]

    std::cout << list1.capactiy_size() << std::endl; // 10
    std::cout << list1.size() << std::endl; // 9
    std::cout << list1.remove_all(1) << std::endl; // 6
    std::cout << list1.capactiy_size() << std::endl; // 5
    std::cout << list1.size() << std::endl; // 3

    std::cout << list1 << std::endl; // [4.3, 5.5, 6.6]






}



#endif