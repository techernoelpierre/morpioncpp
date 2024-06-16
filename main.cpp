#include<iostream>
#include <thread>
#include <chrono>

#ifdef _WIN32
#define WINDOWS true
#endif //_WIN32

#define RED "\x1b[31m"
#define BLUE "\x1b[34m"
#define GREEN "\x1b[32m"
#define VIOLET "\x1b[38;5;93m"
#define PINK "\x1b[38;5;198m"
#define DEFAULT "\x1b[0m"

void clear_std_output(void);
bool between(int min, int max, int value);
void sleep(int milliseconds);
bool all_equal(int arr[3], int value);

class Player {
    public:
        std::string name;
        int number;
};

class Morpion {
public:
    int grid[3][3] = {{0,0,0}, {0,0,0}, {0,0,0}};
    Player player_1;
    Player player_2;
    bool run = true;
    Player *winner; 
    Player *current_player; 

    bool add_element(int number, int x, int y) {
        if (between(0, 2, y) && between(0, 2, x) && grid[y][x] == 0) {
            grid[y][x] = number;
            return true;
        }
        return false;
    }

    void create_players(void) {
        this->player_1.name = "Player 1";
        this->player_1.number = 1;
        this->player_2.name = "Player 2";
        this->player_2.number = 2;
    }

    void display_grid(void) {
        clear_std_output();
        std::cout << "\n";
        std::cout << PINK << "   A  B  C\n" << DEFAULT;
        for (int i = 0; i < 3; i++) {
            std::cout << PINK << " " << i+1 << " " << DEFAULT;
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == 1) {
                    std::cout << BLUE << "X" << DEFAULT;
                } else if (grid[i][j] == 2) {
                    std::cout << RED << "O" << DEFAULT;
                } else {
                    std::cout << VIOLET << "." << DEFAULT;
                }
                std::cout << "  ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    bool check_win(void) {
        int player_number = this->current_player->number;
        for (int i = 0; i < 3; i++) {
            if (all_equal(grid[i], player_number))
                return true;
        }

        for (int i = 0; i < 3; i++) {
            if (grid[0][i] == player_number && grid[1][i] == player_number && grid[2][i] == player_number)
                return true;
        }

        if ((grid[0][0] == player_number && grid[1][1] == player_number && grid[2][2] == player_number) ||
        (grid[0][2] == player_number && grid[1][1] == player_number && grid[2][0] == player_number)) {
            return true;
        }

        return false;
    }
};

void clear_std_output(void) {   
    if (WINDOWS) {
        system("cls");
    } else {
        system("clear");
    }
}

bool between(int min, int max, int value) {
    if (value >= min && value <= max)
        return true;
    return false;
}

void sleep(int milliseconds) {
    auto now = std::chrono::system_clock::now();
    auto wake_up_time = now + std::chrono::milliseconds(milliseconds);

    std::this_thread::sleep_until(wake_up_time);
}

bool all_equal(int arr[3], int value) {
    return (arr[0] == value && arr[1] == value && arr[2] == value);
}

int main(void) {
    clear_std_output();
    std::cout << GREEN << "Bienvenu dans mon jeux du morpion. \n" << "Clickez sur Enter pour continuer" << DEFAULT;
    std::cin.get();
    Morpion morpion;
    morpion.create_players();
    morpion.current_player = &morpion.player_1;
    while(morpion.run) {
        clear_std_output();
        morpion.display_grid();
        std::cout << GREEN << "\nC'est le tour de " << morpion.current_player->name << ".\n" << DEFAULT;
        int x;
        int y;
        std::cout << GREEN << "entrez x: " << DEFAULT;
        std::cin >> x;
        std::cout << GREEN << "entrez y: " << DEFAULT;
        std::cin >> y;
        bool ok = morpion.add_element(morpion.current_player->number, x-1, y-1);
        if (!ok) {
            std::cout << GREEN << "Veuillez choisir use case valide.\n" << DEFAULT;
            sleep(2000);
            continue;
        }
        if (morpion.check_win()) {
            morpion.display_grid();
            std::cout << GREEN << morpion.current_player->name << " vous avez gagne !!!" << DEFAULT;
            break;
        }
        if (morpion.current_player->number == 1) {
            morpion.current_player = &morpion.player_2;
        } else {
            morpion.current_player = &morpion.player_1;
        }
    }
    std::cout << GREEN << "\nFin du script" << DEFAULT << std::endl;
    return 0;
}