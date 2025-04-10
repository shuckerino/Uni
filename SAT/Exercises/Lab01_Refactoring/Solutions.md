# Refactoring

## 1. Recherche

### Was bedeutet Refactoring?
- Änderung an der Struktur / Architektur der Codebasis
- Entfernen von Altlasten (Legacy Code) und ungenutztem Code (Dead Code)
- Verbesserung der Wartbarkeit der Codebasis durch bessere Organisation und Dokumentation der Codebasis
- Beispiele für Refactoring auf dieser [Website](https://www.refactoring.com/catalog/extractFunction.html)

### Beispiel für Refactoring-Maßnahme: "Extract Function"
- Codeabschnitte und Methoden, die ziemlich lange sind, können meist in einzelne Untermethoden aufgeteilt werden
- Code muss dabei in kleinere, aber logisch zusammenhängende Bausteine unterteilt werden
- Für jeden logischen Baustein könnte theoretisch eine eigene Funktion / Methode angelegt werden
- Statt des ehemaligen Codes wird nun die Funktion / Methode aufgerufen
- Vorteile:
    - Höhere Wiederverwendbarkeit von viel genutzten Codeabschnitten
    - Höhere Abhängigkeiten (Kopplung) -> Implementierung der Funktion kann zentral geändert werden
    - Höhere Kohäsion -> Code innerhalb einer Funktion ist logisch stark miteinander verbunden

## 2. Refactoring und Testbarkeit von VierGewinnt

### Welches sind die größten Probleme im Hinblick auf Unit-Testbarkeit?
- Die zu testenden Funktionen so aufbauen, dass diese...
    - eine geringe Kopplung besitzen, sodass die Funktion unabhängig getestet werden kann und nötige Abhängigkeiten der Funktion mitgegeben werden können (besonders wichtig zum Mocken von Objekten, Datenbankverbindungen etc.)
    - eine hohe Kohäsion besitzen, sodass eine einzelne Funktion meiner Anwendung getestet werden kann (und man dann auch herausfinden kann, was der Fehler ist)

## 3. Refactoring und neuer Entwurf
- Ziel: "Bessere" objektorientierte Lösung erarbeiten und dokumentieren

Änderungen:
- Erstellen sinnvoller Objekte, die jeweils Methoden und Variablen beinhalten (aktuell alles static-Methoden, schlecht für Testbarkeit später)
    - Player (enthält Name und Symbol)
    - Board (repräsentiert das Spielfeld)
    - IO_Handler (kümmert sich um alle Ein- und Ausgaben)
    - WinChecker (kümmert sich um das Überprüfen, ob das Spiel zu Ende ist)
    - VierGewinnt (repräsentiert das Spiel an sich)
- Aufteilung in kleinere Funktionen, die logisch zusammenhängen
- VierGewinnt durch Dependency Injection erweitert, sodass besser testbar

## 4. Entwurfskonzepte

### Kohäsion
- Beschreibt die inhaltliche Zusammengehörigkeit einer Komponente
- Kohäsion wurde durch die Refactoring-Maßnahmen erhöht (GUT!), wie beispielsweise an der Klasse Board zu erkennen ist
    - Die Klasse Board kümmert sich nun ausschließlich um die Verwaltung des Zustands des Spielfeldes
    - Es hat keinerlei Bezug zu anderen Aufgaben wie Spielermanagement etc.

### Kopplung
- Beschreibt die Abhängigkeiten zwischen mehrerer Komponenten
- Kopplung wurde durch die Refactoring-Maßnahmen erhöht (NICHT SO GUT!), wie beispielsweise an der Klasse VierGewinnt zu erkennen ist
    - Die Klasse ist nun an alle anderen Klassen wie Board, Player oder WinChecker gebunden
    - Änderungen in einer Klasse kann zu Folge haben, dass ich auch an den anderen Klassen Änderungen vornehmen muss

### Separation of concern
- Beschreibt Prinzip, dass Design so aufgeteilt werden soll, dass die Schnittmenge der Funktionalitäten so gering wie möglich ist
- Hat hier noch nicht so gut funktioniert, da beispielsweise print-statements in nahezu allen Klassen vorkommen (auch wenn ausgelagert durch IO_Handler, der Aufruf ist immer noch in allen Klassen vorhanden -> eventuell Lösung durch Aspekt-Orientierte-Programmierung)
    