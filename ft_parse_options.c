/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <laranda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:14:28 by laranda           #+#    #+#             */
/*   Updated: 2019/04/10 19:55:43 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse_options.h"
#include <stdio.h> // TODO exchange with ft_printf if still needed !!
#include <string.h> // TODO exchange with libftq if still needed !!

int arg_start_by_opt_prefix(char *arg, char *prefix);

int	ft_parse_options(t_parsing_context *context)
{
    int     args_index;
    char    *current_arg;

    args_index = 1;
    printf("\n======\n   inside parser   \n=======\n"); // DEBUG
    printf("argc =>  %i\n", context->argc); // DEBUG
    printf("Scanning for Options\n");
    while (args_index < context->argc)
    {
        current_arg = context->argv[args_index];
        printf("argv[%i] =>  %s\n", args_index, current_arg); // DEBUG
        if (arg_start_by_opt_prefix(current_arg, context->prefix))
        {
            printf("\tOption Prefix detected\n");
            // TODO activate option or raise error
        }
        else
        {
            printf("\tNO Option Prefix detected -> End of scanning, the rest are arguments.\n");
            break;
        }
        args_index++;
    }
    return args_index;
}

int arg_start_by_opt_prefix(char *arg, char *prefix)
{
    int diff;

    diff = strncmp(arg, prefix, strlen(prefix));
    return diff == 0;
}
