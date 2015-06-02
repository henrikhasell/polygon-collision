#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h> /* Used for memory allocation. */
#include <stdio.h>  /* Used for console output.    */

#include <memory.h> /* Used for memcpy and memset. */

/************************************************************************/
/* This structure is used to represent one pixel of an Image.           */
/* Pixel data is stored as a 32 bit RGBA (8 bits per colour component). */
/************************************************************************/
typedef struct PixelRGBA{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
}PixelRGBA;
/*****************************************************************************************/
/* This structure is used to store Image data in a way that OpenGL can easily interpret. */
/* The structure contains the Image's width, height and raw pixel data. When allocated   */
/* with createImage() the Image data buffer is guaranteed to be able to store all of     */
/* an Image's data.                                                                      */
/*****************************************************************************************/
typedef struct Image{
    int width;
    int height;
    PixelRGBA *data;
}Image;

/**************************************************************************************/
/* This function allocates memory for a new blank Image of size "width" and "height". */
/* Any Image allocated with this function should be freed with destroyImage().        */
/**************************************************************************************/
Image *createImage(int width, int height);
/*************************************************************************/
/* This function is used to free any image allocated with createImage(). */
/*************************************************************************/
void destroyImage(Image *img);
/******************************************************************************/
/* This function creates() a new Image with the contents of the cropped *img. */
/* The user should not try to crop an out of bounds area, as this may cause   */
/* cause an access violation error. As the returned Image is dynamically      */
/* allocated, it must also be freed with createImage().                       */
/******************************************************************************/
Image *cropImage(const Image *img, int x, int y, int w, int h);

#endif /* IMAGE_H */
