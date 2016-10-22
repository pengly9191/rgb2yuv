
#include"util.h"

int crop_value = 0;
int main(){
	int w = 1280;
	 int h = 720;
	 int i=1;
    char file[255];
    FILE *fp;
    unsigned char *YUV = NULL;
    unsigned char *RGB = NULL;   
    long imgSize = w*h;
    RGB = (unsigned char*)malloc(imgSize*6);
    YUV = (unsigned char*)malloc(imgSize + (imgSize>>1));

    sprintf(file, "/home/ply/test.bmp");//读取文件
    if((fp = fopen(file, "rb")) == NULL)
    	return 0;

//     ReadBmp(RGB, fp);
//     Convert_rgb_yuv(RGB, YUV);	

	FILE *yuvfile;
	char path[64] = "/home/ply/yuv1.yuv";
	yuvfile = fopen(path, "rb");
	if (!yuvfile)
	{
		printf("cannot open yuv file \n");
		return NULL;
	}
	
	int ret = fread(YUV,sizeof(unsigned char),(imgSize + (imgSize>>1)), yuvfile);
	if (ret != w *h*3/2){
		printf("\n  read  yuv file error  %d \n",ret);
		return NULL;

	}
	printf("output ");
	for(int i = 0 ;i< h ;i++){
		int pos = w*i;	
		for (int j = 0;j < w;j++){
			YUV[pos+j] = 0;
//			printf("  :%d",YUV[pos+j]);
		}
//		printf("\n");
	}



 //    estar_interlace_crop_yuv420p(YUV,w,h,  crop_value);
//     convert_yuv_rgb(file,w,h) ;
    	 
     
	
}


