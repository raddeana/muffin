#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glcommon.hpp"

static const char *readShaderFromFile(const char *path)
{
	FILE *fp;
	char *content = NULL;
	int count=0;
	if (path != NULL)
	{
		fp = fopen(path,"rt");
		if (fp != NULL)
		{
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);
			if (count > 0)
			{
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

static GLuint loadShader(int shaderType, const char *shaderPath)
{
	GLuint shader = glCreateShader(shaderType);
	char *shaderCode = (char *) readShaderFromFile(shaderPath);
	glShaderSource(shader, 1, &shaderCode, 0);//加载顶点着色器源码到 shader 中
	free(shaderCode);
	glCompileShader(shader);

	int infologLength = 0;
	int charsWritten = 0;
	char * infoLog;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLength);//查询glsl里的日志的长度，如果长度为0表示没信息
	if (infologLength > 0)
	{
		infoLog = (char *) malloc(infologLength);
		glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog);//将日志写入到 infoLog 中，charsWritten为实际写入长度
		printf("loadShader type=%d, error : %d, %d, %s\n", shaderType, infologLength, charsWritten, infoLog);
		free(infoLog);
		shader = 0;
	}

	return shader;
}

GLuint createGLProgram(const char *vertPath, const char *fragPath)
{
	GLuint vert = loadShader(GL_VERTEX_SHADER, vertPath);
	GLuint frag = loadShader(GL_FRAGMENT_SHADER, fragPath);
	printf("vert=%u, frag=%u\n", vert, frag);
	if (vert==0 || frag==0) return 0;

	GLuint program = glCreateProgram();//创建着色器程序
	glAttachShader(program, vert);
	glAttachShader(program, frag);//将编译好的着色器放到着色器程序p中，着色器程序中可以放多个着色器
	glLinkProgram(program);//链接

	int infologLength = 0;
	int charsWritten = 0;
	char * infoLog;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infologLength);//查询glsl里的日志的长度，如果长度为0表示没信息
	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(program, infologLength, &charsWritten, infoLog);//将日志写入到 infoLog 中，charsWritten为实际写入长度
		printf("createGLProgram : %d,%d,%s\n", infologLength, charsWritten, infoLog);
		free(infoLog);
		program = 0;
	}

	printf("program=%u\n", program);
	return program;
}
