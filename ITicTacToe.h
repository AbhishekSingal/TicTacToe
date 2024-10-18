#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>


/// @brief The Inputs of the Game , "X" , "0" or " "
enum BOARD_INPUTS{ZERO,CROSS,BLANK};

/// @brief Struct To Represent whether Game is Over or not, if is then who is the winner 
struct GAME_OVER_OBJ
{
    bool GAME_OVER = false;
    BOARD_INPUTS WINNER;
};

/// @brief Represent the a Game Move , which cell has to played on in the board
struct GAME_MOVE
{
    int ROW;
    int COL;
};


/// @brief Utility Function , Check whether a Vector has all same Elements ( Use to determine Game Over )
/// @param ARR The Vector Array
/// @return 
bool IsVectorUniform(std::vector<std::string> ARR);

/// @brief Get The BOARD_INPUT as a string
/// @param INP 
/// @return String of BOARD_INPUT , either '0' , 'X' , ' '
std::string BOARD_INPUT_STR(BOARD_INPUTS INP);

/// @brief Represents the Game Board
class Board
{
    public :
        std::vector< std::vector<std::string> > BOARD 
        {
            {" "," "," "},
            {" "," "," "},
            {" "," "," "}
        };
        Board(){};

        /// @brief Log The Game Board ( For Console Games )
        void LogBoard();

        /// @brief Update a Cell in the Board
        /// @param ROW 
        /// @param COL 
        /// @param INPUT CROSS OR ZERO
        void Update(int ROW,int COL,BOARD_INPUTS INPUT);

};



/// @brief Abstract Class for The TicTacToe Game. Function GameImplement ; OnGameOver(GAME_OVER_OBJ) have to be Implemented
class ITicTacToe
{

    private :
        /// @brief The Game Board 
        Board BOARD;

        /// @brief The Current Player , i.e the players whose turn is there
        BOARD_INPUTS CURRENT_PLAYER = ZERO;

        /// @brief Utility Function for GetComputerMove(BOARD_INPUTS PLAYER) , check if array has a potential move to make 
        /// @param ARR The Vector
        /// @param INP For which BOARD_INPUT , CROSS OR ZERO whose against Move has to be made
        /// @return return the Index in the vector where move can be made , -1 if no move possible
        int CHECK_ARRAY_FOR_MOVE(std::vector<std::string> ARR,BOARD_INPUTS INPUT);

    protected : 

        /// @brief GAME_OVER_OBJ That states the game status , whether the game is over or not
        GAME_OVER_OBJ GAME_STATUS;

        /// @brief Get The Current Player
        /// @return BOARD_INPUTS -> ZERO OR CROSS 
        BOARD_INPUTS GetCurrentPlayer();


        /// @brief Get The Current Player as a string
        /// @return "0" OR "X" 
        std::string GetCurrentPlayerStr(){return BOARD_INPUT_STR(CURRENT_PLAYER);};

        /// @brief Sets the Current Player of the Game
        /// @param PLAYER ZERO OR CROSS
        void SetCurrentPlayer(BOARD_INPUTS PLAYER);

        /// @brief Change The Current Player
        void ChangePlayer();


        /// @brief Play a Move On The Board
        /// @param r ROW 
        /// @param c COL
        /// @param PLAYER What Player's Move to be Played , either ZERO OR CROSS
        void PlayMove(int r,int c,BOARD_INPUTS PLAYER);

        /// @brief Log The Game Board ( For Console Games )
        void LogBoard(){BOARD.LogBoard();};

        /// @brief Get a Board Cell
        /// @param r ROW
        /// @param c COL 
        /// @return "0" OR "X" OR " "
        std::string GetBoardCell(int r , int c){return BOARD.BOARD[r][c];};


        /// @brief Get The Most Optimum move to be played by the Computer based on current board
        /// @param PLAYER The Computer BOARD_INPUT
        /// @param COMPUTER_MOVE_COUNT The Number of Moves the Computer has played so far
        /// @param USER_MOVE_COUNT The Number of Moves the Uses has played so far
        /// @return GAME_MOVE Object , contains the row,col where the move has to be made
        GAME_MOVE GetComputerMove(BOARD_INPUTS PLAYER,int COMPUTER_MOVE_COUNT,int USER_MOVE_COUNT);
        

        //Functions to Override
        virtual void GameImplement()=0;
        virtual void OnGameOver(GAME_OVER_OBJ STATUS)=0;
        
        
    
    public :

        /// @brief Start The Game 
        /// @param START_PLAYER 
        void Start(BOARD_INPUTS START_PLAYER);

        
};

/// @brief Check The Board , if the Game is Over
/// @param BOARD The Board
/// @return GAME_OVER_OBJ -> Contains The Winner , if GAME_OVER = true , if GAME_OVER = false , WINNER will be BLANK
GAME_OVER_OBJ IsGameOver(Board BOARD);
