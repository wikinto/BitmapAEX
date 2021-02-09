#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdbool.h> 
long size=0;
int data;
struct BMPFile{
	uint16_t type;
	uint32_t size;
	uint32_t reserved;
	uint32_t offset;
	uint32_t infosize;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bitcount;
	uint32_t compression;
	uint32_t imagesize;
	uint32_t pixels_x;
	uint32_t pixels_y;
	uint32_t used;
	uint32_t important;
	
}__attribute__((packed));

uint32_t bswap32(uint32_t x) {
    return ((x & 0xFF000000) >> 24) | ((x & 0x00FF0000) >> 8) | ((x & 0x0000FF00) << 8) | (x << 24);
}

char* readBMP(uint32_t* fb, FILE *imagef)
{
	int color = 0;
	struct BMPFile bmp;

	fread(&bmp,sizeof(bmp),1,imagef);
	printf("ojigiejiijeg %i %i %i",bmp.width,bmp.height,bmp.size);
	for (int i = 0; i < bmp.height; i++)
	{
		for (int j = 0; j < bmp.width; j++)
		{
			fread(&color,1,3,imagef);
			fb[(i) * 1280 + j] = color;
		}
		
	}
	
}

void setpixel(uint32_t* fb, uint32_t x, uint32_t y, uint32_t color){
    for (int j = 0; j < 720; j++)
        for (int i = 0; i < 1280; i++)
            fb[(y + j) * 1280 + x + i] = color;
}
int main(){
    ioctl(1,0x01,0x01);
    uint32_t* fb = (uint32_t*) mmap(NULL,ioctl(1,0x07), PROT_READ | PROT_WRITE,0,1,0);
    FILE *fp;
    fp=fopen("/bin/aaa.bmp", "r");
    readBMP(fb,fp);
    fclose(fp);
    return 0;
}