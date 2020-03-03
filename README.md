# MultiPlayer Terminal Chess Game
Project is my implementation of chess game in which I used socket to create multiplayer chess's session. The program was created for college's classes "Network Programming". Project uses a standard chess game with TCP connection beetwen two players.

## Table of contents
* [GamePlay](#gameplay)
* [Installation](#installation)
* [Technologies](#Technologies)
* [Features](#Features)
* [Status](#Status)

## Gameplay
[![Watch the video](https://www.chess.com/bundles/web/images/offline-play/standardboard.6a504885.png)](https://youtu.be/hwKT_WnOBUc)


## Installation
Server side
```
gcc Server.cpp -o Server
./Server PORT_NUMBER
```
PORT_NUMBER - defines on which port the server is listening for connection

Client side
```
gcc Client.cpp -o Client
./Client IP_ADDRESS PORT_NUMBER
```
IP_ADDRESS - server's ip address
PORT_NUMBER - must be the same as server's PORT NUMBER

After the connection on terminal will be displayed short instructions how to play. 

## Technologies
* C++ - version C++14
* Socket libraries

## Features
List of implemented things:
* connection beetwen players
* Pawn can move 2 square as first move
* Pawn promotion
* Check

To-Do list:
* Player's SQL database
* Ranking
* GUI
* En passant
* Castling

## Status
Suspended
