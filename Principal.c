#include <stdio.h>
#include <stdlib.h>

/*Libreria gtk para la interfaz*/
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>

/*Mis librerias .h*/
#include "principal.h"

/*
  METODO MAIN: CARGA LA VENTANA PRINCIPAL Y SE 
  QUEDA  ESPERANDO A QUE EL USUARIO INTERACTUE 
  CON LA INTERFAZ.
*/
int main (int argc, char **argv)
{
    GtkWidget *table;
    GtkWidget *label;
    GtkWidget *txtvariables, *txtrestricciones;  
    GtkWidget *button_aceptar;
    GtkWidget *checkMax, *checkMin;
    
    gtk_init(&argc, &argv);

    //Crea la ventana
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    //Crea una tabla
    table = gtk_grid_new ();
    gtk_container_add (GTK_CONTAINER (window), table);

    //Crea un label que se va a colocar en una casilla de la tabla.
    //Se utilizara solo una variable label para todos los que existan
    label = gtk_label_new ("Número variables: ");
    gtk_grid_attach (GTK_GRID (table),label, 0, 0, 1, 1);

    //Crea el textbox que va a contener el numero de llaves
    txtvariables = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (txtvariables),50);
    gtk_grid_attach (GTK_GRID (table),txtvariables, 1, 0, 1, 1);

    //Crea un label que se va a colocar en una casilla de la tabla.
    //Se utilizara solo una variable label para todos los que existan
    label = gtk_label_new ("Número restricciones: ");
    gtk_grid_attach (GTK_GRID (table),label, 0, 1, 1, 1);

    //Crea el textbox que va a contener el numero de llaves
    txtrestricciones = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (txtrestricciones),50);
    gtk_grid_attach (GTK_GRID (table),txtrestricciones, 1, 1, 1, 1);

    //Crea un label
    label = gtk_label_new ("Funcion objetivo: ");
    gtk_grid_attach (GTK_GRID (table),label, 0, 2, 1, 1);

    //Crea el checkbox que indica que se va a correr 1 ejemplo
    checkMax = gtk_check_button_new_with_label("Maximizar");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkMax), TRUE);
    gtk_grid_attach (GTK_GRID (table),checkMax, 1, 2, 1, 1);

    //Crea el checkbox que indica que se van a correr 1000 ejemplos
    checkMin = gtk_check_button_new_with_label("Minimizar");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkMin), FALSE);
    gtk_grid_attach (GTK_GRID (table),checkMin, 1, 3, 1, 1);

    //Cuando el checkUno es seleccionado
    g_signal_connect(checkMax, "clicked", 
            G_CALLBACK(checkMax_selected), checkMin);        
    //Cuando el checkMil es seleccionado
    g_signal_connect(checkMin, "clicked", 
            G_CALLBACK(checkMin_selected), checkMax);

    //Boton aceptar que llama a ejecutar TODO dependiendo de los parametros obtenidos
    button_aceptar = gtk_button_new_with_label ("Aceptar");
    gtk_grid_attach (GTK_GRID (table),button_aceptar,1, 4, 1, 1);
    //Cuando el boton_aceptar es precionado
    g_signal_connect(button_aceptar, "clicked", 
        G_CALLBACK(pasar_variables), txtvariables);
    g_signal_connect(button_aceptar, "clicked", 
        G_CALLBACK(pasar_restricciones), txtrestricciones);

    initialize_window(window, 2, 1);
    //Abre la interfaz y se queda esperado que el usuario interactue con ella
    gtk_main ();

    //Termmina sin errores y retorna
    return 0;
}