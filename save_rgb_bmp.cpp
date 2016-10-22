#include"util.h"

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
           int size = width*height*3*sizeof(unsigned char); 
         
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
           bih.biPlanes = 1;
           bih.biBitCount = 24;  
           bih.biCompression = 0;
           bih.biSizeImage = size;  
           bih.biXPelsPerMeter = 2835 ; 
           bih.biYPelsPerMeter = 2835 ;  
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
    }  
