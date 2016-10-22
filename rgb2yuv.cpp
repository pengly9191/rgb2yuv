#include "util.h"



#define MY(a,b,c) (( a*  0.2989  + b*  0.5866  + c*  0.1145))
#define MU(a,b,c) (( a*(-0.1688) + b*(-0.3312) + c*  0.5000 + 128))
#define MV(a,b,c) (( a*  0.5000  + b*(-0.4184) + c*(-0.0816) + 128))
//大小判断
#define DY(a,b,c) (MY(a,b,c) > 255 ? 255 : (MY(a,b,c) < 0 ? 0 : MY(a,b,c)))
#define DU(a,b,c) (MU(a,b,c) > 255 ? 255 : (MU(a,b,c) < 0 ? 0 : MU(a,b,c)))
#define DV(a,b,c) (MV(a,b,c) > 255 ? 255 : (MV(a,b,c) < 0 ? 0 : MV(a,b,c)))

#define WIDTH 1920
#define HEIGHT 1080




void ReadBmp(unsigned char *RGB,FILE *fp)
{
    int i,j;
    unsigned char temp;

    fseek(fp,54, SEEK_SET);

    fread(RGB+WIDTH*HEIGHT*3, 1, WIDTH*HEIGHT*3, fp);//读取
    for(i=HEIGHT-1,j=0; i>=0; i--,j++)//调整顺序
    {
        memcpy(RGB+j*WIDTH*3,RGB+WIDTH*HEIGHT*3+i*WIDTH*3,WIDTH*3);
    }
   
    //顺序调整
    for(i=0; (unsigned int)i < WIDTH*HEIGHT*3; i+=3)
    {
        temp = RGB[i];
        RGB[i] = RGB[i+2];
        RGB[i+2] = temp;
    }
}


void Convert_rgb_yuv(unsigned char *RGB, unsigned char *YUV)
{
    //变量声明
    unsigned int i,x,y,j;
    unsigned char *Y = NULL;
    unsigned char *U = NULL;
    unsigned char *V = NULL;
   
    Y = YUV;
    U = YUV + WIDTH*HEIGHT;
    V = U + ((WIDTH*HEIGHT)>>2);

    for(y=0; y < HEIGHT; y++)
        for(x=0; x < WIDTH; x++)
        {
            j = y*WIDTH + x;
            i = j*3;
            Y[j] = (unsigned char)(DY(RGB[i], RGB[i+1], RGB[i+2]));

            if(x%2 == 1 && y%2 == 1)
            {
                j = (WIDTH>>1) * (y>>1) + (x>>1);
                
                U[j] = (unsigned char)
                       ((DU(RGB[i  ], RGB[i+1], RGB[i+2]) +
                         DU(RGB[i-3], RGB[i-2], RGB[i-1]) +
                         DU(RGB[i  -WIDTH*3], RGB[i+1-WIDTH*3], RGB[i+2-WIDTH*3]) +
                         DU(RGB[i-3-WIDTH*3], RGB[i-2-WIDTH*3], RGB[i-1-WIDTH*3]))/4);

                V[j] = (unsigned char)
                       ((DV(RGB[i  ], RGB[i+1], RGB[i+2]) +
                         DV(RGB[i-3], RGB[i-2], RGB[i-1]) +
                         DV(RGB[i  -WIDTH*3], RGB[i+1-WIDTH*3], RGB[i+2-WIDTH*3]) +
                         DV(RGB[i-3-WIDTH*3], RGB[i-2-WIDTH*3], RGB[i-1-WIDTH*3]))/4);
            }
	
        }
}
 
void estar_interlace_crop_yuv420p(unsigned char *pdes, int width,int height, int crop_value)
{
	int i;	
	for(i=height-1; i>=(height-crop_value); i--) //y
	{
		memset(pdes+i*width, 0, width);		
	}
	pdes +=width*height;	
				
	for(i=height/4-1; i>=(height-crop_value)/4; i--) //u
	{		
		memset(pdes+i*width, 128, width);		
	}
	pdes += width*height>>2;	
	for(i=height/4-1; i>=(height-crop_value)/4; i--) //v
	{
		memset(pdes+i*width, 128, width);		
	}

}


