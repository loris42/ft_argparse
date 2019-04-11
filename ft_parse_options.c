/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <laranda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:14:28 by laranda           #+#    #+#             */
/*   Updated: 2019/04/11 16:39:14 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse_options.h"
#include <stdio.h> // TODO exchange with ft_printf if still needed !!
#include <string.h> // TODO exchange with libftq if still needed !!

int 		str_start_by(char *arg, char *prefix);
t_option	*find_option(char *arg, t_option *options);
int			init_options_parsing(t_parsing_context *context);
t_arg_type	get_arg_type(char *arg);
t_arg_type	process_arg(char *arg, t_parsing_context *context);
int			activate_option_by_short_name(char short_name, t_option *options);
int			activate_option_by_long_name(char *long_name, t_option *options);
void		activate_option(t_option *option);
char		*del_option_prefix(char *arg);

int			ft_parse_options(t_parsing_context *context)
{
	int	arguments_first_index;

	D(printf("\n\n=======\n   inside ft_parse_options   \n=======\n\n"));
	D(printf("Init options parsing\n"));
	arguments_first_index = init_options_parsing(context);
	D(printf("Options parsing done\n"));
	D(printf("\n\n======\n  return from ft_parse_options  \n======\n\n"));
	return arguments_first_index;
}

int			init_options_parsing(t_parsing_context *context)
{
	int			args_index;
	char		*current_arg;
	t_arg_type	arg_type;

	args_index = 1;
	while (args_index < context->argc)
	{
		current_arg = context->argv[args_index];
		arg_type = process_arg(current_arg, context);
		if (arg_type == OPTION_ERROR)
		{
			D(printf("Option Error. Stop parsing\n"));
			context->error_callback(current_arg);
			return context->argc;
		}
		if (arg_type == PARAM)
		{
			return args_index;
		}
		if (arg_type == END_OF_OPTION)
		{
			return args_index + 1;
		}
		args_index++;
	}
	return args_index;
}

t_arg_type	process_arg(char *arg, t_parsing_context *context)
{
	t_arg_type	arg_type;
	int			error;

	arg_type = get_arg_type(arg);
	D(printf("processing arg %s\t=> type :\t%i\n", arg, arg_type));
	error = 0;
	if (arg_type == OPTION_SHORT)
	{
		arg += strlen(OPTION_SHORT_PREFIX);
		while (*arg && !error)
		{
			error = activate_option_by_short_name(*arg, context->options);
			arg++;
		}
	}
	if (arg_type == OPTION_LONG)
	{
		arg += strlen(OPTION_LONG_PREFIX);
		error = activate_option_by_long_name(arg, context->options);
	}
	if (error) {
		return OPTION_ERROR;
	}
	return arg_type;
}

// TODO better solution than if forest ?
t_arg_type	get_arg_type(char *arg)
{
	if (strcmp(arg, END_OF_OPTION_STR) == 0)
	{
		return END_OF_OPTION;
	}
	if (str_start_by(arg, OPTION_LONG_PREFIX))
	{
		return OPTION_LONG;
	}
	if (str_start_by(arg, OPTION_SHORT_PREFIX))
	{
		return OPTION_SHORT;
	}
	return PARAM;
}

int			activate_option_by_short_name(char short_name, t_option *options)
{
	while (options->type != OPTION_END)
	{
		if (short_name == options->short_name)
		{
			activate_option(options);
			return 0;
		}
		options++;
	}
	return 1;
}

int			activate_option_by_long_name(char *long_name, t_option *options)
{
	while (options->type != OPTION_END)
	{
		if (options->long_name && strcmp(long_name, options->long_name) == 0)
		{
			activate_option(options);
			return 0;
		}
		options++;
	}
	return 1;
}

void		activate_option(t_option *option)
{
	D(printf(
		"\tActivating Option => short : %c\tlong : %s\n",
		option->short_name,
		option->long_name));
	if (option->type == OPTION_BIT)
	{
		*(int*)(option->value) = 1;
	}
}

/*
 * Checks that str start by prefix and has at least one more char after prefix.
 */
int 		str_start_by(char *str, char *prefix)
{
	int	prefix_len;
	int	diff;

	prefix_len = strlen(prefix);
	diff = strncmp(str, prefix, prefix_len);
	return !diff && str[prefix_len];
}
