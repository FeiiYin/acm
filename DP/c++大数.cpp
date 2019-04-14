/// 别人的，到时候自己重写吧2333333

#include<cstdio>
#include<cstring>
#include<algorithm>
 
void add(char *res, char *m1, char *m2)
{
	int len1 = strlen(m1), len2 = strlen(m2), i1, i2, j, n1, n2, s = 0, si = 0;
	if (len1 == 0)
	{
		memcpy(res, m2, strlen(m2));
	}
	else if (m2 == 0)
	{
		memcpy(res, m1, strlen(m1));
	}
	else
	{
		i1 = len1 - 1;
		i2 = len2 - 1;
		j = 0;
		while (i1 >= 0 && i2 >= 0)
		{
			n1 = m1[i1--] - '0';
			n2 = m2[i2--] - '0';
			s = (n1 + n2 + si) % 10;
			si = (n1 + n2 + si) / 10;
			res[j++] = s + '0';
		}
		while (i1 >= 0)
		{
			n1 = m1[i1--] - '0';
			s = (n1 + si) % 10;
			si = (n1 + si) / 10;
			res[j++] = s + '0';
		}
		while (i2 >= 0)
		{
			n2 = m2[i2--] - '0';
			s = (n2 + si) % 10;
			si = (n2 + si) / 10;
			res[j++] = s + '0';
		}
		if (si)
		{
			res[j++] = si + '0';
		}
		std::reverse(res, res + strlen(res));
	}
}
 
void multiply(char *res, char *m1, char *m2)
{
	int len1 = strlen(m1), len2 = strlen(m2), i1, i2, j, n1, n2, s = 0, si = 0;
	char tmp[315] = {}, res2[315] = {};
	for (i2 = len2 - 1; i2 >= 0; i2--)
	{
		memset(tmp, 0, sizeof(tmp));
		memset(tmp, '0', sizeof(char) *  (len2 - 1 - i2));
		j = len2 - 1 - i2;
		si = 0;
		for (i1 = len1 - 1; i1 >= 0; i1--)
		{
			n1 = m1[i1] - '0';
			n2 = m2[i2] - '0';
			s = (n1 * n2 + si) % 10;
			si = (n1 * n2 + si) / 10;
			tmp[j++] = s + '0';
		}
		if (si)
		{
			tmp[j++] = si + '0';
		}
		std::reverse(tmp, tmp + strlen(tmp));
		if (strlen(res) != 0)
		{
			memcpy(res2, res, strlen(res));
		}
		else
		{
			res2[0] = '\0';
		}
		add(res, res2, tmp);
	}
}
 
int main()
{
	char st[105] = {};
	char s1[210] = {};
	char ans[315] = {};
	scanf("%s", st);
	if (st[0] != '-')
	{
		multiply(s1, st, st);
		multiply(ans, st, s1);
		printf("%s", ans);
	}
	else
	{
		char * ss = st + 1;
		multiply(s1, ss, ss);
		multiply(ans, ss, s1);
		printf("-%s", ans);
	}
	return 0;
}
