#include <iostream>
#include <fstream>
#include <string>

struct Person{
    std::string name;
    std::string surname;
    std::string payment;
    std::string date;
};

void list(std::ifstream& file, Person& text){
    file >> text.name;
    file >> text.surname;
    file >> text.payment;
    file >> text.date;
    std::cout << text.name << " " << text.surname << " " << text.payment << " " << text.date << std::endl;
}

bool nameCorrect(std::string str)
{
    bool nCorrect = true;
    if (str[0] < 'A' || str[0] > 'Z')
    {
        nCorrect = false;
        std::cout << "ERROR,write the name with a capital letter " << std::endl;
        return nCorrect;
    }
    else
    {
        for(int i = 1; i < str.length(); ++i)
        {
            if (str[i] < 'a' || str[i] > 'z')
            {
                nCorrect = false;
                std::cout << "ERROR" << std::endl;
                return nCorrect;
            }
        }
    }
    return nCorrect;
}

bool dateCorrect(std::string str)
{
    bool dCorrect = true;
    if (str.length() != 10 || str[2] != '.' || str[5] != '.')
    {
        dCorrect = false;
        std::cout << "ERROR" << std::endl;
        return dCorrect;
    }
    else
    {
        for (int i = 0; i < str.length(); ++i)
        {
            if (str[i] < '0' && str[i] != '.' || str[i] > '9')
            {
                dCorrect = false;
                std::cout << "ERROR" << std::endl;
                return dCorrect;
            }
        }
    }
    int d = std::stoi(str.substr(0,2));
    int m = std::stoi(str.substr(3,2));
    int y = std::stoi(str.substr(6,4));
    if (d < 1 || d > 31 || m > 12 || m < 1 || y > 2022 || y < 2000)
    {
        dCorrect = false;
        return dCorrect;
    }
    else if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30)
    {
        dCorrect = false;
        return dCorrect;
    }
    else if (y % 4 != 0  && (m == 2 && d > 28))
    {
        dCorrect = false;
        return dCorrect;
    }
    return  dCorrect;
}

bool numberCorrect(std::string str)
{
    bool nCorrect = true;
    for(int i = 0; i < str.length(); ++i)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            nCorrect = false;
            std::cout << "ERROR" << std::endl;
            return nCorrect;
        }
    }
    return nCorrect;
}

int main() {
    Person text;
    std::string temp;
    std::string command;

    std::cout << "Enter the <list> command to read the list" << std::endl;
    std::cout << "OR" << std::endl;
    std::cout << "Enter the <add> command to add an entry" << std::endl;
    std::cin >> command;

    if (command == "add")
    {
        std::ofstream fileOut("bank.txt", std::ios::app);
        fileOut << std::endl;
        if (!fileOut.is_open())
        {
            std::cout << "Error!" << std::endl;
        }
        else
        {
            do {
                std::cout << "Name?" << std::endl;
                std::cin >> text.name;
                fileOut << text.name << " ";
            } while (!nameCorrect(text.name));
            do {
                std::cout << "Surname?" << std::endl;
                std::cin >> text.surname;
                fileOut << text.surname << " ";
            } while (!nameCorrect(text.surname));
            do {
                std::cout << "Date?" << std::endl;
                std::cin >> text.date;
                fileOut << text.date << " ";
            } while (!dateCorrect(text.date));
            do {
                std::cout << "Payment?" << std::endl;
                std::cin >> text.payment;
                fileOut << text.payment << " RUB";
            } while (!numberCorrect(text.payment));
        }
        fileOut.close();
    }
    else if (command == "list")
    {
        std::ifstream fileIn("bank.txt");

        if (!fileIn.is_open())
        {
            std::cout << "Error!" << std::endl;
        }
        else
        {
            while (getline(fileIn, temp))
            {
                list(fileIn,text);
            }
            fileIn.close();
        }
    }
    else
    {
        std::cout << "There is no such command";
    }
}
