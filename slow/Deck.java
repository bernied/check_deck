/*
 * Copyright (c) 2013 Bernhard H. Damberger
 *
 * Contains a literal solution to Apple coding problem.
 */

import java.util.Stack;
import java.util.LinkedList;
import java.util.Collection;

/**
 * @class Deck
 * Deck simulates a deck of cards where each card is represented by a unique integer value.
 */
public class Deck
{
    // List of cards represented by unique integer
    private LinkedList<Integer> _cards;

    /**
     * Constructor to create empty deck.
     */
    public Deck()
    {
        _cards = new LinkedList<Integer>();
    }

    /**
     * Creates a pre-initialized deck.
     * @param num number of cards to add to deck in numerical order
     */
    public Deck(int num)
    {
        _cards = new LinkedList<Integer>();
        for (int i=0; i < num; i++) {
            _cards.addLast(i);
        }
    }

    /**
     * Adds all the "cards" (ie numbers) into the current deck. Does not check for duplicates.
     * @param c Collection to insert
     */
    public void resetDeckWith(Collection<Integer> c)
    {
        _cards.addAll(c);
    }

    /**
     * Adds all the "cards" (ie numbers) into the current deck from a Stack in stack order.
     * @param s Stack to insert cards from
     */
    public void resetDeckWith(Stack<Integer> s)
    {
        while (!s.empty()) {
            _cards.addLast(s.pop());
        }
    }

    /**
     * Equals method to compare two deck of cards to see if they are the same (same number cards, same order).
     * @param obj Incoming deck to compare to
     * @return true if obj is a Deck and its the same as this one.
     */
    @Override
    public boolean equals(Object obj)
    {
        if (obj instanceof Deck == false) {
            return false;
        }
        Deck deck = (Deck) obj;

        return _cards.equals(deck._cards);
    }

    /**
     * Hashcode method for Deck.
     * @return hashCode from LinkedList.
     */
    @Override
    public int hashCode()
    {
        return _cards.hashCode();
    }

    /**
     * Returns number of cards in Deck.
     * @return num cards in Deck
     */
    public int countCards()
    {
        return _cards.size();
    }

    /**
     * Returns card at a given position.
     * @param pos position to get card from
     * @return integer representation of card
     */
    public int cardAt(int pos)
    {
        return _cards.get(pos);
    }

    /**
     * @return true if the Deck is in numerical order from low to high.
     */
    public boolean isInOrder()
    {
        int count=0;
        for(int c : _cards)
        {
            if (count != c) {
                return false;
            }
            count++;
        }
        return true;
    }

    /**
     * Puts a new card on top of Deck. Does not check for uniqueness.
     * @return new card that was inserted
     */
    public int addNewCardToTop()
    {
        int newCard = _cards.size();
        _cards.addFirst(newCard); // cards are assumed unique
        return newCard;
    }

    /**
     * Adds a new card on bottom of Deck. Does not check for uniqueness.
     * @return new card that was inserted
     */
    public int addNewCardToBottom()
    {
        int newCard = _cards.size();
        _cards.addLast(newCard); // cards are assumed unique
        return newCard;
    }

    /**
     * Adds a specific card to the top of the Deck. Does not check for uniqueness.
     * @param card new card to insert
     */
    public void addCardToTop(int card)
    {
        _cards.addFirst(card); // cards are assumed unique
    }
    
    /**
     * Adds a specific card to the bottom of the Deck. Does not check for uniqueness.
     * @param card new card to insert
     */
    public void addCardToBottom(int card)
    {
        _cards.addLast(card); // cards are assumed unique
    }

    /**
     * Removes the top card from the Deck.
     * @return card that was removed
     */
    public int removeCardFromTop()
    {
        return _cards.removeFirst();
    }

    /**
     * Removes the bottom card from the Deck.
     * @return card that was removed
     */
    public int removeCardFromBottom()
    {
        return _cards.removeLast();
    }
}
