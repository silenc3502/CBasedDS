#include <stdio.h>
#include <string.h>

unsigned int elf_hash(const char* str, unsigned int len)
{
	unsigned int hash = 0;
	unsigned int x    = 0;
	unsigned int i    = 0;


	for(i = 0; i < len; str++, i++)
	{
		//    128   64   32   16    8    4    2    1
		//     0     0    0    0    0    0    0    0
		//     0     1    0    0    0    0    0    1  (65)
		//     0     1    0    1    1    0    1    1  (91)
		//     0     1    1    0    0    0    0    1  (97)
		//     0     1    1    1    1    0    1    1  (123)

		// 0. 0000 0000 (first shift)
		// 1. 0000 00XY (+ *str)
		// 2. 0000 0XY0 (second shift)
		// 3. 0000 0XY0 + 0000 00AB = 0000 0XZB (+ *str)
		// 4. 0000 XZB0 (third shift)
		// 5. 0000 XZB0 + 0000 00CD = 0000 XZED (+ *str)
		// 6. 000X ZED0 (fourth shift)
		// 7. 000X ZED0 + 0000 00FG = 000X ZEHG (+ *str)
		hash = (hash << 4) + (*str);

		if((x = hash & 0xF0000000L) != 0)
		{
			hash ^= (x >> 24);
		}
		hash &= ~x;
	}

	return hash;
}


int main(void)
{
	int i;

	char *buf[] = {
		"test channel",
		"hello",
		"c",
		"rust",
		"c",
		"golang",
		"c",
		"c++",
		"stm32",
		"c",
		"ti",
		"fpga",
		"zynq",
		"c",
		"linux",
		"c"
	};

	int len = sizeof(buf) / sizeof(char *);

	for (i = 0; i < len; i++)
	{
		printf("str: %15s, elf hash: %u\n", buf[i], elf_hash(buf[i], strlen(buf[i])));
	}

	return 0;
}
