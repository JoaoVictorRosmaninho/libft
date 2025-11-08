/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:16:21 by jv                #+#    #+#             */
/*   Updated: 2025/11/08 16:27:47 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

// TODO :: Buffer do printf com tamanho fixo, impedindo o uso para strings grandes, processar texto. etc
// solucao: temos que ter um string builder de verdade, que cresce seu bloco dinamicamente


static unsigned char stop_letters[256] = {
	['d'] = PDIGIT, 
	['i'] = PDIGIT, 
	['u'] = PUDIGIT, 
	['o'] = PUOCTAL, 
	['x'] = PLOWX, 
	['X'] = PHIGHX, 
	['f'] = PLOWF, 
	['F'] = PHIGHF, 
	['e'] = PELOW, 
	['E'] = PEHIGH, 
	['g'] = PSHORLOWREPR, 
	['G'] = PSHORHIGHREPR, 
	['a'] = PHEXFLOW, 
	['A'] = PHEXFHIGH, 
	['c'] = PCHAR, 
	['s'] = PSTRING, 
	['p'] = PPOINTER, 
	['n'] = PNOTHING, 
	['%'] = PPERCENT
};

static PrintfStringBuilder init_printf_string_builder(void)
{
	PrintfStringBuilder string = {
		.buffer = ft_coliseu_manager(TAKE),
		.size = 0,
		.content = NULL};

	string.content = ft_calloc(PRINTF_BUFF_SIZE, sizeof(char), string.buffer);

	return string;
}

static void printf_instruction_set_args(PrintfInstruction *instruction, va_list args)
{

	if (instruction->type == PCHAR)
	{
		instruction->content.c = va_arg(args, int);
		return;
	}

	if (instruction->type == PSTRING)
	{
		char *content = va_arg(args, char *);

		if ( content == NULL )
			content = "(null)";

		int content_size = (int)ft_strlen(content);

		if (instruction->width > content_size)
		{
			size_t size = (instruction->width - content_size) + ft_strlen(content) + 1;

			char *spaces = ft_calloc(size, sizeof(char), instruction->buffer);

			ft_memset(spaces, ' ', instruction->width - content_size);

			ft_strlcpy(spaces + instruction->width - content_size, content, size);
			;

			instruction->content.p = spaces;
		}
		else
		{
			instruction->content.p = content;
		}

		return;
	}

	if (instruction->type == PDIGIT)
	{
		instruction->content.p = ft_itoa(va_arg(args, int), instruction->buffer);
		return;
	}

	if (instruction->type == PUDIGIT)
	{
		instruction->content.p = ft_itoa(va_arg(args, unsigned int), instruction->buffer);
		return;
	}

	if (instruction->type == PLOWF)
	{
		instruction->content.p = ft_ftoan(va_arg(args, double), instruction->buffer, instruction->precision);
		return;
	}

	instruction->content.p = "Not implemented yet";
}

static PrintfInstruction printf_instruction_builder(char *start, char *end, va_list args)
{

	char *ini = start;
	char buffer[MAX_FORMAT_SPEC_SIZE] = {0};
	size_t buffer_index = 0;

	PrintfInstruction instruction = {
		.buffer = ft_coliseu_manager(TAKE),
		.precision = 6};

	while (ft_isdigit(*ini) && ini <= end && buffer_index < 64)
	{
		buffer[buffer_index] = *ini;

		++ini;
		++buffer_index;
	}

	if (ini != start)
	{
		instruction.width = ft_atoi(buffer);
		buffer_index = 0;
		start = ini;
		ft_bzero(buffer, 64);
	}

	if (*ini == '.')
	{
		while (ft_isdigit(*(++ini)) && ini <= end && buffer_index < 64)
		{
			buffer[buffer_index++] = *ini;
		}
	}

	if (ini != start)
	{
		instruction.precision = ft_atoi(buffer);
		buffer_index = 0;
		start = ini;
		ft_bzero(buffer, 64);
	}

	// Hierarquia, por ultimo verifica o tipo

	while (!stop_letters[(unsigned char)*ini] && ini < end)
		++ini;

	instruction.type = stop_letters[(unsigned char)*ini];

	printf_instruction_set_args(&instruction, args);

	return instruction;
}

static size_t ft_interpolate_ftprintf(char *start, char *end, va_list args, PrintfStringBuilder *buffer)
{

	PrintfInstruction instruction = printf_instruction_builder(start, end, args);

	size_t content_size = 0;

	if (instruction.type == PCHAR)
	{
		buffer->content[buffer->size++] = instruction.content.c;
	}
	else if (buffer->size < PRINTF_BUFF_SIZE - 1)
	{
		content_size = ft_strlen(instruction.content.p);

		while (content_size > 0)
		{

			size_t space_left    = PRINTF_BUFF_SIZE - buffer->size;
			size_t bytes_to_copy = ( content_size < space_left ) ? content_size : space_left;


			ft_memcpy( buffer->content + buffer->size, instruction.content.p, bytes_to_copy);

			buffer->size          += bytes_to_copy;
			content_size          -= bytes_to_copy;
			instruction.content.p += bytes_to_copy;

			if ( buffer->size >= PRINTF_BUFF_SIZE - 1 ) {
				ft_putstr_fd( buffer->content, 1);
				buffer->size  = 0;
				ft_bzero( buffer->content, PRINTF_BUFF_SIZE );
			}

		}
		ft_arena_free(instruction.buffer);
	}
	return content_size;
}

static size_t ft_printf_lexer(const char *format, va_list args)
{

	/*
		Notas de desenvolvimento da 1.0

		Temporariamente irei usar uma arena como stringBuilder, o ideal é que no futuro, isso tenha sua propria lógica

		já que, não pode se ter a lógica de pool para um stringBuilder, elas sempre tem que estar em sequencia
	*/

	char *end = (char *)format;
	char *start = (char *)format;
	size_t index = 0;
	size_t bytes = 0;

	// TODO -> problema na arena quando usamos o tamanho total
	// TODO -> continuar usando arenas aqui ou usar um buffer da stack ?
	PrintfStringBuilder string = init_printf_string_builder();

	while (format[index])
	{

		// Lendo strings sem interpolacao
		if (stop_letters[(unsigned char)format[index]] != PPERCENT)
		{

			if (string.size >= PRINTF_BUFF_SIZE - 1)
			{
				ft_putstr_fd(string.content, 1);
				string.size = 0;
				ft_bzero(string.content, PRINTF_BUFF_SIZE);
			}
			string.content[string.size++] = format[index];
			++start; ++end; ++index;
			continue;
		}

		// Strings com interpolacao basica %%
		if (stop_letters[(unsigned char)format[index]] == PPERCENT && stop_letters[(unsigned char)format[index + 1]] == PPERCENT)
		{
			string.content[string.size++] = format[index];

			index += 2;
			start += 2;
			end   += 2;

			continue;
		}

		// ou nao tem mais nada para ler, ou vamos comecar de um %
		// garantindo que os ponteiros estarao apontando para os caracteres corretos em casos simples
		// %c ou %d, start -> % ; end -> c ou d
		if (format[index])
		{
			++index;
			++end;
		}

		// casos complexos, esses vao ser os casos onde temos mais informacao entre a interpolacao e o tipo
		// %.4f ou %5.5%f ou %10s
		// deve-se garantir que, os ponteiros start e end estejam apontandos para o local correto
		while (format[index] && !stop_letters[(unsigned char)format[index]])
		{
			++end;
			++index;
		}

		if (format[index] && stop_letters[(unsigned char)format[index]])
		{
			// + 1 -> se nao somar 1, ele ira passar %s, só quero que passe o s
			bytes += ft_interpolate_ftprintf(start + 1, end, args, &string);

			index += 1;
			end   += 1;
			start  = end;
		}
	}

	// Flush final: imprimir qualquer conteúdo restante no buffer
	if (string.size > 0)
	{
		bytes += ft_putstr_fd(string.content, 1);
	}

	ft_arena_free(string.buffer);

	return bytes;
}

int ft_printf(const char *format, ...)
{
	va_list arg_list;
	size_t len = 0;

	if (!format)
		return (0);

	va_start(arg_list, format);

	len = ft_printf_lexer(format, arg_list);

	va_end(arg_list);

	ft_coliseu_manager(GIVE_BACK);

	return (len);
}
