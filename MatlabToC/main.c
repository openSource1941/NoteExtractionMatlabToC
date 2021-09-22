// This is a protocol for instralling libsndfile library. Follow same steps as they are written here for systemc.
// This is a link with protocol https://howto.tech.blog/2016/11/27/installing-systemc-2-3-1/amp/?fbclid=IwAR10tGpNKLgj5Q7oyuFX8q9Ux3dOgvnlURqiQUNTS1uYxziKRIdd2UG99ZY
// this is a link for library http://www.mega-nerd.com/libsndfile/. Make sure to correctly follow rules for installation because it can
//be problem to remove it in case of repeated installation process. Use linux!!. After that you have to go to build options and include
// libsndfile.so from ../../../../../usr/local/libsndfile-1.0.28/lib/libsndfile.so probably. and in search directories in compiler you
// have to put path to include directory, in my case it is ../../../../../usr/local/libsndfile-1.0.28/include in your it should be similar
// and in linker you have to set path to lib directory, in my case it is ../../../../../usr/local/libsndfile-1.0.28/lib. should be similar in your case.
// If you have a problem with math library in linux you will have to setting-compiler-linker settings-other linker opions and simply write "-lm" there.
// it is only needed on newer versions of linux, after 20 or so. I am using ubuntu version of linux!
#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include<math.h>
#define PI 3.14159
#include <complex.h>
double     frequencies[150] = {16.35, 17.32 ,18.35 ,19.45 ,20.6 ,21.83 ,23.12 ,24.5, 25.96, 27.5 ,29.14 ,30.87 ,32.7, 34.65, 36.71 ,38.89 ,41.2, 43.65, 46.25, 49, 51.91, 55, 58.27, 61.74, 65.41, 69.3 ,73.42 ,77.78 ,82.41, 87.31 ,92.5, 98 ,103.83 ,110, 116.54 ,123.47 ,130.81, 138.59 ,146.83, 155.56, 164.81 ,174.61 ,185, 196, 207.65, 220 ,233.08, 246.94, 261.63, 277.18, 293.66, 311.13, 329.63 ,349.23, 369.99 ,392 ,415.3 ,440 ,466.16 ,493.88, 523.25 ,554.37 ,587.33, 622.25, 659.25 ,698.46, 739.99, 783.99 ,830.61, 880, 932.33 ,987.77 ,1046.5 ,1108.73, 1174.66 ,1244.51 ,1318.51, 1396.91 ,1479.98 ,1567.98, 1661.22, 1760, 1864.66, 1975.53 ,2093, 2217.46 ,2349.32, 2489.02, 2637.02 ,2793.83 ,2959.96, 3135.96 ,3322.44 ,3520, 3729.31 ,3951.07, 4186.01, 4434.92, 4698.63, 4978.03, 5274.04, 5587.65, 5919.91, 6271.93, 6644.88, 7040, 7458.62, 7902.13};

    int m=20;
    int countForMedian=5000;
    double coefficient=0.3;
int downsampledCount;
    char writtingFile[7]="WF.wav";
        char writtingFileNote[10]="WFNote.wav";
        char writtingRealFileNote[20]="realNote.wav";
        double fundamentals[100];
        double fundamentals2[100];
SNDFILE * sf;
SNDFILE *sfWrite;
SNDFILE *sfWriteNote;
SNDFILE *sfWriteRealNote;
SF_INFO info;
SF_INFO infoWrite;
SF_INFO infoWriteNote;

int num_of_channels;
int num, file_cnt, num_items;
double *buf, *bufs, *bufNote,*first_channel_real_note,*buf_real_note,*second_channel_real_note,*first_channel,*channelForMedian,*first_channel_note ,*second_channel_note,*second_channel,*first_channel_downsampled,*second_channel_downsampled,*first_channel_low_filter,*second_channel_low_filter;
int items_in_channels;

int frames, samplerate, channels;
int remainder_;
int temp;
int number_of_frames;
FILE *out, *out1,*out3,*out4,*out5,*out6,*out7;

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
        infoWriteNote=infoWrite;
    infoWriteNote.samplerate=infoWrite.samplerate/2;
    sfWrite=sf_open(writtingFile,SFM_WRITE,&infoWrite);

        sfWriteNote=sf_open(writtingFileNote,SFM_WRITE,&infoWrite);
        sfWriteRealNote=sf_open(writtingRealFileNote,SFM_WRITE,&infoWriteNote);

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
// allocating memory for blocks
    first_channel = (double*) malloc((items_in_channels) *sizeof(double));
    second_channel = (double*) malloc((items_in_channels) *sizeof(double));
     first_channel_low_filter = (double*) malloc((items_in_channels) *sizeof(double));
    second_channel_low_filter = (double*) malloc((items_in_channels) *sizeof(double));
      first_channel_downsampled = (double*) malloc((downsampledCount)*sizeof(double));
    first_channel_note = (double*) calloc((downsampledCount),sizeof(double));
        second_channel_note = (double*) calloc((downsampledCount),sizeof(double));
    first_channel_real_note=(double*) calloc((downsampledCount),sizeof(double));
    second_channel_real_note = (double*) calloc((downsampledCount),sizeof(double));
    buf_real_note =(double*) calloc((downsampledCount*2),sizeof(double));
    channelForMedian = (double*) calloc((countForMedian),sizeof(double));
    second_channel_downsampled = (double*) malloc((downsampledCount)*sizeof(double));
    num = sf_read_double(sf, buf, num_items);
    printf("Read %d items\n", num);
    out = fopen("first_channel.out", "w");
    out1 = fopen("second_channel.out", "w");
    out3 = fopen("first_channel_downsampled.out", "w");
    out4 = fopen("second_channel_downsampled.out", "w");
        out5 = fopen("wholeSong.out", "w");
        out6 = fopen("channelNOte.out", "w");
    out7=fopen("wholeSong.out", "w");


    // writting whole song to a file
    for(int i=0;i<num;i++)
    {
    fprintf(out7, "%lf ", buf[i]);
        fprintf(out7, "\n");
    }

    // separating first and second channel
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
// this is not same as matlab code, first two lines is first order low pass filter, if other two lines are not commented than filter is not applied
    for(int i=1;i<items_in_channels;i++)
    {
    first_channel[i]=first_channel[i-1] + coefficient*(first_channel_low_filter[i]-first_channel[i-1]);
        second_channel[i]=second_channel[i-1] + coefficient*(second_channel_low_filter[i]-second_channel[i-1]);
        first_channel[i]=first_channel_low_filter[i];
        second_channel[i]=second_channel_low_filter[i];

    }


    // This is how downsampling is done. average of every m number of samples makes one sample. That means we have sampleCount/m samples now.
     // this is not a way it is made in Matlab code, because there we don't have two channels, but everything is averaged in one channel.

     for(int i=0;i<downsampledCount;i++)
      {
      first_channel_downsampled[i] = mean(first_channel,i*m,m);
      second_channel_downsampled[i]= mean(second_channel,i*m,m);
      }


      int count=1;
      double thresh;
      // separating some parts of a code that meets some conditions
      // median is calculated based on 5000 samples and it is number that has middle index when sorted(middle number)
      while(count<downsampledCount)
      {
      for(int j=0;j<5000;j++)
      {
      channelForMedian[j]=first_channel_downsampled[count+j];
      }

        thresh = 5*median(channelForMedian);

        // if certaing conditions were met then we take 500 samples and put it in first_channel note. It means we will have
        // 500 samples with some values, than 1400 sample resting, then againt 500 samples in case that always conditions are met.
        /// I have changed 1400 to 140, than we get a lot better and precise sound. Try with 1400 and you will see.

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
        count+=1000;
        }

count++;

      }

 count=1;
      // separating some parts of a code that meets some conditions
      // median is calculated based on 5000 samples and it is number that has middle index when sorted(middle number). Same as for a first channel
 while(count<downsampledCount)
      {
      for(int j=0;j<5000;j++)
      {
      channelForMedian[j]=second_channel_downsampled[count+j];
      }
        thresh = 5*median(channelForMedian);
         // if certaing conditions were met then we take 500 samples and put it in first_channel note. It means we will have
        // 500 samples with some values, than 1400 sample resting, then againt 500 samples in case that always conditions are met.
        // same as for first channel
        /// I have changed 1400 to 140, than we get a lot better and precise sound. Try with 1400 and you will see.

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
        count+=1000;
        }

count++;

      }

// putting those two channels in one. Every even index of bufs will be populated with first_channel_downsampled, and every odd index will
// be populated with second_channel_downsampled.
      for(int i=0;i<downsampledCount;i++)
      {
      bufs[i*2]=first_channel_downsampled[i];
      bufs[i*2+1]=second_channel_downsampled[i];
      }
// putting those two channels in one. Every even index of bufs will be populated with first_channel_downsampled, and every odd index will
// be populated with second_channel_downsampled. Same as up there. Now we will have complete sound. Because we have 500 samples with some
// numbers and then 1400 zeroes we expect that sound will have some sound, than rest a little, than other part again and so on.
// This is not written professionaly, but only as help for someone that will read maybe. It called first_channel_note and second_channel_note
// because we will use those parts that are not populated with zero to calculate note of that part using furier transform for calculating frequency
// on that 500 or so frames.

 for(int i=0;i<downsampledCount;i++)
      {
      bufNote[i*2]=first_channel_note[i];
      bufNote[i*2+1]=second_channel_note[i];
      }
// in next two lines we write downsampled sound, and sound with notes into WAV files. We have to use a function and not fprintf!!!!!
//This function is defines in libsndfile library.
         int numWrite= sf_write_double(sfWrite,bufs,downsampledCount*2);
         numWrite= sf_write_double(sfWriteNote,bufNote,downsampledCount*2);

         // Here i am writting note channels in files just for purpose of checking, nothing more. We don't need that!

    for(int i=0;i<downsampledCount;i++)
    {
      fprintf(out3, "%lf ", first_channel_note[i]);
        fprintf(out3, "\n");
        fprintf(out4, "%lf ", second_channel_note[i]);
        fprintf(out4, "\n");
    }
    // files have to be closed, or sometimes it will not work properly.
     sf_close(sf);
    sf_close(sfWrite);

    int i=0;
    int i_note=0;

    while(i<downsampledCount)
    {
    int j=0;
    int end_note=0;

    // We put blocks of 500 frames and than 140 zeroes if conditions were met. Now we go to a first block and find fundamental frequency of that block
    // after that we move to a second block and so on.
    while(((first_channel_note[i]!=0) || (end_note>0)) && (i<downsampledCount))
    {
        first_channel_real_note[j]= first_channel_note[i];
        i++;
        j++;
        // if 20 notes in a row are zeroes, that means that we finished with that block!
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
        // if we have
        if(j>20)
        {
        // first half of a note_padded will be one block of around 500 frames, and second 500 will be zeroes. Maybe 500 will be different number later.

        double *note_padded=(double*) calloc((j*2),sizeof(double));
        double *Note=(double *) calloc((j*2),sizeof(double ));

            for(int k=0;k<j*2;k++)
            {
            note_padded[k]=first_channel_real_note[k];
            }
            int index=calculateDFT(j*2,note_padded,Note);
            int Ns = j*2;

            if(index/2>20)
            {
            i_note=i_note+1;
                        // taken from matlab code

        int index1 = round(17.31232*log(index*2) - 47.37620);
            fundamentals[i_note]=frequencies[index1];
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
/// Everything is just same as for first block
   i=0;
     i_note=0;

    while(i<downsampledCount)
    {
    int j=0;
    int end_note=0;

    // We put blocks of 500 frames and than 140 zeroes if conditions were met. Now we go to a first block and find fundamental frequency of that block
    // after that we move to a second block and so on.
    while(((second_channel_note[i]!=0) || (end_note>0)) && (i<downsampledCount))
    {
        second_channel_real_note[j]= second_channel_note[i];
        i++;
        j++;
        // if 20 notes in a row are zeroes, that means that we finished with that block!
        if(second_channel_note[i]!=0)
        {
        end_note=20;
        }
        else
        {
        end_note--;
        }

        if(end_note==0)
        {
        // if we have
        if(j>20)
        {
        // first half of a note_padded will be one block of around 500 frames, and second 500 will be zeroes. Maybe 500 will be different number later.

        double *note_padded=(double*) calloc((j*2),sizeof(double));
        double *Note=(double *) calloc((j*2),sizeof(double ));

            for(int k=0;k<j*2;k++)
            {
            note_padded[k]=second_channel_real_note[k];
            }
            int index=calculateDFT(j*2,note_padded,Note);
            int Ns = j*2;

            if(index/2>20)
            {
            i_note=i_note+1;
            // taken from matlab code
               int index1 = round(17.31232*log(index*2) - 47.37620);
            fundamentals2[i_note]=frequencies[index1];
            }
            i=i+50;
        }

            for(int k=0;k<j*2;j++)
            {
        second_channel_real_note[k]=0;
        }
        }

    }
    i=i+1;
    }



for(int i=0;i<10;i++)
{
printf("fundamental frequency is:  %lf\n",fundamentals[i]);
printf("fundamental2 frequency is:  %lf\n",fundamentals2[i]);

}
int newSampleRate=info.samplerate/m/2;
int numberOfFundamentals=0;
for(int i=0;i<100;i++)
{
if(fundamentals[i]!=0)
{
numberOfFundamentals++;
}
}

for(int i=0;i<numberOfFundamentals;i++)
{
for(int j=0;j<newSampleRate*2;j+=2)
{
buf_real_note[i*newSampleRate+j]=sin(2*PI*fundamentals[i]*2*j/newSampleRate)*1;
buf_real_note[i*newSampleRate+j+1]=sin(2*PI*fundamentals2[i]*2*j/newSampleRate)*1;
}
}

// writting notes in a wav file realNote.wav
         numWrite= sf_write_double(sfWriteRealNote,buf_real_note,numberOfFundamentals*newSampleRate*2);


// closing wav file.
    sf_close(sfWriteRealNote);


}
int main(int argc, char **argv)
{
load(argv);
    print_info();
    printf("Hello world!\n");
    return 0;
}
