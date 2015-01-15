#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Asteroids.h"

/*******************************************************************
*	Function int asteroid_init(struct Asteroid *a);
********************************************************************/
int asteroid_init(struct Asteroid *asteroid)
{
	float number;
	int number1;

	number1 = rand() % 200 + 1;
	asteroid->lifespan = number1;
	number1 = rand() % 10 + 1;
	asteroid->size = 20;
	number = (rand() / 1000000000 + 1) / 3.77f;
	asteroid->color.r = number;
	number = (rand() / 1000000000 + 1) / 3.77f;
	asteroid->color.b = number;
	number = (rand() / 1000000000 + 1) / 3.77f;
	asteroid->color.g = number;
	asteroid->color.a = 1.0f;

	/*Initiliaze position speed and driection to random values*/
	number = (float)((rand() % 100) * 0.9789687f - 50);
	number = number * 2;
	//printf("x: %f\n", number);
	asteroid->pos.x = number;
	number = (float)((rand() % 100) * 0.9789687f - 50);
	number = number * 2;
	//printf("y: %f\n", number);
	asteroid->pos.y = number;
	asteroid->pos.z = 0.0f;
	number = (float)((rand() % 400) * 0.9789687f - 250);
	number = number / 180;
	if (number > 0){
		number += 0.2;
	}
	else{
		number -= 0.2;
	}
	printf("y: %f\n", number);
	asteroid->dir.x = number;
	number = (float)((rand() % 300) * 0.9789687f - 150);
	number = number / 180;
	if (number > 0){
		number += 0.7;
	}
	else{
		number -= 0.7;
	}
	printf("y: %f\n", number);
	asteroid->dir.y = number;
	number = (float)((rand() % 300) * 0.9789687f - 150);
	asteroid->dir.z = number;
	number = (rand() % 10 + 1) / 200.789687f;
	asteroid->spd.x = number;
	number = (rand() % 10 + 1) / 200.789687f;
	asteroid->spd.y = number;
	number = (rand() % 10 + 1) / 200.789687f;
	asteroid->spd.z = number;
	return 0;
}
/*******************************************************************
*	Function int asteroid_add(struct Asteroid **head);
********************************************************************/
int asteroid_add(struct Asteroid **head)
{
	struct Asteroid * newLink;
	newLink = (struct Asteroid *)malloc(sizeof(struct Asteroid));
	newLink->next = *head;
	asteroid_init(newLink);
	*head = newLink;
	printf("Asteroid added\n");
	return 0;
}
/********************************************************************
*	Function int asteroid remove(struct Asteroid *a);
*********************************************************************/
int asteroid_remove(struct Asteroid *p)
{
	struct Asteroid *temp;
	temp = p;
	p = temp->next;
	free(temp);

	return 0;
}
/*********************************************************************
*	Function int asteroid_destroy(struct Asteroid **head);
**********************************************************************/
int asteroid_destroy(struct Asteroid **head)
{
	int counter = 0;
	struct Asteroid *temp;
	while (*head != NULL){
		temp = *head;
		temp = temp->next;
		asteroid_remove(*head);
		*head = temp;
		counter++;
	}
	return counter;
}
/*********************************************************************
*	Function int asteroid_update(struct particle **head);
**********************************************************************/
int asteroid_update(struct Asteroid **head)
{
	struct Asteroid * temp;
	temp = *head;
	while (temp != NULL)
	{
		temp->pos.x += temp->dir.x * temp->spd.x;
		if (temp->pos.x < 0)
		{
			temp->pos.x = 640;
		}
		else if (temp->pos.x > 640){
			temp->pos.x = 0;
		}
		temp->pos.y += temp->dir.y * temp->spd.y;
		if (temp->pos.y < 0)
		{
			temp->pos.y = 480;
		}
		else if (temp->pos.y > 480){
			temp->pos.y = 0;
		}
		temp = temp->next;
	}
	return 0;
}

