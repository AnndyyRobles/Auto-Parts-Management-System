#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
//DECLARAMOS COLORES QUE USAREMOS DESPUES (SOLO ESTETICA)
#define BLANCO_F   "\x1b[47m"
#define AZUL_T     "\x1b[34m"
#define    AZUL_F      "\x1b[44m"
#define BLANCO_T   "\x1b[37m"
#define NEGRO_T        "\x1b[30m"
#define RESET_COLOR    "\x1b[0m"

HANDLE wHnd; //OBJETO PARA TAMAÑO DE VENTANA

/*SOFTWARE ADMINISTRATIVO QUE LLEVE CONTROL DE MI NEGOCIO*/
//PROTOTIPO DE FUNCIONES DE MI MENU PRINCIPAL
void gotoxy(int x, int y);
void centrar_texto(const char *texto, int y);
int getColor(int number);
int anti_bugeo(const char *cadena);
int layout(int altura, int posicion_Y, int colorear, int ascii);
void imprimir_modelos();
void imprimirCaracter();
void imprimirCabecera();
void logoCarro();
void menu();
//DEFINICION DE STRUCT CLIENTE, GUARDO CLIENTES
struct cliente
{
	char nombre_cliente[55];
	int id_cliente;
	char telefono[25];
	char ciudad[35];
};
int id = 0; //se usara como id con autoincremento
int clientes_agregados = 0; // se usara para contar la cantidad de clientes agregados en el caso 3
//DEFINICION DE MI STRUCT INVENTARIO, GUARDO TODAS MIS PIEZAS DE DIFERENTES MODELOS
struct inventario 
{
	struct pieza* punteros[10];
};
// DIFINICION DE STRUCT DE COTIZACIONES, GUARDO TODAS LAS COTIZACIONES REALIZADAS
struct cotizacion
{
	struct detalle_cotizacion* puntero[5];
};
//PROTOTIPO DE FUNCIONES PARA MI CASE COTIZACION
struct pieza
{
	int no_pieza;
	int precio_pieza;
	int cant_pieza;
	char nombre_pieza[35];
};
struct detalle_cotizacion
{
	int cliente_que_compro;
	int cantidad;
	int no_pieza;
	int precio_pieza;
	char nombre_pieza[25];
	int subtotal;
	float total;
};
int cotizacion(int ID_CLIENTE, struct pieza p[15], struct detalle_cotizacion x[10]);
struct pieza obtener_pieza_por_codigo(int no_pieza, struct pieza p[15]);
//################################

int main()
{
	//DOY TAMAÑO A MI CONSOLA
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, 209, 49};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //###########################################
	//EXTRAS DE DISEÑO
    system("color 9f");
    int cuser = 123, intentos = 0, resp = 0;
    char codigo_ingresado[10];
    logoCarro();printf("\n");  //IMRPIMO LOGO DEL CARRO
    // FUNCIONES DE LAYOUTS
    layout(5,44,1,219);
    layout(2,26,1,219);
    layout(1,28,3,219);
	//VENTANA PRINCIPAL
    centrar_texto(AZUL_F BLANCO_T"Refacciones Triple R  S.A. de C.V.     Version 1.02      Desarrollador: Andres Zahir Rodiguez Robles",46);
    gotoxy(38,46);printf("%c",174);gotoxy(50,46);printf("%c", 174);gotoxy(185,46);printf("%c",175);gotoxy(173,46);printf("%c",175);
    centrar_texto(AZUL_F BLANCO_T"- - - -Bienvenido al Software Administraivo de Refacciones Triple R  S.A de C.V- - - -",30);
    do   // CODIGO DE LOGIN, DANDO 3 INTENTOS
    {
        //AZUL_F BLANCO_T   para color dentro de login
        centrar_texto(AZUL_F BLANCO_T "Ingrese su codigo de usuario: ", 32+intentos);
        scanf("%s", &codigo_ingresado);
		int contra = anti_bugeo(codigo_ingresado); //LA FUNCION ANTI_BUGEO RETORNA O SI EL USUARIO INGRESO UN CARACTER EN VEZ DE UN ENTERO
        if (contra != cuser)
        {
            centrar_texto(AZUL_F BLANCO_T"- - - Codigo incorrecto - - -\n\n",38+intentos);
            intentos++;
        }
        else
        {
            resp = 1;
            break;
        }
    }while(intentos < 3 || resp == 1);
    if(resp == 1)
    {
        menu(); // ENTRA AL MENU PRINCIPAL
    }
    else
    {
        centrar_texto(AZUL_F BLANCO_T"Cierre Automatico, excedio intentos. . .\n",45);
        getch();
    }
}
void menu()
{
	// DEFINO LOS STRUCT QUE USARE DENTRO DE MI PROGRAMA
	struct inventario MiInventario;				//DECLARO MI STRUCT PARA GUARDAR EL INVENTARIO DE MIS PIEZAS
	struct cotizacion cotizaciones;             //DECLARO MI STRUCT PARA GUARDAR LAS COTIZACIONES
	struct detalle_cotizacion Cotizacion1;      //DECLARO MIS STRUCT PARA GENERAR COTIZACIONES
	struct detalle_cotizacion Cotizacion2;
	struct detalle_cotizacion Cotizacion3;
	struct detalle_cotizacion Cotizacion4;
	struct detalle_cotizacion Cotizacion5;
	struct cliente DarAltaCliente[10];			//DECLARO MI STRUCT PARA GUARDAR MIS CLIENTES
	int numero_de_cotizacion = 0; //sera nuestra variable contador dentro del case 4, contara las cotizaciones que se han realizado
	struct pieza LaFerrariAperta[15]=			//STRUCT DE MIS PIEZAS DISPONIBLES
	{
		{1001,5000,99,"Cilindros c/u"},
		{1002,100,59,"Valvulas c/u"},
		{1003,3500,69,"Arbol de levas"},
		{1004,2500,43,"Bomba de combustible"},
		{1005,1500,33,"Radiador"},
		{1006,1200,56,"Alternador"},
		{1007,900,34,"Bomba de agua"},
		{1008,50,87,"Bujias c/u"},
		{1009,30,56,"Filtro de aceite"},
		{1010,500,89,"Correa de Distribucion"},
		{1011,4500,56,"Parachoques"},
		{1012,2500,34,"Faros c/u"},
		{1013,1000,87,"Espejos laterales c/u"},
		{1014,8000,56,"Capo"},
		{1015,6000,89,"Puertas c/u"}
	};
	struct pieza Ferrari335[15]=
	{
		{2001,10000,99,"Cilindros c/u"},
		{2002,150,59,"Valvulas c/u"},
		{2003,5000,69,"Arbol de levas"},
		{2004,3500,43,"Bomba de combustible"},
		{2005,2000,33,"Radiador"},
		{2006,1800,56,"Alternador"},
		{2007,1200,34,"Bomba de agua"},
		{2008,75,87,"Bujias c/u"},
		{2009,50,56,"Filtro de aceite"},
		{2010,1000,89,"Correa de Distribucion"},
		{2011,6500,56,"Parachoques"},
		{2012,3000,34,"Faros c/u"},
		{2013,1500,87,"Espejos laterales c/u"},
		{2014,12000,56,"Capo"},
		{2015,8500,89,"Puertas c/u"}
	};
	struct pieza Ferrari290MMS[15]=
	{
		{3001,8000,99,"Cilindros c/u"},
		{3002,120,59,"Valvulas c/u"},
		{3003,4500,69,"Arbol de levas"},
		{3004,3000,43,"Bomba de combustible"},
		{3005,1800,33,"Radiador"},
		{3006,1500,56,"Alternador"},
		{3007,1000,34,"Bomba de agua"},
		{3008,60,87,"Bujias c/u"},
		{3009,40,56,"Filtro de aceite"},
		{3010,800,89,"Correa de Distribucion"},
		{3011,5500,56,"Parachoques"},
		{3012,2500,34,"Faros c/u"},
		{3013,1200,87,"Espejos laterales c/u"},
		{3014,10000,56,"Capo"},
		{3015,7000,89,"Puertas c/u"}
	};
	struct pieza Ferrari290MM[15]=
	{
		{4001,8000,99,"Cilindros c/u"},
		{4002,120,59,"Valvulas c/u"},
		{4003,4500,69,"Arbol de levas"},
		{4004,3000,43,"Bomba de combustible"},
		{4005,1800,33,"Radiador"},
		{4006,1500,56,"Alternador"},
		{4007,1000,34,"Bomba de agua"},
		{4008,60,87,"Bujias c/u"},
		{4009,40,56,"Filtro de aceite"},
		{4010,800,89,"Correa de Distribucion"},
		{4011,5500,56,"Parachoques"},
		{4012,2500,34,"Faros c/u"},
		{4013,1200,87,"Espejos laterales c/u"},
		{4014,10000,56,"Capo"},
		{4015,7000,89,"Puertas c/u"}
	};
	struct pieza Ferrari275[15]=
	{
		{5001,2500,99,"Cilindros c/u"},
		{5002,80,59,"Valvulas c/u"},
		{5003,3000,69,"Arbol de levas"},
		{5004,500,43,"Bomba de combustible"},
		{5005,1500,33,"Radiador"},
		{5006,400,56,"Alternador"},
		{5007,350,34,"Bomba de agua"},
		{5008,20,87,"Bujias c/u"},
		{5009,25,56,"Filtro de aceite"},
		{5010,150,89,"Correa de Distribucion"},
		{5011,2000,56,"Parachoques"},
		{5012,800,34,"Faros c/u"},
		{5013,500,87,"Espejos laterales c/u"},
		{5014,4000,56,"Capo"},
		{5015,3500,89,"Puertas c/u"}
	};
	struct pieza Ferrari250California[15]=
	{
		{6001,2200,99,"Cilindros c/u"},
		{6002,75,59,"Valvulas c/u"},
		{6003,2800,69,"Arbol de levas"},
		{6004,450,43,"Bomba de combustible"},
		{6005,1200,33,"Radiador"},
		{6006,350,56,"Alternador"},
		{6007,300,34,"Bomba de agua"},
		{6008,18,87,"Bujias c/u"},
		{6009,20,56,"Filtro de aceite"},
		{6010,125,89,"Correa de Distribucion"},
		{6011,1800,56,"Parachoques"},
		{6012,700,34,"Faros c/u"},
		{6013,450,87,"Espejos laterales c/u"},
		{6014,3500,56,"Capo"},
		{6015,3000,89,"Puertas c/u"}
	};
	struct pieza Ferrari375[15]=
	{
		{7001,3000,99,"Cilindros c/u"},
		{7002,90,59,"Valvulas c/u"},
		{7003,3500,69,"Arbol de levas"},
		{7004,550,43,"Bomba de combustible"},
		{7005,1800,33,"Radiador"},
		{7006,450,56,"Alternador"},
		{7007,400,34,"Bomba de agua"},
		{7008,25,87,"Bujias c/u"},
		{7009,30,56,"Filtro de aceite"},
		{7010,200,89,"Correa de Distribucion"},
		{7011,2500,56,"Parachoques"},
		{7012,1000,34,"Faros c/u"},
		{7013,600,87,"Espejos laterales c/u"},
		{7014,5000,56,"Capo"},
		{7015,4000,89,"Puertas c/u"}
	};
	struct pieza Ferrari250Testa[15]=
	{
		{8001,2800,99,"Cilindros c/u"},
		{8002,100,59,"Valvulas c/u"},
		{8003,3200,69,"Arbol de levas"},
		{8004,500,43,"Bomba de combustible"},
		{8005,1500,33,"Radiador"},
		{8006,400,56,"Alternador"},
		{8007,350,34,"Bomba de agua"},
		{8008,22,87,"Bujias c/u"},
		{8009,27,56,"Filtro de aceite"},
		{8010,175,89,"Correa de Distribucion"},
		{8011,2200,56,"Parachoques"},
		{8012,900,34,"Faros c/u"},
		{8013,550,87,"Espejos laterales c/u"},
		{8014,4500,56,"Capo"},
		{8015,3800,89,"Puertas c/u"}
	};
	struct pieza Ferrari250SWB[15]=
	{
		{9001,1500,99,"Cilindros c/u"},
		{9002,60,59,"Valvulas c/u"},
		{9003,2500,69,"Arbol de levas"},
		{9004,300,43,"Bomba de combustible"},
		{9005,1100,33,"Radiador"},
		{9006,350,56,"Alternador"},
		{9007,300,34,"Bomba de agua"},
		{9008,20,87,"Bujias c/u"},
		{9009,25,56,"Filtro de aceite"},
		{9010,130,89,"Correa de Distribucion"},
		{9011,1200,56,"Parachoques"},
		{9012,500,34,"Faros c/u"},
		{9013,400,87,"Espejos laterales c/u"},
		{9014,4000,56,"Capo"},
		{9015,3500,89,"Puertas c/u"}
	};
	struct pieza Ferrari250LWB[15]=
	{
		{10001,1000,99,"Cilindros c/u"},
		{10002,50,59,"Valvulas c/u"},
		{10003,2500,69,"Arbol de levas"},
		{10004,300,43,"Bomba de combustible"},
		{10005,1000,33,"Radiador"},
		{10006,500,56,"Alternador"},
		{10007,300,34,"Bomba de agua"},
		{10008,20,87,"Bujias c/u"},
		{10009,25,56,"Filtro de aceite"},
		{10010,100,89,"Correa de Distribucion"},
		{10011,1000,56,"Parachoques"},
		{10012,500,34,"Faros c/u"},
		{10013,400,87,"Espejos laterales c/u"},
		{10014,5000,56,"Capo"},
		{10015,4500,89,"Puertas c/u"}
	};
	//ASIGNACION... de punteros a mi struct inventario
	MiInventario.punteros[0] = LaFerrariAperta;
	MiInventario.punteros[1] = Ferrari335;
	MiInventario.punteros[2] = Ferrari290MMS;
	MiInventario.punteros[3] = Ferrari290MM;
	MiInventario.punteros[4] = Ferrari275;
	MiInventario.punteros[5] = Ferrari250California;
	MiInventario.punteros[6] = Ferrari375;
	MiInventario.punteros[7] = Ferrari250Testa;
	MiInventario.punteros[8] = Ferrari250SWB;
	MiInventario.punteros[9] = Ferrari250LWB;
	//ASIGNACION... de punteros a mi struct cotizacion
	cotizaciones.puntero[0] = &Cotizacion1;
	cotizaciones.puntero[1] = &Cotizacion2;
	cotizaciones.puntero[2] = &Cotizacion3;
	cotizaciones.puntero[3] = &Cotizacion4;
	cotizaciones.puntero[4] = &Cotizacion5;
    int opc = 0;
    do
    {
        system("cls");
        layout(1,2,3,219);
        layout(3,4,3,219);
        layout(1,7,7,219);
        layout(1,46,1,219);
        layout(1,48,3,219);
        centrar_texto(AZUL_F BLANCO_T"Refacciones Triple R  S.A. de C.V.     Version 1.02      Desarrollador: Andres Zahir Rodiguez Robles",46);
	    gotoxy(38,46);printf("%c",174);gotoxy(50,46);printf("%c", 174);gotoxy(185,46);printf("%c",175);gotoxy(173,46);printf("%c",175);
        centrar_texto("- - - - REPARACIONES TRIPLE R - - - -", 14);
        centrar_texto("Seleccione una de las siguientes", 16);
        centrar_texto("opciones de acuerdo a lo que necesite", 18);
        centrar_texto("1.- Revisar Inventario", 21);
        centrar_texto("2.- Agregar piezas al inventario", 23);
        centrar_texto("3.- Agregar clientes", 25);
        centrar_texto("4.- Cotizacion de piezas", 27);
        centrar_texto("5.- Comprar modelo nuevo", 29);
    	centrar_texto("Opcion: ", 32);
        scanf("%d", &opc);
        switch(opc)
        {
        	case 1:
        		system("cls");
            	char nombre_de_modelos[10][30];
				strcpy(nombre_de_modelos[0], "LaFerrariAperta");
			    strcpy(nombre_de_modelos[1], "Ferrari335");
			    strcpy(nombre_de_modelos[2], "Ferrari290MMS");
			    strcpy(nombre_de_modelos[3], "Ferrari290MM");
			    strcpy(nombre_de_modelos[4], "Ferrari275");
			    strcpy(nombre_de_modelos[5], "Ferrari250California");
			    strcpy(nombre_de_modelos[6], "Ferrari375");
			    strcpy(nombre_de_modelos[7], "Ferrari250Testa");
			    strcpy(nombre_de_modelos[8], "Ferrari250SWB");
			    strcpy(nombre_de_modelos[9], "Ferrari250LWB");
				printf("Inventario:\n");
			    imprimirCaracter();printf("\n");
			    for(int i = 0; i<10; i++)
			    {
			    	
			    	printf("Piezas de %s:\n", nombre_de_modelos[i]);
			    	imprimirCabecera();
			    	struct pieza *Modelo = MiInventario.punteros[i];
			    	for(int cont = 0; cont < 15; cont++)
			    	{
			        	printf("%i\t%-9c\t%-9i\t%-9c\t%-9i\t%-9c\t%-9s\n", Modelo[cont].no_pieza, 179, Modelo[cont].precio_pieza, 179, Modelo[cont].cant_pieza, 179, Modelo[cont].nombre_pieza);
					}
					imprimirCaracter();printf("\n");
				}
				char digite1[10];
				salir1:
    			printf("\n\nPresione 1 para salir al menu... ");
			    scanf("%s", digite1);
			    int resultado = anti_bugeo(digite1);
			    if (resultado == 0) 
				{
			        printf("ERROR");
			        goto salir1;
			    } 
			    break;
            case 2:
            	system("cls");
            	int opc, pieza_a_modificar, elecc, nuevo_precio, nuevo_existencias, seguir;
            	char elegir_modelo[10], elegir_numero_pieza[10], que_modificar[10];
                system("cls");
                printf("Agregar piezas al inventario...\n");
                imprimir_modelos(); printf("\n");
                elegir_modelo:
                printf("Eliga en que modelo agregara piezas a su inventario:\n");
                scanf("%s", elegir_modelo);
			    opc = anti_bugeo(elegir_modelo);
			    if (opc == 0) 
				{
			        printf("ERROR\n");
			        goto elegir_modelo;
			    } 
            	else if(opc >= 1 && opc <= 10)
				{
					struct pieza *structSeleccionado = MiInventario.punteros[opc - 1];
					printf("A continuacion se mostrara el inventario para ese modelo de auto...\n");
					printf("%s\t%-9c\t%-9s\t%-9c\t%-9s\t%-9c\t%-9s\t%-9c\t%-9s\n","No:", 179, "Codigo:", 179, "Precio:", 179, "Existencias:", 179, "Nombre:");
					for(int cont = 0; cont < 15; cont++)
               		{
               			
               			printf("%i\t%-9c\t%-9i\t%-9c\t%-9i\t%-9c\t%-9i\t%-9c\t%-9s\n", cont+1, 179, structSeleccionado[cont].no_pieza, 179, structSeleccionado[cont].precio_pieza, 179, structSeleccionado[cont].cant_pieza, 179, structSeleccionado[cont].nombre_pieza);
					}
					repetir_do_while:
					do
					{
						printf("Selecciona el numero de pieza que quieres modificar: ");
						scanf("%s", elegir_numero_pieza);
						pieza_a_modificar = anti_bugeo(elegir_numero_pieza);
					    if (pieza_a_modificar == 0) 
						{
					        printf("ERROR\n");
					        goto repetir_do_while;
					    } 
						else if(pieza_a_modificar >0 && pieza_a_modificar <16)
						{
							repetir_if:
							printf("Que es lo que quiere modificar?\n1. Precio\n2. Existencias\n");
							scanf("%s", que_modificar);
						    elecc = anti_bugeo(que_modificar);
						    if (elecc == 0) 
							{
						        printf("ERROR\n");
						        goto repetir_if;
						    } 
							if(elecc == 1)
							{
								printf("El precio actual de la pieza %s es: %i\nDigite el precio nuevo: ", structSeleccionado[pieza_a_modificar-1].nombre_pieza, structSeleccionado[pieza_a_modificar-1].precio_pieza);
								scanf("%i", &nuevo_precio);
								structSeleccionado[pieza_a_modificar-1].precio_pieza = nuevo_precio;
								printf("\nEl precio se modificado correctamente...El precio nuevo de la pieza %s es: %i\n", structSeleccionado[pieza_a_modificar-1].nombre_pieza, structSeleccionado[pieza_a_modificar-1].precio_pieza);
							}
							else if(elecc == 2)
							{
								printf("Las existencias actuales de la pieza %s son: %i\nDigite la nueva cantidad de existencias: ", structSeleccionado[pieza_a_modificar-1].nombre_pieza, structSeleccionado[pieza_a_modificar-1].cant_pieza);
								scanf("%i", &nuevo_existencias);
								structSeleccionado[pieza_a_modificar-1].cant_pieza = nuevo_existencias;
								printf("\nLas existencias se han modificado correctamente...Las existencias de la pieza %s son: %i\n", structSeleccionado[pieza_a_modificar-1].nombre_pieza, structSeleccionado[pieza_a_modificar-1].cant_pieza);
							}
							printf("Quiere modificar el precio o existencias de otra pieza?\n1. Si\n2. No\n");
							scanf("%i", &elecc);
						}
					}while(elecc == 1);
				}
                break;
            case 3:
                system("cls");
                int enter;
                char enter_salir[100];
                printf("Agregar clientes\n");
                DarAltaCliente[id].id_cliente = id + 1;
                printf("Nombre del cliente:\n");
                scanf_s("%54s", &DarAltaCliente[id].nombre_cliente, 55);   //funcion scanf_s para evitar desbordamiento de buffer
                printf("Telefono:\n");
                scanf_s("%24s", &DarAltaCliente[id].telefono, 25);
                printf("Ciudad: ");
                scanf_s("%34s", &DarAltaCliente[id].ciudad, 35);
                printf("Cliente guardado con exito!\n");
                printf("Id Cliente: %i\n", DarAltaCliente[id].id_cliente);
			    printf("Nombre: %s\n", DarAltaCliente[id].nombre_cliente);
			    printf("Telefono: %s\n", DarAltaCliente[id].telefono);
			    printf("Telefono: %s\n", DarAltaCliente[id].ciudad);
			    id++;  //Incremento el indice de mi struct cliente DarAltaCliente
			    clientes_agregados++; //incremento el numero de clientes agregados
			    salir3:
				printf("Presiona 1 para regresar al menu...");
				scanf("%s", enter_salir);
			    enter = anti_bugeo(enter_salir);
			    if (enter == 0) 
				{
			        printf("ERROR\n");
			        goto salir3;
			    } 
                break;
            case 4:
                system("cls");
                printf("Cotizacion de piezas\n");
                int opcion, saliir, cliente_encontrado = 0;
                char elegir_opcion[10], elegir_saliir[10], ingrese_cliente[10];
				imprimir_modelos();
				printf("Depende el modelo de auto que eliga, las piezas del motor cambiaran su precio\n");
				seleccione:
				printf("Seleccione la marca del auto: ");
				scanf("%s", elegir_opcion);
				opcion = anti_bugeo(elegir_opcion);
				if (opcion == 0) 
				{
					printf("ERROR\n");
					goto seleccione;
				} 
				if(opcion>0 && opcion<11)
				{
					ingrese_id:
					printf("Ingrese el id del cliente donde se almacenara esta cotizacion: ");
					scanf("%s", ingrese_cliente);
					int ID_cliente = anti_bugeo(ingrese_cliente);
					if (ID_cliente == 0) 
					{
						printf("ERROR * * * SOLO NUMEROS ENTEROS\n");       //Primero vemos si el suuario ingreso un entero o ingreso caracteres
						goto ingrese_id;
					} 
					else
					{
						if (clientes_agregados == 0) 
						{
	        				printf("\nID cliente no encontrado, dar de alta al cliento primero....\n");  //Rectificamos si hay clientes agregados... si no, cierra
	        			} 
						else
						{
							for(int iterar_cliente = 0; iterar_cliente<10; iterar_cliente++)
							{
								if(ID_cliente == DarAltaCliente[iterar_cliente].id_cliente)
								{
									cliente_encontrado = 1;
									struct pieza *modelo_a_cotizar = MiInventario.punteros[opcion-1];
									struct detalle_cotizacion *productos_cotizacion= cotizaciones.puntero[numero_de_cotizacion]; 
									numero_de_cotizacion++;
									cotizacion(ID_cliente, modelo_a_cotizar, productos_cotizacion); //ENTRA LA FUNCION DE COTIZACION * * * *
								}
							}
						}
					}
				}
				salir4:
				printf("\n\nPresione 1 para salir al menu... ");
				scanf("%s", elegir_saliir);
				saliir = anti_bugeo(elegir_saliir);
				if (saliir == 0) 
				{
					printf("ERROR\n");
					goto salir4;
				} 
                break;
            case 5:
                system("cls");
                int saliirr;
                printf("Comprar modelo nuevo...\n");
                printf("LaFerrari Aperta - $4.7 millones\n");
                printf("Ferrari 335 Sport Scaglietti - $35.7 millones\n");
                printf("Ferrari 290 MM Scaglietti - $28 millones\n");
                printf("Ferrari 290 MM - $22.0 millones\n");
                printf("Ferrari 275 GTB/C Speciale - $26.4 millones\n");
                printf("Ferrari 250 GT California Spyder SWB - $18.5 millones\n");
                printf("Ferrari 375-Plus Spider Competizione - $18.4 millones\n");
                printf("Ferrari 250 Testa Rossa - $16.4 millones\n");
                printf("Ferrari 250 GT SWB Berlinetta Speciale - $16.5 millones\n");
                printf("Ferrari 250 GT LWB California Spider Competizione - $14.3 millones\n\n");
                printf("\n\nPresione 1 para salir al menu... ");
				scanf("%i", &saliirr);
                break;
            default:
                system("cls");
                printf("Opcion no valida");
                getch();
                break;
        }
    }while(opc > 0 && opc < 6);
}
// FUNCION DE GOTOXY
void gotoxy(int x, int y)
{
    //control para ventana y manipulacion de consola
    HANDLE ventana;
    ventana = GetStdHandle(STD_OUTPUT_HANDLE);
    //creamos objeto de las cordenadas dentro de una estructura
    COORD cordenadas;
    cordenadas.X = x;
    cordenadas.Y = y;
    //posicionamos el mensaje dentro de nuestra consola, a nuestra ventana con las coordenadas dadas
    SetConsoleCursorPosition(ventana,cordenadas);
}
// FUNCION DE CENTRADO DE TEXTO SABIENDO LA LONGITUD D ELA CONSOLA
void centrar_texto(const char *texto, int y)
{
    int tamano_de_texto = strlen(texto);
    gotoxy((216-tamano_de_texto)/2,y);printf("%s", texto);
}

//IMPRESION DE LOGO DEL AUTOMOVIL
void logoCarro()
{
    int matrizcarro[25][182]={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,2,2,1,1,1,1,1,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,2,2,2,1,1,3,3,3,3,6,6,6,3,3,3,3,3,3,3,3,3,3,3,1,4,2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,3,3,3,6,6,6,3,3,3,3,3,3,3,3,3,3,6,3,3,3,1,4,2,2,1,1,2,2,2,2,2,1,1,1,1,1,1,2,2,4,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,3,3,3,6,6,3,3,3,3,3,3,3,3,3,3,6,6,6,3,3,3,1,1,4,4,2,1,4,1,1,2,2,2,2,2,2,2,2,2,2,2,2,4,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,4,4,4,4,4,4,4,4,4,2,2,2,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,4,4,4,2,2,2,1,4,1,1,2,2,2,2,2,2,2,2,2,2,5,5,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,5,5,2,2,2,2,2,2,2,2,2,2,2,2,2,4,4,4,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,4,4,2,2,2,2,2,2,2,1,4,2,2,2,2,2,2,2,2,2,2,5,5,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,1,1,5,5,5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,4,4,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,4,4,4,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,4,4,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,2,2,2,2,2,2,2,2,2,1,4,2,2,2,2,2,2,2,2,2,2,1,1,1,2,2,2,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,4,4,4,2,2,2,2,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,4,4,2,2,2,2,2,2,1,1,1,1,3,3,1,3,3,3,1,1,1,1,1,4,4,2,2,2,2,2,2,2,2,1,4,2,2,2,2,2,2,2,2,2,2,1,4,4,2,2,2,1,1,2,2,2,2,1,1,1,1,3,3,1,3,3,1,1,1,1,1,1,4,4,2,2,4,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,1,1,1,3,3,3,1,3,3,3,1,1,1,1,1,1,4,2,2,2,2,2,2,2,1,1,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,1,1,3,1,1,3,1,3,1,1,3,3,1,1,1,1,4,2,2,4,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,2,2,2,2,2,2,2,1,1,3,3,3,3,1,3,1,1,1,3,3,1,1,1,4,2,2,2,2,2,2,2,1,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,4,2,2,1,1,1,3,3,3,1,1,1,1,3,3,3,3,1,1,1,4,4,4,4,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,2,2,2,2,2,2,4,1,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,4,4,2,2,2,2,2,1,1,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,1,4,2,2,1,1,1,3,3,3,1,1,1,1,1,1,1,3,1,1,1,4,4,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,2,2,2,2,2,2,4,1,1,3,3,3,1,1,1,1,3,3,3,3,1,1,1,4,4,2,2,2,2,2,1,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,4,4,1,4,2,4,1,1,1,3,1,1,1,3,1,3,3,3,1,1,1,1,1,4,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,2,2,2,2,4,4,4,1,1,3,3,1,1,3,3,1,1,3,3,1,1,1,4,4,4,4,4,4,2,2,1,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,4,4,1,1,4,4,2,4,4,1,1,1,1,3,3,3,1,3,3,3,3,1,1,1,4,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,4,4,4,4,4,1,1,1,1,1,3,3,1,3,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    int color;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const int INITIAL_X_POINT = 13;
    for(int k = 0; k<25; k++)
    {
        for(int u=0; u<INITIAL_X_POINT; u++)
        {
            printf("%c", 219);
            SetConsoleTextAttribute(hConsole, 9);

        }
        for(int g = 0; g<182; g++)
        {
            SetConsoleTextAttribute(hConsole,getColor(matrizcarro[k][g]));
            printf("%c", 219);
        }
        printf("\n");
    }
}
void imprimir_modelos()
{
	printf("1. LaFerrari Aperta\n2. Ferrari 335 Sport Scaglietti\n");
	printf("3. Ferrari 290 MM Scaglietti\n4. Ferrari 290 MM\n");
	printf("5. Ferrari 275 GTB/C Speciale\n6. Ferrari 250 GT California Spyder SWB\n");
	printf("7. Ferrari 375-Plus Spider Competizione\n8. Ferrari 250 Testa Rossa\n");
	printf("9. Ferrari 250 GT SWB Berlinetta Speciale\n10. Ferrari 250 GT LWB California Spider Competizione\n");
}
void imprimirCaracter() 
{
    int i;
    for (i = 0; i < 115; i++) 
	{
        printf("%c", 223);
    }
}
void imprimirCabecera()
{
	printf("\n%s\t%-9c\t%-9s\t%-9c\t%-9s\t%-9c\t%-9s\n","Codigo:", 179, "Precio:", 179, "Existencias:", 179, "Nombre:");
}
// FUNCION PARA GENERAR LAYOUTS, PARTE ESTETICA DEL PROGRAMA
int layout(int altura, int posicion_Y, int colorear, int ascii)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int h = 0; h<altura; h++)
    {
        int posicion_X = 0;
        gotoxy(0,posicion_Y);
        for(int v = 0; v<209; v++)
        {
            gotoxy(posicion_X,posicion_Y+h);
            SetConsoleTextAttribute(hConsole,colorear);
            printf("%c",ascii);
            posicion_X++;
        }
        printf("\n");
    }
}
// CREAMOS UNA FUNCION PARA VERIFICAR SI LO QUE EL USUARIO PUSO ES UN VALOR ENTERO O ES UN CARACTER,
// ASI EVITAMOS QUE EL CODIGO TRUENE
int anti_bugeo(const char *cadena) {
    int longitud = 0;
    bool todos_son_enteros = true;
    
    // CALCULAMOS EL TAMAÑO DE LA CADENA
    while (cadena[longitud] != '\0') {
        longitud++;
    }
    
    // REVISAMOS QUE TODOS LOS CARACTERES DE LA CADENA SEAN ENTEROS
    for (int i = 0; i < longitud; i++) {
        if (!isdigit(cadena[i])) {
            todos_son_enteros = false;
            break;
        }
    }
    
    if (!todos_son_enteros) 
	{
        return 0; // CADENA QUE NO TODOS SUS CARACTERES SON ENTEROS
    } else if (todos_son_enteros) 
	{
        return atoi(cadena);; // CADENA QUE TODOS SUS ENTEROS SON NUMEROS ENTEROS
    } else 
	{
        return 0; 
    }
}
// FUNCION PARA LEER COLOR DEPENDIENDO EL NUMERO ENTERO QUE SE ENCUENTRE EN LA MATRIZ
int getColor(int number)
{
    int color;
    switch(number)
    {
        case 1:
            color = 0;
            break;
        case 2:
            color = 14;
            break;
        case 3:
            color = 8;
            break;
        case 4:
            color = 6;
            break;
        case 5:
            color = 4;
            break;
        case 6:
            color = 15;
            break;
        case 0:
            color = 9;
            break;
    }
    return(color);
}
// FUNCIONES PARA REALIZAR LA COTIZACION
int cotizacion(int ID_CLIENTE, struct pieza p[15], struct detalle_cotizacion x[10]) //funcion con paso de prametros
{
	//struct detalle_cotizacion *productos_cotizacion= cotizaciones.puntero[numero_de_cotizacion]; 
	int opc, n_productos = 1;
	//int numero_de_cotizacion += 0, iterar_cliente, ID_cliente;
	//char ingrese_cliente[10];
	/*ingrese_id:
	printf("Ingrese el id del cliente donde se almacenara esta cotizacion: ");
	scanf("%s", ingrese_cliente);
	ID_cliente = anti_bugeo(ingrese_cliente);
	if (ID_cliente == 0) 
	{
		printf("ERROR * * * SOLO NUMEROS ENTEROS");
		goto ingrese_id;
	} 
	for(iterar_cliente = 0; i<10; i++)
	{
		if(ID_cliente = DarAltaCliente[i].id_cliente)
		{*/
	/*struct cotizacion
	{
		struct detalle_cotizacion * puntero[10];
	}*/
	do
	{
		int codigo, precio, coti, cant_piezas;
		float coti_iva;
		int indice = n_productos - 1;
		char seleccionar_pieza[10];
		//printf("\n");
		printf("\n%s\t%-9c\t%-9s\t%-9c\t%-9s\n","Codigo:", 179, "Existencias:", 179, "Nombre:");
		//printf("Codigo:\tNombre:\tExistencias:\n");
		for(int i=0;i<15;i++)
		{
			printf("%i\t%-9c\t%-9i\t%-9c\t%-9s\n",p[i].no_pieza, 179, p[i].cant_pieza, 179, p[i].nombre_pieza);
		}
		printf("Ingrese el codigo de la pieza: ");
		scanf("%i",&codigo);
		
		struct pieza pieza_encontrada = obtener_pieza_por_codigo(codigo, p); //busca coincidencias entre el codigo de la pieza y el numero de pieza de mi struct pieza p
		
		if(strcmp(pieza_encontrada.nombre_pieza, "NO_ENCONTRADA") == 0)
		{
			printf("Codigo no encontrado vuelva a digitarlo");
			continue;
		}
		
		printf("Ingrese la cantidad de piezas: ");
		scanf("%i",&cant_piezas);
				
		precio = pieza_encontrada.precio_pieza;
		coti = precio*cant_piezas;
		coti_iva = (coti*0.16)+coti;
		
		//int cliente_que_compro;
		//insertar valores al struct, detalles a la cotizacion
		x[indice].cliente_que_compro = ID_CLIENTE;
		x[indice].cantidad=cant_piezas;
		x[indice].no_pieza=pieza_encontrada.no_pieza;
		x[indice].precio_pieza=pieza_encontrada.precio_pieza;
		strcpy(x[indice].nombre_pieza, pieza_encontrada.nombre_pieza);
		x[indice].subtotal=coti;
		x[indice].total=coti_iva;
		otra_pieza:
		printf("Desea agregar otra pieza?\n1. Si\n2. No\n");
		scanf("%s", seleccionar_pieza);
		opc = anti_bugeo(seleccionar_pieza);
		if (opc == 0) 
		{
			printf("ERROR\n");
			goto otra_pieza;
		} 
		if (opc != 1 && opc != 2) 
		{
			printf("ERROR\n");
			goto otra_pieza;
		} 
		n_productos++; //para ir incrementando el indice 
	}while(opc==1);
	
	// Imprimir cotizacion
	system("cls");
	printf("*****************************************\n");
    printf("*               COTIZACION              *\n");
    printf("*****************************************\n");
	//Declaramos las variables para imprimir un ticket final
	int cantidad_productos = 0;
	int subtotal = 0;
	float total = 0;
	
	for(int i = 0; i<n_productos-1;i++)
	{
		printf("No_Pieza: %i\n", x[i].no_pieza);
	    printf("Nombre de Pieza: %s\n", x[i].nombre_pieza);
	    printf("Precio: %i\n", x[i].precio_pieza);
	    printf("Cantidad: %i\n", x[i].cantidad);
	    printf("Subtotal: $%i\n", x[i].subtotal);
	    printf("Total: $%f\n", x[i].total);
	    printf("-----------------------------------------\n");
		cantidad_productos += x[i].cantidad;
		subtotal += x[i].subtotal;
		total += x[i].total;
	}
	printf("-----------------------------------------\n");
	printf("-----------------------------------------\n");
	printf("Total de productos: %i\n", cantidad_productos);
    printf("Subtotal: $%i\n", subtotal);
    printf("-----------------------------------------\n");
    printf("Total: $%.2f\n", total);
    printf("*****************************************\n");
    //numero_de_cotizacion++;
}

struct pieza obtener_pieza_por_codigo(int no_pieza, struct pieza p[15]) 
{                                                                
	for(int i = 0;i<15;i++)
	{
		if(no_pieza==p[i].no_pieza)
		{            
			return p[i];
		}       
	}
	struct pieza pieza_error = {0, 0, 0, "NO_ENCONTRADA"};
	return pieza_error;
}
//#################################################33