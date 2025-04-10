package com.refactor;

public class Board {

    // Members
    private int rows;
    private int cols;
    private char[][] board_array;

    // Constructor
    public Board(int cols, int rows){
        this.rows = rows;
        this.cols = cols;
        this.board_array = new char[rows][cols];
    }

    // Getter
    public int getNumRows(){
        return this.rows;
    }

    public int getNumCols(){
        return this.cols;
    }

    public void showSpielfeld(IO_Handler io_handler) {
        StringBuffer Geruest = new StringBuffer();
        StringBuffer row_start = new StringBuffer(" "); // erste Zeile 1 2 3 4
        StringBuffer row_divide = new StringBuffer("|"); // Trennzeile |-----|
        StringBuffer row_end = new StringBuffer("-"); // letzte Zeile -------

        if (board_array[0].length > 9) {
                for (int i = 1; i <= board_array[0].length; i++)
                        row_start.append((i/10==0) ? " " : i/10).append(" ");
                row_start.append("\n ");
        }
        for (int i = 1; i <= board_array[0].length; i++) {
                row_start.append(i%10).append(" ");
                row_divide.append((i==board_array[0].length)? "-|" : "--");
                row_end.append("--");
        }
        io_handler.printOutput(row_start);
        io_handler.printOutput(row_divide);

        for (char[] arrZeile : board_array) { //iteriere durch alle Zeilen
                for (char arrSpalte : arrZeile) { //iteriere durch alle Spalten
                        Geruest.append("|");
                        Geruest.append((arrSpalte == '\0') ? ' ' : arrSpalte);
                }
                Geruest.append("|\n");
        }
        Geruest.append(row_end).append("\n");
        io_handler.printOutput(Geruest);
    }

    public Player setzeFeld(int column, Player currentPlayer, WinChecker winChecker, IO_Handler io_Handler) {
        column--; // Weil der gemeine Mensch denkt, der Zahlenbereich w�rde sich von 1 bis 4 erstrecken
        int pos2check;
        char zeichen = currentPlayer.getPlayerSymbol();
        if (board_array[0][column] != '\0'){
                io_Handler.printError("Die Reihe ist voll...Pech!");
                return null;
        }
        for (int i = 0; i < board_array.length; i++) { //Iteriere durch die Zeilen
            if (i + 1 == board_array.length) {
                // Nach der letzten Zeile kommt nichts mehr..
                // also darf in das aktuelle K�stchen geschrieben werden, obwohl im
                // n�chsten nichts steht
                pos2check = i;
                if (board_array[pos2check][column] == '\0') {
                    board_array[i][column] = zeichen;
                    if(winChecker.IsGameOver(board_array, i, column, zeichen)) {// Hat jmd gewonnen?
                        io_Handler.printOutput("Spieler mit " + zeichen + " hat gewonnen");
                        return currentPlayer;
                    }
                    break;
                }

            } else {
                // Check the following field 
                pos2check = i+1;
                if (board_array[pos2check][column] != '\0') {
                    board_array[i][column] = zeichen;
                    if(winChecker.IsGameOver(board_array, i, column, zeichen)) {// Hat jmd gewonnen?
                        io_Handler.printOutput("Spieler mit " + zeichen + " hat gewonnen");
                        return currentPlayer;
                    }
                    break;
                }
            }
        }
        return null;
    }
    
}
