#include <GL\glut.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

float lado = 20;
GLuint texID[3];

void quadrado(float SIZE, GLuint texid)
{
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, texid);
	
	glBegin(GL_QUADS);
		//Face frontal
		glTexCoord2f(0,0);	glVertex3f(-SIZE, -SIZE, 0.0);
		glTexCoord2f(1,0);	glVertex3f(SIZE, -SIZE, 0.0);
		glTexCoord2f(1,1);	glVertex3f(SIZE, SIZE, 0.0);
		glTexCoord2f(0,1);	glVertex3f(-SIZE, SIZE, 0.0);
		
		//Face direita
		glTexCoord3f(0,1,0); glVertex3f(SIZE, SIZE, 0);
		glTexCoord3f(1,1,1); glVertex3f(SIZE, SIZE, -SIZE*2);
		glTexCoord3f(1,0,1); glVertex3f(SIZE, -SIZE, -SIZE*2);
		glTexCoord3f(0,0,0); glVertex3f(SIZE, -SIZE, 0);
		
		//Face esquerda
		glTexCoord3f(0,1,0); glVertex3f(-SIZE, SIZE, 0); 
		glTexCoord3f(1,1,1); glVertex3f(-SIZE, SIZE, -SIZE*2);
		glTexCoord3f(1,0,1); glVertex3f(-SIZE, -SIZE, -SIZE*2);
		glTexCoord3f(0,0,0); glVertex3f(-SIZE, -SIZE, 0);
		
		//Face posterior
		glTexCoord2f(0,0);	glVertex3f(-SIZE, -SIZE, -SIZE*2);
		glTexCoord2f(1,0);	glVertex3f(SIZE, -SIZE, -SIZE*2);
		glTexCoord2f(1,1);	glVertex3f(SIZE, SIZE, -SIZE*2);
		glTexCoord2f(0,1);	glVertex3f(-SIZE, SIZE, -SIZE*2);
		
		//Face superior
		glTexCoord3f(0,0,0); glVertex3f(-SIZE, SIZE, 0);
		glTexCoord3f(1,0,0); glVertex3f(-SIZE, SIZE, -SIZE*2);
		glTexCoord3f(1,1,0); glVertex3f(SIZE, SIZE, -SIZE*2);
		glTexCoord3f(0,1,0); glVertex3f(SIZE, SIZE, 0);
		
		//Face inferior
		glTexCoord3f(0,0,0); glVertex3f(-SIZE, -SIZE, 0);
		glTexCoord3f(1,0,0); glVertex3f(-SIZE, -SIZE, -SIZE*2);
		glTexCoord3f(1,1,0); glVertex3f(SIZE, -SIZE, -SIZE*2);
		glTexCoord3f(0,1,0); glVertex3f(SIZE, -SIZE, 0);
		
	glEnd();
}

void desenho(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	quadrado(lado, texID[0]);
	glTranslatef(-50,0,0);
	
	glFlush();
}

void ajuste(int w, int h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45,w/h, 0.4, 500);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(50,100,200,
			0,0,0,
			0,1,0);
}

void carregarTextura(GLuint tex_id, string filepath){
	unsigned char* imgData;
	int largura, altura, canais;
	
	stbi_set_flip_vertically_on_load(true);
	
	imgData = stbi_load(filepath.c_str(), &largura, &altura,&canais, 4);
	
	if(imgData){
		glBindTexture(GL_TEXTURE_2D, tex_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, largura, 
		altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		
		stbi_image_free(imgData);
	}else{
		cout<<"ERRO!Não foi possível carregar a imagem "<<filepath.c_str()<<endl;
	}
}

void initializeTexture(){
	glGenTextures(3, texID);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	carregarTextura(texID[0], "images/brick.png");	
	glEnable(GL_DEPTH_TEST);
}

int main(){
	glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
	glutInitWindowPosition(200,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("3D");
	glutDisplayFunc(desenho);
	glutReshapeFunc(ajuste);
	initializeTexture();
	
	glutMainLoop();	
}
