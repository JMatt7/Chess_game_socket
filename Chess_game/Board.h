#include "Piece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include <iostream>
#pragma once
#ifndef BOARD_H
#define BOARD_H


using namespace std;


class CBoard
{
    public:
        CBoard(){

            //board initialization
            for(int Row = 0; Row < 8; ++Row){
                for(int Col = 0; Col < 8; ++Col){
                    Board[Row][Col] = 0;
                }
            }

            //deployment and set black pieces
            for(int Col = 0; Col < 8; ++Col){
                Board[6][Col] = new Pawn('B');
            }
            Board[7][0] = new Rook('B');
            Board[7][1] = new Knight('B');
            Board[7][2] = new Bishop('B');
            Board[7][3] = new King('B');
            Board[7][4] = new Queen('B');
            Board[7][5] = new Bishop('B');
            Board[7][6] = new Knight('B');
            Board[7][7] = new Rook('B');

            //deployment and set white pieces
            for(int Col = 0; Col < 8; ++Col){
                Board[1][Col] = new Pawn('W');
            }
            Board[0][0] = new Rook('W');
            Board[0][1] = new Knight('W');
            Board[0][2] = new Bishop('W');
            Board[0][3] = new King('W');
            Board[0][4] = new Queen('W');
            Board[0][5] = new Bishop('W');
            Board[0][6] = new Knight('W');
            Board[0][7] = new Rook('W');
        }
        //board deinitialization
        ~CBoard(){
            for(int Row = 0; Row <8; ++Row){
                for(int Col = 0; Col < 8; ++Col){
                    delete Board[Row][Col];
                    Board[Row][Col] = 0;
                }
            }
        }

        void Print(){

            const int FieldWidth = 4;
            const int FieldHeight = 3;

            for(int Row = 0; Row < 8*FieldHeight; ++Row){
                int FieldRow = Row/FieldHeight;
                //sides with number
                if(Row % 3 == 1){
                    cout<<"-"<<(char)('1' + 7 - FieldRow)<<"-";
                }else{
                    cout<<"---";
                }

                //chess board
                for(int Col = 0; Col < 8*FieldWidth; ++Col){
                    int FieldCol = Col/FieldWidth;
                    if(((Row % 3) == 1) && ((Col % 4 ) == 1 || (Col % 4 ) == 2) && Board[7-FieldRow][FieldCol] != 0){
                        if((Col % 4) == 1 ){
                            cout<<Board[7-FieldRow][FieldCol]->GetColor();
                        }else{
                            cout<<Board[7-FieldRow][FieldCol]->GetPiece();
                        }
                    }else{
                        if((FieldRow + FieldCol) % 2 == 1){
                            cout<<"*";
                        }else{
                            cout<<" ";
                        }
                    }
                }
                cout<<endl;
            }
            //Bottom with numbers
            for(int Row = 0; Row < FieldHeight; ++Row){
                if(Row % 3 == 1){
                    cout<<"---";
                    for(int Col = 0; Col < 8*FieldWidth; ++Col){
                        int FieldCol = Col/FieldWidth;
                        if((Col % 4) == 1){
                            cout<<(FieldCol + 1);
                        }else{
                            cout<<"-";
                        }
                    }
                    cout<<endl;
                }else{
                    for(int Col = 1; Col <9*FieldWidth; ++Col){
                        cout<<"-";
                    }
                    cout<<endl;
                }
            }
            cout<<"\n";
            cout<<"\n";
            cout<<"\n";

        }

        bool Check(char mColor){
            //find the king
            int KingRow;
            int KingCol;
            for(int Row = 0; Row<8; ++Row){
                for(int Col = 0; Col <8; ++Col){
                    if(Board[Row][Col] != 0){
                        if(Board[Row][Col]->GetColor() == mColor){
                            if(Board[Row][Col]->GetPiece() == 'K'){
                                KingCol = Col;
                                KingRow = Row;
                            }
                        }
                    }
                }
            }

            //check if the enemy pieces are able to check the king
            for(int Row = 0; Row <8; ++Row){
                for(int Col = 0; Col <8; ++Col){
                    if(Board[Row][Col] != 0){
                        if(Board[Row][Col] -> GetColor() != mColor){
                            if(Board[Row][Col]->PossibleMoves(Row, Col, KingRow, KingCol, Board)){
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
        }

        bool Move(char mColor){
            //check every piece
            for(int Row = 0; Row <8; ++Row){
                for(int Col = 0; Col<8; ++Col){
                    if(Board[Row][Col] != 0){
                        //if this a piece of player who has a turn, check possible moves
                        if(Board[Row][Col]->GetColor() == mColor){
                            for(int MoveRow = 0; MoveRow <8; ++MoveRow){
                                for(int MoveCol = 0; MoveCol <8; ++MoveCol){
                                    if(Board[Row][Col]->PossibleMoves(Row, Col, MoveRow, MoveCol, Board)){
                                        //make a move and check if the king is in check
                                        Piece* Temp = Board[MoveRow][MoveCol];
                                        Board[MoveRow][MoveCol] = Board[Row][Col];
                                        Board[Row][Col] == 0;
                                        bool bMove = !Check(mColor);
                                        //undo move
                                        Board[Row][Col] = Board[MoveRow][MoveCol];
                                        Board[MoveRow][MoveCol] = Temp;
                                        if(bMove){
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            return false;
        }

    
    Piece* Board[8][8];
};

#endif