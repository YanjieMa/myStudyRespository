src = $(wildcard ./*.c)

obj = $(patsubst %.c, %.o, $(src))

incPath = ./

flag = -Wall -g

ALL:a.out

$(obj):./%.o:./%.c
	gcc -c $< -o $@ $(flag) -I $(incPath)
a.out:$(obj)
	gcc $^ -o $@ $(flag)

.PHONY:clean
clean:
	-rm -rf $(obj) a.out
