/*------------------------------------------------------------------------------

    Copyright 2013 (c) Bernhard H. Damberger
    
    Apple coding question (1/30/2013):
    You are given a deck containing 42 cards. While holding the deck with the cards face down:
      1. Take the top card off the deck and set it on the table, face down.
      2. Take the next card off the top and put it on the bottom of the deck in your hand.
      3. Continue steps 1 and 2 until all cards are on the table. This is a round.
      4. Pick up the deck from the table and repeat steps 1-3 until the deck is in the original order.
        
    This file contains a C version of a solution to the given problem statement. 
    
    This is basically a permutation problem. A deck of n cards in a specific
    order can be represented by a "permutation" A permutation is a bijection
    from a set onto itself. They are typically written in the following form:

       1 2 3 4 5
      (1 2 3 4 5)
      
    This represents the identity permutation. Another permutation would be:
    
       1 2 3 4 5
      (2 4 5 3 1)
      
    This means position 1 is mapped to position 2, position 2 is mapped to
    position 4, etc. This second example also happens to represent the given
    problem statement for a deck of 5 cards.
    
    Another form that a permutation can be written in is called a cycle. A
    cycle represents how a given position will change over multiple
    applications of the permutation.
    
    For example, the given permutation of (2 4 5 3 1) is represented as a
    cycle in the form (1 2 4 3 5). This means the value in position 1 will
    be shifted to position 2 on the first application of the permutation.
    Position 2 will be shifted to position 4, 4 to 3, 3 to 5 and finally
    5 will wrap around to 1.
    
    We can use the cycle representation to determine how many times a
    permutation would need to be applied in order to get back to the original
    representation. In this example, it would take 5 applications of the 
    permutation to get back to the original form.
    
    The given problem boils down to the following:
      1.  Find the permutation that is described by steps 1-3. Each
          round represents one application of the given permutation.
      2.  Transform the given permutation into cycle form. The LCM of the cycles
          size will represent the number of steps that are required to get back
          to the original order.
    
    The following code follows this plan. The calc_permutation() function will
    apply the steps 1-3 to construct one permutation round. The function
    find_max_cycle() then constructs all the cycles associated with the
    permutation, and applies the LCM to them. This is the value that is
    returned by the program.
    
    Note, the find_max_cycle() function is based on the cycle-sort. See the
    paper by B. K. Haddon "Cycle-Sort: A Linear Sorting Method" for more
    details.
    
------------------------------------------------------------------------------*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Provides user feed back on how to use check_deck.
*/
void
usage(char* msg)
{
  printf("Usage: check_deck <integer>\n");
  if (msg) {
    printf("  %s\n", msg);
  }
  exit(0);  // NOTE, if usage is called application will exit
}

/*
* Provides user feed back on how to use check_deck.
*/
void
error(char* msg)
{
  if (msg) {
    fprintf(stderr, "%s\n", msg);
  }
  exit(-1);
}

/*
* Linked list to support the construction of the permutation.
*/
typedef struct _node {
  unsigned int value;
  struct _node* next;
} node;

/*
* Creates a node for the permutation construction.
*/
node*
create_node(unsigned int value)
{
  node* n = (node*) malloc(sizeof(node));
  if (!n) {
      error("Can't allocate enough memory for the permutations.\n");
  }
  n->value = value;
  n->next = NULL;
  return n;
}

/*
* Constructor to allocate and initialize permutation array.
* NOTE: position zero contains the size, so the array is 1 based not 0 based!
*/
unsigned int*
create_permutation(unsigned int size)
{
  size_t perm_size = (size + 1) * sizeof(unsigned int);
  unsigned int* perm = (unsigned int*) malloc(perm_size);
  if (!perm) {
    error("Can't allocate enough memory for the permutations.\n");
  }
  perm[0] = size;
  
  return perm;
}

/*
* Creates the permutation array based on optimized version of steps 1-3.
*/
unsigned int*
calc_permutation(unsigned int count)
{
  unsigned int odd = count % 2;
  unsigned int half = (count / 2) + odd;
  unsigned int i;
  unsigned int *p, *perm = create_permutation(count);
  
  // First back fill the permutation with all the odd numbers between 1 and n.
  p = perm + count;
  for (i=1; i <= half; i++) {
    *p-- = (i*2)-1; // odd numbers
  }

  // Construct a linked list of even numbers, which will be used for steps 1-3.
  node* head = create_node(0);
  node* end = head;
  for (i=odd + 1; i < count - half + 1; i++) {
    end->next = create_node(i*2); // even numbers
    end = end->next;
  }
  if (odd) {
    end->next = create_node(2); // no. 2 ends up at end of list in odd case
    end = end->next;
  }

  // Apply steps 1-3 to the linked list.
  // Note, we walk through the permutation array backwards, because putting
  // cards down and picking them up again is like a stack.
  p = perm + count - half;
  node *current = head->next, *prev;
  while(current)
  {
      // assign even value to next space
    *p-- = current->value;
    prev = current;
    current = current->next;
    free(prev);

    if (!current) {
      break;
    }
    
      // move "card" to end
    end = end->next = current;
    current = current->next;
    end->next = NULL;
  }
  free(head);

  return perm;
}

/*
* Function to calculate the greatest common divisor (GCD) of two numbers.
* Code taken from:
*   http://en.wikipedia.org/wiki/Binary_GCD_algorithm#Iterative_version_in_C
*/
unsigned int
gcd(unsigned int u, unsigned int v)
{
  int shift;
 
  /* GCD(0,v) == v; GCD(u,0) == u, GCD(0,0) == 0 */
  if (u == 0) return v;
  if (v == 0) return u;
 
  /* Let shift := lg K, where K is the greatest power of 2
        dividing both u and v. */
  for (shift = 0; ((u | v) & 1) == 0; ++shift)
  {
    u >>= 1;
    v >>= 1;
  }
 
  while ((u & 1) == 0)
  {
    u >>= 1;
  }
  
  /* From here on, u is always odd. */
  do {
    /* remove all factors of 2 in v -- they are not common */
    /*   note: v is not zero, so while will terminate */
    while ((v & 1) == 0)  /* Loop X */
      v >>= 1;
    
    /* Now u and v are both odd. Swap if necessary so u <= v,
    then set v = v - u (which is even). For bignums, the
    swapping is just pointer movement, and the subtraction
    can be done in-place. */
    if (u > v)
    {
      unsigned int t = v; v = u; u = t; // Swap u and v.
    }
    v = v - u;  // Here v >= u.
  } while (v != 0);
 
  /* restore common factors of 2 */
  return u << shift;
}

/*
* Calculate LCM (least common multiple) of set of values.
* LCM(a, b) = |a * b| / gcd(a, b)
*/
unsigned int
calc_lcm(node* n)
{
  unsigned int lcm = 1;
  node* p;
  while (n->next)
  {
    p = n;
    n = n->next;
    lcm *= (n->value / gcd(lcm, n->value));
    free(p);
  }

  return lcm;
}

/*
* Uses cycle-sort algorithm to calculate the cycles from permutations, which in
* turn represents the number of times a permutation needs to be applied to get
* back to the original state.
* See B. K. Haddon's 1990 paper "Cycle-Sort: A Linear Sorting Method".
*/
node*
find_cycles(unsigned int* perm)
{
  unsigned int cycle, max_cycle=1;
  unsigned int tmp, lv; // last value
  unsigned int count=0;
  node *head, *current;
  
  head = create_node(1);
  current = head;
  for (unsigned int i=1; i <= perm[0]; i++)
  {
    if (i != perm[i])
    {
      current->next = create_node(0);
      count++;
      current = current->next;
      cycle = 0;
      unsigned int n = i;
      
      while (1)
      {
        cycle++;
        tmp = perm[n];
        if (n != i) {
          perm[n] = lv;
        }
        lv = tmp;
        n = lv;
        if (n == i)
        {
          perm[n] = lv;
          break;
        }
      }
      if (cycle > max_cycle) {
        max_cycle = cycle;
      }
      current->value = cycle;
    }
  }

  return head;
}

/*
* main entry point for check_deck.
*/
int
main(int argc, char** argv)
{
  // Should have one param only: the number of cards.
  if (argc <= 1 || argc > 2) {
    usage(NULL);
  }
  
  long num_cards_l = atol(argv[1]);
  if (num_cards_l <= 0) {
    usage("Expecting positive integer as input.");
  }
  if (num_cards_l >= UINT_MAX) {
    usage("Expecting smaller value!");
  }
  unsigned int num_cards = (unsigned int) num_cards_l;
  
  // Calculate number of rounds required to get back to original state.
  unsigned int lcm_cycle = 1;
  if (num_cards > 1)
  {
    unsigned int* shuffle = calc_permutation(num_cards);
    node* cycles = find_cycles(shuffle);
    lcm_cycle = calc_lcm(cycles);
    free(shuffle);
  }
  
  printf("%u\n", lcm_cycle);
  exit(1);
}