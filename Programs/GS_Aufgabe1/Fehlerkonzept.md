Fehlerkonzept für den RPN Taschenrechner

Praktikumsufgabe 1 | Tim Behrens, Nishan Khatiwada

Ziel: Die Fehler sollen in einem einheitlichen Muster auftreten, um den Ursprung des Fehlers nachverfolgen zu können.

Konzept:
Bei jeder Funktion wird ein return Wert zurückgegeben, der entweder beschreibt ob alles okay ist oder ob ein Fehler aufgetreten ist. Jeder Fehler erhält hierbei einen einzigartigen negativen Wert als Fehlercode. Der Wert ist 0, wenn kein Fehler auftritt.
Dadurch werden die Ergebnisse von den Funktionen nicht über den return Wert zurückgegeben, sondern die Funktion holt sich den Wert über Call-by-Reference selbst.
Die möglichen Fehlercodes die eine Funktion werfen kann, sind im jeweiligen Header dokumentiert

Fehlercodes:
0, ERR_OK, Erfolg
(-1), ERR_STACK_OVERFLOW, Ablegen auf vollen Stack
(-2), ERR_STACK_UNDERFLOW, Zu wenige Werte auf dem Stack
(-3), ERR_OUT_OF_RANGE, Ergebnis passt nicht in einen Integer
(-4), ERR_DIV_BY_0, Division durch 0
(-5), ERR_OVERFLOW_DURING_INPUT, Eingegebene Zahl ist zu groß
(-6), ERR_UNEXPECTED_INPUT, Unerwarter Token oder Tastendruck