# Futures und Promises

[Zur�ck](../../Readme.md)

---

Das nachfolgende Diagramm skizziert den Ablauf eines Multithreading-Szenarios 
mit `Future`- und `Promise`-Objekt:

<img src="cpp_parallel_programming_future_promise_01.svg" width="700">

Abbildung 1: Workflow von `std::promise` und `std::future` Objekt.

Man beachte, dass zwischen den beiden Objekten des Typs `Future` und `Promise` ein Datenkanal eingerichtet wird.
Die Thread-Prozedur erh�lt zum Ausf�hrungszeitpunkt einen `std::promise<>`-Zeiger / eine `std::promise<>`-Referenz �bergeben.
Daran k�nnen mit Hilfe der `set_value`-Methode Resultate vom Thread zum Thread-Erzeuger transferiert werden.

<img src="cpp_parallel_programming_future_promise_02.svg" width="350">

Abbildung 2: Datenkanal zwischen `std::promise` und `std::future` Objekt.

---

[Zur�ck](../../Readme.md)

---
