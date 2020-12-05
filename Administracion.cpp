/*Módulo Administración:
La gerencia del centro veterinario es la encargada de realizar el alta de los veterinarios que trabajan
en la institución, así como también de los empleados que realizan la registración de los turnos y mascotas.
Es el área encargada desea visualizar las atenciones realizadas por los profesionales según las en el
mes.
Para incentivar a los veterinarios, la gerencia otorga un bono mensual al profesional que haya
registrado la mayor cantidad de turnos en ese periodo*/

/*Nombre y Apellido

-Ruiz Linda Selena 

Comision ; 1k1

Correo Electronico

Linda.Ruiz@alu.frt.utn.edu.ar
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
void registrarVeterinario();
void registrarAsistente();
void cantidadDeAtenciones();
void ranking();

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
            printf("\n1)registrar veterinario");
            printf("\n2)registrar usuario asistente");
            printf("\n3)atenciones por veterinarios");
            printf("\n4)ranking de veterinarios por atenciones");
            printf("\n5)cerrar la aplicación");
            printf("\nElija una opcion: ");
            scanf("%d", &res);
            switch(res)
            {
                case 1:registrarVeterinario();
                break;
                case 2:registrarAsistente();
                break;
                case 3:cantidadDeAtenciones();
                break;
                case 4:ranking();
                break;
            }
        } while(res!=5);
	}
	getch();	
	
}
void registrarVeterinario()
{
    veterinario reg;
    FILE*arch,*arch1;
    arch=fopen("veterinario.dat","ab");
    printf("\nIngrese Apellido y Nombre: ");
    _flushall();
    gets(reg.nom);
    printf("\nIngrese la matricula: ");
    scanf("%d",&reg.mat);
    printf("\nIngrese el dni: ");
    scanf("%d", &reg.dni);
    printf("\nIngrese telefono: ");
    _flushall();
    gets(reg.tel);
    fwrite(&reg, sizeof(reg),1,arch);
    fclose(arch);
    char usu[10],cla[10],linea[80];
    printf("\nIngrese el usuario: ");
    _flushall();
    gets(usu);
    printf("\nIngrese la clave: ");
    _flushall();
    gets(cla);
    strcpy(linea,usu);
    strcat(linea,";");
    strcat(linea,cla);
    strcat(linea,";");
    strcat(linea, reg.nom);
    arch1=fopen("usuario.txt","at");
    fputs(linea,arch1);
    fclose(arch1);
}

void registrarAsistente() 
{
veterinario reg;
    FILE*arch,*arch1;
    arch=fopen("veterinario.dat","ab");
    printf("\nIngrese Apellido y Nombre asistente: ");
    _flushall();
    gets(reg.nom);
    printf("\nIngrese la matricula de asistente: ");
    scanf("%d",&reg.mat);
    printf("\nIngrese el dni de asistente: ");
    scanf("%d", &reg.dni);
    printf("\nIngrese telefono de asistente: ");
    _flushall();
    gets(reg.tel);
    fwrite(&reg, sizeof(reg),1,arch);
    fclose(arch);
    char usu[10],cla[10],linea[80];
    printf("\nIngrese el usuario: ");
    _flushall();
    gets(usu);
    printf("\nIngrese la clave: ");
    _flushall();
    gets(cla);
    strcpy(linea,usu);
    strcat(linea,";");
    strcat(linea,cla);
    strcat(linea,";");
    strcat(linea, reg.nom);
    arch1=fopen("usuario.txt","at");
    fputs(linea,arch1);
	fclose(arch1);
	printf("\n Asistente registrado correctamente \n");

}

void cantidadDeAtenciones()
{

 FILE*arch1,*arch2;
 veterinario rv;
 turno rt;
 int c,mat;
	
 printf("Ingrese la matricula del veterinario");
 scanf("%d" , &mat);
 arch2=fopen("turnos.dat","rb");
  c=0
 fread(&rt, sizeof(rt),1,arch2);
 	while(!feof (arch2))
 	{
 		if(mat==rt.mat)
 		{
 			c++;
 		}
 		
 	fread(&rt, sizeof(rt),1,arch2);
 	}
 printf("\n Matricula del veterinario: %d atendio a : %d mascotas",mat,c);
 fclose(arch2);
}
void ranking()
{
 FILE*arch1,*arch2;
 veterinario rv;
 turno rt;
 int c;
 
 struct registro
 {
 	char nom[60];
	int   cant;
	
 };

registro a[100],aux;
int n  =0, i=0,j=0; 
 arch1=fopen("veterinario.dat","rb");
 arch2=fopen("turnos.dat","rb");
 
 fread(&rv,sizeof(rv),1,arch1);
 while (!feof (arch1))
 {
  c=0
 	fseek(arch2,0,SEEK_SET);
 	fread(&rt, sizeof(rt),1,arch2);
 	while(!feof (arch2))
 	{
 		if(rv.mat==rt.mat)
 		{
 			c++;
 		}
 		
 	fread(&rt, sizeof(rt),1,arch2);
 	}
 strcpy(a[n].nom,rv.nom); //copia el nombre del vet cad
 a[ n].cant=c;    // cantidad q atendio
 n++;
 fread(&rv,sizeof(rv),1,arch1);
 }
 fclose(arch1);
 fclose(arch2);
 
 for(j=0 ; j<n ; j++)
 {
 	for(i=0 ; i<n-1 ; i++)
 	{
 		if(a[i].cant<a[i+1].cant )
 		{
 			aux=a[i];
 			a[i]=a[i+1];
 			a[i+1]=aux;
 		}
 		
 	}
 	
 } // fin del ordenamiento por burbuja
 printf("\n Ranking de atencion");
 for(i=0 ; i<n ; i++)
 {
 	printf("\n Veterinario %s atendio %d mascotas" , a[i].nom,a[i].cant ); //Mostrar  la cantidad de ranking 
 }
 
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

/*
echo "# aed" >> README.md
git init
git add README.md
git commit -m "first commit"		
git branch -M main
git remote add origin https://github.com/Lindaruiz20/aed.git
git push -u origin main
*/ 








