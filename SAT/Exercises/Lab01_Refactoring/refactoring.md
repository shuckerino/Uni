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
    - Geringe Abhängigkeiten (Kopplung) -> Implementierung der Funktion kann zentral geändert werden
    - Höhere Kohäsion -> Code innerhalb einer Funktion ist logisch stark miteinander verbunden

## 2. Refactoring und Testbarkeit von VierGewinnt

### Welches sind die größten Probleme im Hinblick auf Unit-Testbarkeit?
- Die zu testenden Funktionen so aufbauen, dass diese...
    - eine geringe Kopplung besitzen, sodass die Funktion unabhängig getestet werden kann und nötige Abhängigkeiten der Funktion mitgegeben werden können (besonders wichtig zum Mocken von Objekten, Datenbankverbindungen etc.)
    - eine hohe Kohäsion besitzen, sodass eine einzelne Funktion meiner Anwendung getestet werden kann (und man dann auch herausfinden kann, was der Fehler ist)
    