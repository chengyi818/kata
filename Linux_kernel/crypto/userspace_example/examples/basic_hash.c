/*
 * File Name: basic_hash.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 18 Apr 2017 07:53:30 PM CST
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/if_alg.h>
#include <linux/socket.h>
#include <string.h>

int main(void)
{
	int opfd;
	int tfmfd;
	struct sockaddr_alg sa = {
		.salg_family = AF_ALG,
		.salg_type = "hash",
		.salg_name = "sha1"
	};
    char *plaintext = "chengyi";
	char buf[20];
	int i;

	tfmfd = socket(AF_ALG, SOCK_SEQPACKET, 0);

	bind(tfmfd, (struct sockaddr *)&sa, sizeof(sa));

	opfd = accept(tfmfd, NULL, 0);

	write(opfd, plaintext, sizeof(plaintext));
	read(opfd, buf, 20);

	for (i = 0; i < 20; i++) {
		printf("%02x", (unsigned char)buf[i]);
	}
	printf("\n");

	close(opfd);
	close(tfmfd);

	return 0;
}
