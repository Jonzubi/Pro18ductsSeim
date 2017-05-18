#include "Funciones.h"

main()
{
	int opc, opc1, opc2, opc3, opc4;
	void(*ptr_fun_cli[3])() = { AltaCliente,ModifiCliente,ConsulCliente };
	void(*ptr_fun_art[3])() = { AltaArticulo,ModifiArticulo,ConsulArticulo };
	opc=MenuPrincipal();
	while (opc != 5)
	{
		switch (opc)
		{
		case 1:opc1 = MenuClientes();
			while (opc1 != 4)
			{
				(*ptr_fun_cli[opc1 - 1])();
				opc1 = MenuClientes();
			}
			break;
		case 2:opc2 = MenuArticulos();
			while (opc2 != 4)
			{
				(*ptr_fun_art[opc2 - 1])();
				opc2 = MenuArticulos();
			}
			break;
		case 3:ProgramaPedidos();
			break;
		case 4://opc4 = ProgramaFacturacion();
			break;
		}
		opc = MenuPrincipal();
	}
}