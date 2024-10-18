#include "include/ITicTacToe.h"



void Board::LogBoard()
{
    for(int r = 0 ; r < 3 ; r++)
    {
        for(int c = 0 ; c < 3 ;c++)
        {
            if(c == 0){std::cout<<"| "<<BOARD[r][c]<<" |";}
            else if(c == 2){std::cout<<" "<<BOARD[r][c]<<" |";}
            else{std::cout<<" "<<BOARD[r][c]<<" |";};
        }
        std::cout<<std::endl;
    }
}


void Board::Update(int ROW,int COL,BOARD_INPUTS INPUT)
{
    if(BOARD[ROW][COL] == " ")
    {
        BOARD[ROW][COL]=BOARD_INPUT_STR(INPUT);
    }else{
        std::cout<<std::endl;
        std::cout<<"Error : Already Occupied Cell"<<std::endl;
        std::cout<<std::endl;
    }
    
}


std::string BOARD_INPUT_STR(BOARD_INPUTS INP)
{
    std::string str;
    if(INP == CROSS){str="X";};
    if(INP == ZERO){str="0";};
    if(INP == BLANK){str=" ";};
    return str;
}


bool IsVectorUniform(std::vector<std::string> ARR)
{
    bool isSame = std::adjacent_find(ARR.begin(), ARR.end(), std::not_equal_to<std::string>()) == ARR.end();
    return isSame;
}


GAME_OVER_OBJ IsGameOver(Board BOARD)
{
    BOARD_INPUTS WINNER = BLANK;
    bool OVER = false;
    //Check Rows
    for(int r = 0 ; r < 3 ; r++)
    {
        std::vector<std::string> ROW = BOARD.BOARD[r];
        bool isUniform = IsVectorUniform(ROW);
        if(isUniform)
        {
            
            if(ROW[0] == "X"){WINNER = CROSS;OVER=true;}
            if(ROW[0] == "0"){WINNER = ZERO;OVER=true;}
            
        }
    }

    //Check Columns
    for(int c = 0 ; c < 3 ; c++)
    {
        std::vector<std::string> COL = {
            BOARD.BOARD[0][c],
            BOARD.BOARD[1][c],
            BOARD.BOARD[2][c]
        };

        bool isUniform = IsVectorUniform(COL);
        if(isUniform)
        {
            
            if(COL[0] == "X"){WINNER = CROSS;OVER=true;}
            if(COL[0] == "0"){WINNER = ZERO;OVER=true;}
            
        }
    }

    //Check Diagnols
    std::vector<std::string> D1 = {
        BOARD.BOARD[0][0],
        BOARD.BOARD[1][1],
        BOARD.BOARD[2][2]
    };

    std::vector<std::string> D2 = {
        BOARD.BOARD[0][2],
        BOARD.BOARD[1][1],
        BOARD.BOARD[2][0]
    };

    bool isD1Uniform = IsVectorUniform(D1);
    bool isD2Uniform = IsVectorUniform(D2);
    if(isD1Uniform)
    {
        if(D1[0] == "X"){WINNER = CROSS;OVER=true;}
        if(D1[0] == "0"){WINNER = ZERO;OVER=true;}
        
    }
    if(isD2Uniform)
    {
        if(D2[0] == "X"){WINNER = CROSS;OVER=true;}
        if(D2[0] == "0"){WINNER = ZERO;OVER=true;}
        
    }

    if(WINNER == BLANK && OVER == false)
    {
        //std::cout<<"debug"<<std::endl;
        OVER = true;
        for(int r = 0 ; r < 3 ; r++)
        {
            for(int c = 0 ; c < 3 ; c++)
            {
                if(BOARD.BOARD[r][c] == " ")
                {
                    OVER = false;
                }
            }
        }
    }
    
    GAME_OVER_OBJ O_OBJ;
    O_OBJ.GAME_OVER=OVER;
    O_OBJ.WINNER=WINNER;
    return O_OBJ;
}


void ITicTacToe::ChangePlayer()
{
    if(CURRENT_PLAYER == ZERO){CURRENT_PLAYER=CROSS;return;};
    if(CURRENT_PLAYER == CROSS){CURRENT_PLAYER=ZERO;return;};
}


void ITicTacToe::PlayMove(int r,int c,BOARD_INPUTS PLAYER)
{
    BOARD.Update(r,c,PLAYER);
}


BOARD_INPUTS ITicTacToe::GetCurrentPlayer()
{
    return CURRENT_PLAYER;
}


void ITicTacToe::SetCurrentPlayer(BOARD_INPUTS PLAYER)
{
    this->CURRENT_PLAYER = PLAYER;
}


void ITicTacToe::Start(BOARD_INPUTS START_PLAYER)
{
    SetCurrentPlayer(START_PLAYER);
    while (GAME_STATUS.GAME_OVER != true)
    {
        GameImplement();
        ChangePlayer();
        GAME_STATUS = IsGameOver(BOARD);
    }

    OnGameOver(GAME_STATUS);
    
}


int ITicTacToe::CHECK_ARRAY_FOR_MOVE(std::vector<std::string> ARR,BOARD_INPUTS INP)
{
    int counter = 0;
    int blank_at = -1;
    for(int i = 0 ; i < 3 ; i++)
    {
        if(ARR[i] == BOARD_INPUT_STR(INP)){counter++;};
        if(ARR[i] == BOARD_INPUT_STR(BLANK)){blank_at = i;};
    }
    if(counter == 2){return blank_at;}
    else{return -1;};
}


GAME_MOVE ITicTacToe::GetComputerMove(BOARD_INPUTS PLAYER,int COMPUTER_MOVE_COUNT,int USER_MOVE_COUNT)
{
    BOARD_INPUTS AGAINST = BLANK;
    if(PLAYER == CROSS){AGAINST = ZERO;};
    if(PLAYER == ZERO){AGAINST = CROSS;};

    GAME_MOVE PREVENT_LOSE ; PREVENT_LOSE.ROW = -1; PREVENT_LOSE.COL =-1;
    GAME_MOVE WINNIG_MOVE ; WINNIG_MOVE.ROW = -1 ; WINNIG_MOVE.COL = -1;

    std::vector<std::string> R1 = { BOARD.BOARD[0][0] , BOARD.BOARD[0][1] , BOARD.BOARD[0][2]};
    std::vector<std::string> R2 = { BOARD.BOARD[1][0] , BOARD.BOARD[1][1] , BOARD.BOARD[1][2]};
    std::vector<std::string> R3 = { BOARD.BOARD[2][0] , BOARD.BOARD[2][1] , BOARD.BOARD[2][2]};

    std::vector<std::string> C1 = { BOARD.BOARD[0][0] , BOARD.BOARD[1][0] , BOARD.BOARD[2][0]};
    std::vector<std::string> C2 = { BOARD.BOARD[0][1] , BOARD.BOARD[1][1] , BOARD.BOARD[2][1]};
    std::vector<std::string> C3 = { BOARD.BOARD[0][2] , BOARD.BOARD[1][2] , BOARD.BOARD[2][2]};

    std::vector<std::string> D1 = { BOARD.BOARD[0][0] , BOARD.BOARD[1][1] , BOARD.BOARD[2][2]};
    std::vector<std::string> D2 = { BOARD.BOARD[0][2] , BOARD.BOARD[1][1] , BOARD.BOARD[2][0]};


    //Check if Loss Possible
    if(CHECK_ARRAY_FOR_MOVE(R1,AGAINST) != -1){PREVENT_LOSE.ROW=0; PREVENT_LOSE.COL=CHECK_ARRAY_FOR_MOVE(R1,AGAINST);};
    if(CHECK_ARRAY_FOR_MOVE(R2,AGAINST) != -1){PREVENT_LOSE.ROW=1; PREVENT_LOSE.COL=CHECK_ARRAY_FOR_MOVE(R2,AGAINST);};
    if(CHECK_ARRAY_FOR_MOVE(R3,AGAINST) != -1){PREVENT_LOSE.ROW=2; PREVENT_LOSE.COL=CHECK_ARRAY_FOR_MOVE(R3,AGAINST);};

    if(CHECK_ARRAY_FOR_MOVE(C1,AGAINST) != -1){PREVENT_LOSE.COL=0; PREVENT_LOSE.ROW=CHECK_ARRAY_FOR_MOVE(C1,AGAINST);};
    if(CHECK_ARRAY_FOR_MOVE(C2,AGAINST) != -1){PREVENT_LOSE.COL=1; PREVENT_LOSE.ROW=CHECK_ARRAY_FOR_MOVE(C2,AGAINST);};
    if(CHECK_ARRAY_FOR_MOVE(C3,AGAINST) != -1){PREVENT_LOSE.COL=2; PREVENT_LOSE.ROW=CHECK_ARRAY_FOR_MOVE(C3,AGAINST);};

    if(CHECK_ARRAY_FOR_MOVE(D1,AGAINST) != -1){PREVENT_LOSE.ROW=CHECK_ARRAY_FOR_MOVE(D1,AGAINST);PREVENT_LOSE.COL=CHECK_ARRAY_FOR_MOVE(D1,AGAINST);};
    if(CHECK_ARRAY_FOR_MOVE(D2,AGAINST) != -1){PREVENT_LOSE.ROW=CHECK_ARRAY_FOR_MOVE(D2,AGAINST);PREVENT_LOSE.COL=2-CHECK_ARRAY_FOR_MOVE(D2,AGAINST);};

    //Check for any Winning Move
    if(CHECK_ARRAY_FOR_MOVE(R1,PLAYER) != -1){WINNIG_MOVE.ROW=0; WINNIG_MOVE.COL=CHECK_ARRAY_FOR_MOVE(R1,PLAYER);};
    if(CHECK_ARRAY_FOR_MOVE(R2,PLAYER) != -1){WINNIG_MOVE.ROW=1; WINNIG_MOVE.COL=CHECK_ARRAY_FOR_MOVE(R2,PLAYER);};
    if(CHECK_ARRAY_FOR_MOVE(R3,PLAYER) != -1){WINNIG_MOVE.ROW=2; WINNIG_MOVE.COL=CHECK_ARRAY_FOR_MOVE(R3,PLAYER);};

    if(CHECK_ARRAY_FOR_MOVE(C1,PLAYER) != -1){WINNIG_MOVE.COL=0; WINNIG_MOVE.ROW=CHECK_ARRAY_FOR_MOVE(C1,PLAYER);};
    if(CHECK_ARRAY_FOR_MOVE(C2,PLAYER) != -1){WINNIG_MOVE.COL=1; WINNIG_MOVE.ROW=CHECK_ARRAY_FOR_MOVE(C2,PLAYER);};
    if(CHECK_ARRAY_FOR_MOVE(C3,PLAYER) != -1){WINNIG_MOVE.COL=2; WINNIG_MOVE.ROW=CHECK_ARRAY_FOR_MOVE(C3,PLAYER);};

    if(CHECK_ARRAY_FOR_MOVE(D1,PLAYER) != -1){WINNIG_MOVE.ROW=CHECK_ARRAY_FOR_MOVE(D1,PLAYER);WINNIG_MOVE.COL=CHECK_ARRAY_FOR_MOVE(D1,PLAYER);};
    if(CHECK_ARRAY_FOR_MOVE(D2,PLAYER) != -1){WINNIG_MOVE.ROW=CHECK_ARRAY_FOR_MOVE(D2,PLAYER);WINNIG_MOVE.COL=2-CHECK_ARRAY_FOR_MOVE(D2,PLAYER);};

    //Determine which move to to play , winning or prevent loss , if exist
    if(WINNIG_MOVE.ROW != -1 && WINNIG_MOVE.COL != -1)
    {
        return WINNIG_MOVE;
    }
    if(PREVENT_LOSE.ROW != -1 && PREVENT_LOSE.COL != -1)
    {
        return PREVENT_LOSE;
    }

    //If None Exist , play a random move
    GAME_MOVE MOVE;



    //Strategic Moves to be played , to prevent loss 
    if(COMPUTER_MOVE_COUNT == 0 && GetBoardCell(1,1)==" "){MOVE.ROW=1;MOVE.COL=1;return MOVE;}
    else if(USER_MOVE_COUNT == 1 && GetBoardCell(0,0)==BOARD_INPUT_STR(AGAINST)){MOVE.ROW=2;MOVE.COL=2;return MOVE;}
    else if(USER_MOVE_COUNT == 1 && GetBoardCell(2,2)==BOARD_INPUT_STR(AGAINST)){MOVE.ROW=0;MOVE.COL=0;return MOVE;}
    else if(USER_MOVE_COUNT == 1 && GetBoardCell(2,0)==BOARD_INPUT_STR(AGAINST)){MOVE.ROW=0;MOVE.COL=2;return MOVE;}
    else if(USER_MOVE_COUNT == 1 && GetBoardCell(0,2)==BOARD_INPUT_STR(AGAINST)){MOVE.ROW=2;MOVE.COL=0;return MOVE;}

    if(BOARD.BOARD[0][0] == " "){MOVE.ROW=0;MOVE.COL=0;return MOVE;}
    else if(BOARD.BOARD[2][2] == " "){MOVE.ROW=2;MOVE.COL=2;return MOVE;}
    else if(BOARD.BOARD[0][2] == " "){MOVE.ROW=0;MOVE.COL=2;return MOVE;}
    else if(BOARD.BOARD[2][0] == " "){MOVE.ROW=2;MOVE.COL=0;return MOVE;};

    // If None , Play the first empty cell available
    for(int r = 0 ; r < 3 ; r++)
    {
        for(int c = 0 ; c < 3 ; c++)
        {
            if(BOARD.BOARD[r][c]==" ")
            {
                MOVE.ROW=r;
                MOVE.COL=c;
                return MOVE;
            }
        }
    }

}


