#include <plib.h>
#include <chipKITEthernet.h>
#include <IOShieldOled.h>
#include "funciones.h"

#define MAX_LONG_MENSAJE 	8192
#define MAX_LONG_ARRAY		MAX_LONG_MENSAJE / 2

uint8_t mensaje[MAX_LONG_MENSAJE];
char orden[16];
int array_numeros[MAX_LONG_ARRAY];
bool	primer_mensaje = true;

// Declaramos la estructura algoritmo que contiene el nombre de los distintos
// algoritmos y su dirección.
struct  algoritmo {
	char *nombre;
	void (*funcion)(int *, int);
};

struct algoritmo funcion_ordenar[N_ORDENAR] = 
	{
		{"Bubble0", &bubble0},
		{"Bubble1", &bubble1},
		{"Bubble2", &bubble2},
		{"Bubble3", &bubble3},
		{"Quick0", &quick0},
		{"Quick1", &quick1},
		{"Quick2", &quick2},
		{"Quick3", &quick3},
		{"Selection0", &selection0},
		{"Selection1", &selection1},
		{"Selection2", &selection2},
		{"Selection3", &selection3}
	};

// Direccion MAC. Todo 0 indica que se use la del propio ChipKIT
byte mac[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

// Direccion IP
byte ip[] = {
	10,0,0,8 };

//Estos campos estan comentados ya que no necesitamos acceso
//fuera de la red local. En caso de necesitarlo (para acceder
//desde una red externa) se pueden descomentar y cambiar la
//linea Ethernet.begin dentro de la funcion setup por la que
//esta comentada.
//byte router[] = { 10,0,0,1 };
//byte subred[] = { 255, 255, 255, 0 };

// Iniciamos el servidor en el puerto 23 (Telnet)
Server server(23);
// Declaramos al cliente
Client cliente; 

void print_array(int *array, int len);
void selecciona_orden(char *, int);
void array_aleatorio(void);
void ejecuta_orden(int indice_orden, int * array, int lon);
void compara(void);

void setup()
{
	// Inicializamos el dispositivo de red.
	//	Ethernet.begin(mac, ip, router, subred);
	Ethernet.begin(mac,ip);
	// Inicializamos el servidor
	server.begin();
	// Abrimos el puerto serie
	Serial.begin(9600);

	//Inicializamos la pantalla Oled
	IOShieldOled.begin();
	IOShieldOled.setCursor(0, 0);
	IOShieldOled.putString("Sorted ChipKIT");
}

void loop()
{
	cliente = server.available();
	uint long_mensaje = 0;
	int cantidad_num = 0;
	int n = 0;
	int longitud = 0;

	if (cliente)
	{
		if(primer_mensaje)
		{
			cliente.flush();
		}
		mensaje = {0};
		orden = {0};
		array_numeros = {NULL};

		if(cliente.available())
		{
			//Recepcion del mensaje
			char c;
			do
			{
				c = cliente.read();
				if(c != -1)
				{
					mensaje[long_mensaje] = c;
					if(long_mensaje < MAX_LONG_MENSAJE - 1)
					{
						long_mensaje++;
					} else
					{
						cliente.println("Array demasiado largo");
						mensaje = {0};
						long_mensaje = 0;
						break;
					}
				}
			} while(c != '\n');

			Serial.print("Longitud del mensaje: ");
			Serial.println(long_mensaje);

			char numero[16] = {0};
			int j = 0;

			for (int i = 0; i < long_mensaje; ++i)
			{
				if(mensaje[i] == ' '
					|| mensaje[i] == ','
					|| mensaje[i] == '\t'
					|| mensaje[i] == '\r'
					|| mensaje[i] == '\n')
				{
					if(cantidad_num == 0)
					{
						if(i>16)
						{
							cantidad_num = 0;
							break;
						}
						memcpy(orden, mensaje, i);
					} else
					{
						if (mensaje[i - 1] != '\r')
						{
							if(sscanf(numero, "%d", &array_numeros[n]) < 1)
							{
								Serial.println("Error al convertir");
								Serial.print("Num: ");
								Serial.println(numero);
							} else
							{
								n++;
								j = 0;
								numero = {0};
							}
						}

					}
					cantidad_num++;
				} else
				{
					if(cantidad_num > 0)
					{
						numero[j] = mensaje[i];
						j++;
					}
				}
			}

			if(cantidad_num > 0)
			{
				longitud = n;
				Serial.print("Longitud del array: ");
				Serial.println(longitud);
			}

			Serial.println(orden);
		}

		cliente.flush();

		selecciona_orden(orden, longitud);
		if(longitud)
		{
			print_array(array_numeros, longitud);
		}
		primer_mensaje = false;
	}
}

/*
 * Imprime un array por el puerto serie y al cliente conectado por red
 */
void print_array(int *array, int len)
{
	for(int i = 0;i < len; ++i)
	{
		server.print(array[i]);
		Serial.print(array[i]);
		server.print(' ');
		Serial.print(' ');
	}
	server.print('\n');
	Serial.println("");
}

/*
 * En funcion del orden llama a la funcion o realiza la operacion
 * correspondiente a dicho orden.
 */
void selecciona_orden(char *orden, int longitud)
{
	if (!strcmp(orden, "bubble0"))
	{
		ejecuta_orden(0, array_numeros, longitud);
	} else if (!strcmp(orden, "bubble1"))
	{
		ejecuta_orden(1, array_numeros, longitud);
	} else if (!strcmp(orden, "bubble2"))
	{
		ejecuta_orden(2, array_numeros, longitud);
	} else if (!strcmp(orden, "bubble3"))
	{
		ejecuta_orden(3, array_numeros, longitud);
	} else if (!strcmp(orden, "quick0"))
	{
		ejecuta_orden(4, array_numeros, longitud);
	} else if (!strcmp(orden, "quick1"))
	{
		ejecuta_orden(5, array_numeros, longitud);
	} else if (!strcmp(orden, "quick2"))
	{
		ejecuta_orden(6, array_numeros, longitud);
	} else if (!strcmp(orden, "quick3"))
	{
		ejecuta_orden(7, array_numeros, longitud);
	} else if (!strcmp(orden, "sel0"))
	{
		ejecuta_orden(8, array_numeros, longitud);
	} else if (!strcmp(orden, "sel1"))
	{
		ejecuta_orden(9, array_numeros, longitud);
	} else if (!strcmp(orden, "sel2"))
	{
		ejecuta_orden(10, array_numeros, longitud);
	} else if (!strcmp(orden, "sel3"))
	{
		ejecuta_orden(11, array_numeros, longitud);
	} else if (!strcmp(orden, "help"))
	{
		cliente.println("");
		cliente.println("Comandos disponibles:\n");
		cliente.println("bubble0");
		cliente.println("bubble1");
		cliente.println("bubble2");
		cliente.println("bubble3");
		cliente.println("quick0");
		cliente.println("quick1");
		cliente.println("quick2");
		cliente.println("quick3");
		cliente.println("sel0");
		cliente.println("sel1");
		cliente.println("sel2");
		cliente.println("sel3");
		cliente.println("comparar");
		cliente.println("exit");
		cliente.println("");
	} else if (!strcmp(orden, "comparar"))
  {
		compara();
  } else if (!strcmp(orden, "exit"))
	{
		cliente.println("Desconectando...");
		cliente.stop();
		Serial.println("Cliente desconectado");
		primer_mensaje = true;

		IOShieldOled.clear();
		IOShieldOled.setCursor(0, 0);
		IOShieldOled.putString("Sorted ChipKIT");

	} else {
		if(!primer_mensaje) cliente.println("Comando invalido");
	}

}

void ejecuta_orden(int indice_orden, int * array, int lon)
{
	uint32_t cuenta_prev, cuenta_post, ciclos;
	char tiempos[16];
	bool orden_valido = true;

	IOShieldOled.clear();
	IOShieldOled.setCursor(0,0);
	
	//Configuramos el pin 70 (LD1 en la placa IOShield) como salida digital
	TRISAbits.TRISA0 = 0;
	LATAbits.LATA0 = 0;

	LATAbits.LATA0 = 1; // Pin 13 a nivel alto
	cuenta_prev = ReadCoreTimer();
	funcion_ordenar[indice_orden].funcion(array, lon);
	cuenta_post = ReadCoreTimer();
	LATAbits.LATA0 = 0;

	// Numero de ciclos 
	ciclos = 2 * (cuenta_post - cuenta_prev);
	// Envia los resultados al cliente
	cliente.println(funcion_ordenar[indice_orden].nombre);
	cliente.print("Numero de ciclos: ");
	cliente.println(ciclos);
	cliente.print("\n");

	// Muestra los resultados en la pantalla del ChipKIT I/O Shield
	IOShieldOled.putString(funcion_ordenar[indice_orden].nombre);
	IOShieldOled.putString(": ");
	IOShieldOled.setCursor(0,1);
	sprintf(tiempos,"%d ciclos", ciclos);
	IOShieldOled.putString(tiempos);
}

/*
 * Rellena array_numeros con numeros aleatorios
 */
void array_aleatorio(void)
{
	for (int i = 0; i < MAX_LONG_ARRAY; i++)
	{
		array_numeros[i] = (int)random(1L<<(sizeof(int)*8 - 1));
	}
}

/*
 * Genera un array aleatorio y llama a a todas las funciones de ordenacion
 * una por una y muestra los resultados.
 */
void compara(void)
{
	int array_aux[MAX_LONG_ARRAY];
	array_aleatorio();

	for (int i = 0; i < N_ORDENAR; i++) {
		memcpy(array_aux,array_numeros,MAX_LONG_ARRAY);
		ejecuta_orden(i,array_aux,MAX_LONG_ARRAY);
	}
}
