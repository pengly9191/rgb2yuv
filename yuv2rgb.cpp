#include <stdio.h> 
#include <stdlib.h> 
#include <iostream> 
#include <jpeglib.h>  
#define WIDTH 1280 
#define HEIGHT 720 

#include"util.h"
      
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

double YUV2RGB[3][3] = {1,0,1.4022,1,0.3456,0.7145,1,1.771,0};


  void savebmp(unsigned char * pdata, char * bmp_file, int width, int height )  
    {     
           int size = width*height*3*sizeof(char); 
         
           BMPFILEHEADER_T bfh;  
           bfh.bfType = (WORD)0x4D42;  
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
           bih.biHeight = height;
           bih.biPlanes = 1;
           bih.biBitCount = 24;  
           bih.biCompression = 0;
           bih.biSizeImage = size;  
           bih.biXPelsPerMeter = 0 ; 
           bih.biYPelsPerMeter = 0 ;  
           bih.biClrUsed = 0;
           bih.biClrImportant = 0;
           FILE * fp = fopen( bmp_file,"wb" );  
           if( !fp ) return;  
      
           fwrite( &bfh, 8, 1,  fp );
           fwrite(&bfh.bfReserved2, sizeof(bfh.bfReserved2), 1, fp);  
           fwrite(&bfh.bfOffBits, sizeof(bfh.bfOffBits), 1, fp);  
           fwrite( &bih, sizeof(BMPINFOHEADER_T),1,fp );  
           fwrite(pdata,size,1,fp);  
           fclose( fp );  
           printf("save rgb file success");
    }  



int convert_yuv_rgb(char*file,int width,int height){

	int i=0;
	int temp = 0;
	int x=0;
	int y = 0;
	int fReadSize = 0;
	int ImgSize = width*height;
	FILE *fp = NULL; 
	unsigned char* yuv = NULL; 
	unsigned char* rgb = NULL; 
	unsigned char* cTemp[6]; 
	char BmpFileName[256] ="/home/ply/yuv1.yuv"; 
	int FrameSize = ImgSize+ (ImgSize>>1);
	yuv = (unsigned char*)malloc(FrameSize);
	rgb = (unsigned char*)malloc(ImgSize*3);

	if((fp = fopen(BmpFileName,"rb"))==NULL)
		return 0;
	fReadSize = fread(yuv,1,FrameSize,fp);
	fclose(fp);
	if (fReadSize < FrameSize)
		return 0;

	cTemp[0] = yuv;
	cTemp[1]= yuv+ImgSize;	
	cTemp[2]= cTemp[1]+(ImgSize>>1);
	cTemp[3] = rgb;
	cTemp[4]= rgb+ImgSize;	
	cTemp[5]= cTemp[4]+ImgSize;

	for (y =0;y<height;y++){
		for(x =0;x<height;x++){
			//r 
			temp = cTemp[0][y*width+x]+(cTemp[2][(y/2)*(width/2)+x/2]-128) * YUV2RGB[0][2]; 
			cTemp[3][y*width+x] = temp<0 ? 0 : (temp>255 ? 255 : temp); 
			//g
			temp = cTemp[0][y*width+x] + (cTemp[1][(y/2)*(width/2)+x/2]-128) * YUV2RGB[1][1]
					+ (cTemp[2][(y/2)*(width/2)+x/2]-128) * YUV2RGB[1][2];
			cTemp[4][y*width+x] = temp<0 ? 0 : (temp>255 ? 255 : temp); 
			temp = cTemp[0][y*width+x] +(cTemp[1][(y/2)*(width/2)+x/2]-128) * YUV2RGB[2][1];
			cTemp[5][y*width+x] = temp<0 ? 0 : (temp>255 ? 255 : temp); 
					
		}
	}

	char rgbfile[256] = "/home/ply/rgbdata.txt";
	FILE file_rgb;
	file_rgb = fopen
	printf("convert rgb data success!\n");
	sprintf(BmpFileName,"test.bmp");
	savebmp( cTemp[3], BmpFileName, width, height );

	free(yuv);
	free(rgb);		
	return 1;
}


	

