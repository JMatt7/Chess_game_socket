#include "Piece.h"
#pragma once
#ifndef KNIGHT_H
#define KNIGHT_H


class Knight : public Piece
{
public:
    Knight(char mColor): Piece(mColor){}
    ~Knight(){}

private:
    virtual char GetPiece(){
        return 'N';
    }
    bool PossibleField(int ActRow, int ActCol, int DestRow, int DestCol, Piece* Board[8][8]){
        //Check if destination is not occupied by friendly piece or is occupied by enemy piece
        if((ActCol == DestCol + 1) || (ActCol == DestCol -1)){
            if ((ActRow == DestRow + 2) || (ActRow == DestRow - 2)){
                return true;
            }
        }
        if((ActCol == DestCol + 2) || (ActCol == DestCol -2)){
            if ((ActRow == DestRow + 1) || (ActRow == DestRow - 1)){
                return true;
            }
        }
        return false;

    }

};

#endif