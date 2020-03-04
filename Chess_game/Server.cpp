#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include "Piece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Board.h"

using namespace std;

class Chess
{
public:
    Chess(): PlayerTurn('W'){}
    ~Chess(){}

    void Start(int bytesRead, int bytesWritten, char newSd){
        Instruction();
        GameBoard.Print();
        do{
        char msg[1500];
        //waiting for client response
        cout << "Waiting on move White(Client)..." << endl;
        cout<<"Player's turn: White(Client) "<<endl; 
        memset(&msg, 0, sizeof(msg));//cleaning the bufor
        bytesRead += recv(newSd, (char*)&msg, sizeof(msg), 0);
        if(!strcmp(msg, "exit"))
        {
            cout << "Second player leave the session." << endl;
            break;
        }
        cout << "Move White(Client): " << msg << endl;
        int SelectedRow = msg[0] - 49;
        int SelectedCol = msg[1] - 49;
        int DestinationRow = msg[3] - 49;
        int DestinationCol = msg[4] - 49;
        int Promotion = msg[6] - 48;

        GetNextMove(GameBoard.Board,SelectedRow, SelectedCol, DestinationRow, DestinationCol, Promotion);
        AltPlayer();
        GameBoard.Print();
        cout<<"Player's turn Black(Server): "; 
        start1:
        cout<<"Move>"<<endl;
        string data;
        getline(cin, data);
        memset(&msg, 0, sizeof(msg)); //cleaning the buffor
        strcpy(msg, data.c_str());
        int SelectedRow1 = msg[0] - 49;
        int SelectedCol1 = msg[1] - 49;
        int DestinationRow1 = msg[3] - 49;
        int DestinationCol1 = msg[4] - 49;
        int Promotion1 = msg[6] - 48;
        if(data == "man"){
            Instruction();
            goto start1;
        }
        if(data == "exit")
        {
            //sending message to client about ending the connection
            send(newSd, (char*)&msg, strlen(msg), 0);
            break;
        }
        if(!GetNextMove(GameBoard.Board, SelectedRow1, SelectedCol1, DestinationRow1, DestinationCol1, Promotion1)){
            goto start1;
        }
        //sending move to client
        bytesWritten += send(newSd, (char*)&msg, strlen(msg), 0);
        AltPlayer();
        GameBoard.Print();
        }while(!GameOver());
        GameBoard.Print();
    }

    bool GetNextMove(Piece* Board[8][8], int SelectedRow, int SelectedCol, int DestinationRow, int DestinationCol, int Promotion){

        bool ValidMove = false;
            //check if the move is in game board and the current field is diffrent than destination field
            if((SelectedRow >= 0 && SelectedRow <= 7) && (SelectedCol >= 0 && SelectedCol <= 7) && (DestinationRow >=0 && DestinationRow <=7) && (DestinationCol >= 0 && DestinationCol <= 7)){
                //variable to keep current piece
                Piece* CurrPiece = Board[SelectedRow][SelectedCol];
                //check if the piece has the same color like player who has a turn
                if((CurrPiece != 0) && (CurrPiece->GetColor() == PlayerTurn)){
                    //check if the destination field is valid
                    if(CurrPiece->PossibleMoves(SelectedRow, SelectedCol, DestinationRow, DestinationCol, Board)){
                        //make a move
                        Piece* Temp = Board[DestinationRow][DestinationCol];
                        Board[DestinationRow][DestinationCol] = Board[SelectedRow][SelectedCol];
                        Board[SelectedRow][SelectedCol] = 0;
                        //check if the player isn't checked
                        if(!GameBoard.Check(PlayerTurn)){
                            ValidMove = true;
                        }else{//if is checked undo move
                            cout<<"King jest w szachu!"<<endl;
                            Board[SelectedRow][SelectedCol] = Board[DestinationRow][DestinationCol];
                            Board[DestinationRow][DestinationCol] = Temp;
                        }
                        //Piece promotion if the pawn is on the opposite edge on board
                        if(ValidMove && CurrPiece->GetPiece() == 'P' && (DestinationRow == 7 || DestinationRow == 0) && (0 < Promotion && Promotion <= 4)){
                            if(CurrPiece->GetColor() == 'W'){
                                int i = Promotion;
                                switch(i)
                                {
                                    case 1:
                                        Board[DestinationRow][DestinationCol] = 0;
                                        Board[DestinationRow][DestinationCol] = new Queen('W');
                                        break;
                                    case 2:
                                        Board[DestinationRow][DestinationCol] = 0;
                                        Board[DestinationRow][DestinationCol] = new Bishop('W');
                                        break;
                                    case 3:
                                        Board[DestinationRow][DestinationCol] = 0;
                                        Board[DestinationRow][DestinationCol] = new Knight('W');
                                        break;
                                    case 4:
                                        Board[DestinationRow][DestinationCol] = 0;
                                        Board[DestinationRow][DestinationCol] = new Rook('W');
                                        break;
                                }
                            }else{
                                int i = Promotion;
                                switch(i)
                                {
                                    case 1:
                                        Board[DestinationRow][DestinationCol] = 0;
                                        Board[DestinationRow][DestinationCol] = new Queen('B');
                                        break;
                                    case 2:
                                        Board[DestinationRow][DestinationCol] = 0;
                                        Board[DestinationRow][DestinationCol] = new Bishop('B');
                                        break;
                                    case 3:
                                        Board[DestinationRow][DestinationCol] = 0;
                                        Board[DestinationRow][DestinationCol] = new Knight('B');
                                        break;
                                    case 4:
                                        Board[DestinationRow][DestinationCol] = 0;
                                        Board[DestinationRow][DestinationCol] = new Rook('B');
                                        break;
                                }
                            
                            }
                            delete Temp;
                        }else if(ValidMove && CurrPiece->GetPiece() == 'P' && (DestinationRow == 7 || DestinationRow == 0) && (0 >= Promotion || Promotion > 4)){
                            cout<<"Repeat the move and chose the type of promotion "<<endl;
                            cout<<"Type of promotion:"<<endl;
                                cout<<"1 - Queen"<<endl;
                                cout<<"2 - Bishop"<<endl;
                                cout<<"3 - Knight"<<endl;
                                cout<<"4 - Rook"<<endl;
                            Board[SelectedRow][SelectedCol] = Board[DestinationRow][DestinationCol];
                            Board[DestinationRow][DestinationCol] = Temp;
                            ValidMove = false;
                        }else{
                            delete Temp;
                        }
                    }
                }
            }
            if(!ValidMove){
                cout<<"Invalid move!"<<endl;
                return false;
            }
        return true;
    }

    void AltPlayer(){
        PlayerTurn = (PlayerTurn == 'W') ? 'B': 'W';
    }

    bool GameOver(){
        //check if the current player can make a valid move if not checkmate
        bool bMove(false);
        bMove = GameBoard.Move(PlayerTurn);
        if(!bMove){
            if(GameBoard.Check(PlayerTurn)){
                AltPlayer();
                std::cout<<"Checkmate, "<<PlayerTurn<<" Wins!"<<std::endl;
            }else{
                std::cout<<"There is no valid move!"<<std::endl;
            }
        }
        return !bMove;
    }

    void Instruction(void){
        cout<<"Welcome in chess game!"<<endl;
        cout<<"Movements are performed alternately."<<endl;
        cout<<"To make move you give current field of piece and the destination field."<<endl;
        cout<<"You make a move in this template [Row Number][Column Number] [Row Destination][Column Destination]."<<endl;
        cout<<"If the pawn is on opposite site of the board you need to add promotion to your move"<<endl;
        cout<<"Type of promotion"<<endl;
        cout<<"1 - Queen"<<endl;
        cout<<"2 - Bishop"<<endl;
        cout<<"3 - Knight"<<endl;
        cout<<"4 - Rook"<<endl;
        cout<<"Example: [Row Number][Column Number] [Row Destination][Column Destination] [Promotion Number]."<<endl;
        cout<<"If you need this instructions during the game type man."<<endl;
        cout<<"Have a good game!"<<endl;
    }


private:
    CBoard GameBoard;
    char PlayerTurn;

};



int main(int argc, char *argv[])
{
    Chess Game;
    //give a port number to create socket
    if(argc != 2)
    {
        cerr << "Use: port number" << endl;
        exit(0);
    }
    int port = atoi(argv[1]);
    //create a socket and connection
    sockaddr_in servAddr;
    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);
 
    //socket created and start listening
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0)
    {
        cerr << "Problem z nawiazaniem polaczenia." << endl;
        exit(0);
    }
    //assign socket to local adrress
    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr,sizeof(servAddr));
    if(bindStatus < 0)
    {
        cerr << "Issue with assign socket to local number." << endl;
        exit(0);
    }
    cout << "Waiting for connection with second player(Client)..." << endl;
    //listening up to 5 times
    listen(serverSd, 5);
    //get request from client and establish connection
    //assign new adres to connection with client
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);
    //acceptance, and creation new socket descriptor to establish connection
    int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if(newSd < 0)
    {
        cerr << "Issue with client's acceptance request!" << endl;
        exit(1);
    }
    cout << "Connected with z second player(clientem)!" << endl;
    //track data and time of the game
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    int bytesRead, bytesWritten = 0;
    Game.Start(bytesRead, bytesWritten, newSd);
    //closing descriptor after end of the connection
    gettimeofday(&end1, NULL);
    close(newSd);
    close(serverSd);
    cout << "********End of connection********" << endl;
    cout << "Game Duration: " << (end1.tv_sec - start1.tv_sec) << " seconds" << endl;
    cout << "Connection is ended." << endl;
    return 0;
}