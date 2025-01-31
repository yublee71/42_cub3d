/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:26:56 by yublee            #+#    #+#             */
/*   Updated: 2024/04/23 15:26:55 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# define FDMAX 1024

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_gnl_substr(char *s, size_t start, size_t len);
char	*ft_f_strjoin(char *s1, char *s2);
char	*ft_store_until_newline(char *stored);
void	*ft_free(char **s1, char *s2);
char	*ft_initialize(char *stored, int fd);
size_t	ft_chr_idx(char *s, char c);
char	*ft_malloc(size_t n);

#endif
