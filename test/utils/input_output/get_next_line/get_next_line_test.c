#include "../../../test.h"


void    get_next_line_test(void)
{
	ft_printf("\nget_next_line_test: ");

	{
		char *line = get_next_line(-1);
		ft_printf("when is passed a invalid file descriptor\n");
		ft_printf("\texpect return NULL: ");
		assert(line == NULL);
		ft_printf("\n")	;
	}
	ft_printf("get_next_line_test: ");
	{
		ft_printf("when is passed a valid file descriptor\n");

		int fd = open("test/utils/input_output/get_next_line/content_file", O_RDONLY);	
		if (fd < 0) {
			assert(fd > 0);
			ft_printf("Test error: Open file error\n");
			return ;
		}
		char *results[2];
		results[0] = get_next_line(fd);
		results[1] = get_next_line(fd);
		

		ft_printf("\texpect return a line with correct content: ");
		assert(strcmp(results[0], "esse é o conteudo da linha\n") == 0);
		ft_printf("\n");
		
		ft_printf("\texpect a line termineted with '\\n': ");
		assert(results[0][ft_strlen(results[0]) - 1]  == '\n');
		ft_printf("\n");

		ft_printf("\texpect return null when you have nothing else to read: ");
		assert(results[1] == NULL);
		ft_printf("\n");
		

		free(results[0]);

	}
}


