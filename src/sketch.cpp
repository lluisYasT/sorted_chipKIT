#include <chipKITEthernet.h>
#include <IOShieldOled.h>
#include "funciones.h"

#define MAX_LONG_MENSAJE 	8192
#define MAX_LONG_ARRAY		MAX_LONG_MENSAJE / 2
#define N_ORDENAR					12 //Numero de funciones para ordenar

uint8_t mensaje[MAX_LONG_MENSAJE];
char comando[16];
int array_numeros[MAX_LONG_ARRAY];
bool	primer_mensaje = true;

void (*fcomando[N_ORDENAR])(int *, int) =
					{	bubble0,
						bubble1,
						bubble2,
						bubble3,
						quick0,
						quick1,
						quick2,
						quick3,
						selection0,
						selection1,
						selection2,
						selection3 };
const char nombres_funciones[N_ORDENAR][12] =
					{	"Bubble0",
						"Bubble1",
						"Bubble2",
						"Bubble3",
						"Quick0",
						"Quick1",
						"Quick2",
						"Quick3",
						"Selection0",
						"Selection1",
						"Selection2",
						"Selection3"
					};


// Enter a MAC address and IP address for your controller below.
// A zero MAC address means that the chipKIT MAC is to be used
byte mac[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

//			 !!MODIFY THIS!!
// The IP address will be dependent on your local network:
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
void selecciona_comando(char *, int);
void array_aleatorio(void);
void ejecuta_comando(int indice_comando, int * array, int lon);
void compara(int * array, int lon);

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
		comando = {0};
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
							//num_comando = NOP;
							cantidad_num = 0;
							break;
						}
						memcpy(comando, mensaje, i);
						//num_comando = deco_comando();
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

			Serial.println(comando);
		}

		cliente.flush();

		selecciona_comando(comando, longitud);
		if(longitud)
		{
			print_array(array_numeros, longitud);
		}
		primer_mensaje = false;
	}
}

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

void selecciona_comando(char *comando, int longitud)
{
	if (!strcmp(comando, "bubble0"))
	{
		ejecuta_comando(0, array_numeros, longitud);
	} else if (!strcmp(comando, "bubble1"))
	{
		ejecuta_comando(1, array_numeros, longitud);
	} else if (!strcmp(comando, "bubble2"))
	{
		ejecuta_comando(2, array_numeros, longitud);
	} else if (!strcmp(comando, "bubble3"))
	{
		ejecuta_comando(3, array_numeros, longitud);
	} else if (!strcmp(comando, "quick0"))
	{
		ejecuta_comando(4, array_numeros, longitud);
	} else if (!strcmp(comando, "quick1"))
	{
		ejecuta_comando(5, array_numeros, longitud);
	} else if (!strcmp(comando, "quick2"))
	{
		ejecuta_comando(6, array_numeros, longitud);
	} else if (!strcmp(comando, "quick3"))
	{
		ejecuta_comando(7, array_numeros, longitud);
	} else if (!strcmp(comando, "sel0"))
	{
		ejecuta_comando(8, array_numeros, longitud);
	} else if (!strcmp(comando, "sel1"))
	{
		ejecuta_comando(9, array_numeros, longitud);
	} else if (!strcmp(comando, "sel2"))
	{
		ejecuta_comando(10, array_numeros, longitud);
	} else if (!strcmp(comando, "sel3"))
	{
		ejecuta_comando(11, array_numeros, longitud);
	} else if (!strcmp(comando, "help"))
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
	} else if (!strcmp(comando, "comparar"))
  {
     // return COMP;
  } else if (!strcmp(comando, "exit"))
	{
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

void ejecuta_comando(int indice_comando, int * array, int lon)
{
	uint16_t antes_micros, despues_micros, antes_millis, despues_millis;
	char tiempos[16];
	bool comando_valido = true;

	IOShieldOled.clear();
	IOShieldOled.setCursor(0,0);
	
	//Configuramos el pin 70 (LD1 en la placa IOShield) como salida digital
	TRISAbits.TRISA0 = 0;
	LATAbits.LATA0 = 0;

	antes_micros = micros();
	antes_millis = millis();
	LATAbits.LATA0 = 1;
	(*fcomando[indice_comando])(array, lon);
	LATAbits.LATA0 = 0;
	despues_micros = micros();
	despues_millis = millis();

	cliente.print("Tiempo en microsegundos: ");
	cliente.println(despues_micros - antes_micros);
	cliente.print("Tiempo en milisegundos: ");
	cliente.println(despues_millis - antes_millis);

	IOShieldOled.putString("Tiempos");
	IOShieldOled.setCursor(0,1);
	sprintf(tiempos,"%d ms - %d us", despues_millis - antes_millis, despues_micros - antes_micros);
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

void compara(int * array, int lon)
{
	int array_aux[MAX_LONG_ARRAY];
	for (int i = 0; i < N_ORDENAR; i++) {
		memcpy(array_aux,array,lon);
		/* code */
		ejecuta_comando(i,array_aux,lon);
	}
}
