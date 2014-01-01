/*
 * io-scheduler.c
 *
 * From "Linux System Programming : Robert Love", page 124
 *
 * A simple program to fetch disk blocks from logical blocks of a given file.
 * This program prints a table, mapping logical to physical disk blocks. The ioctl
 * FIBMAP call requires root privileges.
 *
 * This information can be used to sort read requests in a large batch as a
 * "user space io scheduler", so reads can be optimized.
 *
 * Unnecessary for most but the heaviest IO programs
 *
 *  Created on: 01-Jan-2014
 *      Author: adil
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/fs.h>

int get_block(int fd, int logical_block)
{
    int ret;

    ret = ioctl(fd, FIBMAP, &logical_block);
    if(ret < 0) {
        perror("ioctl");
        return -1;
    }

    return logical_block;
}

int get_nr_blocks(int fd)
{
    struct stat buf;
    int ret;

    ret = fstat(fd, &buf);
    if(ret < 0){
        perror("fstat");
        return -1;
    }

    return buf.st_blocks;
}

void print_blocks(int fd)
{
    int nr_blocks, i;

    nr_blocks = get_nr_blocks(fd);
    if(nr_blocks < 0){
        fprintf(stderr, "get_nr_blocks failed\n");
        return;
    }

    if(nr_blocks == 0){
        printf("no allocated blocks\n");
        return;
    } else {
        printf("%d allocated blocks\n\n", nr_blocks);
    }

    for(i=0; i< nr_blocks; i++) {
        int phys_block;

        phys_block = get_block(fd, i);
        if(phys_block < 0) {
            fprintf(stderr, "get_block failed\n");
            return;
        }

        if(!phys_block)
            continue;

        printf("(%u %u) ", i, phys_block);
    }

    putchar('\n');
}

int main(int argc, char *argv[])
{
    int fd;

    if(argc < 2) {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if(fd < 0) {
        perror("open");
        return 1;
    }

    print_blocks(fd);
    return 0;
}
