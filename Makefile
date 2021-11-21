lib = libWHY.a
lib_header = why_lib.h
name = sudoku

cc = gcc
flags = -Wall -Wextra -g
release_flags = -Wall -Wextra -O3 -flto

source_folder = src/
obj_folder = obj/
# lib_folder = ~/projects/why/
lib_folder = ./lib/
include_folder = $(lib_folder)src/

include_flag = -I $(lib_folder) -I $(include_folder) -I .
linker_flag = $(lib_folder)$(lib)
headers = $(wildcard $(source_folder)*.h)
source = $(wildcard $(source_folder)*.c)
objects = $(subst $(source_folder),$(obj_folder),$(source:.c=.o))

.PHONY: directory

all: directory $(name)

directory:
	@mkdir -p $(obj_folder)

release: flags = $(release_flags)
release: re

$(obj_folder)%.o: $(source_folder)%.c $(headers)
	$(cc) $(flags) $(include_flag) $< -c -o $@

$(name): $(objects)
	$(cc) $(flags) $(include_flag) $(objects) -o $(name) $(linker_flag)

clean:
	rm -f $(objects)

fclean: clean
	rm -f $(name)

re: fclean all