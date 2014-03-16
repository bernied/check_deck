/*
 * Copyright (c) 2013 Bernhard H. Damberger
 *
 * Contains a literal solution to Apple coding problem.
 */

import java.util.Stack;

/**
 * @class RoundCounter
 * RoundCounter is the main entry point for calculating how many rounds it takes to get a deck of n cards back to its
 * original state based on steps 1-3:
 *   1. Take the top card off the deck and set it on the table, face down.
 *   2. Take the next card off the top and put it on the bottom of the deck in your hand.
 *   3. Continue steps 1 and 2 until all cards are on the table. This is a round.
 *   4. Pick up the deck from the table and repeat steps 1-4 until the deck is in the original order.
*/
public class RoundCounter
{
    /**
     * runRound will simulate one round of steps 1-4.
     * @param d deck of cards to execute on
     * @return number of steps for this round
     */
    static int runRound(Deck d)
    {
        Stack<Integer> table = new Stack<Integer>();

        int card;
        int step = 0;
        while (d.countCards() > 0)
        {
            card = d.removeCardFromTop();
            if (step % 2 == 0 || d.countCards() == 0) {
                table.push(card);
            }
            else {
                d.addCardToBottom(card);
            }
            step++;
        }

        d.resetDeckWith(table);
        return step; // number of steps for each round
    }

    /**
     * main entry point for calculating number of rounds.
     * @param argv command line arguments
     */
    public static void main(String[] args)
    {
        if (args.length != 1)
        {
            System.err.println("Expecting one integer input.");
            System.exit(-1);
        }

        int numCards = 0;
        try {
            numCards = Integer.parseInt(args[0]);
        }
        catch (Exception ex)
        {
            System.err.println("Invalid input. Expecting an integer.");
            System.exit(-1);
        }

        Deck d = new Deck(numCards);

        int numRounds = 0;
        do
        {
            runRound(d);
            numRounds++;
        } while(!d.isInOrder());

        System.out.println(numRounds);
        System.exit(1);
    }
}
