#include "image.h"

Image *createImage(int width, int height){
    Image *newImage = (Image*)malloc(sizeof(Image));
    if(newImage == NULL){
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    newImage->width  = width;
    newImage->height = height;
    newImage->data   = (PixelRGBA*)malloc(width * height * sizeof(PixelRGBA));

    if(newImage->data == NULL){
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    memset(newImage->data, 255, width * height * sizeof(PixelRGBA));
    return newImage;
}

Image *cropImage(const Image *img, int x, int y, int w, int h){
    Image *returnImage = createImage(w, h);
    int i;
    for(i = 0; i < h; i++){
        memcpy(&returnImage->data[i*w],  &img->data[x + y*img->width + i*img->width], w*sizeof(PixelRGBA));
    }
    return returnImage;
}

void destroyImage(Image *img)
{
    free(img->data);
    free(img);
}
