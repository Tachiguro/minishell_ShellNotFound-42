/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_tests.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherzog <jherzog@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:14:20 by jherzog           #+#    #+#             */
/*   Updated: 2025/02/01 14:20:31 by jherzog          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static void	assert_token(t_token *token, t_type expected_type, const char *expected_value)
{
	assert(token != NULL);
	assert(token->type == expected_type);
	assert(ft_strncmp(token->value, expected_value, ft_strlen(expected_value)) == 0);
}

void	test_tokenization_simple(void)
{
	t_token *tokens = create_tokens("echo Hello world");

	assert_token(tokens, T_WORD, "echo");
	assert_token(tokens->next, T_WORD, "Hello");
	assert_token(tokens->next->next, T_WORD, "world");
	assert(tokens->next->next->next == NULL);
	free_tokens(tokens);
}

void	test_tokenization_pipe(void)
{
	t_token *tokens = create_tokens("ls | wc");

	assert_token(tokens, T_WORD, "ls");
	assert_token(tokens->next, T_PIPE, "|");
	assert_token(tokens->next->next, T_WORD, "wc");
	assert(tokens->next->next->next == NULL);
	free_tokens(tokens);
}

void	test_tokenization_redirection(void)
{
	t_token *tokens = create_tokens("echo hello > file");

	assert_token(tokens, T_WORD, "echo");
	assert_token(tokens->next, T_WORD, "hello");
	assert_token(tokens->next->next, T_OUT, ">");
	assert_token(tokens->next->next->next, T_WORD, "file");
	assert(tokens->next->next->next->next == NULL);
	free_tokens(tokens);
}

void	test_tokenization_append(void)
{
	t_token *tokens = create_tokens("echo hello >> file");

	assert_token(tokens, T_WORD, "echo");
	assert_token(tokens->next, T_WORD, "hello");
	assert_token(tokens->next->next, T_APPEND, ">>");
	assert_token(tokens->next->next->next, T_WORD, "file");
	assert(tokens->next->next->next->next == NULL);
	free_tokens(tokens);
}

void	test_tokenization_quotes(void)
{
	t_token *tokens = create_tokens("echo 'Hello World'");

	assert_token(tokens, T_WORD, "echo");
	assert_token(tokens->next, T_WORD, "'Hello World'");
	assert(tokens->next->next == NULL);
	free_tokens(tokens);
}

void	test_tokenization_mixed(void)
{
	t_token *tokens = create_tokens("cat < input.txt | grep 'foo' > output.txt");

	assert_token(tokens, T_WORD, "cat");
	assert_token(tokens->next, T_IN, "<");
	assert_token(tokens->next->next, T_WORD, "input.txt");
	assert_token(tokens->next->next->next, T_PIPE, "|");
	assert_token(tokens->next->next->next->next, T_WORD, "grep");
	assert_token(tokens->next->next->next->next->next, T_WORD, "'foo'");
	assert_token(tokens->next->next->next->next->next->next, T_OUT, ">");
	assert_token(tokens->next->next->next->next->next->next->next, T_WORD, "output.txt");
	assert(tokens->next->next->next->next->next->next->next->next == NULL);
	free_tokens(tokens);
}

void	test_tokenization(void)
{
	test_tokenization_simple();
	test_tokenization_pipe();
	test_tokenization_redirection();
	test_tokenization_append();
	test_tokenization_quotes();
	test_tokenization_mixed();
}
