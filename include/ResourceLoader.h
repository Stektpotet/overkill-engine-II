#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>

#include <gfx.h>
#include <stb_image.h>

#include "noise/OpenSimplex.h"

#include "ShaderProgram.hpp"
#include "Texture.hpp"
// @ref Inspired by https://stackoverflow.com/a/2602060
//    and http://insanecoding.blogspot.no/2011/11/how-to-read-in-file-in-c.html
/// <summary>
/// reads the <paramref name="file"/> into <paramref name="outString"/>
/// </summary>
/// <param name="file">the path of the file to read</param>
/// <param name="outString">the string to be filled</param>
/// <returns> true when successful, false when unsuccessful </returns>
auto fileToString(const char * file, std::string* outString) -> bool
{
	std::ifstream infile(file);

	if (!infile) {
		return false;
	}
	infile.seekg(0, std::ios::end);
	outString->resize(infile.tellg());
	infile.seekg(0, std::ios::beg);
	infile.read(outString->data(), outString->size());
	infile.close();
	return true;
}

/// <summary>
/// creates a new shader object of type <paramref name="shaderType"/>, 
/// and reads the shader code "<paramref name="src"/>" into the shader object 
/// </summary>
/// <param name="src">the source code</param>
/// <param name="shaderType">the shaderType</param>
/// <returns> the id of the created shader object </returns>
auto createShader(const char* src, GLenum shaderType) -> GLuint
{
	// Create an empty shader object
	GLuint shaderID = glCreateShader(shaderType);

	//set the shader source code of the shader object
	glShaderSource(shaderID, 1, &src, nullptr);

	// Compile the shader
	glCompileShader(shaderID);

	GLint compileOK;		//validate shader compilation
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileOK);
	if (!compileOK) {
		std::string str;
		int length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

		str.resize(length); 
		glGetShaderInfoLog(shaderID, length, nullptr, str.data());
		GFX_WARN("%s shader failed to compile with the error: %s\n", Gfx::GLEnumToString(shaderType), str.c_str());
		return 0;
	}
	return shaderID;
}

/// <summary>
/// creates a new shader program and its shaders based on the source files given
/// </summary>
/// <param name="vertFile">the path of the vertex shader file</param>
/// <param name="fragFile">the path of the fragment shader file</param>
/// <returns> the id of the created shader program </returns>
auto createProgram(const char *vertFile, const char *fragFile) -> ShaderProgram
{
	GLuint program = glCreateProgram();
	GLuint vertexShader = 0;
	GLuint fragmentShader = 0;

	std::string sourceStr;

	// Load and compile the vertex and fragment shaders
	if (fileToString(vertFile, &sourceStr)) {
		if (vertexShader = createShader(sourceStr.c_str(), GL_VERTEX_SHADER); !vertexShader) {
			GFX_ERROR(
				"Program creation failed because the vertex shader was invalid:\n\t%s", vertFile
			);
		}
	} else GFX_ERROR("the file \"%s\" could not be found!", vertFile);
	sourceStr.clear();
	if (fileToString(fragFile, &sourceStr)) {
		if (fragmentShader = createShader(sourceStr.c_str(), GL_FRAGMENT_SHADER); !fragmentShader) {
			GFX_ERROR(
				"Program creation failed because the fragment shader was invalid:\n\t%s", fragFile
			);
		}
	} else GFX_ERROR("the file \"%s\" could not be found!", fragFile);

	// Create a program object and attach the two shaders we have compiled, the program object contains
	// both vertex and fragment shaders as well as information about uniforms and attributes common to both.

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);


	// Now that the fragment and vertex shader has been attached, 
	// we no longer need these two separate objects and should delete them to free the memory.
	// The attachment to the shader program will keep them alive, as long as we keep the shaderProgram.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Link the different shaders that are bound to this program, this creates a final shader that 
	// we can use to render geometry with.
	glLinkProgram(program);
	
	GLint linkOK;
	glGetProgramiv(program, GL_LINK_STATUS, &linkOK);
	
	// Verify that the program linked
	if (!linkOK) {
		std::string str;
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		str.resize(length);

		glGetProgramInfoLog(program, length, nullptr, str.data());
		GFX_ERROR("The program consisting of \"%s\" and  \"%s\" failed to link: %s\n", vertFile, fragFile, str.c_str());
	}
	glUseProgram(program);

	return ShaderProgram(program);
}


auto splitTexture(
	const uint8_t* fullSrc,
	const uint16_t channels,
	const uint16_t width,
	const uint16_t height,
	const uint16_t elementWidth,
	const uint16_t elementHeight
) -> std::vector<TextureData>
{
	uint16_t elementsX = width / elementWidth,
		elementsY = height / elementHeight;
	std::vector<TextureData> subTextures(
		elementsX * elementsY,
		{
			elementWidth,
			elementHeight,
			std::vector<uint8_t>(elementWidth * elementHeight * channels)
		}
	);
	for (size_t y = 0; y < height; y++)
	{
		for (size_t elemX = 0; elemX < elementsX; elemX++)
		{
			int fromIndex = (elemX * elementWidth + width * y) * channels;
			int toIndex = elementWidth * (y % elementHeight) * channels;
			int subTexIndex = elemX + (y / elementHeight)*elementsX;

			memcpy(&(subTextures[subTexIndex].pixels[toIndex]), &fullSrc[fromIndex], elementWidth * channels);
		}
	}
	return subTextures;
}


auto splitTexture(
	const uint8_t* fullSrc,
	const uint16_t channels,
	const uint16_t size,
	const uint16_t elementSize
) -> std::vector<TextureData>
{
	return splitTexture(fullSrc, channels, size, size, elementSize, elementSize);
}

auto loadTexture(const char* texturefile, Texture2D* outTexture) -> int
{
	GLubyte* raw_pixels;

	stbi_set_flip_vertically_on_load(true);
	int width, height, channels;
	raw_pixels = stbi_load(texturefile, &width, &height, &channels, STBI_default);
	if (!raw_pixels)
	{
		stbi_image_free(raw_pixels);
		GFX_WARN("failed to load \"%s\"\n", texturefile);
		return 1;
	}


	*outTexture = Texture2D(width, height, channels);
	GFX_GL_CALL(glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA8,
		width,
		height,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		raw_pixels)
	);


	GFX_GL_CALL(glBindTexture(GL_TEXTURE_2D, 0)); //unbind 
	stbi_image_free(raw_pixels);

	return 0;
}

auto loadTextureAtlas(const char* texturefile, const uint16_t dimension, TextureAtlas* outTexture) -> int
{
	GLubyte* raw_pixels;

	stbi_set_flip_vertically_on_load(true);
	int width, height, channels;
	
	raw_pixels = stbi_load(texturefile, &width, &height, &channels, STBI_rgb);
	if (!raw_pixels)
	{
		stbi_image_free(raw_pixels);
		GFX_WARN("failed to load \"%s\"\n", texturefile);
		return 1;
	}
	//GFX_ASSERT(dimension <= 16, "Unsupported dimension of atlas: %dx%d=%d, (max supported is 16x16=256)", dimension, dimension, dimension * dimension);
	*outTexture = TextureAtlas(width / dimension, height / dimension, dimension * dimension, channels);
	GFX_GL_CALL(
		glTexImage3D(GL_TEXTURE_2D_ARRAY,
			0,							// mipmap level
			GL_RGBA8,					// gpu texel format
			outTexture->getWidth(),		// width
			outTexture->getHeight(),	// height
			outTexture->getDepth(),		// depth
			0,							// border
			GL_RGB,						// cpu pixel format
			GL_UNSIGNED_BYTE,			// cpu pixel coord type
			nullptr						// pixel data
		)					
	);

	//GFX_DEBUG("%s", raw_pixels);
	//fwrite(raw_pixels, sizeof(char), width*height*channels, stdout);
	auto atlasData = splitTexture(raw_pixels, channels, width, height, width/dimension, height/dimension);
	for (size_t i = 0; i < atlasData.size(); i++)
	{
		// (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
		GFX_GL_CALL(
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
				0,		// mipmap level
				0,0,i,	// x,y,z
				atlasData[i].width,
				atlasData[i].height,
				1,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				atlasData[i].pixels.data()
			)
		);
	}

	GFX_GL_CALL(glBindTexture(GL_TEXTURE_2D_ARRAY, 0)); //unbind 
	stbi_image_free(raw_pixels);

	return 0;
}


auto createNoiseTexture(glm::ivec2 dimensions, int channels, Texture2D* outTexture, int64_t seed = 0) -> int
{
	OpenSimplex::Noise noise(seed);
	auto raw_pixels = std::vector<uint8_t>(dimensions.x * dimensions.y * channels);
	for (size_t y = 0; y < dimensions.y; y++)
	{
		for (size_t x = 0; x < dimensions.x; x++)
		{
			auto nValue = 0.5*noise.eval(10.0f*x / dimensions.x, 10.0f*y / dimensions.y)+0.5;
			uint8_t value = uint8_t(255 * nValue);
			for (size_t c = 0; c < channels; c++)
			{
				raw_pixels[y * dimensions.x + x * channels + c] = value;
			}
		}
	}
	*outTexture = Texture2D(dimensions.x, dimensions.y, channels);
	GFX_GL_CALL(glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA8,
		dimensions.x,
		dimensions.y,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		raw_pixels.data())
	);


	GFX_GL_CALL(glBindTexture(GL_TEXTURE_2D, 0)); //unbind 

	return 0;
}