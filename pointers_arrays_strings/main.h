#ifndef MAIN_H
#define MAIN_H
#include "stdio.h"
char *string_toupper(char *);
void reverse_array(int *a, int n);
int _strcmp(char *s1, char *s2);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strcat(char *dest, char *src);
int _atoi(char *s);
char *_strcpy(char *dest, char *src);
void print_array(int *a, int n);
void puts_half(char *str);
void puts2(char *str);
void rev_string(char *s);
void print_rev(char *s);
void _puts(char *str);
void swap_int(int *a, int *b);
void reset_to_98(int *n);
int _strlen(char *s);
int _putchar(char c);
#endif
