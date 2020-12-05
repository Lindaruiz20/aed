/*
Módulo Recepción:
Este módulo satisface las necesidades del personal que asiste a los veterinarios en la atención al público. Desde aquí se hace ingreso de las mascotas, y la registración de los turnos.
Esta aplicación debe permitir obtener un informe de las mascotas atendidos en determinada fecha por un determinado veterinario.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>

struct veterinario
{
	char nom[60];
	int mat;
	int dni;
	char tel[25];
	
};
struct fecha
{
    int dia,mes,anio;
};
struct mascota
{
    char nom[60];
    char dom[60];
    int dni;
    char loc[60];
    fecha nac;
    float pes;
    char tel[25];
};
struct turno
{
    int mat;
    fecha fec;
    int dni;
    char det[380];
};
int buscarUsuario(char usu[10],char cla[10]);
void registrarMascotas();
void registrarTurno();
void listado();
bool buscarMatricula(int mat);
bool buscarMascota(int dni);

main()
{
	int h,res;
	char usu[10], cla[10];
	
	
	printf("MODULO RECEPCION");
	printf("\nIngrese el usario: ");
	_flushall( );
	gets(usu);
	printf("Ingrese la clave: ");
	_flushall( );
	gets(cla);
	
	h=buscarUsuario(usu,cla);

	
	if (h==0)
	{
		printf("\nUsuario no reconocido");
	}
	else
	{
		printf("Bienvenido al sistema");
		do
		{
            printf("\n1)registrar mascotas");
            printf("\n2)registrar turno");
            printf("\n3)listado de atenciones por veterinario y fecha");
            printf("\n4)cerrar la aplicación");
            printf("\nElija una opcion: ");
            scanf("%d", &res);
            switch(res)
            {
                case 1:registrarMascotas();
                break;
                case 2:registrarTurno();
                break;
                case 3:listado();
                break;
            }
        } while(res!=4);
	}
	getch();	
	
}
bool buscarMatricula(int mat)
{
    veterinario reg;
    bool hallado=false;
    FILE*arch;
    arch=fopen("veterinario.dat","rb");
    fread(&reg,sizeof(reg),1,arch);
    while(!feof(arch))
    {
        if(mat==reg.mat)
        {
            hallado=true;
        }
        fread(&reg,sizeof(reg),1,arch);
    }
    fclose(arch);
    return hallado;
}
bool buscarMascota(int dni)
{
    mascota reg;
    bool hallado=false;
    FILE*arch;
    arch=fopen("mascotas.dat","rb");
    fread(&reg,sizeof(reg),1,arch);
    while(!feof(arch))
    {
        if(dni==reg.dni)
        {
            hallado=true;
        }
        fread(&reg,sizeof(reg),1,arch);
    }
    fclose(arch);
    return hallado; 
}
void registrarMascotas()
{
    FILE*arch;
    mascota reg;
    printf("\nApellido y Nombre de la mascota: ");
    _flushall();
    gets(reg.nom);
    printf("\nIngrese el domicilio: ");
    _flushall();
    gets(reg.dom);
    printf("\nIngrese el dni: ");
    scanf("%d", &reg.dni);
    printf("\nIngrese la localidad: ");
    _flushall();
    gets(reg.loc);
    printf("\nIngrese dia de nacimiento: ");
    scanf("%d", &reg.nac.dia);
    printf("\nIngrese mes de nacimiento: ");
    scanf("%d", &reg.nac.mes);
    printf("\nIngrese anio de nacimiento: ");
    scanf("%d", &reg.nac.anio);
    printf("\nIngrese el peso: ");
    scanf("%d", &reg.pes);
    printf("\nIngrese el telefono: ");
    _flushall();
    gets(reg.tel);
    arch=fopen("mascotas.dat", "ab");
    fwrite(&reg,sizeof(reg),1,arch);
    fclose(arch);
    printf("\nLa mascota fue exitosamente registrada: ");

    
}
void registrarTurno()
{
   FILE*arch;
   turno reg;
   bool h1,h2;
   printf("\nIngrese la matricula del veterinario: "); 
   scanf("%d", &reg.mat);
   h1=buscarMatricula(reg.mat);
   if(h1==false)
   {
        printf("\nLa matricula no fue identificada: ");
   }
   else
   {
       printf("\nIngrese el dni de la mascota: "); 
       scanf("%d", &reg.dni);
       h2=buscarMascota(reg.dni);
       if(h2==false)
       {
          printf("\nEl dni no fue hallado: ");  
       } else{
                printf("\nIngrese el dia del turno: ");
                scanf("%d", &reg.fec.dia);
                printf("\nIngrese el mes del turno: ");
                scanf("%d", &reg.fec.mes);
                printf("\nIngrese el anio del turno: ");
                scanf("%d", &reg.fec.anio);
                printf("\nIngrese el detalle: ");
                _flushall();
                gets(reg.det);
                arch=fopen("turnos.dat","ab");
                fwrite(&reg,sizeof(reg),1,arch);
                fclose(arch);
                printf("\nTurno exitosamente registrado: ");
            }
   }
}
void listado()
{
    FILE*arch;
    turno reg;
    fecha fec;
    int mat;
    printf("\nIngrese el dia del turno: ");
    scanf("%d", &fec.dia);
    printf("\nIngrese el mes del turno: ");
    scanf("%d", &fec.mes);
    printf("\nIngrese el anio del turno: ");
    scanf("%d", &fec.anio);
    printf("\nIngrese la matricula del veterinario: ");
    scanf("%d", &mat);
    arch=fopen("turnos.dat","rb");
    fread(&reg, sizeof (reg),1,arch);
    while(!feof(arch))
    {
        if(fec.dia==reg.fec.dia && fec.mes==reg.fec.mes && fec.anio==reg.fec.anio && mat==reg.mat)
        {
            printf("\nDni: %d",reg.dni);
            printf("\nFecha %d/%d/%d: ",reg.fec.dia, reg.fec.mes, reg.fec.anio);
            printf("\nDetalle: %s", reg.det);
        }
        fread(&reg, sizeof (reg),1,arch);
    }
    fclose(arch);
}
int Buscar(char linea[80],char usu[10],char cla[10])
{
	if(strstr(linea,usu)!=NULL && strstr (linea,cla)!=NULL)
	return 1;
	
	return 0;
	
}
int buscarUsuario(char usu[10],char cla[10])
{
	FILE*arch;
	char linea[80];
	arch=fopen("usuario.txt","rt");
	fgets(linea,80,arch);
	while(!feof(arch))
	{
		if(Buscar(linea, usu, cla))
		{
			fclose(arch);
			return 1; //1=Hallado
		}
	fgets(linea,80,arch);	
	}
	fclose(arch);
	return 0;//0=No hallado
	
}









