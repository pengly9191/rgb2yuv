#include"util.h"

/*
    extern "C"  
    {  
        #include <stdio.h>  
        #include <stdlib.h>  
        #include <jpeglib.h>  
    }  
      
    typedef long LONG;  
    typedef unsigned long DWORD;  
    typedef unsigned short WORD;  
      
    typedef struct {  
            WORD    bfType;  
            DWORD   bfSize;  
            WORD    bfReserved1;  
            WORD    bfReserved2;  
            DWORD   bfOffBits;  
    } BMPFILEHEADER_T;  
      
    typedef struct{  
            DWORD      biSize;  
            LONG       biWidth;  
            LONG       biHeight;  
            WORD       biPlanes;  
            WORD       biBitCount;  
            DWORD      biCompression;  
            DWORD      biSizeImage;  
            LONG       biXPelsPerMeter;  
            LONG       biYPelsPerMeter;  
            DWORD      biClrUsed;  
            DWORD      biClrImportant;  
    } BMPINFOHEADER_T;  
      
    void savebmp(unsigned char * pdata, char * bmp_file, int width, int height )  
    {     
           int size = width*height*3*sizeof(char); 
         
           BMPFILEHEADER_T bfh;  
           bfh.bfType = (WORD)0x4d42;  
           bfh.bfSize = size  // data size  
                  + sizeof( BMPFILEHEADER_T ) // first section size  
                  + sizeof( BMPINFOHEADER_T ) // second section size  
                  ;  
           bfh.bfReserved1 = 0; // reserved  
           bfh.bfReserved2 = 0; // reserved  
           bfh.bfOffBits = sizeof( BMPFILEHEADER_T )+ sizeof( BMPINFOHEADER_T );
      
    
           BMPINFOHEADER_T bih;  
           bih.biSize = sizeof(BMPINFOHEADER_T);  
           bih.biWidth = width;  
           bih.biHeight = -height;
           bih.biPlanes = 1;//\u4e3a1\uff0c\u4e0d\u7528\u6539  
           bih.biBitCount = 24;  
           bih.biCompression = 0;//\u4e0d\u538b\u7f29  
           bih.biSizeImage = size;  
           bih.biXPelsPerMeter = 2835 ;//\u50cf\u7d20\u6bcf\u7c73  
           bih.biYPelsPerMeter = 2835 ;  
           bih.biClrUsed = 0;
           bih.biClrImportant = 0;//\u6bcf\u4e2a\u50cf\u7d20\u90fd\u91cd\u8981  
           FILE * fp = fopen( bmp_file,"wb" );  
           if( !fp ) return;  
      
           fwrite( &bfh, 8, 1,  fp );
           fwrite(&bfh.bfReserved2, sizeof(bfh.bfReserved2), 1, fp);  
           fwrite(&bfh.bfOffBits, sizeof(bfh.bfOffBits), 1, fp);  
           fwrite( &bih, sizeof(BMPINFOHEADER_T),1,fp );  
           fwrite(pdata,size,1,fp);  
           fclose( fp );  
    }  


    */


#include <stdio.h>
#include <stdlib.h>
#ifndef CHENLEECV_H
#define CHENLEECV_H

typedef struct
{
	//unsigned short    bfType;
	unsigned long    bfSize;
	unsigned short    bfReserved1;
	unsigned short    bfReserved2;
	unsigned long    bfOffBits;
} ClBitMapFileHeader;

typedef struct
{
	unsigned long  biSize; 
	long   biWidth; 
	long   biHeight; 
	unsigned short   biPlanes; 
	unsigned short   biBitCount;
	unsigned long  biCompression; 
	unsigned long  biSizeImage; 
	long   biXPelsPerMeter; 
	long   biYPelsPerMeter; 
	unsigned long   biClrUsed; 
	unsigned long   biClrImportant; 
} ClBitMapInfoHeader;

typedef struct 
{
	unsigned char rgbBlue; //\u8be5\u989c\u8272\u7684\u84dd\u8272\u5206\u91cf
	unsigned char rgbGreen; //\u8be5\u989c\u8272\u7684\u7eff\u8272\u5206\u91cf
	unsigned char rgbRed; //\u8be5\u989c\u8272\u7684\u7ea2\u8272\u5206\u91cf
	unsigned char rgbReserved; //\u4fdd\u7559\u503c
} ClRgbQuad;

typedef struct
{
	int width;
	int height;
	int channels;
	unsigned char* imageData;
}ClImage;

ClImage* clLoadImage(char* path);
bool clSaveImage(char* path, ClImage* bmpImg);

#endif
	


ClImage* clLoadImage(char* path)
{
	ClImage* bmpImg;
	FILE* pFile;
	unsigned short fileType;
	ClBitMapFileHeader bmpFileHeader;
	ClBitMapInfoHeader bmpInfoHeader;
	int channels = 1;
	int width = 0;
	int height = 0;
	int step = 0;
	int offset = 0;
	unsigned char pixVal;
	ClRgbQuad* quad;
	int i, j, k;

	bmpImg = (ClImage*)malloc(sizeof(ClImage));
	pFile = fopen(path, "rb");
	if (!pFile)
	{
		free(bmpImg);
		return NULL;
	}

	fread(&fileType, sizeof(unsigned short), 1, pFile);
	if (fileType == 0x4D42)
	{
		//printf("bmp file! \n");

		fread(&bmpFileHeader, sizeof(ClBitMapFileHeader), 1, pFile);
		printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
		printf("bmp\u6587\u4ef6\u5934\u4fe1\u606f\uff1a\n");
		printf("\u6587\u4ef6\u5927\u5c0f\uff1a%d \n", bmpFileHeader.bfSize);
		printf("\u4fdd\u7559\u5b57\uff1a%d \n", bmpFileHeader.bfReserved1);
		printf("\u4fdd\u7559\u5b57\uff1a%d \n", bmpFileHeader.bfReserved2);
		printf("\u4f4d\u56fe\u6570\u636e\u504f\u79fb\u5b57\u8282\u6570\uff1a%d \n", bmpFileHeader.bfOffBits);

		fread(&bmpInfoHeader, sizeof(ClBitMapInfoHeader), 1, pFile);
		printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
		printf("bmp\u6587\u4ef6\u4fe1\u606f\u5934\n");
		printf("\u7ed3\u6784\u4f53\u957f\u5ea6\uff1a%d \n", bmpInfoHeader.biSize);
		printf("\u4f4d\u56fe\u5bbd\u5ea6\uff1a%d \n", bmpInfoHeader.biWidth);
		printf("\u4f4d\u56fe\u9ad8\u5ea6\uff1a%d \n", bmpInfoHeader.biHeight);
		printf("\u4f4d\u56fe\u5e73\u9762\u6570\uff1a%d \n", bmpInfoHeader.biPlanes);
		printf("\u989c\u8272\u4f4d\u6570\uff1a%d \n", bmpInfoHeader.biBitCount);
		printf("\u538b\u7f29\u65b9\u5f0f\uff1a%d \n", bmpInfoHeader.biCompression);
		printf("\u5b9e\u9645\u4f4d\u56fe\u6570\u636e\u5360\u7528\u7684\u5b57\u8282\u6570\uff1a%d \n", bmpInfoHeader.biSizeImage);
		printf("X\u65b9\u5411\u5206\u8fa8\u7387\uff1a%d \n", bmpInfoHeader.biXPelsPerMeter);
		printf("Y\u65b9\u5411\u5206\u8fa8\u7387\uff1a%d \n", bmpInfoHeader.biYPelsPerMeter);
		printf("\u4f7f\u7528\u7684\u989c\u8272\u6570\uff1a%d \n", bmpInfoHeader.biClrUsed);
		printf("\u91cd\u8981\u989c\u8272\u6570\uff1a%d \n", bmpInfoHeader.biClrImportant);
		printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");

		if (bmpInfoHeader.biBitCount == 8)
		{
			//printf("\u8be5\u6587\u4ef6\u6709\u8c03\u8272\u677f\uff0c\u5373\u8be5\u4f4d\u56fe\u4e3a\u975e\u771f\u5f69\u8272\n\n");
			channels = 1;
			width = bmpInfoHeader.biWidth;
			height = bmpInfoHeader.biHeight;
			offset = (channels*width)%4;
			if (offset != 0)
			{
				offset = 4 - offset;
			}
			//bmpImg->mat = kzCreateMat(height, width, 1, 0);
			bmpImg->width = width;
			bmpImg->height = height;
			bmpImg->channels = 1;
			bmpImg->imageData = (unsigned char*)malloc(sizeof(unsigned char)*width*height);
			step = channels*width;

			quad = (ClRgbQuad*)malloc(sizeof(ClRgbQuad)*256);
			fread(quad, sizeof(ClRgbQuad), 256, pFile);
			free(quad);

			for (i=0; i<height; i++)
			{
				for (j=0; j<width; j++)
				{
					fread(&pixVal, sizeof(unsigned char), 1, pFile);
					bmpImg->imageData[(height-1-i)*step+j] = pixVal;
				}
				if (offset != 0)
				{
					for (j=0; j<offset; j++)
					{
						fread(&pixVal, sizeof(unsigned char), 1, pFile);
					}
				}
			}			
		}
		else if (bmpInfoHeader.biBitCount == 24)
		{
			//printf("\u8be5\u4f4d\u56fe\u4e3a\u4f4d\u771f\u5f69\u8272\n\n");
			channels = 3;
			width = bmpInfoHeader.biWidth;
			height = bmpInfoHeader.biHeight;

			bmpImg->width = width;
			bmpImg->height = height;
			bmpImg->channels = 3;
			bmpImg->imageData = (unsigned char*)malloc(sizeof(unsigned char)*width*3*height);
			step = channels*width;

			offset = (channels*width)%4;
			if (offset != 0)
			{
				offset = 4 - offset;
			}

			for (i=0; i<height; i++)
			{
				for (j=0; j<width; j++)
				{
					for (k=0; k<3; k++)
					{
						fread(&pixVal, sizeof(unsigned char), 1, pFile);
						bmpImg->imageData[(height-1-i)*step+j*3+k] = pixVal;
					}
					//kzSetMat(bmpImg->mat, height-1-i, j, kzScalar(pixVal[0], pixVal[1], pixVal[2]));
				}
				if (offset != 0)
				{
					for (j=0; j<offset; j++)
					{
						fread(&pixVal, sizeof(unsigned char), 1, pFile);
					}
				}
			}
		}
	}
	printf("%d",bmpInfoHeader.biWidth);
	return bmpImg;
}

bool clSaveImage(char* path, ClImage* bmpImg)
{
	FILE *pFile;
	unsigned short fileType;
	ClBitMapFileHeader bmpFileHeader;
	ClBitMapInfoHeader bmpInfoHeader;
	int step;
	int offset;
	unsigned char pixVal = '\0';
	int i, j;
	ClRgbQuad* quad;

	bmpImg->height = 600;
	bmpImg->width =  800;
	bmpImg->channels == 1;

	
	FILE *yuvfile;
	char path1[64] = "/home/ply/YUV.yuv";
	yuvfile = fopen(path1, "rb");
	if (!yuvfile)
	{
		printf("cannot open yuv file \n");
		return NULL;
	}
	unsigned char* imageData1;
	int size =  (sizeof(unsigned char))*bmpImg->height *bmpImg->width*3/2;
	imageData1 = (unsigned char*)malloc(size);
	int ret = fread(imageData1,sizeof(unsigned char),size, yuvfile);
	if (ret != bmpImg->height *bmpImg->width*3/2){
		printf("\n  read  yuv file error  %d \n",ret);
		return NULL;

	}
	printf("output ");
	for(int i = 0 ;i< bmpImg->height ;i++){
		int pos = bmpImg->width*i;	
		for (int j = 0;j < bmpImg->width;j++){
			printf("  :%d",imageData1[pos+j]);
//			printf("  ");
		}
		printf("\n");
	}


	
	bmpImg->imageData = imageData1;
	pFile = fopen(path, "wb");
	if (!pFile)
	{
		return false;
	}

	fileType = 0x4D42;
	fwrite(&fileType, sizeof(unsigned short), 1, pFile);

	if (bmpImg->channels == 3)//24\u4f4d\uff0c\u901a\u9053\uff0c\u5f69\u56fe
	{
		step = bmpImg->channels*bmpImg->width;
		offset = step%4;
		if (offset != 4)
		{
			step += 4-offset;
		}

		bmpFileHeader.bfSize = bmpImg->height*step + 54;
		bmpFileHeader.bfReserved1 = 0;
		bmpFileHeader.bfReserved2 = 0;
		bmpFileHeader.bfOffBits = 54;
		fwrite(&bmpFileHeader, sizeof(ClBitMapFileHeader), 1, pFile);

		bmpInfoHeader.biSize = 40;
		bmpInfoHeader.biWidth = bmpImg->width;
		bmpInfoHeader.biHeight = bmpImg->height;
		bmpInfoHeader.biPlanes = 1;
		bmpInfoHeader.biBitCount = 24;
		bmpInfoHeader.biCompression = 0;
		bmpInfoHeader.biSizeImage = bmpImg->height*step;
		bmpInfoHeader.biXPelsPerMeter = 0;
		bmpInfoHeader.biYPelsPerMeter = 0;
		bmpInfoHeader.biClrUsed = 0;
		bmpInfoHeader.biClrImportant = 0;
		fwrite(&bmpInfoHeader, sizeof(ClBitMapInfoHeader), 1, pFile);

		for (i=bmpImg->height-1; i>-1; i--)
		{
			for (j=0; j<bmpImg->width; j++)
			{
				pixVal = bmpImg->imageData[i*bmpImg->width*3+j*3];
				fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
				pixVal = bmpImg->imageData[i*bmpImg->width*3+j*3+1];
				fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
				pixVal = bmpImg->imageData[i*bmpImg->width*3+j*3+2];
				fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
			}
			if (offset!=0)
			{
				for (j=0; j<offset; j++)
				{
					pixVal = 0;
					fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
				}
			}
		}
	}
	else if (bmpImg->channels == 1)//8\u4f4d\uff0c\u5355\u901a\u9053\uff0c\u7070\u5ea6\u56fe
	{
		step = bmpImg->width;
		offset = step%4;
		if (offset != 4)
		{
			step += 4-offset;
		}

		bmpFileHeader.bfSize = 54 + 256*4 + bmpImg->width;
		bmpFileHeader.bfReserved1 = 0;
		bmpFileHeader.bfReserved2 = 0;
		bmpFileHeader.bfOffBits = 54 + 256*4;
		fwrite(&bmpFileHeader, sizeof(ClBitMapFileHeader), 1, pFile);

		bmpInfoHeader.biSize = 40;
		bmpInfoHeader.biWidth = bmpImg->width;
		bmpInfoHeader.biHeight = bmpImg->height;
		bmpInfoHeader.biPlanes = 1;
		bmpInfoHeader.biBitCount = 8;
		bmpInfoHeader.biCompression = 0;
		bmpInfoHeader.biSizeImage = bmpImg->height*step;
		bmpInfoHeader.biXPelsPerMeter = 0;
		bmpInfoHeader.biYPelsPerMeter = 0;
		bmpInfoHeader.biClrUsed = 256;
		bmpInfoHeader.biClrImportant = 256;
		fwrite(&bmpInfoHeader, sizeof(ClBitMapInfoHeader), 1, pFile);

		quad = (ClRgbQuad*)malloc(sizeof(ClRgbQuad)*256);
		for (i=0; i<256; i++)
		{
			quad[i].rgbBlue = i;
			quad[i].rgbGreen = i;
			quad[i].rgbRed = i;
			quad[i].rgbReserved = 0;
		}
		fwrite(quad, sizeof(ClRgbQuad), 256, pFile);
		free(quad);

		for (i=bmpImg->height-1; i>-1; i--)
		{
			for (j=0; j<bmpImg->width; j++)
			{
				pixVal = bmpImg->imageData[i*bmpImg->width+j];
				fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
			}
			if (offset!=0)
			{
				for (j=0; j<offset; j++)
				{
					pixVal = 0;
					fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
				}
			}
		}
	}
	fclose(pFile);

	return true;
}




int main(int argc, char * argv[])
{
	ClImage* img = clLoadImage("/home/ply/test.bmp");
	printf("width:%d",img->width);
	bool flag = clSaveImage("result.bmp", img);
	if(flag)
	{
		printf("save ok... \n");
	}
	

	
	return 0;
}