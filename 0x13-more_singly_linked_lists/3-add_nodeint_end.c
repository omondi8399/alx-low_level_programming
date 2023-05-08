#include <stdio.h>
#include "lists.h"

/**
  *add_nodeint_end - adds a node at the end of list
  *@head: pointer to the head node.
  *@n: interger value to assign
  *Return: NULL if function fails
  *if success address of the new element
  */
listint_t *add_nodeint_end(listint_t **head, const int n)
{
	listint_t *new, *last;

	new = malloc(sizeof(listint_t));
	if (new == NULL)
		return (NULL);

	new->n = n;
	new->next = NULL;

	if (*head == NULL)
		*head = new;

	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}

	return (*head);
}
