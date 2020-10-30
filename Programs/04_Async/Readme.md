# Die Funktionsschablone `std::async`

Das Zusammenspiel zwischen der Methode `std::async` und Objekten
des Typs `std::future` wird gezeigt.

Die `std::async`-Methode besitzt im Wesentlichen drei �berladungen:

  * `std::async` mit normaler C-Funktion.
  * `std::async` mit Funktor-Objekt.
  * `std::async` mit Lambda-Funktion.

#### Quellcode:

[Siehe hier](Async_01.cpp).

---

## `launch::async` versus `launch::deferred`

Es werden zwei Threads mit `std::async` gestartet, die beide einen Zeitstempel zur�ckliefern.

Sie unterscheiden sich bzgl. der verwendeten *launch policy*:

  * `launch::async`<br/>Startet einen eigenen Thread im Hintergrund.
  * `launch::deferred`<br/>Wartet mit der Ausf�hrung der Threadprozedur, bis der Aufrufer das Ergebnis mit `get` abholen m�chte. Dazu muss nicht zwingend ein separater Thread verwendet werden, die Threadprozedur kann im Kontext des aktuellen Threads ausgef�hrt werden.


Analysieren Sie das Beispiel im Quellcode genau!
Die Ausf�hrung des Programms lautet:

```
Preparing calculations ...
Now waiting for 4 seconds ...
launch::async thread done!
launch::deferred thread done!
asyncLazy evaluated after : 4.00645 seconds.
asyncEager evaluated after: 0.0006665 seconds.
```

#### Quellcode:

[Siehe hier](Async_02.cpp).

---

## 4 Szenarien mit `std::async`

Es werden vier Vertiefungen der Klasse `std::async` studiert:

  * Parallele Ausf�hrung mehrerer Threads - das Resultat wird mit `get` abgeholt.
  * Parallele Ausf�hrung mehrerer Threads - es wird nur ein Resultat (mit `get` abgeholt). Welche Rolle spielt der Destruktor der beteiligten `Future`-Objekte?
  * Parallele Ausf�hrung mehrerer Threads - es wird nur ein Resultat (mit `get` abgeholt). Welche Rolle spielt die *Launch Policy*?
  * Parallele Ausf�hrung eines Threads - das Resultat muss nicht zwingend `get` abgeholt werden, mit der Methode `wait_for` an einem `Future`-Objekt und dem Aufz�hlungstyp `future_status` kann man den Status des `Future`-Objekts erfragen.

```cpp
enum class future_status    // names for timed wait function returns
{
    ready,
    timeout,
    deferred
};
```

Studieren Sie die Ausf�hrung der vier Beispiele genau!

*Ausgabe Beispiel* 1:

```
Please wait ...
fib(40): 102334155
fib(41): 165580141
fib(42): 267914296
fib(43): 433494437
Done.
```

*Ausgabe Beispiel* 2:

```
Please wait ...
fib(40): 102334155
Done.   // <=== ???
```

*Ausgabe Beispiel* 3:

```
Preparing calculations ...
Retrieve single result of fib(42):
fib(42): 267914296
Done.   // <=== ???
```

*Ausgabe Beispiel* 4:

```
Calculation with wait:
not yet calculated ...
not yet calculated ...
not yet calculated ...
not yet calculated ...
not yet calculated ...
not yet calculated ...
not yet calculated ...
not yet calculated ...
not yet calculated ...
not yet calculated ...
not yet calculated ...
fib(40): 102334155
Elapsed time in milliseconds = 5655 [milliseconds]
```

#### Quellcode:

[Siehe hier](Async_03.cpp).

---


[Zur�ck](../../Readme.md)

---