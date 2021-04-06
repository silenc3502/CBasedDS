#include <stdio.h>
#include <string.h>

#define TABLE_SIZE			1000
#define MOD_SIZE			1000

struct contact
{
	char name[12];
	char phone_num[12];
}
contact_arr[TABLE_SIZE];

int hash(char *s)
{
	int n;

	n = strlen(s);

	return (s[0] - 'A' + (s[n / 2 - 1] - 'A') * 26 + (s[n - 2] - 'A') * 26 * 26) % MOD_SIZE;
}

int main(void)
{
	int n;
	char a[12], b[12];

	printf("Name, Phone Num: ");

	while(scanf("%s %s", a, b) != EOF)
	{
		n = hash(a);
		strcpy(contact_arr[n].name, a);
		strcpy(contact_arr[n].phone_num, b);
	}

	rewind(stdin);

	printf("Search Data: ");

	while(scanf("%s", a) != EOF)
	{
		n = hash(a);
		printf("%15s%15s\n", contact_arr[n].name, contact_arr[n].phone_num);
	}

	return 0;
}
