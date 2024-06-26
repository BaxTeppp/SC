#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

struct STACK
{
  char c;
  struct STACK *next;
};

struct STACK *stack_push (struct STACK *head, char a);
char stack_pop (struct STACK **head);
int get_prior (char c);
void translate_to_rpn (char *outstr, char *a);

struct STACK *
stack_push (struct STACK *head, char a)
{
  struct STACK *ptr;

  if ((ptr = malloc (sizeof (struct STACK))) == NULL)
    {
      perror ("Out of memory\n");
      exit (1);
    }
  ptr->c = a;
  ptr->next = head;
  return ptr;
}

char
stack_pop (struct STACK **head)
{
  struct STACK *ptr;
  char a;

  if (*head == NULL)
    return '\0';
  ptr = *head;
  a = ptr->c;
  *head = ptr->next;
  free (ptr);
  return a;
}

int
get_prior (char c)
{
  switch (c)
    {
    case '*':
    case '/':
      return 3;
    case '-':
    case '+':
      return 2;
    case '(':
      return 1;
    }
}

void
translate_to_rpn (char *outstr, char *a)
{
  struct STACK *opers = NULL;
  int k, point;

  k = 0;
  point = 0;
  while (a[k] != '\0' && a[k] != '\n')
    {
      if (a[k] == ')')
        {
          while ((opers->c) != '(')
            outstr[point++] = stack_pop (&opers);
          stack_pop (&opers);
        }
      if (isalpha (a[k]) || isdigit (a[k]))
        outstr[point++] = a[k];
      if (a[k] == '(')
        opers = stack_push (opers, '(');
      if (a[k] == '+' || a[k] == '-' || a[k] == '/' || a[k] == '*')
        {
          if (opers == NULL)
            opers = stack_push (opers, a[k]);
          else if (get_prior (opers->c) < get_prior (a[k]))
            opers = stack_push (opers, a[k]);
          else
            {
              while ((opers != NULL)
                     && (get_prior (opers->c) >= get_prior (a[k])))
                outstr[point++] = stack_pop (&opers);
              opers = stack_push (opers, a[k]);
            }
        }
      k++;
    }
  while (opers != NULL)
    outstr[point++] = stack_pop (&opers);
  outstr[point] = '\0';
}
