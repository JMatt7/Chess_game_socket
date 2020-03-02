#include "Piece.h"
#pragma once
#ifndef PAWN_H
#define PAWN_H
class Pawn : public Piece
{
public:
    Pawn(char mColor): Piece(mColor) {}
    ~Pawn(){}

private:
    virtual char GetPiece(){
        return 'P';
    }

    bool PossibleField(int ActRow, int ActCol, int DestRow, int DestCol, Piece* Board[8][8]){
        Piece* Dest = Board[DestRow][DestCol];
        if(Dest == 0){
            //Check if on the destination field is not occupied by friendly piece
            if(ActCol == DestCol){
                if(GetColor() == 'W'){
                    if(DestRow == ActRow + 2 && ActRow == 1){
                        return true;
                    }
                    else if(DestRow == ActRow + 1){
                        return true;
                    }
                    
                }else{
                    if(DestRow == ActRow - 2 && ActRow == 6){
                        return true;
                    }
                    else if (DestRow == ActRow - 1){
                        return true;
                    }
                }
            }
        }
        else{
            //Check if on the destination field is occupied by enemy pawn
            if((ActCol == DestCol + 1)|| (ActCol == DestCol - 1)){
                if(GetColor() == 'W'){
                    if(DestRow == ActRow + 1){
                        return true;
                    }
                }else{
                    if(DestRow == ActRow - 1){
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

#endif