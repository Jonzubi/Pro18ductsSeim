#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

//Definicion de las estructuras

typedef struct
{
	int IdCliente;
	char Nombre[20];
	char Domicilio[20];
	char CodPostal[6];
	char Municipio[15];
	char NIF[10];

}CLIENTE;
CLIENTE Clientes, ComprobarClientes;

typedef struct
{
	int IdArticulo;
	char Denominacion[20];
	int PrecCoste;
	int PVP;
}ARTICULO;
ARTICULO Articulos, ComprobarArticulos;
typedef struct
{
	int IdCliente;
	int IdArticulo;
	int PVP;
	int Cantidad;

}PEDIDO;
PEDIDO Pedidos;

//Declaracion de la variable de limpiar el buffer y de las funciones

char limp;
int MenuPrincipal();//
int MenuClientes();//
int MenuArticulos();//
void ProgramaPedidos();
void ProgramaFacturacion();
void AltaCliente();//
void AltaArticulo();//
void ModifiCliente();//
void ModifiArticulo();//
void ConsulCliente();//
void ConsulArticulo();//
void PedirDatosCliente();//
void PedirDatosArticulos();//
void PedirModificarCliente();//
void PedirModificarArticulos();//
void gotoxy(int x, int y);//