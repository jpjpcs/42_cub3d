/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:42:01 by joaosilva         #+#    #+#             */
/*   Updated: 2024/11/20 19:05:05 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void check_map(char *file_name)
{
    int fd;
    char *line;
    int ret;

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        exit_error(NULL, "Couldn´t open requested file. Please insert a corrected file.");
    while ((ret = get_next_line(fd, &line)) > 0)
    {
        if (line[0] == '1' || line[0] == '0')
            break;
        free(line);
    }
    if (ret <= 0)
        exit_error(NULL, "Error\nInvalid map\n");
    free(line);
    close(fd);
}

void check_file_open(char *file_name)
{
    int fd;

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        exit_error(NULL,
			"Couldn´t open requested file. Please insert a corrected file.");
    close(fd);
}

static void check_file_name_and_extension(char *file_name)
{
    int len;

    len = ft_strlen(file_name);
    if (len < 5)
        exit_error(NULL,"Error\nInvalid file name\n");
    if (ft_strncmp(file_name + len - 4, ".cub", 4) != 0)
        exit_error(NULL, "Error\nInvalid file extension\n");
}

static int check_args_num(int argc)
{
    if (argc != 2)
        return (exit_error(NULL, "Error\nInvalid number of arguments\n"));
}

void checkers(int argc, char **argv)
{
    check_args_num(argc);
    check_file_name_and_extension(argv[1]);
    check_file_open(argv[1]);
    check_map(argv[1]);
}
