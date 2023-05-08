#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash_tables.h"
/**
 * shash_table_create - creates a hash table
 * @size: size of the hash table
 *
 * Return: pointer to hash table
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht = NULL;

	if (size > 0)
	{
		ht = malloc(sizeof(shash_table_t));
		if (!ht)
			return (NULL);
		ht->array = malloc(size * sizeof(shash_node_t *));
		if (!ht->array)
			return (NULL);
		ht->size = size;
		ht->shead = NULL;
		ht->stail = NULL;
	}
	return (ht);
}
/**
 * add_node - adds a new node at a specific index in a hash table
 * @head: head of linked list at specified index in a hash table
 * @key: element's key
 * @value: element's value
 *
 * Return: nothing
 */
void add_node(shash_node_t **head, const char *key, const char *value)
{
	shash_node_t *new, *temp = *head;

	new = malloc(sizeof(shash_node_t));
	if (!new)
		exit(0);
	new->key = strdup(key);
	if (!new->key)
	{
		free(new);
		exit(0);
	}
	new->value = strdup(value);
	if (!new->value)
	{
		free(new->key);
		free(new);
		exit(0);
	}
	new->next = NULL;
	new->sprev = NULL;
	new->snext = NULL;
	if (temp)
	{
		new->next = temp;
		new->sprev = temp->sprev;
		new->snext = temp->snext;
		temp->sprev = NULL;
		temp->snext = NULL;
	}
	*head = new;
}

/**
 * sort_table - sort hash table
 * @ht: hash table
 * @index: index of new element
 *
 * Return: nothing
 */
void sort_table(shash_table_t *ht, unsigned long int index)
{
	unsigned long int f_idx, l_idx;
	shash_node_t *current, *prev, *next;

	f_idx = key_index((const unsigned char *)ht->shead->key, ht->size);
	l_idx = key_index((const unsigned char *) ht->stail->key, ht->size);
	if (index < f_idx)
	{
		ht->array[index]->snext = ht->shead;
		ht->shead->sprev = ht->array[index];
		ht->shead = ht->array[index];
	}
	else if (index > l_idx)
	{
		ht->array[index]->sprev = ht->stail;
		ht->stail->snext = ht->array[index];
		ht->stail = ht->array[index];
	}
	else
	{
		current = ht->shead;
		prev = NULL;
		while (current)
		{
			if (key_index((const unsigned char *)current->key, ht->size) > index)
				break;
			next = current->snext;
			ht->array[index]->sprev = current;
			ht->array[index]->snext = next;
			current->snext = ht->array[index];
			next->sprev = ht->array[index];
			current->sprev = prev;
			if (prev)
				prev->snext = current;
			prev = current;
			current = next;
		}
	}
}

/**
 * shash_table_set - adds or updates an element in hash table
 * @ht: hash table to sort
 * @key: element's key
 * @value: element's value
 *
 * Return: 1 on success, 0 on failure
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	unsigned long int index;

	if (!ht || !value || !key || *key == '\0')
		return (0);
	index = key_index((const unsigned char *)key, ht->size);

	if (ht->array[index])
	{
		free(ht->array[index]->value);
		ht->array[index]->value = strdup(value);
		if (!ht->array[index]->value)
			return (0);
		return (1);
	}

	add_node(&(ht->array[index]), key, value);

	if (!ht->shead && !ht->stail)
	{
		ht->shead = ht->array[index];
		ht->stail = ht->array[index];
	}
	else
	{
		if (!(ht->array[index]->next))
			sort_table(ht, index);
	}
	return (1);
}

/**
 * shash_table_get - retrieve the value associated with a certain key
 * @ht: hash table to search
 * @key: search key
 *
 * Return: value if key exists, NULL if not found
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int index;
	shash_node_t *temp;

	if (!ht || !key || *key == '\0')
		return (NULL);
	index = key_index((const unsigned char *) key, ht->size);
	temp = ht->array[index];

	if (temp)
		if (strcmp(temp->key, key) == 0)
			return (temp->value);
	return (NULL);
}

/**
 * shash_table_print - prints elements of hash table
 * @ht: hash table
 *
 * Return: nothing
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *temp, *current;
	char *del = "";

	if (!ht)
		return;
	current = ht->shead;
	printf("{");
	while (current)
	{
		temp = current;
		while (temp)
		{
			printf("%s'%s': '%s'", del, temp->key, temp->value);
			del = ", ";
			temp = temp->next;
		}
		current = current->snext;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - prints elements of hash table in reverse
 * @ht: hash table
 *
 * Return: nothing
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *current, *temp;
	char *del = "";

	if (!ht)
		return;
	current = ht->stail;
	printf("{");
	while (current)
	{
		temp = current;
		while (temp)
		{
			printf("%s'%s': '%s'", del, temp->key, temp->value);
			del = ", ";
			temp = temp->next;
		}
		current = current->sprev;
	}
	printf("}\n");
}

/**
 * shash_table_delete - deletes sorted hash table
 * @ht: hash table
 *
 * Return: nothing
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *temp, *next;

	if (!ht)
		return;
	temp = ht->shead;
	while (temp)
	{
		while (temp)
		{
			next = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			temp = next;
		}
		ht->shead = ht->shead->snext;
		temp = ht->shead;
	}
	free(ht->array);
	free(ht);
}
