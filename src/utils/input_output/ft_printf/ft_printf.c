/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:16:21 by jv                #+#    #+#             */
/*   Updated: 2024/11/22 23:58:00 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"


// TODO :: Buffer do printf com tamanho fixo, impedindo o uso para strings grandes, processar texto. etc 
// solucao: temos que ter um string builder de verdade, que cresce seu bloco dinamicamente

// TODO :: ft_printf nao reconhece \n no final de uma interpolacao de strinf

static unsigned char STOPLETTERS[256] = {
    ['d'] = PDIGIT,       ['i'] = PDIGIT,
    ['u'] = PUDIGIT,      ['o'] = PUOCTAL,
    ['x'] = PLOWX,        ['X'] = PHIGHX,
    ['f'] = PLOWF,        ['F'] = PHIGHF,
    ['e'] = PELOW,        ['E'] = PEHIGH,
    ['g'] = PSHORLOWREPR, ['G'] = PSHORHIGHREPR,
    ['a'] = PHEXFLOW,     ['A'] = PHEXFHIGH,
    ['c'] = PCHAR,        ['s'] = PSTRING,
    ['p'] = PPOINTER,     ['n'] = PNOTHING,
    ['%'] = PPERCENT
};


static PrintfStringBuilder init_printf_string_builder( void ) {
	PrintfStringBuilder string = {
		.buffer  = ft_coliseu_manager(TAKE),
		.size    = 0,
		.content = NULL
	};

	string.content = (char*) ft_calloc(PRINTF_BUFF_SIZE, sizeof(char), string.buffer);
	
	return string;
}

static void printf_instruction_set_args(PrintfInstruction* instruction, va_list args) {
	
	if ( instruction->type == PCHAR ) {
		instruction->content.c = va_arg(args, int);
		return; 
	}

	if ( instruction->type == PSTRING ) {
		char  *content      = va_arg(args, char*);
		
		int content_size    = (int) ft_strlen(content);

		if (instruction->width > content_size) {
			size_t size    = (instruction->width - content_size) + ft_strlen(content) + 1;

  			char *spaces   = ft_calloc(size, sizeof(char), instruction->buffer);
			
			ft_memset(spaces, ' ', instruction->width - content_size);
			
			ft_strlcpy(spaces + instruction->width - content_size, content, size); ;

			instruction->content.p = spaces;
		} else {
			instruction->content.p = content;
		}

		return ;
	}

	if ( instruction->type == PDIGIT ) {
		instruction->content.p =  ft_itoa(va_arg(args, int), instruction->buffer);
		return ;
	}

	if (instruction->type == PUDIGIT) {
		instruction->content.p =  ft_itoa(va_arg(args, unsigned int), instruction->buffer);
		return ;
	}

	if (instruction->type == PLOWF) {
		instruction->content.p =  ft_ftoan(va_arg(args, double), instruction->buffer, instruction->precision);
		return;
	}

	instruction->content.p = "Not implemented yet";
}

static PrintfInstruction printf_instruction_builder(char* start, char* end, va_list args) {
	
	char*			  ini 		   = start;
	char			  buffer[64]   = { 0 };
	size_t			  buffer_index = 0; 

	PrintfInstruction instruction  = { 
		.buffer    = ft_coliseu_manager(TAKE),
		.precision = 6
	};

	while ( ft_isdigit(*ini) && ini <= end && buffer_index < 64 ) {
		buffer[buffer_index] = *ini;

		++ini; ++buffer_index;
	}

	if ( ini != start ) {
		instruction.width = ft_atoi( buffer );
		buffer_index      = 0;
		start 			  = ini;
		ft_bzero(buffer, 64);
	} 

	if ( *ini == '.' ) {
		while ( ft_isdigit(*(++ini)) && ini <= end && buffer_index < 64 ) {
			buffer[buffer_index++] = *ini;
		}
	}

	if ( ini != start ) {
		instruction.precision = ft_atoi( buffer );
		buffer_index      = 0;
		start 			  = ini;
		ft_bzero(buffer, 64);
	} 
	
	// Hierarquia, por ultimo verifica o tipo

	while ( !STOPLETTERS[(unsigned char) *ini] && ini < end ) ++ini;

	instruction.type = STOPLETTERS[(unsigned char)*ini];

	printf_instruction_set_args(&instruction, args);

	return instruction;
	
}

static size_t ft_interpolate_ftprintf(char* start, char* end, va_list args, PrintfStringBuilder* buffer) {	
	
	PrintfInstruction instruction = printf_instruction_builder(start, end, args);

	size_t content_size 		  = 0;

	if ( instruction.type == PCHAR) {
		buffer->content[buffer->size++] = instruction.content.c;
	} else if (buffer->size < PRINTF_BUFF_SIZE - 1) {
		content_size = ft_strlen(instruction.content.p);

		while ( content_size > 0 ) {
			size_t bytes_readed = ft_strlcat(buffer->content, instruction.content.p, PRINTF_BUFF_SIZE);
			ft_putstr_fd(buffer->content, 1);
			
			buffer->size = 0;
			ft_bzero(buffer->content, PRINTF_BUFF_SIZE);
			
			content_size 		  -= bytes_readed;
			instruction.content.p += bytes_readed;

	  	}
		ft_arena_free(instruction.buffer);
	}
	return content_size;
}


static size_t ft_printf_lexer(const char* TEMPLATE, va_list args) {
	
	/* 
		Notas de desenvolvimento da 1.0

		Temporariamente irei usar uma arena como stringBuilder, o ideal é que no futuro, isso tenha sua propria lógica
		
		já que, não pode se ter a lógica de pool para um stringBuilder, elas sempre tem que estar em sequencia 
	*/

	char* end    = (char*) TEMPLATE;
	char* start  = (char*) TEMPLATE;
	size_t index = 0; 
	size_t bytes = 0;


	// TODO -> problema na arena quando usamos o tamanho total
	// TODO -> continuar usando arenas aqui ou usar um buffer da stack ?
	PrintfStringBuilder string = init_printf_string_builder();
	
	while (TEMPLATE[index]) {

		//Lendo strings sem interpolacao
		if ( STOPLETTERS[(unsigned char)TEMPLATE[index]] != PPERCENT ) {
			string.content[string.size++] = TEMPLATE[index];
			++start; ++end; ++index;
			continue;
		}

		// Strings com interpolacao basica %%
		if ( STOPLETTERS[(unsigned char)TEMPLATE[index]] == PPERCENT &&  STOPLETTERS[(unsigned char)TEMPLATE[index + 1]] == PPERCENT) {
			string.content[string.size++] = TEMPLATE[index];
			
			index += 2;
			start += 2;
			end   += 2; 

			continue;	
		}

		// ou nao tem mais nada para ler, ou vamos comecar de um %
		// garantindo que os ponteiros estarao apontando para os caracteres corretos em casos simples
		// %c ou %d, start -> % ; end -> c ou d 
		if (TEMPLATE[index]) { 
			++index; ++end;		
		}
 		
		// casos complexos, esses vao ser os casos onde temos mais informacao entre a interpolacao e o tipo
		// %.4f ou %5.5%f ou %10s
		// deve-se garantir que, os ponteiros start e end estejam apontandos para o local correto
		while( TEMPLATE[index] && !STOPLETTERS[(unsigned char)TEMPLATE[index]] ) {
			++end; ++index;
		}
		
		if ( TEMPLATE[index] && STOPLETTERS[(unsigned char)TEMPLATE[index]] ) {
			// + 1 -> se nao somar 1, ele ira passar %s, só quero que passe o s
			bytes += ft_interpolate_ftprintf(start + 1, end, args, &string);

			index += 1;
			end   += 1;
			start  = end;
		}
	}
	return bytes;
} 

int	ft_printf(const char *TEMPLATE, ...)
{
	va_list		arg_list;
	size_t      len = 0;

	if (!TEMPLATE)
		return (0);
	
	va_start(arg_list, TEMPLATE);
	
	len = ft_printf_lexer(TEMPLATE, arg_list);

	va_end(arg_list);

    ft_coliseu_manager(GIVE_BACK);

	return (len);
}
