# C++20: *Latches* und *Barrieren*

[Zur�ck](../../Readme.md)

---

#### Quellcode:

[Latches.cpp](Latches.cpp)<br/>
[Barriers.cpp](Barriers.cpp)

---

C++ hat weitere Klassen erhalten, um die Synchronisierung von Threads zu vereinfachen: *Latches* und *Barrieren*.

---

*Hinweis*: Windows-Systemprogrammierern d�rften *Latches* und *Barrieren* in
gewisser Weise bekannt vorkommen: Sie haben viele Gemeinsamkeiten mit den
Win32-Betriebssystemfunktionen `WaitForSingleObject` und `WaitForMultipleObjects`.

---

## Einf�hrung

Ein *Latch* ist eine Art &ldquo;Countdown&rdquo;-Z�hler,
der mit einem Startwert initialisiert wird und beim Eintreten bestimmter Ereignisse heruntergez�hlt wird.
Erreicht der Z�hler den Wert 0, meldet er auf eine bestimmte Art &ldquo;fertig&rdquo;.

So kann man beispielsweise 5 Threads beauftragen, etwas zu tun, und den Z�hler
mit 5 vorbelegen. Wenn dann jeder Thread sein Ende dem Latch
als Ereignis mitteilt, meldet dieser nach 5 fertigen Threads, dass
die gesamte Ausf�hrung abgeschlossen ist.

Beliebig viele Threads k�nnen ein *Latch*-Objekt zum Herunterz�hlen auf 0 verwenden.
Jeder Thread darf beliebig oft herunterz�hlen.
Steht der Wert des *Latch*-Objekts auf 0, kann es seinen Zustand nicht mehr ver�ndern.
Es eignet sich also nur f�r einen einmaligen *Countdown*.

---

*Barrieren* sind so organisiert, dass sie mehrfach Ereignisse verschiedener Threads synchronisieren k�nnen.
Auch hier handelt es sich um einen Z�hler, den jeder Thread aber nur einmal herunterz�hlen kann. Steht das *Barrieren*-Objekt auf 0,
wird eine vordefinierte Aktion aufgerufen und das *Barrieren*-Objekt l�sst sich erneut verwenden.
Das ist hilfreich, wenn das Programm nach einem bestimmten Ereignis immer wieder darauf warten muss,
dass eine bestimmte Anzahl paralleler Reaktionen erfolgt ist.

---

## `std::latch`

Einen groben �berblick auf die wesentlichen Methoden der Klasse `std::latch` gibt *Tabelle* 1:

| Element | Beschreibung |
| :---- | :---- |
| Konstruktor | `explicit latch(std::ptrdiff_t expected);`<br/>Erzeugt ein `std::latch`-Objekt und initialisiert seinen internen Z�hler. |
| Methode<br/>`count_down()` | `void count_down(std::ptrdiff_t n = 1);`<br/>Dekrementiert den internen Z�hler atomar um den Wert *n*, ohne den Anrufer zu blockieren. |
| Methode<br/>`wait()` | `void wait() const;`<br/>Blockiert den aufrufenden Thread, bis der interne Z�hler 0 erreicht. Wenn er bereits Null ist, wird sofort zur�ckgekehrt. |
| Methode<br/>`arrive_and_wait()` | `void arrive_and_wait(std::ptrdiff_t n = 1);`<br/>Dekrementiert den internen Z�hler atomar um *n* und blockiert (falls erforderlich) den aufrufenden Thread, bis der Z�hler Null erreicht. |

*Tabelle* 1: Wesentliche Elemente der Klasse `std::latch`.

Knapp formuliert kann man sagen, dass die Klasse `std::latch`
ein Abw�rtsz�hler vom Typ `ptrdiff_t` ist, mit dem Threads synchronisiert werden k�nnen.
Der Wert des Z�hlers wird bei der Erstellung initialisiert.
Threads k�nnen an der Verriegelung (engl. &ldquo;*latch*&rdquo;)  blockieren,
bis der Z�hler auf Null dekrementiert wird.
Es gibt keine M�glichkeit, den Z�hler zwischendurch zu vergr��ern oder zur�ckzusetzen.

---

## `std::barrier`

Einen groben �berblick auf die wesentlichen Methoden der Klasse `std::barrier` gibt *Tabelle* 2:

| Element | Beschreibung |
| :---- | :---- |
| Konstruktor | `explicit barrier(std::ptrdiff_t expected);`<br/>Erzeugt ein `std::barrier`-Objekt und initialisiert seinen internen Z�hler. |
| Methode<br/>`wait()` | `void wait() const;`<br/>Blockiert den aufrufenden Thread, bis alle Threads den Synchronisationspunkt erreicht haben. |
| Methode<br/>`arrive_and_wait()` | `void arrive_and_wait();`<br/>Erreicht die Barriere und verringert den Z�hler um 1, blockiert dann, bis die aktuelle Phase abgeschlossen ist. |
| Methode<br/>`arrive_and_drop()` | `void arrive_and_drop();`<br/>Dekrementiert sowohl den initial erwarteten Z�hler f�r die nachfolgende Phase als auch die aktuelle Phase um 1. |

*Tabelle* 2: Wesentliche Elemente der Klasse `std::barrier`.

Die Klasse `std::barrier` bietet einen Thread-Koordinierungsmechanismus,
mit dem eine festgelegte Anzahl von Threads blockiert werden kann,
bis diese alle den Synchronisationspunkt (*Barriere*) erreicht haben.
Im Gegensatz zu `std::latch` sind Barrieren wiederverwendbar:
Sobald die ankommenden Threads am Synchronisationspunkt einer Barriere ihre Blockade verlassen,
kann dieselbe Barriere erneut verwendet werden.

---

[Zur�ck](../../Readme.md)

---
