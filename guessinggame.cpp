#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>

int upper_bound = 100, points = 0;
bool show_attempts = true, show_points = true;

int generate_random_number(int upper_bound) {
    return rand() % upper_bound;
}

void update_highscore(int points)
{
    std::ifstream input("high_score.txt");

    int high_score;
    input >> high_score;

    std::ofstream output("high_score.txt");

    if (input.is_open()) {
        if (points > high_score) {
            output << points;
        }
        else
        {
            output << high_score;
        }
        input.close();
    }
    else
    {
        std::cout << "Unable to read file" << std::endl;
        return;
    }
}

void print_guesses(std::vector<int> guesses) {
    if (guesses.size() > 1) {
        std::cout << "You got it right!" << std::endl;
        std::cout << "See your inputs" << std::endl;

        for (int i = 0; i < guesses.size(); ++i)
        {
            std::cout << guesses[i] << "\t";
        }

        std::cout << std::endl;
        std::cout << "It took you " << guesses.size() << " attempt(s)" << std::endl;
    }
    else
    {
        std::cout << "Bingo! You nailed it on your first attempt." << std::endl;
    }
    update_highscore(points);
}

void set_difficulty(int difficulty = 1) {
    std::cout << "1. Easy" << std::endl;
    std::cout << "2. Normal" << std::endl;
    std::cout << "3. Hard" << std::endl;
    std::cout << "4. Expert" << std::endl;
    std::cout << "5. Nightmare" << std::endl;

    std::cout << "Enter an option: ";
    std::cin >> difficulty;

    switch (difficulty)
    {
    case 1:
        upper_bound = 100;
        break;

    case 2:
        upper_bound = 200;
        break;

    case 3:
        upper_bound = 350;
        break;

    case 4:
        upper_bound = 600;
        break;

    case 5:
        upper_bound = 1000;
        break;

    default:
        upper_bound = 100;
        break;
    }
    return;
}

void attempt_settings() {
    int option;
    std::cout << "1. Show remaining attempts" << std::endl;
    std::cout << "2. Hide remaining attempts" << std::endl;

    std::cout << "Enter option: ";
    std::cin >> option;

    switch (option)
    {
    case 1:
        show_attempts = true;
        break;

    case 2:
        show_attempts = false;
        break;

    default:
        show_attempts = true;
        break;
    }
}

void display_settings() {
    int settings_option;

    std::cout << "-----------" << std::endl << "  Settings" << std::endl << "-----------" << std::endl;
    std::cout << "1. Difficulty" << std::endl;
    std::cout << "2. Show/Hide number of attempts" << std::endl;
    std::cout << "3. Show/Hide points earned" << std::endl;
    std::cout << "4. Main Menu" << std::endl;
    std::cout << "Enter an option: ";

    std::cin >> settings_option;

    switch (settings_option)
    {
    case 1:
        std::cout << "------------------" << std::endl << " Select Difficulty" << std::endl << "------------------" << std::endl;
        set_difficulty();
        break;

    case 2:
        std::cout << "------------------" << std::endl << "  Attempt Settings" << std::endl << "------------------" << std::endl;
        attempt_settings();
        break;

    case 3:
        std::cout << "------------------" << std::endl << "    Point Settings" << std::endl << "------------------" << std::endl;
        break;

    case 4:
        return;

    default:
        break;
    }
}


void play_game() {
    int attempts = 10;
    
    std::vector<int> guesses;

    std::cout << "Guess a number between 0 and " << upper_bound << std::endl;

    int random_number = generate_random_number(upper_bound);

    do {
        if ((show_attempts==true) && (show_points==true)) {
            std::cout << attempts << " attempt(s) remaining." << "\t" << "Points: " << points <<std::endl;
        }
        else if ((show_attempts==true) && (show_points == false)) {
            std::cout << attempts << " attempt(s) remaining." <<std::endl;
        }
        else if ((show_attempts==false) && (show_points == true))
        {
            std::cout << "Points: " << points <<std::endl;
        }
        
        if (attempts < 1) {
            std::cout << "Game Over!" << std::endl;
            break;
        }

        int user_guess;
        std::cout << "Guess: ";
        std::cin >> user_guess;

        if (user_guess == random_number) {
            guesses.push_back(user_guess);
            points += attempts;

            print_guesses(guesses);
            break;
        }
        else if (user_guess < random_number) {
            std::cout << "Too low. Guess again." << std::endl;
            guesses.push_back(user_guess);
            --attempts;
        }
        else if (user_guess > random_number) {
            std::cout << "Too high. Guess again." << std::endl;
            guesses.push_back(user_guess);
            --attempts;
        }
        else {
            std::cout << "Input a correct character...Goddamit";
        }

    } while (true);
}


int main() {
    srand(time(NULL));

    int menu_option;

    do {
        std::cout << "-----------" << std::endl << "   Menu" << std::endl << "-----------" << std::endl;
        std::cout << "1. Play Game" << std::endl;
        std::cout << "2. Settings" << std::endl;
        std::cout << "0. Quit" << std::endl;

        std::cout << "Enter an option: ";
        std::cin >> menu_option;

        switch (menu_option)
        {
        case 1:
            play_game();
            break;

        case 2:
            display_settings();
            break;

        case 0:
            return 0;

        default:
            break;
        }
    } while (true);
}
