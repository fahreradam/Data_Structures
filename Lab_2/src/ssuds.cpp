// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array_list.h>
#include <fstream>

#define MODE = 2

#if MODE == 1
{ }
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

void main()
{
    ssuds::ArrayList<std::string> database;

    database.append("ifnsges");
}

#endif