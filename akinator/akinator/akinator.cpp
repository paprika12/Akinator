// akinator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <stdio.h>
using namespace std;
/*******************ESTRUCTURA***********************/
struct nodo {
	string dato="";
	struct nodo *izq=NULL, *der=NULL;
};
ifstream fe("akinator.txt");
typedef struct nodo *akinator;

/******************Prototipos**********************************/
akinator crearNodo(string dato);
void empezarAkinator(akinator arbol);
void guardarArchivo(nodo *akin);
void leerArchivo(nodo *akin);
void limpiarArchivo();

akinator crearNodo(string dato)
{
	akinator nuevoNodo = new(struct nodo);
	nuevoNodo->dato = dato;
	nuevoNodo->izq = NULL;
	nuevoNodo->der = NULL;

	return nuevoNodo;
}

void empezarAkinator(akinator arbol) {
	int  rep = 0, sino = 0;
	string cu, per;
	akinator r=NULL;
	
	do {
		//si el arbol ya tiene datos
		if (arbol != NULL) {
			r = arbol;
		}
		do {
			//si el arbol no tiene datos
			if (arbol == NULL)
			{
				cout << "En quien estas pensando?" << endl;
				cin >> per;
				arbol = crearNodo(per);
				sino = 0;
			}
			else {//si el arbol ya tiene datos y ya empezo el juego
				if (r->izq == NULL && r->dato !="") { //si solo hay un nodo con sus lados nullos
					cout << "la persona en la que estas pensando es " << r->dato << "? \n1.-si 2.-no:" << endl;
					cin >> sino;
				}
				else if(r->dato != "") {//si hay mas nodos
					cout << "esta persona es o hace lo siguiente... " << r->dato << "? \n1.-si 2.-no:" << endl;
					cin >> sino;
				}
				
				//si la persona hace lo anterior
				if (sino == 1) {
					//si no hay mas opciones
					if (r->izq == NULL) {
						//recorrido = recorrido->izq;
						cout << "demostrado." << endl;
						system("pause");
						sino = 0;
					}
					//si hay mas opciones le pregunta si es esa persona (pregunta primero la caracterisitica)
					else
					{
						r = r->izq;
					}
				}
				else {
					//cuando no es lo que piensas
					if (r->der == NULL  ) { //si ya no hay mas opciones
						system("cls");

						cout << "En que profesor estas pensando? : ";
						cin >> per;
						cout << "En que se diferencia del profesor " << r->dato << " ? : ";
						cin >> cu;

						
						r->der = crearNodo(r->dato);
						r->dato = cu;
						r->izq = crearNodo(per);
						sino=0;
					}
					else {//se recorre si hay mas
						r = r->der;
					}
				}
				
			}
		} while (sino != 0);
		system("cls");
		cout << "REPETIR: \n1.- si\n2.- no:" << endl;
		cin >> rep;
		system("cls");

	} while (rep == 1);
	guardarArchivo(arbol);
}

/*****************Funciones de escritura y lectura de archivo*********************************/
//otra manera de guardar el archivo
/*void guardarArchivo(akinator arbol) {
FILE * file = fopen("output", "wb");
if (file != NULL) {
fwrite(arbol, sizeof(struct nodo), 1, file);
fclose(file);
}
}*/
void limpiarArchivo() {
	std::ofstream ofs;
	ofs.open("akinator.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}
void guardarArchivo(nodo *akin) {
	std::fstream fs;
	fs.open("akinator.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	fs << akin->dato << endl;

	if (akin->izq != NULL)
		guardarArchivo(akin->izq);
	else
		fs << "@" << endl;
	if (akin->der != NULL)
		guardarArchivo(akin->der);
	else
		fs << "@" << endl;

}

void leerArchivo(nodo *akin) {
	string cadena = "";


	fe >> cadena;
	if (cadena != "" && cadena != "@") {
		akin->dato = cadena;

		akin->der = new nodo();
		akin->izq = new nodo();
		leerArchivo(akin->izq);
		leerArchivo(akin->der);
	}

}
/******************Principal**********************************/
int main(int argc, char** argv) {
	int op = 0;
	akinator arbol = NULL;
	cout << "1.Empezar \n2.Cargar Archivo\n";
	cin >> op;
	system("cls");
	if (op == 1) {
		limpiarArchivo();
		empezarAkinator(arbol);

	}

	if (op == 2) {
		//esta es otra manera de leerlo 
		/*arbol = (struct nodo*)malloc(sizeof(struct nodo));
		FILE * file = fopen("output", "rb");
		if (file != NULL) {
			fread(arbol, sizeof(struct nodo), 1, file);
			fclose(file);
		}*/

		arbol = new nodo();
		leerArchivo(arbol);
		fe.close();
		empezarAkinator(arbol);

	}

	return 0;
}
