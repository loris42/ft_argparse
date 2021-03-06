/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <laranda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:56:42 by laranda           #+#    #+#             */
/*   Updated: 2019/04/11 16:33:54 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "ft_parse_options.h"

int			g_option_1 = 0;
int			g_option_2 = 0;

t_option	g_options[3] = {
	{ OPTION_BIT, 'z', NULL, &g_option_1 },
	{ OPTION_BIT, 'q', NULL, &g_option_2 },
	{ OPTION_END }
};

void		print_error(char *option_name);
void		print_parsing_init(t_option *options);
void		print_parsing_done(t_parsing_context context, int args_index);

int			main(int argc, char **argv)
{
	t_parsing_context	context;
	int					args_index;

	memset(&context, 0, sizeof(context));
	args_index = 0;
	context.argc = argc;
	context.argv = argv;
	context.error_callback = &print_error;
	context.options = g_options;
	print_parsing_init(context.options);
	args_index = ft_parse_options(&context);
	print_parsing_done(context, args_index);
	return (0);
}

void		print_error(char *option_name)
{
	if (strncmp(
		option_name, OPTION_SHORT_PREFIX, strlen(OPTION_SHORT_PREFIX)) == 0)
	{
		option_name += strlen(OPTION_SHORT_PREFIX);
	}
	printf("illegal option -- %c\n", *option_name);
}

void		print_parsing_init(t_option *options)
{
	t_option	*current_option;
	int			first;

	current_option = options;
	first = 1;
	printf("====  Init parsing ====\nActivable options are : ");
	while (current_option->type != OPTION_END)
	{
		if (first)
		{
			first = 0;
		}
		else
		{
			printf(", ");
		}
		
		printf("%c", current_option->short_name);
		current_option++;
	}
	printf("\n");
}

void		print_parsing_done(t_parsing_context context, int args_index)
{
	t_option	*current_option;

	current_option = context.options;
	printf("==== Parsing Done ====\nOptions State :\n");
	while (current_option->type != OPTION_END)
	{
		printf(
			"%c => %i\n",
			current_option->short_name,
			*(int*)(current_option->value));
		current_option++;
	}
	printf("\nParameters are :\n");
	while (args_index < context.argc)
	{
		printf("%s\n", context.argv[args_index++]);
	}
}
