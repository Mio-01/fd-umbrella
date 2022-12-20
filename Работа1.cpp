#include <iostream>
#include <ctime>
#include <string>
#include <random>
#include <algorithm>
#include <iomanip> // для ограничения количества вводимых симолов для std::cin

void startTheGame();
int getUsersGuess();
int getRandomNumber(int min, int max);
void compUsrWthCmptr(std::string userInput, std::string computerInput);

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(0)));
    startTheGame();
    return 0;
}

void compUsrWthCmptr(std::string userInput, std::string computerInput)
{
    //  Считаем правильно угаданные позиции

    std::reverse(userInput.begin(), userInput.end());
    std::reverse(computerInput.begin(), computerInput.end());
    int guessedPositions{ 0 };
    for (int i = 0; (i < userInput.length()) && (i < computerInput.length()); ++i)
    {
        if (userInput[i] == computerInput[i])
        {
            guessedPositions++;
        }
    }

    std::string::iterator it_userInput;
    std::string::iterator it_computerInput;

    // Удаляем повторяющиеся цифры

    it_userInput = std::unique(userInput.begin(), userInput.end());
    userInput.resize(std::distance(userInput.begin(), it_userInput));
    it_computerInput = std::unique(computerInput.begin(), computerInput.end());
    computerInput.resize(std::distance(computerInput.begin(), it_computerInput));

    //  Считаем количество правильно угаданных цифр без учета повторяющихся

    int guessedDigits{ 0 };
    for (int i = 0; i < userInput.length(); ++i)
    {
        for (int x = 0; x < computerInput.length(); ++x)
        {
            if (userInput[i] == computerInput[x])
            {
                guessedDigits++;
            }
        }
    }
    std::cout << "Цифр угадано: " << guessedDigits << ". Позиция угаданных чисел: " << guessedPositions << std::endl << std::endl;

};
void startTheGame()
{
    int pcsRandomNumber = getRandomNumber(0, 999);      //Загаданое число.
    std::cout << "Компьютер загадал трехзначное число от 0 до 999!\n" << std::endl;
    std::string pcNumber{ std::to_string(pcsRandomNumber) };
    bool win = false;
    do
    {
        int usersGuess = getUsersGuess();
        std::string guess{ std::to_string(usersGuess) };
        std::cout << "Ваш вариант: " << guess << std::endl;
        compUsrWthCmptr(guess, pcNumber);
        if (usersGuess == pcsRandomNumber)
        {
            win = true;
            std::cout << "*** Вы угадали число " << pcsRandomNumber << "!***\n";
        }
    } while (!win);
};

int getUsersGuess()
{
    while (true) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
    {
        std::cout << "Ваш вариант: ";
        int a;
        std::cin >> std::setw(3) >> a;

        // Проверка на предыдущее извлечение
        if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
            std::cout << " Вы ввели не число. Попытайтесь еще раз.\n\n";
        }
        else
        {
            if (a >= 1000 || a < 0)
            {
                std::cin.ignore(32767, '\n'); // удаляем лишние значения
                std::cout << "  Введенное число вне требуемого диапазонате. Попытайтесь еще раз.\n\n";
            }
            else
            {
                std::cin.ignore(32767, '\n'); // удаляем лишние значения
                return a;
            }
        }
    }
}
int getRandomNumber(int min, int max)
{
    return static_cast<int>(rand() % (max - min + 1) + min);
}
