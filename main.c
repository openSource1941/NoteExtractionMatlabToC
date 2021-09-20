#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include<math.h>
#define PI 3.14159

#include <complex.h>
const int BLOCK_SIZE = 8192;
    int m=20;
    int countForMedian=5000;
    double coefficient=0.3;
int downsampledCount;
    char writtingFile[7]="WF.wav";
        char writtingFileNote[10]="WFNote.wav";
        char writtingRealFileNote[20]="realNote.wav";
        double fundamentals[100];
SNDFILE * sf;
SNDFILE *sfWrite;
SNDFILE *sfWriteNote;
SNDFILE *sfWriteRealNote;
SF_INFO info;
SF_INFO infoWrite;
SF_INFO infoWrite1;

int num_of_channels;
int num, file_cnt, num_items;
double *buf, *bufs, *bufNote,*first_channel_real_note,*buf_real_note,*second_channel_real_note,*first_channel,*channelForMedian,*first_channel_note ,*second_channel_note,*second_channel,*first_channel_downsampled,*second_channel_downsampled,*first_channel_low_filter,*second_channel_low_filter;
int items_in_channels;

int frames, samplerate, channels;
int remainder_;
int temp;
int number_of_frames;
FILE *out, *out1,*out3,*out4,*out5,*out6;

int calculateDFT(int len,double *a,double *Note)
{

    int i, k, n, N = len;
    double Xr[len];
    double Xi[len];
    double complex X[N];
    int max=0;
    for (k = 0; k < N; k++) {
        Xr[k] = 0;
        Xi[k] = 0;
        for (n = 0; n < len; n++) {
            Xr[k] = (Xr[k] + a[n] * cos(2 * 3.141592 * k * n / N));
           Xi[k] = (Xi[k] + a[n] * sin(2 * 3.141592 * k * n / N));
        }


               Note[k] = sqrt(Xr[k]*Xr[k]+Xi[k]*Xi[k]*I);
               if(fabs(Note[k])>max)
               {
               max=k;
               }
    }
    return max;
}
void swap(double *p,double *q) {
   double t;

   t=*p;
   *p=*q;
   *q=t;
}

void sort(double a[],double n) {
   int i,j;
   double temp;

   for(i = 0;i < n-1;i++) {
      for(j = 0;j < n-i-1;j++) {
         if(fabs(a[j]) > fabs(a[j+1]))
            swap(&a[j],&a[j+1]);
      }
   }
}

double median(double *channel)
{
sort(channel,countForMedian);
int n=countForMedian;
return channel[(n+1) / 2 - 1];
}

double mean(double *array,int n,int m)
{
double sum=0;
for(int i=n;i<m+n;i++)
{
sum+=array[i];
}
return sum/m;
}

void load(char **argv)
{
    /*Open the WAV file. */
    info.format = 0;
    char *audiofile;
    audiofile = argv[1];
    sf = sf_open(audiofile, SFM_READ, &info);
    if (sf == NULL)
    {
        printf("Failed to open the file.\n");
        exit(-1);
    }

    infoWrite=info;
    infoWrite.samplerate=infoWrite.samplerate/m;
        infoWrite1=infoWrite;
    infoWrite1.samplerate=infoWrite.samplerate/2;
    sfWrite=sf_open(writtingFile,SFM_WRITE,&infoWrite);

        sfWriteNote=sf_open(writtingFileNote,SFM_WRITE,&infoWrite);
        sfWriteRealNote=sf_open(writtingRealFileNote,SFM_WRITE,&infoWrite1);

  if (sfWrite == NULL)
    {
        printf("Failed to open the file.\n");
        exit(-1);
    }



}
void print_info()
{
   	// Print some of the info, and figure out how much data to read
    frames = info.frames;
    samplerate = info.samplerate;
    channels = info.channels;
    printf("Number of frames = %d\n", frames);
    printf("Samplerate = %d\n", samplerate);
    printf("Number of channels = %d\n", channels);
    num_items = frames * channels;
    items_in_channels = num_items / 2;
    printf("Number of items = %d\n", num_items);

   	// Allocate space for the data to be read, then read it
   	 downsampledCount=items_in_channels/m;
    buf = (double*) malloc(num_items* sizeof(double));
    bufs = (double*) malloc((downsampledCount*2)*sizeof(double));
    bufNote = (double*) malloc((downsampledCount*2)*sizeof(double));

    first_channel = (double*) malloc((items_in_channels) *sizeof(double));
    second_channel = (double*) malloc((items_in_channels) *sizeof(double));
     first_channel_low_filter = (double*) malloc((items_in_channels) *sizeof(double));
    second_channel_low_filter = (double*) malloc((items_in_channels) *sizeof(double));
      first_channel_downsampled = (double*) malloc((downsampledCount)*sizeof(double));
    first_channel_note = (double*) calloc((downsampledCount),sizeof(double));
        second_channel_note = (double*) calloc((downsampledCount),sizeof(double));
    first_channel_real_note=(double*) calloc((downsampledCount),sizeof(double));
    second_channel_real_note = (double*) calloc((downsampledCount),sizeof(double));
    buf_real_note =(double*) calloc((downsampledCount),sizeof(double));
    channelForMedian = (double*) calloc((countForMedian),sizeof(double));
    second_channel_downsampled = (double*) malloc((downsampledCount)*sizeof(double));
    num = sf_read_double(sf, buf, num_items);
    printf("Read %d items\n", num);
    remainder_ = items_in_channels % BLOCK_SIZE;
    printf("Remainder = %d", remainder_);
    number_of_frames = (items_in_channels - remainder_) / BLOCK_SIZE;
    out = fopen("first_channel.out", "w");
    out1 = fopen("second_channel.out", "w");
    out3 = fopen("first_channel_downsampled.out", "w");
    out4 = fopen("second_channel_downsampled.out", "w");

        out5 = fopen("wholeSong.out", "w");
        out6 = fopen("channelNOte.out", "w");

 for (int i = 0; i < num + 2; i += 2)
    {
        int k = i / 2;
        first_channel_low_filter[k] = buf[i];
    }
    for (int i = 1; i < num + 3; i += 2)
    {
        int d = (i - 1) / 2;
        second_channel_low_filter[d] = buf[i];

    }

    for(int i=1;i<items_in_channels;i++)
    {
    first_channel[i]=first_channel[i-1] + coefficient*(first_channel_low_filter[i]-first_channel[i-1]);
        second_channel[i]=second_channel[i-1] + coefficient*(second_channel_low_filter[i]-second_channel[i-1]);
        first_channel[i]=first_channel_low_filter[i];
        second_channel[i]=second_channel_low_filter[i];

    }




     for(int i=0;i<downsampledCount;i++)
      {
      first_channel_downsampled[i] = mean(first_channel,i*m,m);
      second_channel_downsampled[i]= mean(second_channel,i*m,m);
      }


      int count=1;
      double thresh;
      while(count<downsampledCount)
      {
      for(int j=0;j<5000;j++)
      {
      channelForMedian[j]=first_channel_downsampled[count+j];
      }
        thresh = 5*median(channelForMedian);
        if(fabs(first_channel_downsampled[count])>thresh)
        {
        for(int k=0;k<500;k++)
        {
        if(count+k<downsampledCount)
        {
        first_channel_note[count]=first_channel_downsampled[count];
        count++;
        }
        }
        count+=1400;
        }

count++;

      }

 count=1;
 while(count<downsampledCount)
      {
      for(int j=0;j<5000;j++)
      {
      channelForMedian[j]=second_channel_downsampled[count+j];
      }
        thresh = 5*median(channelForMedian);
        if(fabs(second_channel_downsampled[count])>thresh)
        {
        for(int k=0;k<500;k++)
        {
        if(count+k<downsampledCount)
        {
        second_channel_note[count]=second_channel_downsampled[count];
        count++;
        }
        }
        count+=1400;
        }

count++;

      }








      for(int i=0;i<downsampledCount;i++)
      {
      bufs[i*2]=first_channel_downsampled[i];
      bufs[i*2+1]=second_channel_downsampled[i];
      }

 for(int i=0;i<downsampledCount;i++)
      {
      bufNote[i*2]=first_channel_note[i];
      bufNote[i*2+1]=second_channel_note[i];
      }







         int numWrite= sf_write_double(sfWrite,bufs,downsampledCount*2);
         numWrite= sf_write_double(sfWriteNote,bufNote,downsampledCount*2);

    for(int i=1;i<items_in_channels;i++)
    {
     fprintf(out, "%lf ", first_channel[i]);
        fprintf(out, "\n");
        fprintf(out1, "%lf ", second_channel[i]);
        fprintf(out1, "\n");
        fprintf(out5, "%lf ", second_channel[2*i]);
        fprintf(out5, "\n");
        fprintf(out5, "%lf ", second_channel[2*i+1]);
        fprintf(out5, "\n");
    }
    for(int i=0;i<downsampledCount;i++)
    {
      fprintf(out3, "%lf ", first_channel_note[i]);
        fprintf(out3, "\n");
        fprintf(out4, "%lf ", second_channel_downsampled[i]);
        fprintf(out4, "\n");
    }
     sf_close(sf);
    sf_close(sfWrite);


    int i=0;
    int i_note=0;

    while(i<downsampledCount)
    {
    int j=0;
    int end_note=0;
    while(((first_channel_note[i]!=0) || (end_note>0)) && (i<downsampledCount))
    {
        first_channel_real_note[j]= first_channel_note[i];
        i++;
        j++;
        if(first_channel_note[i]!=0)
        {
        end_note=20;
        }
        else
        {
        end_note--;
        }

        if(end_note==0)
        {
        if(j>20)
        {
        double *note_padded=(double*) calloc((j*2),sizeof(double));
        double *Note=(double *) calloc((j*2),sizeof(double ));

            for(int k=0;k<j*2;k++)
            {
            note_padded[k]=first_channel_real_note[k];
            }
            int index=calculateDFT(j*2,note_padded,Note);
            int Ns = j*2;

            if(index/2>10)
            {
            i_note=i_note+1;
            fundamentals[i_note]=index*2;
            }
            i=i+50;
        }

            for(int k=0;k<j*2;j++)
            {
        first_channel_real_note[k]=0;
        }
        }





    }



    i=i+1;
    }


for(int i=0;i<10;i++)
{
printf("fundamental frequency is:  %lf\n",fundamentals[i]);

}
int newSampleRate=info.samplerate/m/2;
for(int i=0;i<8;i++)
{
for(int j=0;j<newSampleRate*2;j+=2)
{
buf_real_note[i*newSampleRate+j]=sin(2*PI*fundamentals[i]*2*j/newSampleRate)*1;
buf_real_note[i*newSampleRate+j+1]=sin(2*PI*fundamentals[i]*j/newSampleRate)*1;
fprintf(out6, "%lf ", buf_real_note[i*newSampleRate+j]);
        fprintf(out6, "\n");
}
}

         numWrite= sf_write_double(sfWriteRealNote,buf_real_note,downsampledCount*2);



    sf_close(sfWriteRealNote);


}
int main(int argc, char **argv)
{
load(argv);
    print_info();
    printf("Hello world!\n");
    return 0;
}
