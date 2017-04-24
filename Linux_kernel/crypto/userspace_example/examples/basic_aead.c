/*
 * File Name: basic_aead.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 21 Apr 2017 08:48:51 AM CST
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/if_alg.h>
#include <linux/socket.h>
#include <string.h>
#include <errno.h>

#ifndef AF_ALG
#define AF_ALG 38
#endif
#ifndef SOL_ALG
#define SOL_ALG 279
#endif
#ifndef BUFF_SIZE
#define BUFF_SIZE 32
#endif
#ifndef ALG_SET_AEAD_ASSOCLEN
#define ALG_SET_AEAD_ASSOCLEN		4
#endif
#ifndef ALG_SET_AEAD_AUTHSIZE
#define ALG_SET_AEAD_AUTHSIZE		5
#endif

/*
kcapi -x 2 -e -c "authenc(hmac(sha1),cbc(aes))" -p 53696e676c6520626c6f636b206d7367
-k 0800010000000010000000000000000000000000000000000000000006a9214036b8a15b512e03d534120006
-i 3dafba429d9eb430b422da802c9fac41 -a 3dafba429d9eb430b422da802c9fac41 -l 20
*/
int main(void)
{
	int opfd;
	int tfmfd;
    int ret;
    struct sockaddr_alg sa = {
        .salg_family = AF_ALG,
        .salg_type = "aead",
        .salg_name = "authenc(hmac(sha1),cbc(aes))"
    };
    struct msghdr msg = {};
    struct cmsghdr *cmsg;
    char cbuf[CMSG_SPACE(4) + CMSG_SPACE(20) + CMSG_SPACE(4)] = {0};
    char buf[BUFF_SIZE];
    struct af_alg_iv *iv;
    struct iovec iov;
    int i;

	tfmfd = socket(AF_ALG, SOCK_SEQPACKET, 0);
    if(tfmfd == -1) {
        perror("create socket error");
    }

	ret = bind(tfmfd, (struct sockaddr *)&sa, sizeof(sa));
    if(ret == -1) {
        perror("bind error");
    }

    // set key
    ret = setsockopt(tfmfd, SOL_ALG, ALG_SET_KEY,
                     "\x06\xa9\x21\x40\x36\xb8\xa1\x5b\x51\x2e"
                     "\x03\xd5\x34\x12\x00\x06\x35\x14\x02\x07"
                     "\x03\xd5\x34\x12\x00\x06\x35\x14\x02\x07"
                     "\x03\xd5\x34\x12\x00\x06\x35\x14\x02\x07"
                     "\x03\xd5\x34\x12", 44);
    if(ret == -1) {
        perror("setsockopt ALG_SET_KEY error");
    }

    // set taglen
    ret = setsockopt(tfmfd, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 16);
    if(ret == -1) {
        perror("setsockopt ALG_SET_AEAD_AUTHSIZE error");
    }

	opfd = accept(tfmfd, NULL, 0);
    if(opfd == -1) {
        perror("accept error");
    }

    // message prepare start
    msg.msg_control = cbuf;
    msg.msg_controllen = sizeof(cbuf);

    // set operation type
    cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_ALG;
    cmsg->cmsg_type = ALG_SET_OP;
    cmsg->cmsg_len = CMSG_LEN(4);
    *(__u32 *)CMSG_DATA(cmsg) = ALG_OP_ENCRYPT;

    // set initialize vector
    cmsg = CMSG_NXTHDR(&msg, cmsg);
    cmsg->cmsg_level = SOL_ALG;
    cmsg->cmsg_type = ALG_SET_IV;
    cmsg->cmsg_len = CMSG_LEN(20);
    iv = (void *)CMSG_DATA(cmsg);
    iv->ivlen = 16;
    memcpy(iv->iv,
           "\x3d\xaf\xba\x42\x9d\x9e\xb4\x30"
           "\xb4\x22\xda\x80\x2c\x9f\xac\x41", 16);

    // set assoc len
    cmsg = CMSG_NXTHDR(&msg, cmsg);
    cmsg->cmsg_level = SOL_ALG;
    cmsg->cmsg_type = ALG_SET_AEAD_ASSOCLEN;
    cmsg->cmsg_len = CMSG_LEN(4);
    *(__u32 *)CMSG_DATA(cmsg) = 16;

    // set plaintext
    iov.iov_base = "012345679ABCDEF0123456789ABCDEF";
    iov.iov_len = 32;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    // message prepare end

    // show before
    printf("before encrypt buf: \t");
	for (i = 0; i < BUFF_SIZE; i++) {
		printf("%02x", (unsigned char)buf[i]);
	}
	printf("\n");

    // really encrypt
    ret = sendmsg(opfd, &msg, 0);
    if(ret == -1) {
        perror("sendmsg error");
    }
    ret = read(opfd, buf, BUFF_SIZE);
    if(ret == -1) {
        perror("read error");
    }

    // show after
    printf("after encrypt buf: \t");
	for (i = 0; i < BUFF_SIZE; i++) {
		printf("%02x", (unsigned char)buf[i]);
	}
	printf("\n");

    // clean
	close(opfd);
	close(tfmfd);

	return 0;
}
