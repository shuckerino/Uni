package com.refactor;

public class Player {

    private String playerName;
    private Character playerSymbol;

    public Player(String _name, Character _symbol){
        playerName = _name;
        playerSymbol = _symbol;
    }

    public String getPlayerName(){
        return this.playerName;
    }

    public Character getPlayerSymbol(){
        return this.playerSymbol;
    }
}
