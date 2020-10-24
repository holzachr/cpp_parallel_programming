# Future

Das nachfolgende Diagramm skizziert den Ablauf eines Multithreading-Szenarios 
mit `Future`- und `Promise`-Objekt:

![](Futures.png)

Man beachte, dass zwischen den beiden Objekten des Typs `Future` und `Promise` ein Datenkanal eingerichtet wird.

Die Thread-Prozedur erh�lt zum Ausf�hrungszeitpunkt einen `std::promise<>`-Zeiger / eine `std::promise<>`-Referenz �bergeben.

Daran k�nnen mit Hilfe der `set_value`-Methode Resultate vom Thread zum Thread-Erzeuger transferiert werden.

<img src="tasks_data_channel.png" style="width:200px;"/>


---

[Zur�ck](../../Readme.md)

---