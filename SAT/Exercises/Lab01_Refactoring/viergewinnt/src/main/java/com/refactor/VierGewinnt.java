package com.refactor;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;

public class VierGewinnt {

        private Player player1;
        private Player player2;
        private IO_Handler io_Handler;
        private Board gameBoard;
        private WinChecker winChecker;

        // Custom constructor
        public VierGewinnt(Player p1, Player p2, IO_Handler io_handler, Board gameBoard, WinChecker winChecker) {
                this.player1 = p1;
                this.player2 = p2;
                this.io_Handler = io_handler;
                this.gameBoard = gameBoard;
                this.winChecker = winChecker;
        }

        public static VierGewinnt createDefaultGame(){

                // Create IO handler
                final InputStream in = InputStream.nullInputStream();
                final ByteArrayOutputStream out = new ByteArrayOutputStream();
                final ByteArrayOutputStream err = new ByteArrayOutputStream();
                IO_Handler io_Handler = new IO_Handler(in, new PrintStream(out), new PrintStream(err));
                
                // Create players
                Player player1 = new Player(io_Handler.eingabeString("Name von SpielerIn A mit Zeichen o\t\t\t: "), 'o');
                Player player2;

                do {
                        player2 = new Player(io_Handler.eingabeString("Name von SpielerIn B mit Zeichen x\t\t\t: "),
                                        '+');
                } while (player1.getPlayerName().equals(player2.getPlayerName())); // Frage erneut, wenn die
                                                                                   // Spielernamen gleich sind

                // Create game board
                int rows = 0, cols = 0;
                do {
                        cols = io_Handler.eingabeInt("Breite des Spielfeldes (mindestens 4)\t: ");
                } while (cols < 4); // Frage erneut, wenn die Breite zu klein gew�hlt wurde

                do {
                        rows = io_Handler.eingabeInt("Hoehe des Spielfeldes (mindestens 4)\t: ");
                } while (rows < 4); // Frage erneut, wenn die H�he zu klein gew�hlt wurde
                Board board = new Board(rows, cols);
                WinChecker winChecker = new WinChecker();

                return new VierGewinnt(player1, player2, io_Handler, board, winChecker);
        }

        // Main play function
        public void play() {
                int zaehler = 0, eingabe;
                Player winner = null;

                while (zaehler < gameBoard.getNumCols() * gameBoard.getNumRows() && winner == null) {
                        Player playerWithTurn = (zaehler % 2 == 0) ? player1 : player2;
                        gameBoard.showSpielfeld(io_Handler);
                        eingabe = io_Handler.eingabeInt("\n" + playerWithTurn.getPlayerName() + "(" + playerWithTurn.getPlayerSymbol()
                                        + ") ist am Zug. Bitte gib die Spalte ein: ");
                        if (eingabe > gameBoard.getNumCols() || eingabe < 1)
                                io_Handler.printError("Feld existriert nicht.. Bitte versuch es nochmal!");
                        else {
                                zaehler++; // naechster Bitte
                                winner = gameBoard.setzeFeld(eingabe, playerWithTurn, winChecker, io_Handler);
                        }
                }
                if (winner == null) {
                        gameBoard.showSpielfeld(io_Handler);
                        io_Handler.printOutput("Unentschieden!");
                }
        }
}