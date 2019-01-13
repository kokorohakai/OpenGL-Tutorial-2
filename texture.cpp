/***************************
* Open GL 2 Tutorial: Electric Boogaloo
****************************/
/*
to install png, use:
apt-get install libpng-dev

You most likely already have this installed!

A little lesson about data structures here, keep in mind png_byte is
virtually the same as a byte. 
It is an unsigned byte with a range of 0-255.
So we can use it as such for determining the value of each r,g,b,a
*/
#include <png.h>

struct Texture {
	FILE *file; //The file pointer. It needs to be opened by you, for data to be streamed from.
	png_structp ptr; //png Pointer.
	png_infop info; //Information of PNG Pointer.

	/*
		Some pointless information for this tutorial, but let's get them anyways
		so you know how to obtain it in the future.
	*/
	int width,height; //the height and width of the image.
	png_byte colorType; //the color type of the image usually rbga
	png_byte bpp; //color type, usually 32

	//The actual file data:
	png_bytep *rows; //a dynamic array which will point to dynamic arrays of each pixel in the row.	

	//And now the texture Data:
	GLubyte *data;//the data prepared for video transfer.
	GLuint tid; //This is assigned by openGL

	void setup(){
		//turn on the texture engine.
		glEnable( GL_TEXTURE_2D ); 
		//tell how Open GL to blend the texture, this is the standard "multiple" method.
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glEnable( GL_BLEND );	
	}

	void load(){
		cout << "Hi! I'm loading meme.png!" << endl;
		loadFromDisk();
		prepare();
		transferToVideoMemory();

		cout << "loaded into video memory." << endl;
	};

	void loadFromDisk(){
		cout << "Decompressing PNG.... " << endl;
		//first begin by opening the file:
		file = fopen("meme.png","rb"); //rb = read binary.
		//next initialize the png decompressor:
		ptr =  png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL );
		if (!ptr) cout << "Seems to have a problem creating the pointer." << endl;
		//Then the info pointer, containing our png meta data.
		info = png_create_info_struct( ptr );
		if (!info) cout << "Seems to have a problem creating the info pointer." << endl;
		//now bind the pointer to the file.
		png_init_io( ptr, file );
		//And now read in the meta information.
		png_read_info( ptr, info );

		//Let's get that useless meta data. But Keep in mind how to do this, just in case.
		width = png_get_image_width( ptr, info );
		height = png_get_image_height( ptr, info );
		colorType = png_get_color_type( ptr, info );
        bpp = png_get_bit_depth( ptr, info );
        cout << "Dimensions: " << width << "x" << height << endl;
        cout << "colorType: " << bpp << endl;
        cout << "BPP: " << bpp << endl;

        //update the information. I'm not sure if this is necessary.
        png_read_update_info( ptr, info );

        //Now we need to allocate the data for our png to be decompressed into.
		rows = ( png_bytep* ) malloc( sizeof(png_bytep) * height );
		for ( int i = 0; i < height; i++ ){
			//So because a single pixel could be 3 bytes (RGB) or 4 bytes (RGBA),
			//you shoud use png_get_rowbytes to determine how many bytes the row actually has.
			//However for this example, we expect only RGBA anyways.
			rows[i] = ( png_byte* ) malloc( png_get_rowbytes( ptr, info ) );
		}
		//now we can read our png and decompress it.
		png_read_image( ptr, rows );
		//don't forget to close the file! 
		fclose(file); 
		cout << "Done!"<< endl << endl;
	}

	void prepare(){
		//So... we need to now convert the way the data was stored, into a format that can be transferred into memory.
		//We need to convert the array of rows into just one giant array of the entire image.
		//So all this does is iterate through all the bytes
		int rowBytes = png_get_rowbytes( ptr, info );
		data = (GLubyte* ) malloc( rowBytes * height);
		for ( int y = 0; y < height; y++ ){
			for ( int x = 0; x < rowBytes; x++ ){
				int n = ( y * rowBytes ) + x;
				data[n] = (GLubyte)rows[y][x];
			}
			//let's not forget to erase the data we are no longer using.
			free(rows[y]); 
		}
		//And then erase the structure of that data, now that we're all done with it.
		free(rows);
	}

	void transferToVideoMemory(){
		cout << "now transferring to video memory.... " << endl;
		//purge errors, just in case.
		while(glGetError()){;};
		//glGenTextures will generate a dynamic space in video memory for our texture,
		//it'll return a reference id for us to use to work with that texture.
		glGenTextures( 1, &tid );
		cout << "Our texture reference: " << tid << endl;
		//now tell Open GL we will be using that texture.
		glBindTexture( GL_TEXTURE_2D, tid );
		//And setup some parameters to how the texture will behave and generate.
		//you might want to look up how clamp / wrap work, in this case we'll use "Clamp" which 
		//says the texture will not repeat on its surface, and have a hard edge.
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		
		//now load that crazy thing into memory!
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLubyte *)data );

		//This is how the texture will be filtered when zoomed in / out.
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		//check with OpenGL to see if any errors have occured.
		int e = 0;
		while (e = glGetError()) { 
			cout << "ERROR:" << e << endl; 
		}
		//finally let's delete the png data from memory (But not video memory) since it won't be needed anymore.
		free(data);
		cout << "Done!"<< endl << endl;
	}
} texture;