# Thêm -lm vào CFLAGS để liên kết thư viện math
CC = gcc
CFLAGS = -Wall -g -lm

# Các file nguồn và đối tượng
SRC = helpers.c filter.c
OBJ = $(SRC:.c=.o)

# Quy tắc build
all: filter

filter: $(OBJ)
	$(CC) $(CFLAGS) -o filter $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) filter
# neu khong build duoc thi chay lenh: gcc filter.c helpers.c -o filter-less -lm