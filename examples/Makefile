# Copyright (c) 2021 jdeokkim
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.
#

.PHONY: all clean

EXAMPLES = \
    playground

CC := gcc
CFLAGS := -g -Isrc/external -I../include -lm -std=c99 -O0 -D_DEFAULT_SOURCE

all: $(EXAMPLES)

$(EXAMPLES): %: src/%.c
	mkdir -p bin
	$(CC) $< -o bin/$@ $(CFLAGS) $(LDFLAGS) $(LDLIBS)
    
clean:
	find . -type d -name bin -exec rm -rf {} +
