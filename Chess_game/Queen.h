#include "Piece.h"
#pragma once
#ifndef QUEEN_H
#define QUEEN_H
class Queen : public Piece
{
public:
    Queen(char mColor): Piece(mColor){}
    ~Queen(){}
private:
    virtual char GetPiece(){
        return 'Q';
    }
    bool PossibleField(int ActRow, int ActCol, int DestRow, int DestCol, Piece* Board[8][8])
    {
    if(ActRow == DestRow){
            //check if the all fields by column is empty to make a move
            int ColOffset = (DestCol - ActCol > 0) ? 1 : -1;
            for(int CheckKol = ActCol + ColOffset; CheckKol != DestCol; CheckKol = CheckKol + ColOffset){
                if(Board[ActRow][CheckKol] != 0){
                    return false;
                }
            }
            return true;
        }else if(DestCol == ActCol){
            //check if the all fields by row is empty to make a move
            int RowOffset = (DestRow - ActRow > 0) ? 1 : -1;
            for(int CheckRow = ActRow + RowOffset; CheckRow != DestRow; CheckRow = CheckRow + RowOffset){
                if(Board[CheckRow][ActCol] != 0){
                    return false;
                }
            }
            return true;
        }else if((DestCol - ActCol == DestRow - ActRow) || (DestCol - ActCol == ActRow - DestRow)){
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