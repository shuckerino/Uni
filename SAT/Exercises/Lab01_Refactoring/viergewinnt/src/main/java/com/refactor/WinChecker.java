package com.refactor;

public class WinChecker {
   
    
    public boolean IsGameOver(char[][] spielfeld, int column, int row, char zeichen) {
            boolean b1 = GameIsOver_row(spielfeld, column, row, zeichen);
            boolean b2 = GameIsOver_column(spielfeld, column, row, zeichen);
            boolean b3 = GameIsOver_straight1(spielfeld, column, row, zeichen);
            boolean b4 = GameIsOver_straight2(spielfeld, column, row, zeichen);
            
            return (b1||b2||b3||b4);
    }

    public boolean GameIsOver_row(char[][] spielfeld, int column, int row, char zeichen) {
            // nach links
            int go = row - 1; // mit dem Punkt links neber dem gesetzten beginne
                                                    // ich
            int i = 1; // der gesetzte Punkt = 1 Treffer
            while (go >= 0) {
                    if (spielfeld[column][go] != zeichen)
                            break;
                    go--;
                    i++;
            }

            // nach rechts
            go = row + 1;
            while (go < spielfeld.length) {

                    if (column == 7 || go == 7){
                        //c
                        System.out.println("Test");
                    }
                    if (spielfeld[column][go] != zeichen)
                            break;
                    go++;
                    i++;
            }

            return (i > 3);
    }

    public boolean GameIsOver_column(char[][] spielfeld, int column, int row, char zeichen) {
            // nach oben
            int go = column - 1;
            int i = 1;
            while (go >= 0) {
                    if (spielfeld[go][row] != zeichen)
                            break;
                    go--;
                    i++;
            }

            // nach unten
            go = column + 1;
            while (go < spielfeld.length) {
                    if (spielfeld[go][row] != zeichen)
                            break;
                    go++;
                    i++;
            }

            return (i > 3);
    }

    public boolean GameIsOver_straight1(char[][] spielfeld, int column, int row, char zeichen) {
            // nach links oben
            int go = row - 1;
            int go2 = column - 1;
            int i = 1;
            while (go >= 0 && go2 >= 0) {
                    if (spielfeld[go2][go] != zeichen)
                            break;
                    go--;
                    go2--;
                    i++;
            }

            // nach rechts unten
            go = row + 1;
            go2 = column + 1;
            while (go < spielfeld[0].length && go2 < spielfeld.length) {
                    if (spielfeld[go2][go] != zeichen)
                            break;
                    go++;
                    go2++;
                    i++;
            }

            return (i > 3);
    }

    public boolean GameIsOver_straight2(char[][] spielfeld, int column, int row, char zeichen) {
            // nach links unten
            int go = row - 1;
            int go2 = column + 1;
            int i = 1;
            while (go >= 0 && go2 < spielfeld.length) {
                    if (spielfeld[go2][go] != zeichen)
                            break;
                    go--;
                    go2++;
                    i++;
            }

            // nach rechts oben
            go = row + 1;
            go2 = column - 1;
            while (go < spielfeld[0].length && go2 >= 0) {
                    if (spielfeld[go2][go] != zeichen)
                            break;
                    go++;
                    go2--;
                    i++;
            }

            return (i > 3);
    }

}
