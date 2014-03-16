JCC=javac
JFLAGS=

round_counter: Deck.class RoundCounter.class

Deck.class: Deck.java
	$(JCC) $(JFLAGS) Deck.java

RoundCounter.class: Deck.class RoundCounter.java
	$(JCC) $(JFLAGS) RoundCounter.java 

clean:
	rm -rf *.class
