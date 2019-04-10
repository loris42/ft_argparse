/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_options.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <laranda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:58:43 by laranda           #+#    #+#             */
/*   Updated: 2019/04/10 17:02:39 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSE_OPTIONS_H
# define FT_PARSE_OPTIONS_H

typedef	struct s_option				t_option;
typedef	struct s_parsing_context	t_parsing_context;
typedef	enum e_opt_type				t_opt_type;

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
	char							*prefix;
	t_option						*options;
	char							*usage;
	void							*error_callback;
};

int									ft_parse_options(t_parsing_context *ctxt);

#endif
