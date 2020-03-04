#include "Piece.h"
#pragma once
#ifndef KING_H
#define KING_H

class King:public Piece
{
public:
    King(char mColor): Piece(mColor){}
    ~King(){}
private:
    virtual char GetPiece(){
        return 'K';
    }
    bool PossibleField(int ActRow, int ActCol, int DestRow, int DestCol, Piece* Board[8][8])
    {   //sprawdzamy wszykie pola mozliwe dla ruchu krola 
        //check if all neighboring field is available for king's move
        int RowD = DestRow - ActRow;
        int ColD = DestCol - ActCol;

        if(((RowD >= -1) && (RowD <= 1)) && ((ColD >= -1) && (ColD <= 1)))
        {
            return true;
        }
        return false;
    }

};
#endif