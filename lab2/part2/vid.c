/****************** vid.c file *******************/
int volatile *display_buffer; // display buffer
// extern UART *up;

#define LCD_CONTROLLER_BASE_ADDR 0x10120000
#define VGA_WIDTH 640
#define VGA_HEIGHT 480

int fbuf_init()
{
    int i;

    /********* for VGA 640x480 ************************/
    *(volatile unsigned int *)(0x1000001c) = 0x2C77;     // LCDCLK SYS_OSCCLK
    *(volatile unsigned int *)(0x10120000) = 0x3F1F3F9C; // time0
    *(volatile unsigned int *)(0x10120004) = 0x090B61DF; // time1
    *(volatile unsigned int *)(0x10120008) = 0x067F1800; // time2
    *(volatile unsigned int *)(0x10120010) = (0x400000); // panelBaseAddress
    *(volatile unsigned int *)(0x10120018) = 0x82B;      // control register

    // |code|data|bss|wsu.o|stack| may > 3MB; display_buffer must be higher
    display_buffer = (int *)(0x400000); // display_buffer[ ] at 4MB; for VGA 640x480
    // clear display_buffer[]
    for (i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
        display_buffer[i] = 0x00000000; // clean screen; all pixels are BLACK
}

int show_bmp(char *bit_map_ptr, int startRow, int startCol)
{
    int scalar = 2, size_of_pixel = 3;
    int image_height, image_width, pixel, row_size, i, j;
    unsigned char pixel_red, pixel_green, pixel_blue;
    char *bit_map_ptr_iterator;

    int *q = (int *)(bit_map_ptr + 14); // skip over 14 bytes file header
    q++;                                // skip 4 bytes in image header
    image_width = *q;                   // width in pixels
    image_height = *(q + 1);            // height in pixels

    uprintf(up, "\nBMP image height=%d width=%d\n", image_height, image_width);

    bit_map_ptr += 54; // bit_map_ptr point at pixels now

    // the picture is up-side DOWN
    // image_width = 1151
    //                  3456 --> this is getting truncated to a mult of 4, why?
    row_size = 4 * ((3 * image_width + 3) / 4);   // row size is a multiple of 4 bytes
    unsigned int row_starting_addr = (unsigned int)bit_map_ptr;
    bit_map_ptr += (image_height - 1) * row_size; // I thnk this line is flipping it


    int scalar_height = image_height / VGA_HEIGHT + 1;
    int scalar_width = image_width / VGA_WIDTH + 1;
    scalar = (scalar_height > scalar_width ) ? scalar_height : scalar_width;

    // KC's code doesn't make sense bc it's not addressing all the values on vga display.

    for (i = 0; i < VGA_HEIGHT; i++) {
        bit_map_ptr_iterator = bit_map_ptr;

        for (j = 0; j < VGA_WIDTH; j++ ) {
            if (j < image_width / scalar && i < image_height / scalar)
            {
                pixel_blue = *bit_map_ptr_iterator;
                pixel_green = *(bit_map_ptr_iterator + 1);
                pixel_red = *(bit_map_ptr_iterator + 2);
                pixel = (pixel_blue << 16) + (pixel_green << 8) + pixel_red;
                display_buffer[i * VGA_WIDTH + j] = pixel;
                bit_map_ptr_iterator += (size_of_pixel * scalar); // back pp by 3 bytes
            } else {
                pixel = 0x0FFF;
                display_buffer[i * VGA_WIDTH + j] = pixel;
            }

        }
        bit_map_ptr -= (row_size * scalar);
    }
    
    // for (i = startRow; i < (image_height / scalar) + startRow; i++)
    // {
    //     bit_map_ptr_iterator = bit_map_ptr;
    //     unsigned int column_starting_addr = (unsigned int)bit_map_ptr_iterator;
    //     // uprintf(up, "\nStarting address: %x", bit_map_ptr_iterator);

    //     for (j = startCol; j < startCol + image_width ; j++)
    //     {
    //         if (((unsigned int)bit_map_ptr_iterator - column_starting_addr <= size_of_pixel * image_width) )
    //             // && (unsigned int)bit_map_ptr_iterator > row_starting_addr)
    //         {
    //             pixel_blue = *bit_map_ptr_iterator;
    //             pixel_green = *(bit_map_ptr_iterator + 1);
    //             pixel_red = *(bit_map_ptr_iterator + 2);
    //             pixel = (pixel_blue << 16) + (pixel_green << 8) + pixel_red;
    //             display_buffer[i * VGA_WIDTH + j] = pixel;
    //             bit_map_ptr_iterator += (size_of_pixel * scalar); // back pp by 3 bytes
    //         } else { // if there is no more data, display blackness
    //             pixel = 0x0FFF;
    //             display_buffer[i * VGA_WIDTH + j] = pixel;
    //         }
    //     }
    //     bit_map_ptr -= (row_size * scalar);
    //     // bit_map_ptr += row_size;
    // }
    // REQUIRED: use YOUR uprintf() of Part 1 to print image_height,image_width to UART0
    //
}
