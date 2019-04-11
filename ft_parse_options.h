/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_options.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <laranda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:58:43 by laranda           #+#    #+#             */
/*   Updated: 2019/04/11 16:28:50 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSE_OPTIONS_H
# define FT_PARSE_OPTIONS_H

# ifdef DEV
#  define D(x) x
# else
#  define D(x)
# endif

# define OPTION_SHORT_PREFIX "-"
# define OPTION_LONG_PREFIX "--"
# define END_OF_OPTION_STR "--"

typedef	struct s_option				t_option;
typedef	struct s_parsing_context	t_parsing_context;
typedef	enum e_opt_type				t_opt_type;
typedef	enum e_arg_type				t_arg_type;

enum								e_arg_type
{
	OPTION_SHORT,
	OPTION_LONG,
	OPTION_ERROR,
	END_OF_OPTION,
	PARAM
};

enum								e_opt_type
{
	OPTION_END = 0,
	OPTION_BIT,
};

struct								s_option
{
	t_opt_type						type;
	char							short_name;
	char							*long_name;
	void							*value;

};

struct								s_parsing_context
{
	int								argc;
	char							**argv;
	t_option						*options;
	char							*usage;
	void							(*error_callback)(char *arg);
};

int									ft_parse_options(t_parsing_context *ctxt);

#endif
