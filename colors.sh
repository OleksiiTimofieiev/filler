# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    colors.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otimofie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/12 22:40:50 by otimofie          #+#    #+#              #
#    Updated: 2018/03/12 22:40:57 by otimofie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

yellow=$(printf "😀")
blue=$(printf "\033[34mX\033[0m")
green=$(printf "\033[32mo\033[0m")
red=$(printf "\033[35mx\033[0m")

sed "s|O|$yellow|g" |
sed "s|X|$blue|g" |
sed "s|x|$red|g" |
sed "/^0.. /s|o|$green|g" |
sed "s|fin|player|g" 
