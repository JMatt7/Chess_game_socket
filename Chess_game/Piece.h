#pragma once
#ifndef PIECE_H
#define PIECE_H


class Piece
{
public:
    Piece(char mColor) : mcColor(mColor) {}
    ~Piece(){}                              
    virtual char GetPiece() = 0;            
    char GetColor(){                         
        return mcColor;
    }

    bool PossibleMoves(int ActRow, int ActCol, int DestRow, int DestCol, Piece* Board[8][8]){
        Piece* Dest = Board[DestRow][DestCol];
        if ((Dest == 0) || (mcColor != Dest->GetColor())){
            return PossibleField(ActRow, ActCol, DestRow, DestCol, Board);
        }
        return false;
    }
private:
    virtual bool PossibleField(int ActRow, int ActCol,int DestRow, int DestCol, Piece* Board[8][8]) = 0;
    char mcColor;
};

#endif