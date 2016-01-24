#include "follow_line.h"


typedef struct 
{
	int Front_Data_Min;
        int Front_Data_Max;
        int Behind_Data_Min;
        int Behind_Data_Max;
}light_data;

light_data Now;
light_data Last;
u8 data_input[48];
  int T ;//阈值 
int flag;
int min_number_last;
int max_number_last;
int min_number_now;
int max_number_now;
int min_number;
int max_number;
int count_last;
int count_now;

/*************************************************************************
         otsuThreshold(u8* data_in,u8 *dataout1,u8 *dataout2)
描述：数据的动态阈值计算
输入参数：u8* data_in
输出参数：u8 *dataout1,u8 *dataout2
*************************************************************************/

void otsuThreshold(u8* data_in,u8 *dataout1,u8 *dataout2)
{
  
         T=0;

	int height = 48;
	int width = 1;
	double gSum0;//第一类灰度总值  
	double gSum1;//第二类灰度总值  
	double N0 = 0;//前景像素数  
	double N1 = 0;//背景像素数  
	double u0 = 0;//前景像素平均灰度  
	double u1 = 0;//背景像素平均灰度  
	double w0 = 0;//前景像素点数占整幅图像的比例为ω0  
	double w1 = 0;//背景像素点数占整幅图像的比例为ω1  
	double u = 0;//总平均灰度  
	double tempg = -1;//临时类间方差   可以改
	double g = 100;//类间方差  
	double Histogram[256] = { 0 };// = new double[256];//灰度直方图  
	double N = width*height;//总像素数  
	//int max_number,min_number;
        
       
	for (int row = 0; row<height; row++)
	{//计算直方图  
		//uchar* grayimgptr = grayimg.ptr<uchar>(row);

	
          double temp = data_in[row];
			temp = temp<0 ? 0 : temp;
			temp = temp>255 ? 255 : temp;
			Histogram[(int)temp]++;
		
	}
	//计算阈值  
	for (int i = 0; i<256; i++)
	{
		gSum0 = 0;
		gSum1 = 0;
		N0 += Histogram[i];//前景像素数
		N1 = N - N0;//背景像素数  
		if (0 == N1)break;//当出现前景无像素点时，跳出循环  
		w0 = N0 / N;//前景像素点数占整幅图像的比例为ω0 
		w1 = 1 - w0;//前景像素点数占整幅图像的比例为ω1
		for (int j = 0; j <= i; j++)
		{
			gSum0 += j*Histogram[j];
		}//前景灰度总和
		u0 = gSum0 / N0;//前景灰度均值
		for (int k = i + 1; k<256; k++)
		{
			gSum1 += k*Histogram[k];
		}//背景灰度总和
		u1 = gSum1 / N1;//背景灰度均值
		//u = w0*u0 + w1*u1;  //总平均灰度
		g = w0*w1*(u0 - u1)*(u0 - u1);
		if (tempg<g)
		{
			tempg = g;
			T = i;
		}
	}
	
        for(int i=0;i<47;i++)
        {
          if(data_in[i]<T)
          {
            data_input[i]=0;
  
          }
          else 
          {
            data_input[i]=1; 
          }
        }
        
         flag=0;
         count_last=0;
         count_now=0;
        for(int j=0;j<48;j++)
          {
           
            if((flag==0)&&((data_input[j+1]-data_input[j])==-1))
            {
              min_number_now=j+1;
              flag=1;
            }
             else;
             if((flag==1)&&((data_input[j+1]-data_input[j])==0))
              {
                count_now++;
              }
           else;
           if((flag==1)&&((data_input[j+1]-data_input[j])==1))
            {
              max_number_now = j;
              flag = 2;
            }
            else ;
            if((j < 48)&&(flag == 2))
            {
              flag = 0;
              if(count_now > count_last)
              {
              min_number_last = min_number_now;
              max_number_last = max_number_now;
              count_last = count_now;
              count_now=0;
              }
              else ;
            }
            min_number = min_number_last;
            max_number = max_number_last;
          }
          
        
          *dataout1 = min_number;
          *dataout2 = max_number;
          
        


}


/*************************************************************************
        dis_angle(float* distance,float* angle )
描述：角度与偏移量的读取函数
输入参数：
输出参数：float* distance,float* angle
*************************************************************************/
void dis_angle(float* distance,float* angle ) //通过前排巡线板标记点最大、小值与后排标记点比较，得出角度和偏移量
{
    u8 a,b,c,d;
  otsuThreshold(buffer_blue_front,&a,&b);      // 前排巡线板最大值，最小值
  Now.Front_Data_Min=a;
  Now.Front_Data_Max=b;
//  otsuThreshold(buffer_blue_behind,&c,&d);     // 后排巡线板最大值，最小值
//  Now.Behind_Data_Min=c;
//  Now.Behind_Data_Max=d;
//  if(abs(Now.Front_Data_Min-Last.Front_Data_Min)<5)   //比较上一次与现在值
//  {                                                                       //计算角度
//    *angle=atan((Now.Front_Data_Min+Now.Front_Data_Max-Now.Behind_Data_Min-Now.Behind_Data_Max)*L/2*L_distance);
//                                                                          //计算偏移量
//    *distance=(Now.Front_Data_Min+Now.Front_Data_Max-Now.Behind_Data_Min-Now.Behind_Data_Max)/2-middle_number;
//  }
//  else 
//  Last.Front_Data_Min=Now.Front_Data_Min;
//  Last.Front_Data_Max=Now.Front_Data_Max;
//  Last.Behind_Data_Min=Now.Behind_Data_Min;
//  Last.Behind_Data_Max=Now.Behind_Data_Max;
}