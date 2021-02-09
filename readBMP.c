#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdbool.h> 
long size=0;
int data;
#define REV(X) ((X << 24) | (( X & 0xff00 ) << 8) | (( X >> 8) & 0xff00 ) | ( X >> 24 ))
char* readBMP(uint32_t* fb, FILE *imagef)
{
	int i,j,data,offset,hbytes,width,height;
	long size=0,datacut=0,bpp=0;
	int **image;
	int temp=0;
	if(imagef==NULL)
	{
		printf("Error trying opening file");
		exit(1);
	}
	else
	{
		printf("Processing BMP Header...\n");
		offset = 0;
		fseek(imagef,offset,0);
		for(i=0;i<2;i++)
		{
			fread(&data,1,1,imagef);
			printf("%c",data);
		}
		fread(&size,4,1,imagef);
		offset = 10;
		fseek(imagef,offset,0);
		fread(&datacut,4,1,imagef);
		fread(&hbytes,4,1,imagef);
		fread(&width,4,1,imagef);
		fread(&height,4,1,imagef);
		fseek(imagef,2,1);
		fread(&bpp,2,1,imagef);
		fseek(imagef,datacut,0);
		int **image = (int **)malloc(height*sizeof(int *));
		for(i=0;i<height;i++)
		{
			image[i] = (int *)malloc(width*sizeof(int));
		}
		int numbytes = (size - datacut)/3;
		int r,c;
		for(r=252;r>0;r--)
		{
			for(c=0;c<420;c++)
			{
				fread(&temp,1,3,imagef);
                printf("%x ",temp);
                fb[(r * 1280 * 2) + c * 2] = REV(temp);
}
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
    fp=fopen("/bin/posterpropaganda.bmp", "r");
    readBMP(fb,fp);
    fclose(fp);
    return 0;
}