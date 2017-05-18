#include "Funciones.h"

//Definicion del menu que saltara en el inicio del programa

int MenuPrincipal()
{
	int opc;
	char limp;
	system("cls");
	printf("\t\t\tMENU FACTURACION\n\t\t\t----------------\n");
	printf("1-Clientes\n2-Articulos\n3-Pedidos\n4-Facturacion\n5-Salir\n\nOpcion : ");
	scanf("%d%c", &opc, &limp);
	return opc;
}
//Definicion del menu de la opcion 1

int MenuClientes()
{
	int opc;
	char limp;
	system("cls");
	printf("\t\t\tMENU CLIENTES\n\t\t\t-------------\n");
	printf("1-Altas\n2-Modificar\n3-Consultar\n4-Atras\n\nOpcion : ");
	scanf("%d%c", &opc, &limp);
	return opc;
}

//Definicion del menu de la opcion 2
int MenuArticulos()
{
	int opc;
	char limp;
	system("cls");
	printf("\t\t\tMENU ARTICULOS\n\t\t\t--------------\n");
	printf("1-Altas\n2-Modificar\n3-Consultar\n4-Atras\n\nOpcion : ");
	scanf("%d%c", &opc, &limp);
	return opc;
}
//Definicion del apartado de alta de la opcion 1
void AltaCliente()
{
	FILE *pf;
	int r;
	if ((pf = fopen("Clientes.txt", "rb"))==NULL)
	{
		pf = fopen("Clientes.txt", "wb+");
	}
	else
	{
		fclose(pf);
		pf = fopen("Clientes.txt", "rb+");
	}

	fseek(pf, 0, SEEK_END);
	int reg = ftell(pf) ;
	rewind(pf);
	reg -= ftell(pf);
	reg /= sizeof(Clientes);
	if (reg == 0)
	{
		printf("El fichero de clientes esta vacio! Pulsa una tecla para proceder a registrar\n");
		getch();
	}
	else
	{
		for (int i = 0; i < reg; i++)
			{
				fread(&Clientes, sizeof(Clientes), 1, pf);
			}
		printf("El NºCliente del Ultimo Registro : %d\n\n", Clientes.IdCliente);
	}

	PedirDatosCliente();
	do {
		printf("REGISTRAR DATOS?\n0-No\n1-Si\n");
		scanf("%d%c", &r, &limp);
		if (r != 1)
		{
			PedirDatosCliente();
			printf("REGISTRAR DATOS?\n0-No\n1-Si\n");
			scanf("%d%c", &r, &limp);
		}
		else
		{
			break;
		}
	} while (r != 1);
	fseek(pf, 0, SEEK_SET);
	for (int i = 0; i < reg; i++)
	{
		fread(&ComprobarClientes, sizeof(ComprobarClientes), 1, pf);
		if (ComprobarClientes.IdCliente == Clientes.IdCliente)
		{
			printf("\nEl IdCliente introducido ya existe!Introduzca otra que no exista!\n");
			getch();
			return;
		}
	}
	fseek(pf, 0, SEEK_END);
	fwrite(&Clientes, sizeof(Clientes), 1, pf);
	printf("Cliente Registrado!\n");
	getch();
	fclose(pf);
}
//Definicion del apartado de modificado de la opcion 1
void ModifiCliente()
{
	FILE *pf;
	int r, idcliente, ultidcliente;
	if ((pf = fopen("Clientes.txt", "r")) == NULL)
	{
		printf("El fichero no existe!ELige la opcion 1 para crear el fichero!Pulsa intro para Salir al Menu!");
		getch();
		return;
	}
	else
	{
		pf = fopen("Clientes.txt", "rb+");
	}

	fseek(pf, 0, SEEK_END);
	int reg = ftell(pf) / sizeof(Clientes);
	rewind(pf);

	if (reg == 0)
	{
		printf("El fichero de clientes esta vacio! Primero dale de alta a un cliente!Pulsa Intro\n");
		fclose(pf);
		getch();
		return;
	}
	else
	{
		for (int i = 0; i < reg; i++)
		{
			fread(&Clientes, sizeof(Clientes), 1, pf);
		}
		ultidcliente = Clientes.IdCliente;
		printf("El NºCliente del Ultimo Registro : %d\n\n", Clientes.IdCliente);
		do {
			printf("Introduce el Id del Cliente que quieras modificar : ");
			scanf("%d%c", &idcliente, &limp);
		} while (idcliente < 0 || idcliente>ultidcliente);
		rewind(pf);
		for (int i = 0; i < reg; i++)
		{
			fread(&Clientes, sizeof(Clientes), 1, pf);
			if (Clientes.IdCliente == idcliente)
			{
				do {
					PedirModificarCliente();
					printf("REGISTRAR DATOS?\n0-No\n1-Si\nRespuesta : ");
					scanf("%d%c", &r, &limp);
				} while (r != 1);
				if (Clientes.IdCliente<0 || Clientes.IdCliente>ultidcliente)
				{
					printf("ERROR: IdCliente fuera de rango!");
					fclose(pf);
					return;
				}
				else
				{
					rewind(pf);
					if (idcliente != Clientes.IdCliente)
					{
						for (int i = 0; i < reg; i++)
						{
							fread(&ComprobarClientes, sizeof(ComprobarClientes), 1, pf);
							if (ComprobarClientes.IdCliente == Clientes.IdCliente)
							{
								printf("\nEl IdCliente introducido ya existe!Introduzca otra que no exista!\n");
								getch();
								return;
							}
						}
					}
					fseek(pf, ftell(pf) - sizeof(Clientes), SEEK_SET);
					fwrite(&Clientes, sizeof(Clientes), 1, pf);
				}
				printf("Cliente modificado!Pulsa intro para Salir");
				getch();
				fclose(pf);
				return;
			}
		}
		


	}
}
//Definicion del apartado de consulta de la opcion 1
void ConsulCliente()
{
	FILE *pf;
	int r, idcliente, ultidcliente;
	if ((pf = fopen("Clientes.txt", "r")) == NULL)
	{
		printf("El fichero no existe!ELige la opcion 1 para crear el fichero!Pulsa intro para Salir al Menu!");
		getch();
		return;
	}
	else
	{
		pf = fopen("Clientes.txt", "rb");
	}

	fseek(pf, 0, SEEK_END);
	int reg = ftell(pf) / sizeof(Clientes);
	rewind(pf);

	if (reg == 0)
	{
		printf("El fichero de clientes esta vacio! Primero dale de alta a un cliente!Pulsa Intro\n");
		getch();
		fclose(pf);
		return;
	}
	else
	{
		for (int i = 0; i < reg; i++)
		{
			fread(&Clientes, sizeof(Clientes), 1, pf);
		}
		ultidcliente = Clientes.IdCliente;
		printf("El NºCliente del Ultimo Registro : %d\n\n", Clientes.IdCliente);
		do {
			printf("IDCliente que quiera consultar : ");
			scanf("%d%c", &idcliente, &limp);
		} while (idcliente<0 || idcliente>ultidcliente);
		rewind(pf);
		for (int i = 0; i < reg; i++)
		{
			fread(&Clientes, sizeof(Clientes), 1, pf);
			if (Clientes.IdCliente == idcliente)
			{
				system("cls");
				printf("\t\t\tFICHERO DE CLIENTES\n\t\t\t------------------\n");
				printf("NºCliente : %d\nNombre : %s\nDomicilio : %s\nCodPostal : %s\nMunicipio : %s\nNIF : %s\n", Clientes.IdCliente, Clientes.Nombre, Clientes.Domicilio, Clientes.CodPostal, Clientes.Municipio, Clientes.NIF);
				printf("Pulsa Intro para continuar");
				getch();
				fclose(pf);
				return;
			}
		}
	}
}
//Funcion para pedir datos del cliente
void PedirDatosCliente()
{
	system("cls");
	printf("\t\t\tFICHERO DE CLIENTES\n\t\t\t------------------\n");
	printf("NºCliente : \nNombre : \nDomicilio : \nCodPostal : \nMunicipio : \nNIF : \n");
	gotoxy(11, 2);
	scanf("%d%c", &Clientes.IdCliente, &limp);
	gotoxy(8, 3);
	gets(Clientes.Nombre);
	gotoxy(11, 4);
	gets(Clientes.Domicilio);
	gotoxy(11, 5);
	gets(Clientes.CodPostal);
	gotoxy(11, 6);
	gets(Clientes.Municipio);
	gotoxy(5, 7);
	gets(Clientes.NIF);
}
//Funcion para pedir los datos del modificado de los datos del cliente
void PedirModificarCliente()
{
	system("cls");
	printf("\t\t\tFICHERO DE CLIENTES\n\t\t\t------------------\n");
	printf("NºCliente : %d\nNombre : %s\nDomicilio : %s\nCodPostal : %s\nMunicipio : %s\nNIF : %s\n", Clientes.IdCliente, Clientes.Nombre, Clientes.Domicilio, Clientes.CodPostal, Clientes.Municipio, Clientes.NIF);
	printf("\n\nNuevo NºCliente : \nNuevo Nombre : \nNuevo Domicilio : \nNuevo CodPostal : \nNuevo Municipio : \nNuevo NIF : \n");
	gotoxy(17, 10);
	scanf("%d%c", &Clientes.IdCliente, &limp);
	gotoxy(14, 11);
	gets(Clientes.Nombre);
	gotoxy(17, 12);
	gets(Clientes.Domicilio);
	gotoxy(17, 13);
	gets(Clientes.CodPostal);
	gotoxy(17, 14);
	gets(Clientes.Municipio);
	gotoxy(11, 15);
	gets(Clientes.NIF);
}
//Funcion para pedir datos de articulo
void PedirDatosArticulos()
{
	system("cls");
	printf("\t\t\tFICHERO DE ARTICULOS\n\t\t\t------------------\n");
	printf("NºArticulo : \nDenominacion : \nPrecioCoste : \nPVP : \n");
	gotoxy(12, 2);
	scanf("%d%c", &Articulos.IdArticulo, &limp);
	gotoxy(14, 3);
	gets(Articulos.Denominacion);
	gotoxy(13, 4);
	scanf("%d%c", &Articulos.PrecCoste, &limp);
	gotoxy(5, 5);
	scanf("%d%c", &Articulos.PVP, &limp);
}
//Funcion para dar de alta a articulos
void AltaArticulo()
{
	FILE *pf;
	int r;
	if ((pf = fopen("Articulos.txt", "r")) == NULL)
	{
		pf = fopen("Articulos.txt", "wb+");
	}
	else
	{
		pf = fopen("Articulos.txt", "ab+");
	}

	fseek(pf, 0, SEEK_END);
	int reg = ftell(pf);
	rewind(pf);
	reg -= ftell(pf);
	reg /= sizeof(Articulos);

	if (reg == 0)
	{
		printf("El fichero de articulos esta vacio! Pulsa una tecla para proceder a registrar\n");
		getch();
	}
	else
	{
		for (int i = 0; i < reg; i++)
		{
			fread(&Articulos, sizeof(Articulos), 1, pf);
		}
		printf("El NºArticulo del Ultimo Registro : %d\n\n", Articulos.IdArticulo);
	}

	
	do {
		PedirDatosArticulos();
		printf("REGISTRAR DATOS?\n0-No\n1-Si\n");
		scanf("%d%c", &r, &limp);
	} while (r != 1);
	rewind(pf);
	for (int i = 0; i < reg; i++)
	{
		fread(&ComprobarArticulos, sizeof(ComprobarArticulos), 1, pf);
		if (ComprobarArticulos.IdArticulo == Articulos.IdArticulo)
		{
			printf("\nEl IdArticulo introducido ya existe!Introduzca otra que no exista!\n");
			getch();
			return;
		}
	}
	fseek(pf, 0, SEEK_END);
	fwrite(&Articulos, sizeof(Articulos), 1, pf);
	printf("Articulo Registrado!\n");
	fclose(pf);
}
//Funcion para modificar datos de articulos
void ModifiArticulo()
{
	FILE *pf;
	int r, idarticulo, ultidarti;
	if ((pf = fopen("Articulos.txt", "r")) == NULL)
	{
		printf("El fichero no existe!ELige la opcion 1 para crear el fichero!Pulsa intro para Salir al Menu!");
		getch();
		fclose(pf);
		return;
	}
	else
	{
		pf = fopen("Articulos.txt", "rb+");
	}

	fseek(pf, 0, SEEK_END);
	int reg = ftell(pf) / sizeof(Articulos);
	rewind(pf);

	if (reg == 0)
	{
		printf("El fichero de articulos esta vacio! Primero dale de alta a un cliente!Pulsa Intro\n");
		getch();
		fclose(pf);
		return;
	}
	else
	{
		for (int i = 0; i < reg; i++)
		{
			fread(&Articulos, sizeof(Articulos), 1, pf);
		}
		ultidarti = Articulos.IdArticulo;
		printf("El NºCliente del Ultimo Registro : %d\n\n", Articulos.IdArticulo);
		do {
			printf("Introduce el Id del Articulo que quieras modificar : ");
			scanf("%d%c", &idarticulo, &limp);
		} while (idarticulo < 0 || idarticulo>ultidarti);
		rewind(pf);
		for (int i = 0; i < reg; i++)
		{
			fread(&Articulos, sizeof(Articulos), 1, pf);
			if (Articulos.IdArticulo == idarticulo)
			{
				do {
					PedirModificarArticulos();
					printf("REGISTRAR DATOS?\n0-No\n1-Si\nRespuesta : ");
					scanf("%d%c", &r, &limp);
				} while (r != 1);
				if (Articulos.IdArticulo<0 || Articulos.IdArticulo>ultidarti)
				{
					printf("ERROR: IdCliente fuera de rango!");
					fclose(pf);
					return;
				}
				else
				{
					rewind(pf);
					for (int i = 0; i < reg; i++)
					{
						fread(&ComprobarArticulos, sizeof(ComprobarArticulos), 1, pf);
						if (ComprobarArticulos.IdArticulo == Articulos.IdArticulo)
						{
							printf("\nEl IdArticulo introducido ya existe!Introduzca otra que no exista!\n");
							getch();
							return;
						}
					}
					fseek(pf, ftell(pf) - sizeof(Articulos), SEEK_SET);
					fwrite(&Articulos, sizeof(Articulos), 1, pf);
				}
				printf("Articulo modificado!Pulsa intro para Salir");
				getch();
				fclose(pf);
				return;
			}
		}



	}
}
//Funcion para consultar articulos
void ConsulArticulo()
{
	FILE *pf;
	int r, idarticulo, ultidarti;
	if ((pf = fopen("Articulos.txt", "r")) == NULL)
	{
		printf("El fichero no existe!ELige la opcion 1 para crear el fichero!Pulsa intro para Salir al Menu!");
		getch();
		fclose(pf);
		return;
	}
	else
	{
		pf = fopen("Articulos.txt", "rb");
	}

	fseek(pf, 0, SEEK_END);
	int reg = ftell(pf) / sizeof(Articulos);
	rewind(pf);

	if (reg == 0)
	{
		printf("El fichero de articulos esta vacio! Primero dale de alta a un articulo!Pulsa Intro\n");
		getch();
		fclose(pf);
		return;
	}
	else
	{
		for (int i = 0; i < reg; i++)
		{
			fread(&Articulos, sizeof(Articulos), 1, pf);
		}
		ultidarti = Articulos.IdArticulo;
		printf("El NºCliente del Ultimo Registro : %d\n\n", Articulos.IdArticulo);
		do {
			printf("IDArticulo que quiera consultar : ");
			scanf("%d%c", &idarticulo, &limp);
		} while (idarticulo<0 || idarticulo>ultidarti);
		rewind(pf);
		for (int i = 0; i < reg; i++)
		{
			fread(&Articulos, sizeof(Articulos), 1, pf);
			if (Articulos.IdArticulo == idarticulo)
			{
				system("cls");
				printf("\t\t\tFICHERO DE ARTICULOS\n\t\t\t------------------\n");
				printf("NºArticulo : %d\nDenominacion : %s\nPrecCoste : %d\nPVP : %d\n", Articulos.IdArticulo, Articulos.Denominacion, Articulos.PrecCoste, Articulos.PVP);
				printf("Pulsa Intro para continuar");
				getch();
				fclose(pf);
				return;
			}
		}
	}
}
//Funcion para pedir los datos a modificar de articulos
void PedirModificarArticulos()
{
	system("cls");
	printf("\t\t\tFICHERO DE ARTICULOS\n\t\t\t------------------\n");
	printf("NºArticulo : %d\nDenominacion : %s\nPrecCoste : %d\nPVP : %d\n", Articulos.IdArticulo, Articulos.Denominacion, Articulos.PrecCoste, Articulos.PVP);
	printf("\n\nNuevo NºArticulo : \nNuevo Denominacion : \nNuevo PrecCoste : \nNuevo PVP : \n");
	gotoxy(18, 8);
	scanf("%d%c", &Articulos.IdArticulo, &limp);
	gotoxy(20, 9);
	gets(Articulos.Denominacion);
	gotoxy(17, 10);
	scanf("%d%c", &Articulos.PrecCoste, &limp);
	gotoxy(11, 11);
	scanf("%d%c", &Articulos.PVP, &limp);
	
}
//Funcion para mover el cursor en la consola
void gotoxy(int x, int y)
{
	HANDLE hnd;
	COORD coor;
	hnd = GetStdHandle(STD_OUTPUT_HANDLE);
	coor.X = x;
	coor.Y = y;
	SetConsoleCursorPosition(hnd, coor);
}
void ProgramaPedidos()
{
	FILE *pf1, *pf2, *pf3;
	int opc, idcliente, idarticulo, cant, i;

	pf1 = fopen("Clientes.txt", "rb");
	pf2 = fopen("Articulos.txt", "rb");
	if (pf1 == NULL)
	{
		printf("El fichero de clientes no esta creado! Vete al apartado de clientes para crearlo!\n");
		getch();
		fclose(pf1);
		fclose(pf2);
		return;
	}
	else
	{
		if (pf2 == NULL)
		{
			printf("El fichero de articulos no esta creado! Vete al apartado de articulos para crearlo!\n");
			getch();
			fclose(pf1);
			fclose(pf2);
			return;
		}
	}
	pf3 = fopen("Pedidos.txt", "rb");
	if (pf3 == NULL)
	{
		printf("El fichero de pedidos no esta creado! Deasea crearlo?\n0-No\n1-Si\nRespuesta : ");
		scanf("%d%c", &opc, &limp);
		if (opc == 1)
		{
			fclose(pf3);
			pf3 = fopen("Pedidos.txt", "wb+");
		}
		else
		{
			return;
		}
	}
	else
	{
		fclose(pf3);
		pf3 = fopen("Pedidos.txt", "rb+");
	}

	fseek(pf1, 0, SEEK_END);
	int reg1 = ftell(pf1) / sizeof(Clientes);
	rewind(pf1);
	fseek(pf2, 0, SEEK_END);
	int reg2 = ftell(pf2) / sizeof(Articulos);
	rewind(pf2);
	if (reg1 == 0)
	{
		printf("El fichero de clientes esta vacio! Introduce clientes para proceder con los pedidos!");
		return;
	}
	else
	{
		
		if (reg2 == 0)
		{
			printf("El fichero de articulos esta vacio! Introduce articulos para proceder con los pedidos!");
			return;
		}
	}
	rewind(pf1);
	for ( i = 0; i < reg1; i++)
	{
		fread(&Clientes, sizeof(Clientes), 1, pf1);
	}
	printf("\n\nEl NºCliente del Ultimo Registro : %d\n", Clientes.IdCliente);
	rewind(pf2);
	for ( i = 0; i < reg2; i++)
	{
		fread(&Articulos, sizeof(Articulos), 1, pf2);
	}
	printf("El NºArticulo del Ultimo Registro : %d\n\n", Articulos.IdArticulo);
	printf("Pulsa Intro para proceder con la introduccion de datos\n");
	getch();
	
	
	do
	{
	system("cls");
	printf("\t\tFICHERO DE PEDIDOS\n\t\t------------------\n");
	printf("NºCliente: \n\nNºArticulo\tDenominacion\tPVP\tCantidad\n------------------------------------------------\n");
	gotoxy(10, 2);
	scanf("%d%c", &idcliente, &limp);
		if (idcliente<0 || idcliente>Clientes.IdCliente)
		{
			printf("IdCliente fuera del limite!");
			getch();
			continue;
		}
		else
		{
			rewind(pf1);
			for ( i = 0; i < reg1; i++)
			{
				fread(&Clientes, sizeof(Clientes), 1, pf1);
				if (idcliente == Clientes.IdCliente)
				{
					gotoxy(13, 2);
					printf("%s %s %s %s %s", Clientes.Nombre, Clientes.Domicilio, Clientes.CodPostal, Clientes.Municipio, Clientes.NIF);
					break;
				}
				if (i == reg1 - 1)
				{
					printf("El IDCliente introducido no existe!");
					getch();
					continue;
				}
			}
		
		}
		
		do
		{
			gotoxy(0, 6);
			scanf("%d%c", &idarticulo, &limp);
			if (idarticulo<1 || idarticulo>Articulos.IdArticulo)
			{
				printf("IdArticulo fuera del limite!");
				getch();
				continue;
			}
			else
			{
				rewind(pf2);
				for (i = 0; i < reg2; i++)
				{
					fread(&Articulos, sizeof(Articulos), 1, pf2);
					if (idarticulo == Articulos.IdArticulo)
					{
						
						gotoxy(16, 6);
						printf("%s", Articulos.Denominacion);
						gotoxy(32, 6);
						printf("%d", Articulos.PrecCoste);
						gotoxy(40, 6);
						scanf("%d%c", &cant, &limp);
						break;
					}
					
				}
				if (i == reg2 - 1)
				{
					printf("El IdArticulo introducido no existe!");
					getch();
					break;
				}
				printf("\n\nRegistrar?\n1-Si\n2-No\nRespuesta : ");
				scanf("%d%c", &opc, &limp);
				if (opc == 1)
				{
					Pedidos.IdCliente = Clientes.IdCliente;
					Pedidos.IdArticulo = Articulos.IdArticulo;
					Pedidos.PVP = Articulos.PVP;
					Pedidos.Cantidad = cant;
					fseek(pf3, 0, SEEK_END);
					fwrite(&Pedidos, sizeof(Pedidos), 1, pf3);
					printf("Pedido Registrado!\n");
					getch();
					return;
				
				}
				else
				{
					printf("\nOperacion Cancelada!\n");
				}
				
			}
		}while (idarticulo != 0);
		printf("\nNºCliente: ");
		scanf("%d%c", &idcliente, &limp);
	}while (idcliente != 0);
	
}
void ProgramaFacturacion()
{
	FILE *pf1, *pf2, *pf3, *pf4;
	int regPed;
	pf3 = fopen("Pedidos.txt", "rb");
	if (pf3 == NULL)
	{
		printf("El fichero de pedidos no existe!\n");
		return;
	}
	pf1 = fopen("Clientes.txt", "rb");
	if (pf1 == NULL)
	{
		printf("El fichero de clientes no existe!");
		return;
	}
	pf2 = fopen("Articulos.txt", "rb");
	if (pf2 == NULL)
	{
		printf("El fichero de articulos no existe!");
		return;
	}
	pf4 = fopen("Resumen.txt", "wb+");
	fseek(pf3, 0, SEEK_END);
	regPed = ftell(pf3) / sizeof(Pedidos);

}

int fCalcularNumeroArticulo(FILE * pf)
{
	ARTICULO reg;
	int id = -1, i, tamArchivo;
	tamArchivo = fCalcularTamanoFicheroArticulo(pf);
	for (i = 0; i < tamArchivo && id == -1; i++) {
		fread(&reg, sizeof(reg), 1, pf);
		if (reg.estado == 0) {
			id = i;
		}
	}
	if (id == -1)
		id = i;
	return id;
}
