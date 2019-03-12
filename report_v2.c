#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main (void) {
	char LOG[46]="/var/log/apache2/error.log";
	FILE *log_file;
	log_file = fopen (LOG, "r");
	char palabra[24];
	char texto[1024];
	char prueba[]="Yo soy una prueba ";
	strcat(texto,prueba);
	int var_control=0;
	int var_limpio=0;
	int temp=0;
	int muestra_datos=0; //Esto indica que el día es mayor, por cual la hora ya no importa mucho validarla :v
	//Variables del usuario inicio:
	int usr_ano_men=0;
	int usr_mes_men=0;
	int usr_dia_men=0;
	int usr_hor_men=0;
	int usr_min_men=0;
	int usr_seg_men=0;
	//Variables del usuario fin del reporte:
	/*
	int usr_ano_may=2019;
	int usr_mes_may=2;
	int usr_dia_may=24;
	int usr_hor_may=10;
	int usr_min_may=0;
	int usr_seg_may=0;
	*/
	//variales_de la bitacora;
	int log_ano=0;
	int log_mes=0;
	int log_dia=0;
	int log_hor=0;
	int log_min=0;
	int log_seg=0;
	if ( log_file == NULL ){
		printf ("\nError de apertura del archivo. \n\n");
	}else{
		//Se solicitan los datos al usuario
		printf("Ingrese apartir de que fecha y hora se extraerá reporte del LOG de errores de apache\n");
		printf("Todos los datos ingresados deben ser númericos.\n\n");
		printf("Año: ");
		scanf("%i", &usr_ano_men);
		printf("Mes: ");
		scanf("%i", &usr_mes_men);
		printf("Día: ");
		scanf("%i", &usr_dia_men);
		printf("Hora: ");
		scanf("%i", &usr_hor_men);
		printf("Minutos: ");
		scanf("%i", &usr_min_men);
		printf("Segundos: ");
		scanf("%i", &usr_seg_men);


		char caracter=fgetc(log_file);
		while (caracter != EOF){
			while (caracter != '\n'){
				if (var_control==0 && caracter=='['){
					var_control=1; //Evita que se vuelva a meter en esta validación hasta encontrar un "enter"
					//Se ignoran los primeros 4 caracteres ya que no se ocuparan
					for (int cont=0; cont<5; cont++){
						caracter=fgetc(log_file);
					}
					//Se comprueban los primeros 3 caracteres que son el mes para pasarlo a números:
					switch (caracter){
						case 'J': 
							caracter=fgetc(log_file);
							var_limpio++;//indica que ya avance 1 caracter.
							if (caracter=='a'){
								//Es January (Enero).
								log_mes=1;
							}else{ //Caracter == u.
								caracter=fgetc(log_file);
								var_limpio++;//indica que ya avance 1 caracter.
								if (caracter=='n'){
									//Es June (Junio)
									log_mes=6;
								}else //Sólo queda l :v
									//Es july (Julio)
									log_mes=7;
							}
							break;
						case 'F':
							//Sólo hay un mes que empieza con F y es: February (Febrero).
							log_mes=2;
							break;
						case 'M':
							caracter=fgetc(log_file);
							var_limpio++;//indica que ya avance 1 caracter.
							//Los dos meses continuan con "a", entonces válido con el 3er caracter
							caracter=fgetc(log_file);
							var_limpio++;//indica que ya avance 1 caracter.
							if (caracter=='r'){
								//Es March (Marzo)
								log_mes=3;
							}else{
								//Es May (Mayo)
								log_mes=5;
							}
							break;
						case 'A':
							caracter=fgetc(log_file);
							var_limpio++;//indica que ya avance 1 caracter.
							if (caracter='p'){
								//El mes es April (Abril)
								log_mes=4;
							}else{
								//caracter=u y el mes es August (Agosto)
								log_mes=8;
							}
							break;
						case 'S':
							//El mes es September (Septiembre)
							log_mes=9;
							break;
						case 'O':
							//El mes es October (Octubre)
							log_mes=10;
							break;
						case 'N':
							//El mes es November (Noviembre)
							log_mes=11;
							break;
						case 'D':
							//El mes es diciembre
							log_mes=12;
							break;
					}
					//Se limpian las letras faltantes, ejemplo: "Feb "
					while (var_limpio<4){ 
						caracter=fgetc(log_file);
						var_limpio++;
					}
					//Se reinicia el contador
					//printf("Mes: %i ", log_mes);
					var_limpio=0;
					//caracter=Numero
					//Como no se si el log marca el día del mes como 01 o 1, se crea lo siguiente:
					//Inicia conversión del día de mes de caracter a día.
					if (caracter=='0'){
						caracter=fgetc(log_file);
						//Convierte el caracter a entero
						log_dia=(int)(caracter-48);
					}else{
						log_dia=(int)(caracter-48);
						log_dia=log_dia*10;
						caracter=fgetc(log_file);
						if (caracter==' '){
							//Significa que sólo era un digito
							log_dia=log_dia/10;
						}else{
							temp=(int)(caracter-48);
							log_dia=log_dia+temp;
						}
					}
					//printf("Dia: %i ",log_dia);
					//Se limpia el " " restante
					while (caracter !=' '){
						caracter=fgetc(log_file);
					}
					//Termina limpieza
					//Se define la hora
					caracter=fgetc(log_file);

					if (caracter=='0'){
						caracter=fgetc(log_file);
						if (caracter=='0'){
							log_hor=0;
						}else{
							log_hor=(int)(caracter-48);
						}
					}else{
						log_hor=(int)(caracter-48);
						log_hor=log_hor*10;
						caracter=fgetc(log_file);
						if (caracter!='0'){
							temp=(int)(caracter-48);
							log_hor=log_hor+temp;
						}
					}
					//printf("Hora: %d ",log_hor);
					caracter=fgetc(log_file);

					//Se definen los minutos
                                        caracter=fgetc(log_file);
                                        if (caracter=='0'){
                                                caracter=fgetc(log_file);
                                                if (caracter=='0'){
                                                        log_min=0;
                                                }else{
                                                        log_min=(int)(caracter-48);
                                                }
                                        }else{
                                                log_min=(int)(caracter-48);
                                                log_min=log_min*10;
                                                caracter=fgetc(log_file);
                                                if (caracter!='0'){
                                                        temp=(int)(caracter-48);
                                                        log_min=log_min+temp;
                                                }
                                        }
                                        //printf("Min: %d ",log_min);
                                        caracter=fgetc(log_file);

					//Se definen los segundos
                                        caracter=fgetc(log_file);
                                        if (caracter=='0'){
                                                caracter=fgetc(log_file);
                                                if (caracter=='0'){
                                                        log_seg=0;
                                                }else{
                                                        log_seg=(int)(caracter-48);
                                                }
                                        }else{
                                                log_seg=(int)(caracter-48);
                                                log_seg=log_seg*10;
                                                caracter=fgetc(log_file);
                                                if (caracter!='0'){
                                                        temp=(int)(caracter-48);
                                                        log_seg=log_seg+temp;
                                                }
                                        }
                                        //printf("Seg: %d ",log_seg);
                                        caracter=fgetc(log_file);
					//Se limpia hasta llegar al año
					while (caracter!=' '){	caracter=fgetc(log_file); }
                                        caracter=fgetc(log_file);
					//Se define el año
					temp=(int)(caracter-48);
					log_ano=temp*1000;
					caracter=fgetc(log_file);
					temp=(int)(caracter-48);
					log_ano=log_ano+(temp*100);
					caracter=fgetc(log_file);
					temp=(int)(caracter-48);
					log_ano=log_ano+(temp*10);
					caracter=fgetc(log_file);
					temp=(int)(caracter-48);
					log_ano=log_ano+temp;
					caracter=fgetc(log_file);
					//printf("Año: %d",log_ano);
				}//Fin valida "["
				caracter=fgetc(log_file);
					if (usr_ano_men<=log_ano){
						if (usr_ano_men<log_ano){
							//Indica que el registro empieza desde un(os) añitos antes
							usr_mes_men=0; 
						}
						if (usr_mes_men<=log_mes){
							if (usr_mes_men<log_mes){
								//Indica que el registro es de mes(es) anterior(es)
								usr_dia_men=0;
							}
							if (usr_dia_men<=log_dia){
								if (usr_dia_men<log_dia){
									//Indica que el registro es de mes(es) anterior(es)
									usr_hor_men=0;
								}
								if (usr_hor_men<=log_hor ){
									if (usr_hor_men<log_hor){
										usr_min_men=0;
									}
									if (usr_min_men<=log_min){
										if (usr_min_men<log_min){
											usr_seg_men=0;
										}
										if (usr_seg_men<=log_seg){
											if (muestra_datos==0){
												printf ("[ %i/%i/%i %i:%i:%i ]:", log_dia, log_mes, log_ano, log_hor, log_min, log_seg);
												muestra_datos=1;
											}
											printf("%c",caracter);
										}
									}
								}
							}
						}
					}

				if (caracter=='\n'){
					var_control=0;
					muestra_datos=0;
				}
			}//fin de validación \n
			caracter=fgetc(log_file);

		}
	}
	//printf ("%s", texto);
	fclose ( log_file );
	return 0;
}
