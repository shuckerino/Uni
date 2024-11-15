#### Task 1: 
Aufgabe: Beschreiben Sie für eine t x k Matrix Motive den minimalen und den maximalen Wert von SCORE(Motive)
- min: 0 (wenn jede Spalte nur aus dem häufigsten Symbol)
- max: t - round_up(4/t) (da gleichverteilt reicht für konsensus) -> auch round_down((3 / 4) * t)


#### Task 2: 
Aufgabe: Alternativ bzw. analog zur Berechnung von SCORE(Motive) können auch die Entropie-Werte der einzelnen Spalten von Motive zu einer Gesamt-Entropie 
der Matrix aufaddiert werden. Bestimmen Sie nach dieser Regel die Entropie 
der Matrix des NF-κB Motives aus dem Seminar.
- 1. Spalte: 1.157
- 2. Spalte: 1.371
- 3. Spalte: 0.332
- 4. Spalte: 0.332
- 5. Spalte: 0.469
- 6. Spalte: 0.469
- 7. Spalte: 0.469
- 8. Spalte: 1.361
- 9. Spalte: 0.922
- 10. Spalte: 1.157
- 11. Spalte: 1.571
- 12. Spalte: 0.971
- Gesamt: 8.581

#### Task 3:
Aufgabe: Was ist der maximale und was der minimale Wert für den Informationsgehalt, 
und bei welchen Eingaben tritt jeder dieser Extremwerte auf?
Entropie:
- min: 0 (wenn in jeder Spalte genau eine 1)
- max: 2 (wenn jedes Symbol 0.25)

Informationsgehalt = 2 - Entropie
- min: 0 (wenn jedes Symbol 0.25)
- max: 2 (wenn in jeder Spalte genau eine 1)