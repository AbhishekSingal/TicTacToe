#include <include/ITicTacToe.h>
#include <thread>
#include <chrono>

std::string START_MSG = R"(
C++(17) ConsoleTicTacToe version 1.1.0
    
Instructions :
(1) The Board is a 3x3 Matrix , with indexes from 0,0 to 2,2 (row,column)
(2) To Enter a Move , the format is : ROW SPACE COL

USER : ZERO (0)
COMPUTER : CROSS (X)

)"; 

#define CONSOLE_TICTACTOE_INIT\
    ConsoleTicTacToeWithComputer GAME(ZERO,CROSS)\

#define CONSOLE_TICTACTOE_START\
    GAME.Start(CROSS)\
    

class ConsoleTicTacToeWithComputer : public ITicTacToe
{

    private :
        BOARD_INPUTS USER ;
        BOARD_INPUTS COMPUTER;
        int COMPUTER_MOVE_COUNT = 0;
        int USER_MOVE_COUNT = 0;

    public :
        ConsoleTicTacToeWithComputer(BOARD_INPUTS USER,BOARD_INPUTS COMPUTER)
        {
            this->USER = USER;
            this->COMPUTER = COMPUTER;
        };
    
    void GameImplement() override 
    {
        std::cout << "\033[2J\033[1;1H";
        std::cout<<START_MSG<<std::endl;
        LogBoard();
        std::cout<<"\n";
        if(GetCurrentPlayer() == USER)
        {
            std::cout<<"Enter Move("<<GetCurrentPlayerStr()<<") : ";
            std::string MOVE="";
            std::getline(std::cin,MOVE);
            int r = static_cast<int>(MOVE[0])-'0';
            int c = static_cast<int>(MOVE[2])-'0';
            PlayMove(r,c,GetCurrentPlayer());
            USER_MOVE_COUNT++;
        }
        if(GetCurrentPlayer() == COMPUTER)
        {
            std::cout<<"Computer : Thinking ...\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            GAME_MOVE COMPUTER_MOVE = GetComputerMove(GetCurrentPlayer(),COMPUTER_MOVE_COUNT,USER_MOVE_COUNT);
            PlayMove(COMPUTER_MOVE.ROW,COMPUTER_MOVE.COL,GetCurrentPlayer());
            COMPUTER_MOVE_COUNT++;
        }

    }

    void OnGameOver(GAME_OVER_OBJ OBJ) override
    {
        std::cout << "\033[2J\033[1;1H";
        std::cout<<START_MSG<<std::endl;
        LogBoard();
        const char* coolEmoji = u8"\U0001F60E";
        if(OBJ.WINNER == COMPUTER){std::cout<<"\nGame Over : Computer Wins ! "<<coolEmoji<<"\n\n";};
        if(OBJ.WINNER == USER){std::cout<<"\nGame Over : Player Wins\n\n";};
        if(OBJ.WINNER == BLANK){std::cout<<"\nGame Over : Draw\n\n";}
        std::cout<<"Press Any Key to Exit ...";
        std::cin.get();
    }

};

int main(int argc , char** argv)
{
    CONSOLE_TICTACTOE_INIT;
    CONSOLE_TICTACTOE_START;
    return 0;
}