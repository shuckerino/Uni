package com.refactor;

import java.io.InputStream;
import java.io.PrintStream;

public class IO_Handler {

        static PrintStream outputStream;
        static PrintStream errorStream;
        static java.util.Scanner inputScanner;

        // Constructor
        public IO_Handler(InputStream inputStr, PrintStream outputStr, PrintStream errorStr){
                outputStream = outputStr;
                errorStream = errorStr;
                inputScanner = new java.util.Scanner(inputStr);
        }

         /**
         * @param text -> Bildschirmausgabe
         * @return -> Tastatureingabe
         */
        int eingabeInt(String text) {
                outputStream.print(text);
                return inputScanner.nextInt();
        }

        /**
         * @param text -> Bildschirmausgabe
         * @return -> Tastatureingabe
         */
        String eingabeString(String text) {
                outputStream.print(text);
                return inputScanner.next();
        }
}
