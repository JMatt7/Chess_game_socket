#include "Piece.h"
#pragma once
#ifndef BISHOP_H
#define BISHOP_H

class Bishop: public Piece
{
public:
    Bishop(char mColor): Piece(mColor){}
    ~Bishop(){}
private:
    virtual char GetPiece(){
        return 'B';
    }
    bool PossibleField(int ActRow, int ActCol, int DestRow, int DestCol, Piece* Board[8][8]){
        if((DestCol - ActCol == DestRow - ActRow) || (DestCol - ActCol == ActRow - DestRow)){
            //check if every field by diagonal is not occupied to make a move 
            int RowOffset = (DestRow - ActRow > 0) ? 1 : -1;
            int ColOffset = (DestCol - ActCol > 0) ? 1 : -1;
            int CheckRow;
            int CheckKol;
            for(CheckRow = ActRow + RowOffset, CheckKol = ActCol + ColOffset; CheckRow != DestRow; CheckRow = CheckRow + RowOffset, CheckKol = CheckKol + ColOffset){
                if(Board[CheckRow][CheckKol] != 0){
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

#endif
