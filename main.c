#include <math.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./Headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./Headers/stb_image_write.h"

/**
 * Create a new 1-dimensional array with the given size
 * @param[in] _size the size of the array
 * @param[out] _ empty 1-dimensional array filled with 0
 */
unsigned char *uc_arrayNew_1d(int _size)
{
    return (unsigned char *)calloc(_size, sizeof(unsigned char));
}

/**
 * Delete a quarter of the image
 * @param[in] image the input image
 * @param[in] width the width of the image
 * @param[in] height the height of the image
 * @param[in] channel the channel of the image
 */
unsigned char *background_subtraction(unsigned char * bg,unsigned char * fg,unsigned char *nbg, int width, int height, int channel)
{
    unsigned char *temp_array = uc_arrayNew_1d(width * height * channel);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
                for (int k = 0; k < channel; k++)
                    if(abs( bg[ i * width * channel + j * channel + 1] - fg[i * width * channel + j * channel + 1]< 55))
                    {
                    temp_array[i * width * channel + j * channel + k] = nbg[i * width * channel + j * channel + k];
                    }
                    else{
                    temp_array[i * width * channel + j * channel + k] = fg[i * width * channel + j * channel + k];
                    }
        }
    }
    return temp_array;
}


int main()
{
    // declare variables
    int width, height, channel;
    char path_img_1[] = "./images/background.jpg";
    char path_img_2[] = "./images/foreground.jpg";
    char path_img_3[] = "./images/new_background.jpg";
    char save_path[] = "./images/Result.jpg";

    // read image data
    unsigned char *bg = stbi_load(path_img_1, &width, &height, &channel, 0);
    unsigned char *fg = stbi_load(path_img_2, &width, &height, &channel, 0);
    unsigned char *nbg = stbi_load(path_img_3, &width, &height, &channel, 0);
    if (bg == NULL  || fg == NULL || nbg == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }
    printf("Width = %d\nHeight = %d\nChannel = %d\n", width, height, channel);


    // fill a quarter of the image with black pixels
    unsigned char *mimage = background_subtraction(bg,fg,nbg, width, height, channel);
    
    stbi_write_png(save_path, width, height, channel, mimage, width * channel);
    printf("New image saved to %s\n", save_path);
}