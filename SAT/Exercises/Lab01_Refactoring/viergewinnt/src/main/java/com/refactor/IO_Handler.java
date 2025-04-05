package com.refactor;

import java.io.InputStream;
import java.io.PrintStream;

public class IO_Handler {

        private PrintStream outputStream;
        private PrintStream errorStream;
        private java.util.Scanner inputScanner;

        // Constructor
        public IO_Handler(InputStream inputStr, PrintStream outputStr, PrintStream errorStr){
                outputStream = outputStr;
                errorStream = errorStr;
                inputScanner = new java.util.Scanner(inputStr);
        }

        public int eingabeInt(String text) {
                outputStream.print(text);
                return inputScanner.nextInt();
        }

        public String eingabeString(String text) {
                outputStream.print(text);
                return inputScanner.next();
        }

        public void printError(String errorMsg){
            errorStream.print(errorMsg);
        }

        public void printOutput(StringBuffer outputMsgBuffer){
            outputStream.print(outputMsgBuffer);
        }
        
        public void printOutput(String outputMsg){
            outputStream.print(outputMsg);
        }
}
